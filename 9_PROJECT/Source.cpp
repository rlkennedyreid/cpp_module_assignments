#include "numerical_measurement.h"
#include "experiment_class.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <functional>

//  Prototype functions
template <class T> void UserNumericExptInput(Experiment<T>&);

template <class T> void FileNumericExptInput(Experiment<T>&);

void MakeExperiment(const int experiment_count, std::vector< std::unique_ptr<Experiment<double>>>& experiments_vector, void (*func)(Experiment<double>&));

std::string TakeStringInput(std::vector<std::string>&);

bool is_number(const std::string&);

bool is_integer(const std::string&);

void OpenFile(std::ifstream&);


int main(){

	// NUMERIC MEASUREMENT 1-VARIABLE CONSTRUCTOR AND PRINT FUNCTION DEMONSTRATION - USING FLOATS
	std::vector< std::shared_ptr<base_measurement::Measurement<float>> > meas_vector_float; // vector to stor float measurements
	float demo_float{ 1.5 }; // variable to assign to measurement

	std::cout << "Printing vector of 1-variable measurements:" << std::endl;
	for (int i{ 0 }; i < 10; i++){ // assign 10 measurements to vector
		meas_vector_float.push_back(std::make_shared<num_measurement::NumericMeasurement<float>>("eV", demo_float, demo_float, demo_float)); // units, measurement, sys_error, meas_error
		meas_vector_float[i]->Print(std::cout); // print each component
		std::cout << std::setw(10) << " Units: " << meas_vector_float[i]->GetUnits(0) << std::endl; // Show units are correct
	}
	meas_vector_float.clear(); // clear vector

	// NUMERIC MEASUREMENT MULTI-VARIABLE PARAMATERISED CONSTRUCTOR DEMONSTRATION - USING DOUBLES

	std::array<double, 3> demo_variable{ { 1., 1., 1. } }; // measurement, sys_error, meas_error
	std::vector< std::array<double, 3> >  demo_measurement{ demo_variable, demo_variable }; // two variables
	std::vector<std::string> demo_units{ "eV", "keV" }; // units for each variable

	std::vector< std::shared_ptr<base_measurement::Measurement<double>> > meas_vector_double; // vector to store double measurements
	std::cout << "Printing vector of Multi-variable measurements:" << std::endl;
	for (int i{ 0 }; i < 10; i++){ // assign 10 measurements to vector
		meas_vector_double.push_back(std::make_shared<num_measurement::NumericMeasurement<double>>(demo_units, demo_measurement));
		meas_vector_double[i]->Print(std::cout);
		std::cout << std::setw(10) << " Units: " << meas_vector_double[i]->GetUnits(0) + ", " + meas_vector_double[i]->GetUnits(1) << // show units are correct
		std::endl;
	}
	meas_vector_double.clear(); // clear vector

	// User and File Input demonstration
	std::cout << "\nUser and File Input Demonstration:" << std::endl;
	std::vector< std::unique_ptr<Experiment<double>> > experiments_vector; // Vector of experiment pointers
	int experiment_count{ -1 }; // count number of experiments, -1 due to increment on do-while loop!
	do {
		experiment_count++;
		// Ask user for decision on file or manual input, forcing valid reply with TakeStringInput
		std::cout << "Would you like to input by file or manually (see 3_variable.dat for format of file input)?" << std::endl;

		if (TakeStringInput(std::vector< std::string >{ "file", "manual" }) == "file")
			MakeExperiment(experiment_count,experiments_vector,FileNumericExptInput);
		else
			MakeExperiment(experiment_count, experiments_vector, UserNumericExptInput);

		std::cout << "Would you like to record another experiment?" << std::endl;
	} while (TakeStringInput(std::vector< std::string >{ "y", "n" }) == "y"); // rerun on request

	std::cout << "Program complete, see default directory for report files." << std::endl;
	return 0;
}

