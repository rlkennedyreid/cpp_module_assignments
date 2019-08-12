#ifndef BASE_MEASUREMENT_H
#define BASE_MEASUREMENT_H

/*
ABSTRACT BASE CLASS FOR MEASUREMENT

- The only member data assumed to be common to all measurements is a timestamp,
which is implemented as a time_t value. This 'raw time' value can then be
printed in various ways using member functions, depending on need

- Base class constructor is defined, purely to initiate timestamp to the
current time (at time of construction). Is protected to ensure it can only be called
in derived classes

- Pure virtual access functions implemented for obvious usage, such as printing
measurement or timestamp, or giving 'type' identifier etc.
*/

#include <string>
#include <iostream>
#include <ctime> // timestamps

namespace base_measurement {

	template <class T> class Measurement {
	protected:
		time_t timestamp_;
		Measurement() : timestamp_(time(nullptr)) {}
	public:
		// Destructor
		virtual ~Measurement(){};

		// Printing value into some general ostream
		virtual void Print(std::ostream&) const = 0;

		virtual std::string GetTimestamp() const = 0;

		virtual std::string GetUnits(const int) const = 0;

		virtual int GetNumVariables() const = 0;

		virtual T GetValue() const = 0;
		virtual T GetTotalError() const = 0;


	};

} // namespace base_measurement

#endif