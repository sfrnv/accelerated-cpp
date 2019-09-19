#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cin;
using std::sort;
using std::cout;
using std::streamsize;
using std::endl;
using std::string;
using std::setprecision;
using std::vector;
using std::istream;
using std::domain_error;

int f1();
int f2();
void quartiles();

// compute a student's overall grade from midterm and final exam grades and homework grade
double grade(double midterm, double final, double homework) {
	return  0.2 * midterm + 0.4 * final + 0.4 * homework;
}

// compute the median of a vector<double>
// note that calling this function copies the entire argument vector
double median(vector<double> vec) {
	typedef vector<double>::size_type vec_sz;

	vec_sz size = vec.size();

	if (size == 0)
		throw domain_error("median of an empty vector");

	sort(vec.begin(), vec.end());

	vec_sz mid =  size / 2;
	return size % 2 == 0 ? (vec[mid] + vec[mid-1]) / 2 : vec[mid];
}

// compute a student's overall grade from midterm and final exam grades
// and vector of homework grades.
// this function does not copy its argument, because median does so for us.
double grade(double midterm, double final, const vector<double>& hw) {
	if (hw.size() == 0)
		throw domain_error("student has done no homework");
	return grade(midterm, final, median(hw));
}

// read homework grades from an input stream into a vector<double>
istream& read_hw(istream& in, vector<double>& hw) {
	if (in) {
		// get rid of previous contents
		hw.clear() ;
		// read homework grades
		double x;
		while (in >> x)
			hw.push_back(x);
		// clear the stream so that input will work for the next student
		in.clear();
	}
	return in;
}

int f1() {

	// ask for and read the student's name
	cout << "Please enter your first name: ";
	string name;
	cin >> name;
	cout << "Hello, " << name << "!" << endl;

	// ask for and read the midterm and final grades
	cout << "Please enter your midterm and final exam grades: ";
	double midterm, final;
	cin >> midterm >> final;

	// ask for the homework grades
	// two string literals, separated only by whitespace, are automatically concatenated
	cout << "Enter all your homework grades, "
			"followed by end-of-file: ";

	// the number and sum of grades read so far
	int count = 0;
	double sum = 0;

	// a variable into which to read
	double x;

	// invariant:
	// we have read count grades so far, and
	// sum is the sum of the first count grades
	while (cin >> x) {
		++count;
		sum += x;
	}

	// write the result
	streamsize prec = cout.precision();
	cout << "Your final grade is " << setprecision(3)
		<< grade(midterm, final, sum / count)
		<< setprecision(prec) << endl;

	return 0;
}

int f2() {

	// ask for and read the student's name
	cout << "Please enter your first name: ";
	string name;
	cin >> name;
	cout << "Hello, " << name << "!" << endl;

	// ask for and read the midterm and final grades
	cout << "Please enter your midterm and final exam grades: ";
	double midterm, final;
	cin >> midterm >> final;

	// ask for and read the homework grades
	cout << "Enter all your homework grades, followed by end-of-file: ";

	vector<double> homework;

	// read the homework grades
	read_hw(cin, homework);

	// compute and generate the final grade, if possible
	try  {
		double final_grade = grade(midterm, final, homework);
		streamsize prec = cout.precision();
		cout << "Your final grade is " << setprecision(3)
			<< final_grade << setprecision(prec) << endl;
	} catch (domain_error) {
		cout << endl <<	"You must enter your grades.  "
						"Please try again." << endl;
		return 1;
	}
	return 0;
}

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

int main() {
	return f1();
	// return f2();
	// quartiles();
	return 0;
}