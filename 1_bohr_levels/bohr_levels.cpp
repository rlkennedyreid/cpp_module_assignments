

#include <iostream>
#include <string>
#include <cmath> 
#include <iomanip>

using namespace std;

const double e{ 1.602e-19 };
const double rydberg{ 13.6 };

// Function to check for valid integer input (except for empty input)
bool IsPositiveInteger(const string& input){
    bool failure = true; // bool reassigned for invalid input

    for (int i = 0; i < input.size(); ++i) { // run over string elements checking for non-digits
        if (!isdigit(input[i])) {
            failure = false;
            break; // first failure, exit loop and return false
        }
    }
    return failure;
}

bool ValidAtomic(const string& input)
{
    if (!IsPositiveInteger(input)){
        cout << "Error: Not positive integer" << endl;
        return false;
    }
    else if (stoi(input) <= 0){ // stoi() safe as input checked
        cout << "Atomic number cannot be <= 0." << endl;
        return false;
    }
    else if (stoi(input) > 119){
        cout << "No atoms with Z>119 have been discovered." << endl;
        return false;
    }
    else
        return true;
}

// Function to test for valid input of inital energy level
bool ValidInitial(const string& input)
{
    if (!IsPositiveInteger(input)){
        cout << "Error: Not positive integer" << endl;
        return false;
    }
    if (stoi(input) < 2){
        cout << "Initial energy level must be above 1." << endl;
        return false;
    }
    else
        return true;
}

// Function to test for valid input of final energy level
bool ValidFinal(int initial, const string& final)
{
    if (!IsPositiveInteger(final)){
        cout << "Error: Not positive integer" << endl;
        return false;
    }
    else if (stoi(final) <= 0){ // stoi() safe as input checked
        cout << "Atomic number cannot be <= 0." << endl;
        return false;
    }
    else if (stoi(final) >= initial){
        cout << "For photon to be emitted, final energy level must be below the initial." << endl;
        return false;
    }

    else
        return true;
}

// Function to convert all characters in a string to lower case
string LowerCaseString(string response) {

    for (string::iterator i = response.begin(); i < response.end(); i++) { *i = tolower(*i); }
    return response;
}

// Function to test for valid input of a string for two possible options (not case sensitive)
bool ValidString(string response, string accepted) {
    if (LowerCaseString(response) == accepted)
        return true; // Valid input

    else {
        return false; // true statement above allows all other bad input to be caught here, no need for failure variable
    }
}

// Function to calculate photon energy (in eV), given atomic number and energy levels
double photonEnergy(int atomic_num, int initial_lev, int final_lev){
    return rydberg*pow(atomic_num, 2)*(pow(final_lev, -2) - pow(initial_lev, -2));
}

int main(){
    // Declare variables
    int initial_level, final_level, atomic_number;
    string units, input;
    bool re_run{ true };
    do {
        // Ask user to enter atomic number and check inputs
        cout << "Please enter the atomic number" << endl;
        cin >> input;

        while (cin.fail() || !ValidAtomic(input)) {
            // clear error, ignore stream
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter the atomic number" << endl; // try again
            cin >> input;
        } atomic_number = stoi(input); // assign variable

        // Ask user to enter initial quantum number and check inputs
        cout << "Please enter initial quantum number" << endl;
        cin >> input;
        while (cin.fail() || !ValidInitial(input)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter initial quantum number" << endl;
            cin >> input;
        } initial_level = stoi(input); // assign variable

        // Ask user to enter final quantum number and check inputs
        cout << "Please enter final quantum number" << endl;
        cin >> input;

        while (cin.fail() || !ValidFinal(initial_level, input)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter final quantum number" << endl;
            cin >> input;
        } final_level = stoi(input); // assign variable

        // ask user for units and check inputs
        cout << "What units would you like your transition energy to be in? [J/eV]" << endl;
        cin.ignore(); getline(cin, units); // got input
        while (!ValidString(units, "j") && !ValidString(units, "ev")){
            cout << "Invalid response! (see square brackets for accepted responses)" << endl;
            cout << "What units would you like your transition energy to be in? [J/eV]" << endl;
            cin.clear(); getline(cin, units);
        } units = LowerCaseString(units); // assign lower case string for if statements below

        // Output answer, formatted
        if (LowerCaseString(units) == "ev"){ // in eV
            cout << "The photon energy for this transition is " << setprecision(3)
                << photonEnergy(atomic_number, initial_level, final_level) << " eV" << endl;
        }
        else{ // in Joules
            cout << "The photon energy for this transition is " << setprecision(3)
                << photonEnergy(atomic_number, initial_level, final_level)*e << " J" << endl;
        }

        // ask user if they'd like to re-run
        cout << "Would you like to run this program again? [y/n]" << endl;
        getline(cin, input);

        while (!ValidString(input, "y") && !ValidString(input, "n")){
            cout << "Would you like to run this program again? [y/n]" << endl;
            cout << "Invalid response! (see square brackets for accepted responses)" << endl;
            cin.clear();
            getline(cin, input);
        }

        // exit loop
        if (LowerCaseString(input) == "n")
            re_run = false;

    } while (re_run);

    return 0;
}