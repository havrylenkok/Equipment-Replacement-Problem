#pragma once
#include "Controller.h"
#include "RegExp.h"


//считывание инпута при помощи regex

int  main(int argc, char* argv[]) {

	auto input = Input();
	std::map<int, int> r;
	std::map<int, int> u;
	int p = 0;
	int T = 0;

	
	if (argc < 2) {
		cout << "\nYou can open program with console: program-name $T r $elements u $elements $p\n";
		input.console(r, u, p, T);
		}
	else {
		input.nice(argc, argv, r, u, p, T);
	}

	auto cont = Controller(r, u, p, T);
	cont.startProcess();
	
	return 0;

}