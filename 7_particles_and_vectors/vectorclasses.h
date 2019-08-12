#ifndef _VECTORCLASSES_
#define _VECTORCLASSES_

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

// ############################################################################
// ################### Class for Cartesian Vector #############################
// ############################################################################

/*
A C++ class for a general Cartesian vector with an arbitrary number of
components.

Paramaterized constructors and default constructors are defined, as well as
copy and move constructors to implement deep copying. Copy and move assigment
operators are also defined.

A function has been created to compute the dot product of two vectors, the +/-
operators overloaded for addition and subtraction of vectors, and the * operator
overloaded for multiplication by a scalar (double).

<< operator is overloaded for output of vectors.

Access functions for the member data are included (element access is implemented
via overload of [] operator. An access function that returns the vector itself
is implemented for use in the derived class, FourVector.
*/

class CartesianVector
{
    // friend function overloads insertion to output stream
    friend std::ostream& operator<<(std::ostream &os, const CartesianVector &vector);
    friend std::istream& operator>>(std::istream &is, CartesianVector &vector);
protected:
    double* vector_data_;
    int num_elements_;
public:
    // default constructor
    CartesianVector() : vector_data_(nullptr), num_elements_(0){
        //std::cout << "CV: Default constructor called\n";
    }
    CartesianVector(const int&); // Parameterized constructor
    CartesianVector(const CartesianVector&); // Copy constructor
    CartesianVector(CartesianVector&&); // Move constructor

    // Destructor
    ~CartesianVector(){
        //std::cout << "CV: Destructor called\n";
        delete[] vector_data_;
    }

    // Access functions
    int GetNumElements() const { return num_elements_; }
    double& operator[](const int&) const; // element access
    CartesianVector& GetCartesian(){ return *this; } // Return self for used in derived classes

    CartesianVector& operator=(const CartesianVector&); // Copy  Assignment operator
    CartesianVector& operator=(CartesianVector&&); // Move Assignment operator

    // Addition, subtraction, multiplication by scalar (prototypes)
    CartesianVector operator+(const CartesianVector&) const;
    CartesianVector operator-(const CartesianVector&) const;
    CartesianVector operator*(const double&) const;

    // dot product
    double GetDotProductWith(const CartesianVector&) const;

};

// #################### Member Functions for Cartesian Vector #################
// Parameterized constructor
CartesianVector::CartesianVector(const int& num){
    //std::cout << "CV: Parameterized constructor called\n";
    if (num > 1){
        // Create array, initialise elements to .0
        num_elements_ = num;
        vector_data_ = new double[num_elements_];
        for (int i{ 0 }; i < num_elements_; i++)
            vector_data_[i] = .0;
    }
    else{
        std::cerr << "Error: Invalid input to CartesianVector paramaterized constructor.\n";
        exit(1);
    }
}

// Copy constructor for deep copying
CartesianVector::CartesianVector(const CartesianVector& vector){
    //std::cout << "CV: Copy constructor called.\n";

    num_elements_ = vector.num_elements_;
    if (num_elements_ > 0){
        vector_data_ = new double[num_elements_];
        for (int i{ 0 }; i < num_elements_; i++)
            vector_data_[i] = vector.vector_data_[i];
    }
}

// Move constructor, clearing data from rvalue vector
CartesianVector::CartesianVector(CartesianVector&& vector){
    //std::cout << "CV: Move constructor called.\n";
    num_elements_ = vector.num_elements_;
    vector_data_ = vector.vector_data_;
    vector.num_elements_ = 0;
    vector.vector_data_ = nullptr;
}

// Copy assigment operator for deep copying
CartesianVector& CartesianVector::operator=(const CartesianVector& vector){
    //std::cout << "Assignment copy operator called\n";
    // Avoid self assignment
    if (&vector != this){
        delete[] vector_data_; vector_data_ = nullptr; // clear
        num_elements_ = vector.num_elements_; 

        if (num_elements_ > 0){
            vector_data_ = new double[num_elements_];
            for (int i{ 0 }; i < num_elements_; i++)
                vector_data_[i] = vector.vector_data_[i];
        }
    }
    return *this;
}

// Move assigment operator using swap, stealing data from rvalue vector
CartesianVector& CartesianVector::operator=(CartesianVector&& vector) {
    //std::cout << "Move assignment operator called.\n";
    std::swap(num_elements_, vector.num_elements_);
    std::swap(vector_data_, vector.vector_data_);
    return *this;
}

// Overload [] to access components
double& CartesianVector::operator[](const int& component) const {
    // Check for calls out of range
    if (component < 0 || component > num_elements_-1) {
        std::cerr << "Error: element call out of range.\n";
        exit(1);
    }
    return vector_data_[component];
}

