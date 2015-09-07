#pragma once
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <functional>
#include <fstream>
using namespace std;

class Controller 
{

public:

	//œ≈–≈Ã≈ÕÕ€≈
	int t = 0; // t
	int p; // p
	int T; // T
	int k = 1; // k

	struct returnElementsFromOneOfSteps {
		int year;
		int functionValue;
		bool trueForSaveFalseForChange;
	};

	std::map<int, int> r; // r(t)
	std::map<int, int> u; // u(t)


	//Ã≈“Œƒ€
	Controller();
	Controller::Controller(int T, std::map<int, int> r, std::map<int, int> u, int p);
	~Controller();

	std::tuple<int, bool> calculationFunction(int k, int t); // func k (t) TRUE - SAVE, FALSE - CHANGE
	std::tuple<int, bool> lastStep(int k, int t);
	std::vector<returnElementsFromOneOfSteps> oneOfSteps(int t); //Ó‰ËÌ ¯‡„ k
	virtual std::vector<bool> unwrapperFromVectorToBool(int counter);
	std::tuple<int, bool> unwrapperFromVectorForLast(int counter);
	
	int Controller::fullCycle();

	int saveConditions();
	int saveCalculationFunction(int k, int t, int temp1, int temp2);
	int saveOneOfSteps(std::vector<Controller::returnElementsFromOneOfSteps> storage, int tipaK);
	int saveFullCycle(vector<bool> finalStrategy, int maxZ);
};

