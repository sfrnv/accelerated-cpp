#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include "grade.h"
#include "student_info.h"
#include "analysis.h"

using std::cin;
using std::setprecision;
using std::cout;
using std::sort;
using std::domain_error;
using std::streamsize;
using std::endl;
using std::string;
using std::max;
using std::vector;
using std::list;

bool fgrade(const Student_info&);
bool pgrade(const Student_info&);
vector<Student_info> extract_fails(vector<Student_info>&);
list<Student_info> extract_fails(list<Student_info>&);
int alt_main();

int main() {
	//return alt_main();
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0;       // the length of the longest name

	// read and store all the students data.
	// Invariant:	students contains all the student records read so far
	//				maxlen contains the length of the longest name in students
	while (read(cin, record)) {
		// find length of longest name
		maxlen = max(maxlen, record.name.size());
		students.push_back(record);
	}

	// alphabetize the student records
	// students.sort(compare);
	sort(students.begin(), students.end(), compare);
	extract_fails(students);

	// write the names and grades
	vector<Student_info>::iterator iter = students.begin();
	while (iter != students.end()) {
		// write the name, padded on the right to maxlen + 1 characters
		cout << iter->name
			<< string(maxlen + 1 - iter->name.size(), ' ');
		// compute and write the grade
		try {
			double final_grade = grade(*iter);
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade
				<< setprecision(prec);
		} catch (domain_error e) {
			cout << e.what();
		}
		cout << endl;
		++iter;
	}
	return 0;
}

// predicate to determine whether a student failed
bool fgrade(const Student_info& s) {
	return grade(s) < 60;
}

// predicate that inverts the result of calling fgrade 
bool pgrade(const Student_info& s) {
	return !fgrade(s);
}

// version 3.2: use stable_partition function to rearrange the elements
vector<Student_info> extract_fails(vector<Student_info>& students) {
	vector<Student_info>::iterator iter = stable_partition(students.begin(), students.end(), pgrade);
	vector<Student_info> fail(iter, students.end());
	students.erase(iter, students.end());
	return fail;
}

// version 4: use list instead of vector
list<Student_info> extract_fails(list<Student_info>& students) {
	list<Student_info> fail;
	list<Student_info>::iterator iter = students.begin();
	while (iter != students.end()) {
		if (fgrade(*iter)) {
			fail.push_back(*iter);
			iter = students.erase(iter);
		} else
			++iter;
	}

	return fail;
}

int alt_main() {
	// students who did and didn't do all their homework
	vector<Student_info> did, didnt;

	// read the student records and partition them
	Student_info student;
	while (read(cin, student)) {
		if (did_all_hw(student))
			did.push_back(student);
		else
			didnt.push_back(student);
	}

	// verify that the analyses will show us something
	if (did.empty()) {
		cout << "No student did all the homework" << endl;
		return 1;
	}
	if (didnt.empty()) {
		cout << "Every student did all the homework" << endl;
		return 1;
	}

	// do the analyses
	write_analysis(cout, "median", median_analysis, did, didnt);
	write_analysis(cout, "average", average_analysis, did, didnt);
	write_analysis(cout, "median of homework turned in", optimistic_median_analysis, did, didnt);
	return 0;
}