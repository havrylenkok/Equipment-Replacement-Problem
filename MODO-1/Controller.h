#pragma once
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <functional>
#include <boost>

class Controller
{
public:
	Controller();
	~Controller();

	std::vector<int, int, boost::any> oneOfSteps (int currentAge, std::function<std::tuple<int, bool>> )
	
};

