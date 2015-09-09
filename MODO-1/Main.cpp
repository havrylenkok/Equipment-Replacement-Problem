#pragma once
#include "Controller.h"
#include "RegExp.h"


//считывание инпута при помощи regex

int  main(int argc, char* argv[]) {

	auto input = Input();
	std::map<int, int> r;
	std::map<int, int> u;
	int p;
	int T;
	string arg1, arg2; 

	if (argc < 5) {
		input.console(r, u, p, T);
		}
	else {
		arg1 = argv[0]; //need regex
		arg2 = argv[1]; //need regex
		p = stoi(argv[2]);
		T = stoi(argv[3]);
	}

	
	auto cont = Controller(r, u, p, T);
	cont.startProcess();
	
	return 0;

}