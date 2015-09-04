#pragma once
#include "Controller.h"
class Model : public Controller
{
public:
	Model(); //constructor by default
	~Model(); //destructor

	int currentAge = 0; // t
	int costOfBuyOfNewEquipment; // p
	int lengthOfPlannedPeriod; // T
	int processOfExpluatation = 1; // k

	std::tuple<int, bool> functionOfOptimalValues(int k, int currentYearOfExpluatation); // func k (t) TRUE - SAVE, FALSE - CHANGE
	std::tuple<int, bool> lastStep(int k, int currentYearOfExpluatation);
	
	

	std::map<int, int> productionCostAfterExpluatation; // r(t)
	void setProductionCostAfterExpluatation(int currentAge, int newValue) {
		productionCostAfterExpluatation[currentAge] = newValue;
	}
	std::map<int, int> costOfServiceInExpluatation; // u(t)
	void setCostOfServiceInExpluatation(int currentAge, int newValue) {
		costOfServiceInExpluatation[currentAge] = newValue;
	}

	


	
};