// Overload + for vector addition
CartesianVector CartesianVector::operator+(const CartesianVector &vector) const{
    if (num_elements_ != vector.num_elements_){
        std::cerr << "Error: adding vectors with different dimensions.\n";
        exit(1);
    }
    CartesianVector temp{ num_elements_ };
    for (int i{ 0 }; i < num_elements_; i++)
        temp.vector_data_[i] = vector_data_[i] + vector.vector_data_[i];

    return temp;
}


// Overload - for vector subtraction
CartesianVector CartesianVector::operator-(const CartesianVector &vector) const{
    if (num_elements_ != vector.num_elements_){
        std::cerr << "Error: subtracting vectors with different dimensions.\n";
        exit(1);
    }

    CartesianVector temp{ num_elements_ };
    for (int i{ 0 }; i < num_elements_; i++)
        temp.vector_data_[i] = vector_data_[i] - vector.vector_data_[i];

    return temp;
}

// overlad * for multiplication of vector by a scalar (double)
CartesianVector CartesianVector::operator*(const double& number) const {
    CartesianVector temp{ num_elements_ };
    for (int i{ 0 }; i < num_elements_; i++)
        temp.vector_data_[i] = number*vector_data_[i];
    return temp;
}

// Dot product function
double CartesianVector::GetDotProductWith(const CartesianVector& vector) const {
    // checks

    if (num_elements_ == vector.num_elements_ && num_elements_ != 0){
        double temp{ .0 };
        for (int i{ 0 }; i < num_elements_; i++)
            temp += vector_data_[i] * vector.vector_data_[i];
        return temp;

    }
    else{
        std::cerr << "Error in CartesianVector::GetDotProductWith; Vectors may be empty or of different size" << std::endl;
        exit(1);
    }
}

// ###################### Friend Functions CartesianVector ####################
// overload insertion to output stream for cartesian vectors
std::ostream& operator<<(std::ostream &os, const CartesianVector &vector)
{
    if (vector.num_elements_ >= 1){
        os << "(";
        for (int i{ 0 }; i < vector.num_elements_; i++){
            if (i != vector.num_elements_ - 1)
                os << vector.vector_data_[i] << ",";
            else
                os << vector.vector_data_[i] << ")";
        }
    }
    else
        std::cerr << "Error: printing an empty vector." << std::endl;

    return os;
}

// ############################################################################
// ###################### Class for Minkowski 4-Vector ########################
// ############################################################################

/*
C++ class for a Minkowski Four-Vector, implemented as a specialisation of
the CartesianVector class. The 'zeroth' component of the four vector is
stored as a double in the member data of the new class, and the spatial
components as a 3 dimensional CartesianVector.

Copy/move constructors and copy/move assigment operators are defined, as in
CartesianVector. Two parameterized constructors are defined for both 4
explicit double components as the argument, and a double and a 3D CartesianVector
argument.

The dot product function has been overriden in this class to compute the
proper dot product for Minkowski vectors.

<< operator similarly overloaded as in the CartesianVector class.
*/

class FourVector : public CartesianVector
{
    friend std::ostream& operator<<(std::ostream &os, const FourVector &vector);
    friend std::istream& operator>>(std::istream &is, FourVector &vector);
protected:
    double zeroth_component_;
public:
    // default constructor
    FourVector() : CartesianVector(3), zeroth_component_(.0){
        //std::cout << "4V: Default constructor called\n";
    }
    // Parameterized constructors
    FourVector(const double&, const double&, const double&, const double&); // explicit components
    FourVector(const double&, const CartesianVector&); // given double and Cartesian Vector

    // Destructor, memory deleted in base class
    ~FourVector(){
        //std::cout << "4V: Destructor called\n";
    }

    FourVector(const FourVector&); // Copy constructor
    FourVector(FourVector&&); // Move constructor

    double& operator[](const int); // element access


    FourVector& operator=(const FourVector&); // Copy  Assignment operator
    FourVector& operator=(FourVector&&); // Move Assignment operator

    // Addition, subtraction (prototype)
    FourVector operator+(const FourVector&) const;
    FourVector operator-(const FourVector&) const;

    // dot product
    double GetDotProductWith(const FourVector&) const;

    FourVector GetLorentzBoost(CartesianVector&);
};

// #################### Member Functions for 4 Vector #########################
// PARAMETERIZED CONSTRUCTORS
FourVector::FourVector(const double& t, const double& i, const double& j, const double& k)
    : zeroth_component_(t), CartesianVector(3) {
    //std::cout << "4V: Parameterized constructor 1 called\n";
    vector_data_[0] = i; vector_data_[1] = j; vector_data_[2] = k;
}

FourVector::FourVector(const double& t, const CartesianVector& r)
    : zeroth_component_(t), CartesianVector(r) {
    //std::cout << "4V: Parameterized constructor 2 called\n";
    if (num_elements_ != 3){
        std::cerr << "Error: Cartesian vector has wrong dimension in FourVector constructor.\n";
        exit(1);
    }
}

