#pragma once
#include "Controller.h"

Controller::Controller(map<int, int> r, map<int, int> u, int p, int T) {
	tableInterResultValues[0] = nullVectorOfInt;
	tableInterStrategy[0] = nullVectorOfBool;

	this->r = r;
	this->u = u;
	this->p = p;
	this->T = T;
	this->stableT = this->T;
	this->showingT = this->T;
	this->t = 0;

	ofstream fout;
	fout.open("result.txt");
	cout << "hi" << endl;
	fout.close();


}



int Controller::resultTable(vector<int> final) { // записывает вектор булей из fullCycle в файл, формируя последнюю табличку (t=0 зб, t=1 замена)

									  //ВЕКТОР ИНТ ЗНАЧЕНИЙ НУЖНО ПРЕОБРАЗОВАТЬ В КОНТЕЙНЕР БУЛЕВЫХ
	
	std::ofstream fout("result.txt", std::ios::app);

	fout << "maxZ = " << maxZ << endl;
	fout << "Age:\t\t| ";
	cout << "resulttable start" << endl;
	for (int i = 0; i < stableT; i++) {
		if (final[i] == 0) {
			fout << i+1 << " | ";
			
		}
		else {
			fout << i+1 << " | ";
		}
	}

	fout << endl << "Strategy:\t| ";

	for (int i = 0; i < stableT; i++) {
		if (final[i] == 0) {
			fout << "change" << " | ";
			
		}
		else {
			fout << "save" << " | ";
		}
	}
	cout << "resulttable end" << endl;
	fout.close();
	return 0;
}

vector<int> Controller::fullCycle() { //проходит по всему T как итератор, вызывая каждый раз функцию-итератор fk(t) 
	std::ofstream fout("result.txt", std::ios::app);
	cout << "fullcycle1" << endl;
	for (k; k <= stableT; k++) {
		cout << "fullcycle2" << endl;
		auto result = fkt();
		
		auto values = get<vector<int>>(result);
		tableInterResultValues[k] = values; //сохранение промежуточной таблички fk - значения
		auto strategies = get<vector<double>>(result);
		tableInterStrategy[k] = strategies; //сохранение промежуточной таблички fk - стратегии
		cout << "fullcycle3" << endl;
		fout << "Age\t\t" << "f" << k << "(t)\t\t" << "Strategy" << endl;
		
		if (k != stableT) {
			for (int i = 0; i < showingT - 1; i++) {

				auto strat = strategies[i+1];
				fout << i + 1 << "\t\t" << values[i+1] << "\t\t" << (bool)strat << endl;

				/*auto strat = strategies[i];
				fout << i << "\t\t" << values[i] << "\t\t" << (bool)strat << endl;*/

			} showingT -= 1;
		}
		else { fout << stableT << "\t\t" << values.back() << "\t\t" << true << endl; }
		
		cout << "fullcycle4" << endl;
	}
	fout.close();

	cout << "fullcycle5" << endl;
	vector<int> resultStrategyTable{ 1 };
	
	auto counterOft = 0;
	for (auto i = stableT; i > 0; i--) {
		cout << "fullcycle6" << endl;
		auto result = tableInterStrategy[i];

		if (i == stableT) { // t = 0
			resultStrategyTable.push_back(1);
		}
		else { //норм
			resultStrategyTable.push_back(result[counterOft]);
		}
		counterOft++;
	}
	cout << "fullcycle7" << endl;

	return resultStrategyTable;
}

tuple<vector<int>, vector<double> > Controller::fkt() { //проход по всем t для k-того года
	cout << "fkt2" << endl;
	vector<int> valueOfF;
	vector<double> strategy;
	cout << "fkt2" << endl;
	while (t < T) {
		if (k == 1) { // first
			tuple<int, bool> result = functionFrom1(t);
			valueOfF.push_back(get<int>(result));
			strategy.push_back(double(get<bool>(result)));
		}
		else { // first < k < last
			tuple<int, bool> result = functionFromK(t);
			valueOfF.push_back(get<int>(result));
			strategy.push_back(double(get<bool>(result)));
		}


		
		t++;
	}

	if (k == stableT) { // last
		int result = functionFromLast(t);
		valueOfF.push_back(result);
		strategy.push_back(1);
		cout << "ftk last" << endl;
		return make_tuple(valueOfF, strategy);
	}

	cout << "fkt3" << endl;
	t = 0;
	T -= 1;
	return make_tuple(valueOfF, strategy);
}

tuple<int, bool> Controller::functionFrom1(int t) {
	cout << "funcFrom1 1" << endl;
	int save = r[t] - u[t];
	int change = r[0] - u[0] - p;

	if (save > change) return make_tuple(save, true);
	else return make_tuple(change, false);
}

tuple<int, bool> Controller::functionFromK(int t) {
	cout << "funcFromK 1" << endl;
	auto resultOfPreStep = tableInterResultValues[k - 1];

	int save = r[t] - u[t] + resultOfPreStep[t + 1]; // + f k-1 (t)
	int change = r[0] - u[0] - p + resultOfPreStep[1]; // + f k-1 (1)

	if (save > change) return make_tuple(save, true);
	else return make_tuple(change, false);
}

int Controller::functionFromLast(int t) {
	cout << "funcFromLast 1" << endl;
	auto resultOfPreStep = tableInterResultValues[k - 1];
	auto result = r[0] - u[0] + resultOfPreStep[t];
	maxZ = result;
	return result;
}

void Controller::startProcess() {
	resultTable(fullCycle());
}