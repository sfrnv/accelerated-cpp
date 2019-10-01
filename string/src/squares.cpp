#include <iostream>
#include <iomanip>


int squares() {
	for (int i = 0; i < 100; ++i) {
		cout << i << std::setw(6);
		cout << i * i << std::endl;
	}
	return 0;
}