#define _USE_MATH_DEFINES

#include "ellipsoid.h"

// Printing messages in constructors for demonstration
Ellipsoid::Ellipsoid() : a_(.0), b_(.0), c_(.0) {
    std::cout << "Ellipsoid: Default constructor called" << std::endl;
}

Ellipsoid::Ellipsoid(const double& a, const double& b, const double& c)
    : a_(a), b_(b), c_(c) {
    std::cout << "Ellipsoid: Parameterised constructor called" << std::endl;
}

// Approximate formula
double Ellipsoid::GetArea() const{
    double ab_16{ pow(a_*b_, 1.6) };
    double ac_16{ pow(a_*c_, 1.6) };
    double bc_16{ pow(b_*c_, 1.6) };
    double temp{ pow((ab_16 + ac_16 + bc_16) / 3, 1 / 1.6) };
    return 4 * M_PI * temp;
}

double Ellipsoid::GetVolume() const{
    return (4. / 3.) * M_PI * a_ * b_ *c_;
}

std::string Ellipsoid::PrintType() const{
    return "Ellipsoid";
}