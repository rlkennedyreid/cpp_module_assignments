// OOP in C++ Assigment 3

// Robin Kennedy-Reid - 9436360

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>

using namespace std;

// Function that prints a vector of strings using iterator
void PrintVector( vector<string>& input_vector ){

	vector<string>::iterator input_begin{ input_vector.begin() },
		input_end{ input_vector.end() },
		input_current;

	for (input_current = input_begin; input_current < input_end; ++input_current){
		cout << "'" << *input_current << "'" << endl;
	}
}

// Function that checks for invalid input for course code
bool CheckCourseCode(const string& input){

	string correct_years{"1234"}; // variable to check valid first digit
	// no input
	if (input.size() == 0)
		return false;
	// not right size
	else if (input.size() != 5)
		return false;
	// find return npos if first character of our string is not a specified year
	else if (correct_years.find(input[0]) == string::npos)
		return false;
	// good input
	else
		return true;
}

// Function to gather full course titles into vector of strings
void CollectCourses(vector<string>& data){
	// declare variables
	string input, course_code, course_title, digits{"0123456789"};
	ostringstream output_stream;

	while (true){
		// request and take data
		cout << "Please enter course in the following format:" << endl <<
			"30762 Object-Oriented Programming in C++" << endl <<
			"Enter 'x' to exit" << endl << endl;

		getline(cin, input);

		if (input == "x" || input == "X")
			break; // exit loop on request

		// Create substrings for code and title, assumming course code ends with first non-digit
		course_code = input.substr(0, input.find_first_not_of(digits));

		// and the course title is just the rest of the string, ignoring 1 space between
		course_title = input.substr(input.find_first_not_of(digits) + 1, input.npos);

		// validate input, don't take data if bad
		if (CheckCourseCode(course_code)){
			// full code
			output_stream << "PHYS " + course_code + " " + course_title;
			// store
			data.push_back(output_stream.str()); output_stream.str("");
		}
		else
			cout << "Invalid course code, please try again." << endl;
	}
}

// argument for sort, to check course title substring alphabetically
bool SortAlpha(string &a, string &b) {
	return a.substr(10, a.npos) < b.substr(10, b.npos);
}

// argument for sort, to check course code substring numerically
bool SortNumeric(string &a, string &b) {
	return a.substr(4, a.npos) < b.substr(4, b.npos);
}


int main(){
	string input, correct_years{ "1234" };
	vector<string> all_courses;

	// Take data into all_courses
	CollectCourses(all_courses);

	// If data is taken, start displaying
	if (all_courses.size() != 0){

		// declare iterators
		vector<string>::iterator all_courses_begin{ all_courses.begin() },
			all_courses_end{ all_courses.end() },
			all_courses_current;

		cout << "Here is the list of courses in the order you gave them:" << endl;

		PrintVector(all_courses);

		// Print a specific year, given by user. Check for correct input of a digit
		do{
			cout << "Pick a year to view only courses for that year [1/2/3/4]: " << endl;
			getline(cin, input);
		} while (input.size() != 1 || correct_years.find(input) == string::npos);

		// Display data for the given year
		cout << "Here is a list of the year " << input << " courses:" << endl;

		for (all_courses_current = all_courses_begin;
			all_courses_current < all_courses_end;
			++all_courses_current){

			if ( (*all_courses_current)[5] == input[0] ) // only print the year we want
				cout << "'" << *all_courses_current << "'" << endl;
		}

		// Sort alphabetically/numerically and print
		cout << endl << "All courses sorted alphabetically:" << endl;

		sort(all_courses_begin, all_courses_end, SortAlpha); PrintVector(all_courses);

		cout << endl << "All courses sorted Numerically:" << endl;

		sort(all_courses_begin, all_courses_end, SortNumeric); PrintVector(all_courses);

	}
	return 0;
}