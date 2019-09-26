#include <string>
#include <vector>
#include <cctype>

using std::string;
using std::vector;
using std::max;

// Breaks a line of input into words, separated from each other by whitespace
vector<string> split(const string& s) {
	vector<string> ret;
	typedef string::size_type string_size;
	string_size i = 0;

	// invariant: we have processed characters [original value of i, i)
	while (i != s.size()) {
		// ignore leading blanks
		// invariant: characters in range [original i, current i) are all spaces
		while (i != s.size() && isspace(s[i]))
			++i;

		// find end of the next word
		string_size j = i;
		// invariant: none of the characters in range [original j, current j) is a space
		while (j != s.size() && !isspace(s[j]))
			++j;
		// if we found some nonwhitespace characters
		if (i != j) {
			// copy from s starting at i and taking j - i chars
			ret.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return ret;
}

// Finds longest string in the vector
string::size_type width(const vector<string>& v) {
    string::size_type maxlen = 0;
    for (vector<string>::size_type i = 0; i != v.size(); ++i)
    	maxlen = max(maxlen, v[i].size());
    return maxlen;
}

// Puts strings in the vector in a box of asterisks
vector<string> frame(const vector<string>& v) {
	vector<string> ret;
	string::size_type maxlen = width(v);
	string border(maxlen + 4, '*');

	// write the top border
	ret.push_back(border);

	// write each interior row, bordered by an asterisk and space
	for (vector<string>::size_type i = 0; i != v.size(); ++i)
		ret.push_back("* " + v[i] + string(maxlen - v[i].size(), ' ') + " *");

	//write the bottom border
	ret.push_back(border);
	return ret;
}

// Vertical vector concatenation
vector<string> vcat(const vector<string>& top, const vector<string>& bottom) {
	// copy the top picture
	vector<string> ret = top;

	// copy entire bottom picture
	for (vector<string>::const_iterator i = bottom.begin(); i != bottom.end(); ++i)
		ret.push_back(*i);

	return ret;
}