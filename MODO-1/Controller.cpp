#include "Controller.h"
#include "Model.h"
#include "View.h"



Controller::Controller()
{
}


Controller::~Controller()
{
}

std::vector<Controller::returnElementsFromOneOfSteps> Controller::oneOfSteps(int t, std::function<std::tuple<int, bool>>)
{
	std::vector<Controller::returnElementsFromOneOfSteps> storage;
	auto it = storage.begin();

	for (int i = 1; i <= Controller::T; i++)
	{
		if (i == Controller::T) {
			auto temp = Controller::lastStep(i, t);
			Controller::returnElementsFromOneOfSteps tempStruct = { t, std::get<int>(temp), std::get<bool>(temp) };
			storage.insert(it+1, tempStruct);
			break;
		}
		else {
			auto temp = Controller::calculationFunction(i, t);
			Controller::returnElementsFromOneOfSteps tempStruct = { t, std::get<int>(temp), std::get<bool>(temp) };
			storage.insert(it + 1, tempStruct);
		}
	}

	return storage;
}




