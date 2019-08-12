#define _USE_MATH_DEFINES

#include "ellipse.h"

// Printing messages in constructors for demonstration
Ellipse::Ellipse() : minor_axis_(.0), major_axis_(.0) {
    std::cout << "Ellipse: Default constructor called" << std::endl;
}

Ellipse::Ellipse(const double& minor, const double& major) : minor_axis_(minor), major_axis_(major) {
    std::cout << "Ellipse: Parameterised constructor called" << std::endl;
}

double Ellipse::GetArea() const{
    return M_PI * minor_axis_ * major_axis_;
}

double Ellipse::GetVolume() const{
    return .0;
}

std::string Ellipse::PrintType() const{
    return "Ellipse";
}