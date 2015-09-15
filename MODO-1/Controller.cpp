#pragma once
#include "Controller.h"

Controller::Controller(map<int, int> r, map<int, int> u, int p, int T) {
	setlocale(LC_ALL, "Russian");
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
	fout.open("temp.txt");
	fout << endl;
	fout.close();

	saveConditions();
	
}


//формирование последней таблицы в файле вывода
int Controller::resultTable(vector<int> final) { // записывает вектор булей из fullCycle в файл, формируя последнюю табличку (t=0 зб, t=1 замена)
	setlocale(LC_ALL, "Russian");
									  
	
	std::ofstream fout("temp.txt", std::ios::app);

	fout << endl << "maxZ = " << maxZ << endl << endl;
	fout << setw(10) << "Вiк:\t\t";
	
	for (int i = 0; i < stableT; i++) {
		fout << "| ";
		if (final[i] == 0) {
			fout << i << "\t";
			break;
		}
		else fout << i << "\t";
	} fout << "|";

	fout << endl << setw(10) << "Стратегiя:\t";

	for (int i = 0; i < stableT; i++) {
		fout << "| ";
		if (final[i] == 0) {
			fout << "зам\t";
			break;
			
		}
		else {
			fout << "зб.\t";
		}
		
	} fout << "|";

	fout << endl << endl << "u ( t ) - затрати, r ( t ) - прибуток, t - рiк, T - перiод" << endl <<
		"Стретегiя: 1 - зберегти, 0 - замiнити; maxZ - макс. прибуток" << endl << "p - цiна замiни обладнання" << endl;
	
	fout.close();
	return 0;
}


//главный метод алгоритма, вызывает остальные методы, формирует вывод
vector<int> Controller::fullCycle() { //проходит по всему T как итератор, вызывая каждый раз функцию-итератор fk(t) 
	setlocale(LC_ALL, "Russian");
	std::ofstream fout("temp.txt", std::ios::app);

	//проход по всем шагам k - рассчеты в fkt()
	for (k; k <= stableT; k++) {
		
		auto result = fkt();
		
		auto values = get<vector<int>>(result);
		tableInterResultValues[k] = values; //сохранение промежуточной таблички fk - значения
		auto strategies = get<vector<double>>(result);
		tableInterStrategy[k] = strategies; //сохранение промежуточной таблички fk - стратегии
		
		fout << "Вiк\t\t" << "f" << k << " ( t )\t\t" << "Стратегiя" << endl;
		
		if (k != stableT) {
			for (int i = 0; i < showingT - 1; i++) {

				auto strat = strategies[i+1];
				fout << i + 1 << "\t\t" << values[i+1] << "   \t\t" << (bool)strat << endl;

				/*auto strat = strategies[i];
				fout << i << "\t\t" << values[i] << "\t\t" << (bool)strat << endl;*/

			} showingT -= 1;
		}
		else { fout << stableT << "\t\t" << values.back() << "   \t\t" << true << endl; }
		fout << endl;
		
		
	}
	fout.close();

	//заранее созданный вектор, чтобы начинать счет с 1, а не 0.
	vector<int> resultStrategyTable{ 1 };
	
	//запись значений в специальный вектор, который передается в resultTable() для формирования
	//последней таблицы
	auto counterOft = 0;
	for (auto i = stableT; i > 0; i--) {
		
		auto result = tableInterStrategy[i];

		if (i == stableT) { // t = 0
			resultStrategyTable.push_back(1);
		}
		else { //норм
			resultStrategyTable.push_back(result[counterOft]);
		}
		counterOft++;
	}
	

	return resultStrategyTable;
}

//проход по всем доступным t в конкретном k (вызывается в fullcycle() )
tuple<vector<int>, vector<double> > Controller::fkt() { //проход по всем t для k-того года
	
	vector<int> valueOfF;
	vector<double> strategy;
	
	//проход по всем T (итерацией), запись результатов - значения + були
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

	//вызов функции для последнего k, так как по-человечески всунуть в while выше я его не смог
	if (k == stableT) { // last
		int result = functionFromLast(t);
		valueOfF.push_back(result);
		strategy.push_back(1);
		
		return make_tuple(valueOfF, strategy);
	}

	//обнуление и декремент для дальнейших итераций
	t = 0;
	T -= 1;
	return make_tuple(valueOfF, strategy);
}

//вычисление результатов для первого шага
tuple<int, bool> Controller::functionFrom1(int t) {
	
	int save = r[t] - u[t];
	int change = r[0] - u[0] - p;

	if (save > change) return make_tuple(save, true);
	else return make_tuple(change, false);
}

//вычисление результатов для k-атых шагов
tuple<int, bool> Controller::functionFromK(int t) {
	
	auto resultOfPreStep = tableInterResultValues[k - 1];

	int save = r[t] - u[t] + resultOfPreStep[t + 1]; // + f k-1 (t)
	int change = r[0] - u[0] - p + resultOfPreStep[1]; // + f k-1 (1)

	if (save > change) return make_tuple(save, true);
	else return make_tuple(change, false);
}

//вычисление результатов для последнего шага
int Controller::functionFromLast(int t) {
	
	auto resultOfPreStep = tableInterResultValues[k - 1];
	int result = 0;
/*	if (T != 1) {
		result = r[0] - u[0] + resultOfPreStep[t];
	} else result = r[0] - u[0] + resultOfPreStep[t-1];*/


		result = r[0] - u[0] + resultOfPreStep[t];
	
	maxZ = result;
	return result;
}

//сохранение переданных пользователем условий в файле вывода
void Controller::saveConditions()
{
	setlocale(LC_ALL, "Russian");
	std::ofstream fout("temp.txt", std::ios::app);

	fout << "p = " << p << "\t\tT = " << T << endl << endl;
	fout << setw(20) << "Характеристики / T\t";
	for (int i = 0; i <= T; i++) {
		fout << setw(5) << i;
	}
	fout << endl;
	fout << endl << setw(20) << "r ( t )\t\t";
	for (int i = 0; i <= T; i++) {
		fout << setw(5) << r[i];
	}

	fout << endl << setw(20) << "u ( t )\t\t";
	for (int i = 0; i <= T; i++) {
		fout << setw(5) << u[i];
	}
	fout << endl << endl;;
}

//public метод для начала рассчетов
void Controller::startProcess() {
	cout << endl << "Працюю..." << endl;
	resultTable(fullCycle());
	cout << endl << "Робота завершена. Результати можна побачити у файлi, або у формi." << endl;
}