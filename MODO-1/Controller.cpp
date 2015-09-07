#include "Controller.h"
using namespace std;



Controller::Controller(int T, std::map<int, int> r, std::map<int, int> u, int p)
{


	

	this->r = r;
	this->u = u;
	this->p = p;
	this->T = T;

	saveConditions();
}

Controller::~Controller()
{
	

}

tuple<int, int, bool> Controller::SupportFunction1(int t, int k) {

	if (k == T) {
		auto result = r[0] - u[0] + get<int>(SupportFunction1(1, T - 1));
		return std::make_tuple(result, 0, true);
	}
	else if (k == 1) {
		auto result = f1FromT(t);
		return result;
	}
	else if (k == 2) {
		auto result = f1fromTplus1(t);
		return result;
	}
	else {
		auto result1 = r[t] - u[t] + get<int>(f1FromT(t + 1)); //fk(t)
		auto result2 = r[0] - u[0] - p + get<int>(f1FromT(1)); //куда тут пихать k?

		if (result1 > result2) return make_tuple(result1, result2, true);
		else return make_tuple(result2, result1, false);
	}
}

tuple<int, int, bool> Controller::f1FromT(int t) {
	auto result1 = r[t] - u[t];
	auto result2 = r[0] - u[0] - p;

	if (result1 > result2) return make_tuple(result1, result2, true);
	else return make_tuple(result2, result1, false);
}

tuple<int, int, bool> Controller::f1fromTplus1(int t) {
	auto result1 = r[t] - u[t] + get<int>(f1FromT(t+1));
	auto result2 = r[0] - u[0] - p + get<int>(f1FromT(1));

	if (result1 > result2) return make_tuple(result1, result2, true);
	else return make_tuple(result2, result1, false);


}



// короткая справка для ленивых: std::get - метод кортежа, чтобы получить необходимый элемент
std::tuple<int, bool> Controller::calculationFunction(int k, int t)
{
	auto temp1 = SupportFunction1(t,k);
	

	
	saveCalculationFunction(k, t, get<1>(temp1), get<2>(temp1)); //!

	return std::make_tuple(get<1>(temp1), false);
}

std::tuple<int, bool> Controller::lastStep(int k, int t)
{
	auto lambda = [this, t, k]() {
		auto result = r[0] - u[0]
			+ std::get<int>(calculationFunction(k - 1, 1));
		return result;
	};

	auto temp = lambda();

	saveCalculationFunction(k, t, temp, 0); //!

	return std::make_tuple(temp, true);
}

std::vector<Controller::returnElementsFromOneOfSteps> Controller::oneOfSteps(int tipaK)
{
	std::vector<Controller::returnElementsFromOneOfSteps> storage;
	

	for (int k = 1; k <= this->T - tipaK; k++)
	{
		if (k == Controller::T) {
			auto temp = this->lastStep(k, tipaK);
			Controller::returnElementsFromOneOfSteps tempStruct = { tipaK, std::get<int>(temp), std::get<bool>(temp) };
			storage.push_back(tempStruct);
			break;
		}
		else {
			auto temp = this->calculationFunction(k, tipaK);
			Controller::returnElementsFromOneOfSteps tempStruct = { tipaK, std::get<int>(temp), std::get<bool>(temp) };
			storage.push_back(tempStruct);
		}
	}

	saveOneOfSteps(storage, tipaK); //!

	return storage;
}

vector<bool> Controller::unwrapperFromVectorToBool (int counter) {
	vector <bool> one;
	auto temp = Controller::oneOfSteps(counter);
	for (auto it = 0; it < temp.size(); it++)
	{
		one.push_back (temp[it].trueForSaveFalseForChange);
	}
	return one;
}

std::tuple<int, bool> Controller::unwrapperFromVectorForLast(int counter)
{
	
	auto temp = Controller::oneOfSteps(counter);
	
	return make_tuple(temp[0].functionValue, temp[0].trueForSaveFalseForChange);
}


int Controller::fullCycle()
{
	cout << "Task is in the process of solving. Your results will be in file \"results\"" << endl;
	vector<bool> giveMeResults;
	int maxZ = 0;

	for (int i = 0; i < T; i++) {

		if (i == T) {
			auto temp = unwrapperFromVectorForLast(i);
			giveMeResults.push_back(get<bool>(temp)); ////f5(0)
			maxZ = get<int>(temp); 
		}
		else {
			auto temp = unwrapperFromVectorToBool(i);
			for (int j = 0; j < T; j++) {
				if (j == T - i) {
					giveMeResults.push_back(temp[j]); //f4(1),...
				}
			}


		}
	}

	saveFullCycle(giveMeResults, maxZ);
	cout << "Task completed." << endl;
	return 0;
}


int Controller::saveConditions()
{
	std::ofstream fout("results");
	if (!fout.is_open()) {
		std::cerr << "Can't open first file!" << std::endl;
		return 1;
	}

	fout << "\t\t\tCONDITIONS START" << endl;

	fout << "P = " << p << endl;
	fout << "T = " << T << endl;

	fout << "\t\tr[t]: ";
	for (int i = 0; i < this->T; i++) {
		fout << endl;
		fout << "r[" << i << "] = " << r[i];
	} fout << endl;

	fout << "\t\tu[t]: ";
	for (int i = 0; i < this->T; i++) {
		fout << endl;
		fout << "u[" << i << "] = " << u[i];
	} fout << endl;

	fout << "\t\t\tCONDITIONS END" << endl;

	fout.close();
	return 0;
}

int Controller::saveCalculationFunction(int k, int t, int temp1, int temp2)
{
	std::ofstream fout("results");
	if (!fout.is_open()) {
		std::cerr << "Can't open first file!" << std::endl;
		return 1;
	}

	fout << "\t\t\tf" << k << "(" << t << ") START" << endl << endl;

	fout << temp1 << " for SAVE" << endl;
	fout << temp2 << " for CHANGE" << endl;

	fout << "\t\t\tf" << k << "(" << t << ") END" << endl;

	return 0;
}

int Controller::saveOneOfSteps(std::vector<Controller::returnElementsFromOneOfSteps> storage, int tipaK)
{
	std::ofstream fout("results");
	if (!fout.is_open()) {
		std::cerr << "Can't open first file!" << std::endl;
		return 1;
	}

	fout << "\t\t\tSTART" << endl << endl;

	fout << "Age\t|\tf" << tipaK << "(t)\t|\tStrategy" << endl;
	for (int i = 0; i < Controller::T - tipaK; i++)
	{
		fout << i + 1 << "\t|\t" << storage[i].functionValue << "\t|\t" << storage[i].trueForSaveFalseForChange
			<< endl;
	}

	fout << "\t\t\tEND" << endl;

	return 0;
}

int Controller::saveFullCycle(vector<bool> finalStrategy, int maxZ)
{
	std::ofstream fout("results");
	if (!fout.is_open()) {
		std::cerr << "Can't open first file!" << std::endl;
		return 1;
	}

	fout << "\t\t\tfinal START" << endl << endl;

	fout << "Age:\t";
	for (auto i = 0; i < finalStrategy.size(); i++)
	{
		fout << "| t = " << i;
	} fout << endl;

	fout << "Strategy:\t";
	for (auto i = 0; i < finalStrategy.size(); i++)
	{
		if (finalStrategy[i] == true) {
			fout << "| Save ";
		}
		else
		{
			fout << "| Change ";
			break;
		}
	}

	fout << endl << "maxZ = " << maxZ << endl;
	fout << "\t\t\tfinal END" << endl;

	return 0;
}




