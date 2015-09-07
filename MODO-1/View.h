#pragma once
#include "Controller.h"
class View : Controller
{
public:
	View();
	~View();

	int saveConditions();
	int saveCalculationFunction(int k, int t, int temp1, int temp2);
	int saveOneOfSteps(std::vector<Controller::returnElementsFromOneOfSteps> storage, int tipaK);
	int saveFullCycle();
};

