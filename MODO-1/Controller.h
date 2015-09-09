#pragma once
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iomanip>
#include <regex>

using namespace std;

class Controller 
{

private:
	//ПЕРЕМЕННЫЕ
	int t; // t - текущий год
	int p; // p - цена покупки нового оборудования
	int T; // T - длительность периода
	int stableT;
	int k = 1; // k - итератор по периоду
	int maxZ = 0;
	int showingT;

	map<int, int> r; // r(t) - прибыль за конкретный год
	map<int, int> u; // u(t) - затраты на обслуживание за конкретный год

	vector<int> nullVectorOfInt{ 0 };
	vector<double> nullVectorOfBool{ 0 };
	map<int, vector<int> > tableInterResultValues; // промежуточные таблички, значения fk(t)
	map<int, vector<double> > tableInterStrategy; // промежуточные таблички, стратегия
	
	int resultTable(vector<int> final);
	vector<int> fullCycle();
	tuple<vector<int>, vector<double>> fkt();
	tuple<int, bool> functionFrom1(int t);
	tuple<int, bool> functionFromK(int t);
	int functionFromLast(int t);
	void saveConditions();

public:
	void startProcess();
	Controller(map<int, int> r, map<int, int> u, int p, int T);

};

