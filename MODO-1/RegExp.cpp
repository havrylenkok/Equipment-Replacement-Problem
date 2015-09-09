#include "RegExp.h"

int Input::console(std::map<int, int>& r, std::map<int, int>& u, int & p, int & T)

{
		int ner;
		cout << "Enter num of elements in r: "; cin >> ner;

		cout << "Enter r { ";
		for (int i = 1; i <= ner; i++) {
			cin >> r[i - 1];
		}

		int uer;
		cout << "\t}\nEnter num of elements in r: "; cin >> uer;

		cout << "\nEnter u { ";
		for (int i = 1; i <= uer; i++) {
			cin >> u[i - 1];
		}

		cout << "\t}\n Enter p: "; cin >> p;
		if ((p / 10000) > 1) { p /= 10000; }

		cout << "\nEnter T: "; cin >> T; cout << endl;
}

#include "RegExp.h"


string Input::analysis() {

}