#pragma once
#include "Controller.h"
class View : public Controller
{
public:

	

	View();
	~View();

	int saveConditions();
	int saveCalculationFK();
	int saveFinalResults();
};

