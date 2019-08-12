#include "rectangle.h"

// Printing messages in constructors for demonstration
Rectangle::Rectangle() : height_(.0), width_(.0) {
    std::cout << "Rectangle: Default constructor called" << std::endl;
}

Rectangle::Rectangle(const double& height, const double& width) : height_(height), width_(width) {
    std::cout << "Rectangle: Parameterised constructor called" << std::endl;
}

double Rectangle::GetArea() const{
    return height_*width_;
}

double Rectangle::GetVolume() const{
    return .0; // 2D
}

std::string Rectangle::PrintType() const{
    return "Rectangle";
}