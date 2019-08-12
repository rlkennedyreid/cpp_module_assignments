
// PHYS30762 - Programming in C++
// Assignment 4
// Robin Leaf Kennedy-Reid (9436360)
// Submitted 01/03/2017

// SIMPLE DEMONSTRATION OF C++ CLASS FEATURES

// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;

// enum to define simplified inputs for hubble types
enum HUBBLE_TYPE {
	// Ellipticals
	E0, E1, E2, E3, E4, E5, E6, E7,
	// Spirals
	S0, Sa, Sb, Sc,
	// Barred spirals
	SB0, SBa, SBb, SBc,
	// Irregulars
	Irr,
	// Blank
	BLANK
};

// Function that returns a string for elements in HUBBLE_TYPE (for use in printing)
const string GetHubbleType(HUBBLE_TYPE type){
	switch (type){
		// Ellipticals
	case E0: return "E0"; break; case E1: return "E1"; break;
	case E2: return "E2"; break; case E3: return "E3"; break;
	case E4: return "E4"; break; case E5: return "E5"; break;
	case E6: return "E6"; break; case E7: return "E7"; break;
		// Spirals
	case S0: return "S0"; break; case Sa: return "Sa"; break;
	case Sb: return "Sb"; break; case Sc: return "Sc"; break;
		// Barred spirals
	case SB0: return "SB0"; break; case SBa: return "SBa"; break;
	case SBb: return "SBb"; break; case SBc: return "SBc"; break;
		// Irregulars
	case Irr: return "Irr"; break;
		// Blank/errors
	case BLANK: return "BLANK"; break; default: return "ERROR"; break;
	}
}

// Galaxy class definition
class Galaxy
{
private:
	// variables for galaxy properties and vector of galaxy objects for satellites
	HUBBLE_TYPE hubble_type_;
	double redshift_, total_mass_, stellar_mass_fraction_;
	vector<Galaxy> satellites_;
public:
	// Default constructor
	Galaxy() :
		hubble_type_(BLANK), redshift_(.0), total_mass_(.0), stellar_mass_fraction_(.0){}
	// Prototype function for paramaterized constructor
	Galaxy(HUBBLE_TYPE ptype, double pshift, double ptotal_mass, double pfraction);
	// Destructor
	~Galaxy(){}
	// Return stellar mass
	double GetStellarMass() { return stellar_mass_fraction_ * total_mass_; }

	// Change galaxy's Hubble type
	void ChangeType(HUBBLE_TYPE new_type) { hubble_type_ = new_type; }
	// Prototype for function to print out an object's data
	void PrintGalaxy();
	// Add satellite galaxy
	void AddSatellite(Galaxy satellite) { satellites_.push_back(satellite); }
};

// paramaterized constructor, tests for invalid inputs.
// if found, declare a default galaxy and output  awarning
Galaxy::Galaxy(HUBBLE_TYPE ptype, double pshift, double pmass, double pfraction){
	if (pshift < .0 || pshift > 10){
		cout << "Invalid input! Red shift should be in range [0,10]\n";
		hubble_type_ = BLANK; redshift_ = .0; total_mass_ = .0; stellar_mass_fraction_ = .0;
	}
	else if (pmass < 1e7 || pmass > 1e12){
		cout << "Invalid input! Red shift should be in range [1e7,1e12]\n";
		hubble_type_ = BLANK; redshift_ = .0; total_mass_ = .0; stellar_mass_fraction_ = .0;
	}
	else if (pfraction < 0 || pfraction > .05){
		cout << "Invalid input! Red shift should be in range [1e7,1e12]\n";
		hubble_type_ = BLANK; redshift_ = .0; total_mass_ = .0; stellar_mass_fraction_ = .0;
	}
	else{
		hubble_type_ = ptype; redshift_ = pshift; total_mass_ = pmass;
		stellar_mass_fraction_ = pfraction; // Valid galaxy is declared here
	}
}

// Print out an object's data, if the galaxy object has satellites, print also
void Galaxy::PrintGalaxy(){
	// No satellites
	if (satellites_.size() == 0){
		setprecision(3);
		cout << "[Type, Shift, Mass, f*] = [" << GetHubbleType(hubble_type_) <<
			", " << redshift_ << ", " << total_mass_ << ", "<<
			stellar_mass_fraction_ << "]\n";
	}
	else {
		setprecision(3);
		cout << "[Type, Shift, Mass, f*] = [" << GetHubbleType(hubble_type_) <<
			", " << redshift_ << ", " << total_mass_ << ", " <<
			stellar_mass_fraction_ << "]\n\n";
		// Print satellites
		cout << "This Galazy has " << satellites_.size() << " satellites:\n";
		for (auto iter = satellites_.begin(); iter < satellites_.end(); ++iter)
			iter->PrintGalaxy();
		cout << endl;
	}
	return;
}

// Main program
int main()
{
	//vector of particles
	vector<Galaxy> galaxy_data;

	// Set values for two particles
	// Example using default constructor
	galaxy_data.push_back(Galaxy());

	// Example using paramaterized constructor
	galaxy_data.push_back(Galaxy(SBc, .0, 4.8e11, 0.01));

	// print out data
	cout << "Printed data for default and paramaterized constructor\n";
	for (auto iter = galaxy_data.begin(); iter < galaxy_data.end(); ++iter)
		iter->PrintGalaxy();

	// Get and print out stellar mass
	cout << "\nStellar mass of paramaterized galaxy is "
		<< galaxy_data[1].GetStellarMass() << " Solar Masses" << endl;

	// Change Hubble type
	galaxy_data[1].ChangeType(Irr);
	cout << "\nChanged Hubble type for paramaterized galaxy:\n";
	galaxy_data[1].PrintGalaxy();

	// Add default satellite galaxies
	galaxy_data[1].AddSatellite(Galaxy());
	galaxy_data[1].AddSatellite(Galaxy());
	galaxy_data[1].AddSatellite(Galaxy());
	galaxy_data[1].AddSatellite(Galaxy());

	// Print result
	cout << "\n4 default galaxies added to paramaterized galaxy:\n";
	galaxy_data[1].PrintGalaxy();

	return 0;
}