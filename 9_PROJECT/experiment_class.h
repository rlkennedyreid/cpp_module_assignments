#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <memory>
#include <algorithm>
#include<vector>
#include<iomanip>
#include<sstream>
#include<fstream>
#include "base_measurement.h"

/*
CLASS FOR EXPERIMENT

*/

template <class T> class Experiment {
private:
	time_t datestamp_;
	std::string title_;
	std::vector< std::shared_ptr<base_measurement::Measurement<T>> > data_;

public:
	// Default constructor
	Experiment();
	// Parameterized constructors
	Experiment(const std::string&, const std::vector< std::shared_ptr<base_measurement::Measurement<T>> >& data_);
	Experiment(const std::string&); // Just title

	void Print(std::ostream&) const;
	void AddMeasurement(std::shared_ptr<base_measurement::Measurement<T>>);

	void UserNumericInput();
	void FileNumericInput();

	std::string GetTitle() const;

	void SetTitle(const std::string&);

	std::string GetDateStamp() const;

	T GetWeightedMean() const;
	T GetMeanError() const;

	void PrintToFile() const;
	// Destructor
	~Experiment(){};
};

// #################### Member Functions for Numeric Measurement #################
// Default constructor
template <class T> Experiment<T>::Experiment() : title_("default_title"), datestamp_(time(nullptr)) {}

// Parameterized Constructor
template <class T> Experiment<T>::Experiment(const std::string& title, const std::vector< std::shared_ptr<base_measurement::Measurement<T>> >& data)
	: title_(title), data_(data), datestamp_(time(nullptr)) {}

template <class T> Experiment<T>::Experiment(const std::string& title) : title_(title), datestamp_(time(nullptr)){}

template <class T> std::string Experiment<T>::GetTitle() const{ return title_; }

template <class T> void Experiment<T>::SetTitle(const std::string& title){ title_ = title; }

template <class T> void Experiment<T>::AddMeasurement(const std::shared_ptr<base_measurement::Measurement<T>> measurement){ data_.push_back(measurement); }

// Print measurements and their errors into ostream
template <class T> void Experiment<T>::Print(std::ostream& os) const{
	if (data_.size() != 0){
		std::stringstream title_stream;
		std::string title;

		// Print Title
		for (int i{ 0 }; i < data_[0]->GetNumVariables(); i++){
			title_stream.str("");
			title_stream << "Variable " << i + 1 << " (" << data_[0]->GetUnits(i) << ")";
			title = title_stream.str();
			os << std::setw(20) << title << std::setw(20) << "sys_error" << std::setw(20) << "meas_error";
		}
		os << std::setw(20) << "Timestamp" << std::endl;
		for (auto row = (data_).begin(); row < (data_).end(); row++){
			(*row)->Print(os);
			os << std::endl;
		}
	}
	else
		std::cerr << "Error: Empty data_ in Experiment::Print" << std::endl;
}

template <class T> std::string Experiment<T>::GetDateStamp() const{
	tm timeinfo; localtime_s(&timeinfo, &datestamp_);

	char time[20];
	strftime(time, sizeof time, "%Y-%m-%d", &timeinfo);
	return time;
}

template <class T> void Experiment<T>::PrintToFile() const{
	std::ofstream output_file;
	std::string file_name{ GetTitle() + "_" + GetDateStamp() + ".dat" };
	output_file.open(file_name);
	Print(output_file);
	output_file.close();
}

template <class T> T Experiment<T>::GetWeightedMean() const{
	if (data_.size() != 0 && data_[0]->GetNumVariables() == 1){
		T sum{ static_cast<T>(.0) };
		T denominator{ static_cast<T>(data_.size()) };
		for (auto it = data_.begin(); it < data_.end(); it++){
			T weight{ pow((*it)->GetTotalError(), static_cast<T>(-2.)) };
			sum += ((*it)->GetValue())*weight;
		}
		return sum / pow(GetMeanError(), static_cast<T>(-2.));
	}
	else{
		std::cerr << "Error: Experiment::GetWeightedMean() called on empty or multivariable experiment" << std::endl;
		return static_cast<T>(.0);
	}
}

template <class T> T Experiment<T>::GetMeanError() const{
	if (data_.size() != 0 && data_[0]->GetNumVariables() == 1){
		T sum{ static_cast<T>(.0) };
		T denominator{ static_cast<T>(data_.size()) };
		for (auto it = data_.begin(); it < data_.end(); it++){
			T error_2{ pow((*it)->GetTotalError(), static_cast<T>(-2.)) };
			sum += error_2;
		}
		return static_cast<T>(1.0) / pow(sum, static_cast<T>(.5));
	}
	else{
		std::cerr << "Error: Experiment::GetMeanError() called on empty or multivariable experiment" << std::endl;
		return static_cast<T>(.0);
	}
}

// Template class for user inputs to experiment, uses Experiment::AddMeasurement
// Template allows for the creation of different types, T, of measurement
template <class T> void Experiment<T>::UserNumericInput();

// Template function to create experiment from input file, uses Experiment::AddMeasurement
// Template allows for the creation of different types, T, of measurement
template <class T> void Experiment<T>::FileNumericInput(){
	std::ifstream input_file;
	OpenFile(input_file);

	std::cout << "Please input the title of your experiment:" << std::endl;
	std::getline(std::cin, title_);

	int no_variables{ 0 };
	std::string input_string; std::stringstream input_stream;
	do{
		std::cout << "Please enter the number of variables per measurement:" << std::endl;
		std::getline(std::cin, input_string);
	} while (!is_integer(input_string) || input_string == "0");

	input_stream.str(input_string); input_stream >> no_variables; input_stream.clear();

	std::vector<std::string> units_temp(no_variables); // create unit array

	// Lamda function to input units from std::getline user input
	int units_count{ 1 };
	std::for_each(units_temp.begin(), units_temp.end(),
		[&units_count](std::string& units_input) mutable {
		std::cout << "Please enter the units of variable " << units_count << ":" << std::endl;
		std::getline(std::cin, units_input); units_count++;
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

			measurement_temp.push_back(variable_temp); // store variable
		}

		AddMeasurement(std::make_shared<NumericMeasurement<T>>(units_temp, measurement_temp)); // store measurement
	}

	std::cout << "File read complete." << std::endl;

}

#endif