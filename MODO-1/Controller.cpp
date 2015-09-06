#include "Controller.h"
#include "View.h"



Controller::Controller()
{
	this->p = 40000; // p
	this->T = 5; //max t

	r[0] = 80; //r(t)
	r[1] = 75;
	r[2] = 65;
	r[3] = 60;
	r[4] = 60;
	r[5] = 55;

	u[0] = 20; // u(t)
	u[1] = 25;
	u[2] = 30;
	u[3] = 35;
	u[4] = 45;
	u[5] = 55;

}

Controller::Controller(int T, std::map<int, int> r, std::map<int, int> u, int p)
{
	this->r = r;
	this->u = u;
	this->p = p;
	this->T = T;
}

Controller::~Controller()
{
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

	return storage;
}

int Controller::fullCycle() //ТИП - ПЛЕЙСХОЛДЕР
{
	std::vector<std::vector<Controller::returnElementsFromOneOfSteps>> storageOfAllData; 
	

	for (auto counter = 0; counter < this->T; counter++)
	{
		storageOfAllData.push_back(Controller::oneOfSteps(counter));
	}

	//СФОРМИРОВАТЬ ПОСЛЕДНЮЮ ТАБЛИЧКУ

	//ВЫКИНУТЬ ДАННЫЕ В ФАЙЛ через функции view (которые есть, которых нет - не забыть сделать их вывод отдельно)


	return 0;
}




// короткая справка для ленивых: std::get - метод кортежа, чтобы получить необходимый элемент
std::tuple<int, bool> Controller::calculationFunction(int k, int t)
{
	auto first = [this, t, k]() {
		auto result = r[t] - u[t]
			+ std::get<int>(calculationFunction(k, t + 1));
		return result;
	};

	auto second = [this, k]() {
		auto result = r[0] - u[0] - p
			+ std::get<int>(calculationFunction(k - 1, 1));
		return result;
	};

	auto temp1 = first();
	auto temp2 = second();

	if (temp1 > temp2) {
		return std::make_tuple(temp1, true);
	}
	else return std::make_tuple(temp2, false);
}

std::tuple<int, bool> Controller::lastStep(int k, int t)
{
	auto lambda = [this, t, k]() {
		auto result = r[0] - u[0]
			+ std::get<int>(calculationFunction(k - 1, 1));
		return result;
	};

	auto temp = lambda();

	return std::make_tuple(temp, true);
}



