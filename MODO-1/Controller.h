#pragma once
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iomanip>
#include <regex>
#include <locale>

using namespace std;

class Controller 
{
	//значени€ хран€тс€ в <int>, були - в <double>. vector<bool> не имеет subscript синтаксиса по
	//историческим причинам, пришлось выкручиватьс€ (деку или ещЄ что-то € использовать не хотел)

private:
	//ѕ≈–≈ћ≈ЌЌџ≈
	int t; // t - текущий год
	int p; // p - цена покупки нового оборудовани€
	int T; // T - длительность периода
	int stableT; // const T
	int k = 1; // k - итератор по периоду
	int maxZ = 0; //максимальна€ прибыль. ѕеременна€ среды, чтобы не возитьс€ с передачей в программе
	int showingT; //конст T дл€ функций вывода

	map<int, int> r; // r(t) - прибыль за конкретный год
	map<int, int> u; // u(t) - затраты на обслуживание за конкретный год

	//нулевые векторы дл€ значений и булей, чтобы считать с 1, а не 0
	vector<int> nullVectorOfInt{ 0 }; 
	vector<double> nullVectorOfBool{ 0 };

	map<int, vector<int> > tableInterResultValues; // промежуточные таблички, значени€ fk(t)
	map<int, vector<double> > tableInterStrategy; // промежуточные таблички, стратеги€
	
	int resultTable(vector<int> final); //последн€€ таблица
	vector<int> fullCycle(); //проход по всем k
	tuple<vector<int>, vector<double>> fkt(); //проход по всем t
	tuple<int, bool> functionFrom1(int t); //рассчет дл€ первого
	tuple<int, bool> functionFromK(int t); //рассчет дл€ k-того
	int functionFromLast(int t); //рассчет дл€ последнего
	void saveConditions(); //сохранение условий в файле вывода

public:
	void startProcess(); //начать рассчеты
	Controller(map<int, int> r, map<int, int> u, int p, int T);

};