// Function to take numeric measurements into experiment class from user
template <class T> void UserNumericExptInput(Experiment<T>& expt) {

	// Variables to hold input given by user throughout
	std::string input_string; std::stringstream input_stream;

	// Assign experiment title
	std::cout << "Please input the title of your experiment:" << std::endl;
	std::getline(std::cin, input_string); expt.SetTitle(input_string);

	int no_variables{ 0 };
	// Get number of variables from user, force integer input
	do {
		std::cout << "Please enter the number of variables per measurement:" << std::endl;
		std::getline(std::cin, input_string);
	} while (!is_integer(input_string) || input_string == "0"); // retry if not
	
	// Assign valid input, clear stream
	input_stream.str(input_string); input_stream >> no_variables; input_stream.clear();

	std::vector<std::string> units_temp(no_variables); // create vector of units of correct size

	// Lamda function to assign units from std::getline to each vector component
	int units_count{ 1 }; // count variable to display to user
	std::for_each(units_temp.begin(), units_temp.end(),
		[&units_count](std::string& units_input) mutable {
		std::cout << "Please enter the units of variable " << units_count << ":" << std::endl;
		std::getline(std::cin, units_input); units_count++; // increment to next unit
	});

	// Container variables for measurements and measurement components
	std::array<T, 3> variable_temp; std::vector< std::array<T, 3> > measurements_temp; 

	// Measurement collection
	bool re_run{ true };
	while (re_run){
		measurements_temp.clear();
		for (int variable_count{ 1 }; variable_count <= no_variables; variable_count++){

			// Lamda function to request input for a variable (with a string identifier) and force re-entry if not numeric
			auto check_input = [&variable_count, &input_string](std::string identifier) mutable {
				do{
					std::cout << identifier << " for variable " << variable_count << ":" << std::endl;
					std::getline(std::cin, input_string);
				} while (!is_number(input_string)); // force re-entry
			};
			
			// Lamda function to take valid input, checked by check_input above
			int index{ 0 }; // increment on each call to assign variable, then 1st error, then 2nd error.
			auto take_input = [&index, &input_stream, &input_string, &variable_temp]() mutable {
				input_stream.str(input_string); input_stream >> variable_temp[index]; input_stream.clear(); // take input, clear stream
				index++; // increment, so next value taken is assigned to next variable
			};

			// Check and take inputs to each variable of the measurement with functions above
			check_input("Value"); take_input();
			check_input("Systematic error"); take_input();
			check_input("Measurement error"); take_input();

			measurements_temp.push_back(variable_temp); // store array into measurement
		}
		// Add measurement to expt
		expt.AddMeasurement(std::make_shared<num_measurement::NumericMeasurement<T>>(units_temp, measurements_temp));

		// new measurement request, TakeStringInput forces valid response
		std::cout << "Input new measurement?" << std::endl;

		// stop if requested
		if (TakeStringInput(std::vector<std::string>{"y", "n"}) == "n")
			re_run = false;
	}

}

// Function to take numeric measurements into experiment class from file
// user must specify the number of variables. Function assumes each measurement
// on a line, with two errors for each variable, separated by whitespace, see 3_variable.dat
template <class T> void FileNumericExptInput(Experiment<T>& expt){
	std::ifstream input_file; // filestream

	// Variables to hold input given by user throughout
	std::string input_string; std::stringstream input_stream;

	OpenFile(input_file); // Open file, force success with OpenFile

	// Assign experiment title
	std::cout << "Please input the title of your experiment:" << std::endl;
	std::getline(std::cin, input_string); expt.SetTitle(input_string);

	int no_variables{ 0 };
	// Get number of variables from user, force integer input
	do{
		std::cout << "Please enter the number of variables per measurement:" << std::endl;
		std::getline(std::cin, input_string);
	} while (!is_integer(input_string) || input_string == "0"); // retry if not

	// Assign valid input, clear stream
	input_stream.str(input_string); input_stream >> no_variables; input_stream.clear();

	std::vector<std::string> units_temp(no_variables); // create unit array

	// Lamda function to input units from std::getline user input
	int units_count{ 1 };
	std::for_each(units_temp.begin(), units_temp.end(),
		[&units_count](std::string& units_input) mutable {
		std::cout << "Please enter the units of variable " << units_count << ":" << std::endl;
		std::getline(std::cin, units_input); units_count++; // increment to next unit
	});

	// take each line, convert to stream, take each variable from stream
	while (std::getline(input_file, input_string)){
		std::vector< std::array<T, 3> > measurement_temp; // hold current measurement
		input_stream.str(input_string);
		for (int i{ 1 }; i <= no_variables; i++){
			std::array<T, 3> variable_temp;
			input_stream >> variable_temp[0];
			input_stream >> variable_temp[1];
			input_stream >> variable_temp[2];

			measurement_temp.push_back(variable_temp); // store variables into measurement
		}
		// Add measurement to expt
		expt.AddMeasurement(std::make_shared<num_measurement::NumericMeasurement<T>>(units_temp, measurement_temp)); // store measurement
	}
	// confirm completion
	std::cout << "File read complete." << std::endl;

}

