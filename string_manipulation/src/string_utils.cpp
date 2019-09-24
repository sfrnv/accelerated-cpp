#include <string>
#include <vector>
#include <cctype>

using std::vector;

vector<string> split(const string& s) {
	vector<string> ret;
	typedef string::size_type string_size;
	string_size i = 0;

	// invariant: we have processed characters [original value of i, i)
	while (i != s.size()) {
		// ignore leading blanks
		// invariant: characters in range [original i, current i) are all spaces
		while (i != size() && isspace(s[i]))
			++i;

		// find end of the next word
		string_size j = i;
		// invariant: none of the characters in range [original j, current j) is a space
		while (j != size() && !isspace(s[j]))
			++J;
		// if we found some nonwhitespace characters
		if (i != j) {
			// copy from s starting at i and taking j - i chars
			ret.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return ret;
}