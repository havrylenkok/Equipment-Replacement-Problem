#pragma once
#include "Controller.h"
class Model : public Controller
{
public:
	Model(); //constructor by default
	~Model(); //destructor

	int timeInExpluatation = 0; // t
	
	int costOfBuyOfNewEquipment; // p
	int lengthOfPlannedPeriod; // T
	int processOfExpluatation = lengthOfPlannedPeriod; // k = T

	bool functionOfOptimalValues(int k, int currentYearOfExpluatation); // func k (t) TRUE - SAVE, FALSE - CHANGE
	//void lastStep () { r(0) - u(0) + f T-1 (1) -> save }
	

	std::map<int, int> productionCostAfterExpluatation; // r(t)
	void setProductionCostAfterExpluatation(int timeInExpluatation, int newValue) {
		productionCostAfterExpluatation[timeInExpluatation] = newValue;
	}
	std::map<int, int> costOfServiceInExpluatation; // u(t)
	void setCostOfServiceInExpluatation(int timeInExpluatation, int newValue) {
		costOfServiceInExpluatation[timeInExpluatation] = newValue;
	}

	


	
};

