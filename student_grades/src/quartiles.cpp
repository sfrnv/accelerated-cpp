#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using std::cin;
using std::setprecision;
using std::cout;
using std::sort;
using std::streamsize;
using std::endl;
using std::vector;

void quartiles() {
	cout << "Enter all your numbers, followed by end-of-file: ";

	vector<double> set;
	double x;

	while (cin >> x)
		set.push_back(x);

	typedef vector<double>::size_type vec_sz;
	vec_sz size = set.size();

	if (size == 0) {
		cout << endl << "You must enter your numbers.  Please try again." << endl;
		return;
	}

	sort(set.begin(), set.end());
	double q1, q2, q3;
	vec_sz mid = size / 2;
	vec_sz quad;
	if (size % 2 == 0) { // ok
		q2 = (set[mid] + set[mid - 1] ) / 2;
		quad = mid / 2;
		if (mid % 2 == 0) {
			q1 = (set[quad] + set[quad - 1]) / 2;
			q3 = (set[mid + quad] + set[mid + quad - 1]) / 2;
		} else {
			q1 = set[quad];
			q3 = set[mid + quad];
		}
	} else {
		q2 = set[mid];
		quad = (mid - 1) / 2;
		if (mid % 2 == 0) {
			cout << "mid = " << mid << "; quad = " << quad << endl;
			q1 = (set[quad] + set[quad + 1]) / 2;
			q3 = (set[(mid + 1) + quad] + set[(mid + 1) + (quad + 1)]) / 2;
		} else {
			q1 = set[quad];
			q3 = set[mid + quad + 1];
		}
	}
	streamsize prec = cout.precision();
	cout << setprecision(3) << q1 << " " << q2 << " " << q3 << setprecision(prec) << endl;
}