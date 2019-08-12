#include "square.h"

// Printing messages in constructors for demonstration
Square::Square() : Rectangle() {
    std::cout << "Square: Default constructor called" << std::endl;
}

Square::Square(const double& length) : Rectangle(length, length) {
    std::cout << "Square: Parameterised constructor called" << std::endl;
}

double Square::GetArea() const{
    return height_*width_;
}

double Square::GetVolume() const{
    return .0; // 2D
}

std::string Square::PrintType() const{
    return "Square";
}