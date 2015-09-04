#include "Controller.h"
#include "Model.h"
#include "View.h"



Controller::Controller()
{
}


Controller::~Controller()
{
}

std::vector<Controller::returnElementsFromOneOfSteps> Controller::oneOfSteps(int currentAge, std::function<std::tuple<int, bool>>)
{
	std::vector<Controller::returnElementsFromOneOfSteps> storage;
	auto it = storage.begin();

	for (int i = 1; i <= Controller::lengthOfPlannedPeriod; i++)
	{
		if (i == Controller::lengthOfPlannedPeriod) {
			auto temp = Controller::lastStep(i, currentAge);
			Controller::returnElementsFromOneOfSteps tempStruct = { currentAge, std::get<int>(temp), std::get<bool>(temp) };
			storage.insert(it+1, tempStruct);
			break;
		}
		else {
			auto temp = Controller::functionOfOptimalValues(i, currentAge);
			Controller::returnElementsFromOneOfSteps tempStruct = { currentAge, std::get<int>(temp), std::get<bool>(temp) };
			storage.insert(it + 1, tempStruct);
		}
	}

	return std::vector<returnElementsFromOneOfSteps>();
}




