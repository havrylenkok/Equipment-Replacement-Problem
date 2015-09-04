#pragma once
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <functional>


class Controller : public Model
{
public:
	Controller();
	~Controller();

	struct returnElementsFromOneOfSteps {
		int year;
		int functionValue;
		bool trueForSaveFalseForChange;
	};

	std::vector<returnElementsFromOneOfSteps> oneOfSteps(int currentAge, std::function<std::tuple<int, bool>>);
	
};