// Copy constructor for deep copying
FourVector::FourVector(const FourVector& vector)
    : zeroth_component_(vector.zeroth_component_){
    //std::cout << "4V: Copy constructor called.\n";
    // deep copy
    num_elements_ = 3;
    vector_data_ = new double[3];

    for (int i{ 0 }; i < num_elements_; i++)
        vector_data_[i] = vector.vector_data_[i];
}

// Move constructor, clearing data from rvalue vector
FourVector::FourVector(FourVector&& vector){
    //std::cout << "4V: Move constructor called.\n";

    std::swap(num_elements_, vector.num_elements_);
    std::swap(vector_data_, vector.vector_data_);
    std::swap(zeroth_component_, vector.zeroth_component_);
}

// Overload [] to access components
double& FourVector::operator[](const int component) {
    if (component < 0 || component > 3) {
        std::cerr << "Error: element call out of range.\n";
        exit(1);
    }
    else if (component == 0) {
        return zeroth_component_;
    }
    else{
        return vector_data_[component - 1];
    }
}

// Copy assigment operator for deep copying
FourVector& FourVector::operator=(const FourVector& vector){
    //std::cout << "Assignment copy operator called\n";
    //avoid self assignment
    if (&vector != this){
        delete[] vector_data_; vector_data_ = nullptr;
        zeroth_component_ = 0.; // clear

        zeroth_component_ = vector.zeroth_component_;
        num_elements_ = 3;
        vector_data_ = new double[3];
        for (int i = 0; i < 3; i++)
            vector_data_[i] = vector.vector_data_[i];
    }
    return *this;
}

// Move assigment operator using swap, stealing data from rvalue vector
FourVector& FourVector::operator=(FourVector&& vector) {
   // std::cout << "Move assignment operator called.\n";

    std::swap(num_elements_, vector.num_elements_);
    std::swap(vector_data_, vector.vector_data_);
    std::swap(zeroth_component_, vector.zeroth_component_);

    return *this;
}

// Overload + for vector addition
FourVector FourVector::operator+(const FourVector &vector) const{
    FourVector temp;
    temp.zeroth_component_ = zeroth_component_ + vector.zeroth_component_;
    for (int i = 0; i < 3; i++)
        temp.vector_data_[i] = vector_data_[i] + vector.vector_data_[i];
    return temp;
}

// Overload - for vector subtraction
FourVector FourVector::operator-(const FourVector &vector) const{
    FourVector temp;
    temp.zeroth_component_ = zeroth_component_ - vector.zeroth_component_;
    for (int i = 0; i < 3; i++)
        temp.vector_data_[i] = vector_data_[i] - vector.vector_data_[i];
    return temp;
}

// ###################### Member Functions FourVector #########################

// Dot product function
double FourVector::GetDotProductWith(const FourVector& vector) const{
	double spatial{ .0 };

	for (int i = 0; i < num_elements_; i++)
		spatial += vector_data_[i] * vector.vector_data_[i];

	return  zeroth_component_ * vector.zeroth_component_ - spatial;
}

FourVector FourVector::GetLorentzBoost(CartesianVector& beta) {
    // Preliminaries for calculation
    double beta_2 = beta.GetDotProductWith(beta);
    if (beta_2 > 1.){
        std::cerr << "Beta > 1 in GetLorentzBoost" << std::endl;
        exit(1);
    }
    double gamma = 1. / pow(1. - beta_2, 0.5);

    // Extract the three vector from the particle 4-vector
    CartesianVector spatial_vector = (*this).GetCartesian();

    // Define terms for ease of calculation
    double beta_dot_r = beta.GetDotProductWith(spatial_vector);
    double multiplication_term = (beta_dot_r*(gamma - 1.) / beta_2) - gamma*(*this)[0];

    // Compute the new components
    double new_zeroth{ gamma*((*this)[0] - beta_dot_r) };
    CartesianVector new_three_vector = spatial_vector + beta*multiplication_term;

    // Use paramterized constructor to return the boosted 4 vector
    return FourVector{ new_zeroth, new_three_vector };
}

// ###################### Friend Functions FourVector #########################
// overload insertion to output stream for four vectors
std::ostream& operator<<(std::ostream &os, const FourVector &vector)
{
    if (vector.num_elements_ == 0)
        std::cerr << "Error: printing an empty vector.\n";
    else{
        os << "(" << vector.zeroth_component_ << ", "; // print first component
        for (int i{ 0 }; i < 3; i++){
            if (i != 2) // format last element differently
                os << vector.vector_data_[i] << ", ";
            else
                os << vector.vector_data_[i] << ")";
        }
    }
    return os;
}


#endif // _VECTORCLASSES_