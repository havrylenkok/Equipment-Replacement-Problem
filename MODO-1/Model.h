#pragma once
#include "Controller.h"
class Model : public Controller
{
public:
	Model(); //constructor by default
	~Model(); //destructor

	int t = 0; // t
	int p; // p
	int T; // T
	int k = 1; // k

	std::tuple<int, bool> calculationFunction(int k, int currentYearOfExpluatation); // func k (t) TRUE - SAVE, FALSE - CHANGE
	std::tuple<int, bool> lastStep(int k, int currentYearOfExpluatation);
	
	

	std::map<int, int> r; // r(t)
	void setr(int t, int newValue) {
		r[t] = newValue;
	}
	std::map<int, int> u; // u(t)
	void setu(int t, int newValue) {
		u[t] = newValue;
	}

	


	
};

