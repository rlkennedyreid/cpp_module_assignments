#include "prism.h"

// Printing messages in constructors for demonstration
Prism::Prism() : depth_(.0), base_(nullptr) {
    std::cout << "Prism: Default constructor called" << std::endl;
}

Prism::Prism(const double& depth, Shape* base) : depth_(depth), base_(base) {
    std::cout << "Prism: Parameterised constructor called" << std::endl;
}

double Prism::GetArea() const {
    return 0.; // Not possible for general shape
}

double Prism::GetVolume() const{
    return depth_ * ( base_->GetArea() );
}

std::string Prism::PrintType() const{
    return "Prism (" + (base_->PrintType()) + " base)";
}