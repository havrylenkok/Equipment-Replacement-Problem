#pragma once
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <functional>
#include <fstream>


class Controller
{

public:

	//����������
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
	void setr(int t, int newValue) {
		r[t] = newValue;
	}

	std::map<int, int> u; // u(t)
	void setu(int t, int newValue) {
		u[t] = newValue;
	}


	//������
	Controller();
	Controller::Controller(int T, std::map<int, int> r, std::map<int, int> u, int p);
	~Controller();

	std::tuple<int, bool> calculationFunction(int k, int t); // func k (t) TRUE - SAVE, FALSE - CHANGE
	std::tuple<int, bool> lastStep(int k, int t);
	std::vector<returnElementsFromOneOfSteps> oneOfSteps(int t);
	int Controller::fullCycle();
	
	//������
	friend int saveCalculationFunction(int k, int t, int temp1, int temp2);
	friend int saveOneOfSteps(std::vector<Controller::returnElementsFromOneOfSteps> storage, int tipaK);
};

