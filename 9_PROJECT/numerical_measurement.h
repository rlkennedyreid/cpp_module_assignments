#ifndef NUMERIC_MEASUREMENT_H
#define NUMERIC_MEASUREMENT_H

/*
DERIVED TEMPLATE CLASS FOR NUMERIC MEASUREMENT

- 'Measurements' are assumed to be numerical value, with two error sources;
systematic and measurement.

- This is constrained by using a 3-element array for values and their errors

- Vector of arrays is used to allow for measurements of multiple values.
e.g. voltage and current, x-y-z coordinates etc. <array> container is used, rather
than the standard, for use of iterators to pass over values

- Template allows for different numerical types, such as float, double, long double etc.
*/

#include<vector>
#include<array>
#include<iomanip>
#include "base_measurement.h"

namespace num_measurement {

	template <class T> class NumericMeasurement : public base_measurement::Measurement<T> {
	private:
		std::vector< std::array<T, 3> > data_;
		std::vector< std::string > units_;
	public:
		NumericMeasurement(); // Default constructor

		// PARAMETERIZED CONSTRUCTORS
		NumericMeasurement(std::vector< std::string >, std::vector< std::array<T, 3> >&); // General measurement
		NumericMeasurement(std::string, const T&, const T&, const T&); // 1 variable, 2 errors

		NumericMeasurement(const NumericMeasurement&); // Copy Constructor
		NumericMeasurement(NumericMeasurement&&); // Move Constructor

		std::string GetTimestamp() const;

		int GetNumVariables() const;

		void Print(std::ostream&) const;

		std::string GetUnits(const int) const;

		T GetValue() const{
			if (data_.size() == 1)
				return data_[0][0];
			else{
				std::cerr << "ERROR: NumericMeasurement::GetValue() called on empty or multi-variable measurement!" << std::endl;
				exit(1);
			}
		}

		T GetTotalError() const{
			if (data_.size() == 1)
				return data_[0][1] + data_[0][2];
			else{
				std::cerr << "ERROR: NumericMeasurement::GetValue() called on empty or multi-variable measurement!" << std::endl;
				exit(1);
			}
		}


		// Destructor
		~NumericMeasurement(){}
	};


	// #################### Member Functions for Numeric Measurement #################

	// Default constructor, calls Measurement() to intiate timestamp_
	template <class T> NumericMeasurement<T>::NumericMeasurement() : Measurement(){}

	// Parameterized constructor for a vector of units and a vector of variable
	template <class T> NumericMeasurement<T>::NumericMeasurement(std::vector< std::string > units, std::vector< std::array<T, 3> >& input_vector)
		: data_(input_vector), units_(units), Measurement() {

		// Ensure the number of units given matches the number of variables, exit if not
		if (data_.size() != units_.size()){
			std::cerr << "Error: Size of vector of units and vector of variables do not match" << std::endl;
			exit(1);
		}
	}

	// Parameterized constructor for simple measurement, error checking as above not present as units_ & data_ match assured
	template <class T> NumericMeasurement<T>::NumericMeasurement(std::string units, const T& value, const T& sys_error, const T& meas_error)
		: Measurement(), data_({ { value, sys_error, meas_error } }), units_({ units }) {}

	/*// Copy Constructor - deep copy
	template <class T> NumericMeasurement<T>::NumericMeasurement(const NumericMeasurement& input) : data_(input.data_), units_(input.units_) {
		timestamp_ = input.timestamp_;
	}

	// Move Constructor
	template <class T> NumericMeasurement<T>::NumericMeasurement(NumericMeasurement&& input) : data_(input.data_), units_(input.units_){
		timestamp_ = input.timestamp_; input.data_.clear(); input.units_.clear();
	}*/

	// Return formatted date as string type, using strftime and time_t data member
	template <class T> std::string NumericMeasurement<T>::GetTimestamp() const{
		tm timeinfo; localtime_s(&timeinfo, &timestamp_); // input time_t data in tm type
		// input formatted data in char array
		char time[9]; strftime(time, sizeof time, "%H:%M:%S", &timeinfo);
		return time;
	}

	// Member function to return units for a variable in measurement, given by index
	template <class T> std::string NumericMeasurement<T>::GetUnits(const int index) const{
		int size{ static_cast<int>(units_.size()) }; // signed/unsigned mismatch
		// check index is in range
		if (index < size)
			return units_[index];
		// Used in printing reports, so exit if incorrect
		else{
			std::cerr << "Error: Call to units_ vector in NumericMeasurement out of range" << std::endl;
			return "Error: NumericMeasurement<T>::GetUnits";
		}
	}

	// Return number of variables
	template <class T> int NumericMeasurement<T>::GetNumVariables() const{ return data_.size(); }

	// Print measurements and their errors into an ostream, can be eg cout of fstream
	template <class T> void NumericMeasurement<T>::Print(std::ostream& os) const{
		// Check if data exists
		if (data_.size() != 0){
			// Print each variable and errors in order, setw(20) used to match printing in Experiment class
			for (auto row = (data_).begin(); row < (data_).end(); row++){
				for (auto col = row->begin(); col < row->end(); col++)
					os << std::setw(20) << *col;
				os << std::setw(20);
			}
			os << this->GetTimestamp();
		}
		// Exit if no data input, indicating error
		else
			std::cerr << "Error: Empty data_ in NumericMeasurment::Print" << std::endl;
	}

} // namespace num_measurement
#endif