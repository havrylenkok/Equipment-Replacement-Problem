#include "RegExp.h"

int Input::console(std::map<int, int>& r, std::map<int, int>& u, int & p, int & T)

{
		cout << "\nEnter T: "; cin >> T; cout << endl;
		
		cout << "Enter r { ";
		for (int i = 1; i <= T + 1; i++) {
			cin >> r[i - 1];
		}

		cout << "\t}\n";

		cout << "\nEnter u { ";
		for (int i = 1; i <= T + 1; i++) {
			cin >> u[i - 1];
		}

		cout << "\t}\n Enter p in thousands: "; cin >> p;
		return 0;
}

int Input::nice(int & argc, char * argv[], std::map<int, int>& r, std::map<int, int>& u, int & p, int & T)
{
	T = stoi(argv[1]);

	if (T != 0 && argc > T + T + 6) {

		if (argv[3] != "elements" || argv[3] != "u" || argv[3] != "U" || argv[3] != "ELEMENTS") {
			for (int i = 0; i <= T; i++) {
				r[i] = stoi(argv[3 + i]);
			}
		}
		else { cout << "you made mistake in input. Try again\n"; return 10; }

		if (argv[4 + T] != "elements" || argv[4 + T] != "p" || argv[4 + T] != "P" || argv[4 + T] != "ELEMENTS") {
			for (int i = 0; i <= T; i++) {
				u[i] = stoi(argv[5 + T + i]);
			}
		}
		else { cout << "you made mistake in input. Try again\n"; return 11; }
		p = stoi(argv[T * 2 + 6]);
		return 0;
	}
}

