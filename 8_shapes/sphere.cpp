#define _USE_MATH_DEFINES

#include "sphere.h"

// Printing messages in constructors for demonstration
Sphere::Sphere() : Ellipsoid() {
    std::cout << "Sphere: Default constructor called" << std::endl;
}

Sphere::Sphere(const double& radius) : Ellipsoid(radius, radius, radius) {
    std::cout << "Sphere: Parameterised constructor called" << std::endl;
}

double Sphere::GetArea() const{
    return 4.0 * M_PI * pow(a_, 2);
}

double Sphere::GetVolume() const{
    return (4. / 3.) * M_PI * pow(a_, 3.);
}

std::string Sphere::PrintType() const{
    return "Sphere";
}