// Function to for use in creating experiments in main; takes a function as an argument that is intended to be either
// UserNumericExptInput or FileNumericExptInput. Intended to reduce repeated code in main.
void MakeExperiment(const int experiment_count, std::vector< std::unique_ptr<Experiment<double>> >& experiments_vector, void(*func)(Experiment<double>&)){
	experiments_vector.push_back(std::make_unique<Experiment<double>>()); // push default experiment onto vector
	func(*experiments_vector[experiment_count]); // input experiment
	experiments_vector[experiment_count]->PrintToFile(); // print experiment to file
	std::cout << "Experiment printed to file, would you like to view a report in console?" << std::endl;
	if (TakeStringInput(std::vector< std::string >{ "y", "n" }) == "y")
		experiments_vector[experiment_count]->Print(std::cout);

	std::cout << "Would you like to view weighted mean and error for your experiment?" << std::endl;
	if (TakeStringInput(std::vector< std::string >{ "y", "n" }) == "y")
		std::cout << "Mean = " << experiments_vector[experiment_count]->GetWeightedMean() << std::endl <<
		"Standard Error = " << experiments_vector[experiment_count]->GetMeanError() << std::endl;
}

// Function to request and return inputs from user, forcing entry of accepted inputs
std::string TakeStringInput(std::vector<std::string>& accepted_inputs) {
	std::string input_string; // store user input
	do {
		// Print accepted inputs for user
		std::cout << "Accepted Inputs: ["; 
		for (auto iter = accepted_inputs.begin(); iter < accepted_inputs.end(); iter++)
			std::cout << *iter << "/";
		std::cout << "]:" << std::endl;
		// Take input
		std::getline(std::cin, input_string);
		// Loop forces retry if input_string not found in accepted_inputs
	} while (std::find(accepted_inputs.begin(), accepted_inputs.end(), input_string) == accepted_inputs.end());
	// valid input out of loop, return it
	return input_string;
}

// Function to check if a a string input is a number by attempting a long double conversion
// assuming an input that will not convert to long double will not convert to float or double etc.
bool is_number(const std::string& input){

	try { std::stold(input); }

	catch (...) { return false; }

	return true;
}

// Function to check if a string input is an integer by checking for empty input or non-digit characters with a lamda function
bool is_integer(const std::string& input){
	return !input.empty() && std::find_if(input.begin(), input.end(), [](char c) { return !std::isdigit(c); }) == input.end();
}

// Opens a file into a given ifstream using user input, checks success, forces retry if not
void OpenFile(std::ifstream& input_file){

	std::string file_name; // input variable
	std::cout << "Please input the name of your data file." << std::endl;

	std::getline(std::cin, file_name);
	input_file.open(file_name);

	while (!input_file.is_open()){ // error handling, forces re-attempt
		input_file.close(); input_file.clear(); // close and clear
		std::cerr << "Error reading file, please check file name and directory." << std::endl;
		std::cout << "Please input the name of your data file." << std::endl;

		std::getline(std::cin, file_name);
		input_file.open(file_name);
	} // passed succesfully at this point

	std::cout << "File opened successfully." << std::endl;
}