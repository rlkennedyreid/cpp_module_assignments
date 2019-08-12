// Robin Leaf kennedy-Reid (9436360)

#ifndef _PARTICLE_
#define _PARTICLE_

#include "vectorclasses.h"

// ############################################################################
// ########################### Class for Particles ############################
// ############################################################################

/*
C++ class for a relativistic particle. Particle member functions are a 4-vector
for spacetime position, a cartesian vector for beta, and a double for mass
of particle.

Parameterized constructor is defined, taking these as arguments

member functions are defined to return usual quantities, such as gamma factor
relativistic momentum and total energy
*/

class Particle
{
protected:
    double Mass_; // MeV/c^2
    FourVector Position_;
    CartesianVector Beta_;
public:
    // default constructor
    Particle() : Position_(), Beta_(), Mass_(0){
        //std::cout << "CV: Default constructor called\n";
    }
    // Parameterized constructor
    Particle(const double&, const FourVector&, const CartesianVector&);
    // Destructor
    ~Particle(){
        //std::cout << "P: Destructor called\n";
    }

    // Access functions
    double GetMass() const { return Mass_; }

    // Functions
    double GetGamma() const;
    double GetMomentum() const;
    double GetTotalEnergy() const;
};

// #################### Member Functions for Particle #########################
// parameterized constructor, using constructors of element classes
Particle::Particle(const double& mass, const FourVector& position, const CartesianVector& beta)
    : Mass_(mass), Position_(position),Beta_(beta){
    // Check physical
    double beta_2 = beta.GetDotProductWith(beta);
    if (beta_2 > 1.0 || mass < .0){
        std::cerr << "Error: Particle called with invalid beta or mass";
        exit(1); // abort if not
    }
}

double Particle::GetGamma() const {
    return 1. / pow(1. - Beta_.GetDotProductWith(Beta_), 0.5);
}

double Particle::GetMomentum() const {
    // Root dotproduct to get magnitude of beta
    double beta_scalar{ pow(Beta_.GetDotProductWith(Beta_), 0.5) };

    return Mass_*beta_scalar*(*this).GetGamma();
}

double Particle::GetTotalEnergy() const {

    // Square energies
    double momentum_energy_2 = pow((*this).GetMomentum(), 2);
    double mass_energy_2 = pow(Mass_, 2);

    return pow(mass_energy_2 + momentum_energy_2, 0.5);
}

#endif // _PARTICLE_