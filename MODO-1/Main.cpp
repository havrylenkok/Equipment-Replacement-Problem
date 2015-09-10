#pragma once
#include "Controller.h"
#include "RegExp.h"


//���������� ������ ��� ������ regex

int  main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	auto input = Input();
	std::map<int, int> r;
	std::map<int, int> u;
	int p = 0;
	int T = 0;

	
	if (argc < 2) {
		cout << "\n�� ������ �i������ �������� ����� �������: program-name $T r $elements u $elements $p\n";
		input.console(r, u, p, T);
		}
	else {
		input.nice(argc, argv, r, u, p, T);
	}

	auto cont = Controller(r, u, p, T);
	cont.startProcess();
	
	return 0;

}