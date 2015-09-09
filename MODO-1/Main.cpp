#pragma once
#include "Controller.h"

//падения на fullCycle
//убрать запись поверх старых данных в файл
//правильность результатов
//деструкторы
//считывание инпута при помощи regex

int main() {

	std::map<int, int> r;
	r[0] = 80; //r(t)
	r[1] = 75;
	r[2] = 65;
	r[3] = 60;
	r[4] = 60;
	r[5] = 55;

	std::map<int, int> u;
	u[0] = 20; // u(t)
	u[1] = 25;
	u[2] = 30;
	u[3] = 35;
	u[4] = 45;
	u[5] = 55;


	auto work = Controller(r, u, 40, 5);
	work.startProcess();
	getchar();
	return 0;

}