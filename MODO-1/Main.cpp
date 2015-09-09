#pragma once
#include "Controller.h"


//считывание инпута при помощи regex

int  main(int argc, char* argv[]) {

	std::map<int, int> r;
	std::map<int, int> u;
	int p;
	int T;
	string arg1, arg2; 

	//if (argc < 5) {
		int ner;
		cout << "Enter num of elements in r: "; cin >> ner; 

		cout << "Enter r { ";
		for (int i = 1; i <= ner; i++) {
			cin >> r[i-1];
		}

		int uer;
		cout << "\t}\nEnter num of elements in r: "; cin >> uer;

		cout << "\nEnter u { ";
		for (int i = 1; i <= uer; i++) {
			cin >> u[i-1];
		}

		cout << "\t}\n Enter p: "; cin >> p;
		if ((p / 10000) > 1) { p /= 10000; }

		cout << "\nEnter T: "; cin >> T; cout << endl;
		
		/*}
	else {
		arg1 = argv[0]; //need regex
		arg2 = argv[1]; //need regex
		p = stoi(argv[2]);
		T = stoi(argv[3]);
	}

	regex regex1("");
	regex regex2("{int,}");*/

	if (r[0] == 755) {

	std::map<int, int> defr;
	r[0] = 80; //r(t)
	r[1] = 75;
	r[2] = 65;
	r[3] = 60;
	r[4] = 60;
	r[5] = 55;

	std::map<int, int> defu;
	u[0] = 20; // u(t)
	u[1] = 25;
	u[2] = 30;
	u[3] = 35;
	u[4] = 45;
	u[5] = 55;


	auto work = Controller(r, u, 40, 5);
	work.startProcess();
	}
	else {
		auto cont = Controller(r, u, p, T);
		cont.startProcess();
	}
	return 0;

}