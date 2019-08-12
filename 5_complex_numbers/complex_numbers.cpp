// PHYS 30762 Programming in C++
// Assignment 5 - Class for Complex numbers
// Robin Leaf Kennedy-Reid (9436360)

#include<iostream>
#include<cmath>
#include<string>
using namespace std;

/*
-----------------------CLASS FOR COMPLEX NUMBERS-------------------------------
- This class uses operator overloads to implement basic operations between
complex numbers.

- Member functions are also used to call many of the common variables
associated with complex numbers, such as the modulus and principle argument.

- Friend functions have been used to overload the input/output operators for
printing ComplexNumber objects, as well as take them from user input,
with assumptions of input format. */

class ComplexNumber
{
	// Functions to overload insertion/extraction operators
	friend ostream& operator<<(ostream &os, const ComplexNumber &z);
	friend istream& operator>>(istream &is, ComplexNumber &z);
private:
	double re_, im_; // components
public:
	// Constructors & destructor
	ComplexNumber() : re_(.0), im_(.0) {}
	ComplexNumber(double real, double imaginary) : re_(real), im_(imaginary) {}
	~ComplexNumber(){}

    //--------------------- ACCESS FUNCTIONS-----------------------------------
	const double GetReal() const{ return re_; } // Return real component
	
	double GetImag() const{ return im_; } // Return imaginary component
	
	double GetModulus() const{ 
        return sqrt( pow(re_, 2) + pow(im_, 2) ); // Return modulus
        }
	// Return argument
	double GetArgument() const{ return atan2( im_, re_ ); };

	// Return Complex conjugate
	ComplexNumber Conjugate() const{ ComplexNumber temp(re_, -im_); return temp; }

    //----------------------OVERLOADS------------------------------------------
	// Overload + operator for addition 
	ComplexNumber operator+(const ComplexNumber &z) const{
		ComplexNumber temp(re_ + z.re_, im_ + z.im_); return temp;
	}

	// Overload - operator for subtraction
	ComplexNumber operator-(const ComplexNumber &z) const{
        ComplexNumber temp(re_ - z.re_, im_ - z.im_); return temp;
	}

	// Overload * operator for multiplication, z1*z2
	ComplexNumber operator*(const ComplexNumber &z) const{
		ComplexNumber temp(re_*z.re_ - im_*z.im_, re_*z.im_ + im_*z.re_);
        return temp;
	}

	// Overload / operator for division, z1/z2
	ComplexNumber operator/(const ComplexNumber &z) const{
		if (z.re_ == .0 && z.im_ == .0){ // Warn for bad inputs
			cout << "Warning! Dividing by 0" << endl;
            ComplexNumber temp;
			return temp; // output default Complex
		}
		else{
			double div{ pow(z.re_, 2) + pow(z.im_, 2) }; // streamline next line
			ComplexNumber temp((re_*(z.re_) + im_*(z.im_)) / div, (im_*(z.re_) - re_*(z.im_)) / div);
			return temp;
		}
	}
};

// Function to overload << operator for ComplexNumber class
ostream& operator<<(ostream &os, const ComplexNumber &z){
    if(z.im_ > .0)
        os << z.re_ << '+' << z.im_ << 'i'; // add a '+' for +ve im_
    else
	    os << z.re_ << z.im_ << 'i'; // '-' already generated
	return os;
}

// Function to overload >> operator for for ComplexNumber class
// Assumes the form a+ib or a-ib
istream& operator>>(istream &is, ComplexNumber &z){
	string input; // hold full input
	int i_pos;  // where 'i' is

	getline(is, input);

    i_pos = input.find_first_of("i");

    // Tests for invalid input (i not present)
    if(i_pos == string::npos){ z.re_ = z.im_ = .0; return is; }

    else{
        // Real part is from start to the character before i
        z.re_ = stod( input.substr(0, i_pos - 1) );

        // Imaginary part requires checking the sign
        if (input[i_pos - 1] == '+')
            z.im_ = stod( input.substr(i_pos + 1, input.size() - i_pos - 1) );
        else
            z.im_ = -stod( input.substr(i_pos + 1, input.size() - i_pos - 1) );

	    return is;
    }
}

int main()
{
	cout.precision(3);

	// CREATE TWO COMPLEX NUMBERS WITH PARAMETERISED CONSTRUCTOR, ONE DEFAULT
	ComplexNumber a(3, 4), b(1, -2), input;

	// DEMONSTRATE OVERLOADED <<
	cout << "Our starting vectors are a = " << a << " and b = " << b << endl;

    // DEMONSTRATE MEMBER FUNCTIONS
	cout << "Re(a)\t= "  << a.GetReal()     << "\t\tRe(b)\t= "    << b.GetReal()     << endl
	     << "Im(a)\t= "  << a.GetImag()     << "\t\tIm(b)\t= "    << b.GetImag()     << endl
	     << "|a|\t= "    << a.GetModulus()  << "\t\t|b|\t=  "     << b.GetModulus()  << endl
         << "arg(a)\t= " << a.GetArgument() << " rad\targ(b)\t= " << b.GetArgument() << " rad" << endl
	     << "a*\t=  "    << a.Conjugate()   << "\t\tb*\t=  "      << b.Conjugate()   << endl;

	// DEMONSTRATE OVERLOADS
	cout << "\na+b = " << a+b << endl << "a-b = " << a - b << endl
	     << "a*b = "   << a*b << endl << "a/b = " << a / b << endl;

	// DEMONSTRATE OVERLOADED >>
	cout << "\nPlease input a complex number in the form x(+/-)iy, no spaces: ";

	cin >> input;

	// PRINT INPUTTED VECTOR, ALONG WITH MORE DEMOS OF MEMBER FUNCTIONS
	cout << "Input\t= "  << input               << endl
		 << "Re(z)\t= "  << input.GetReal()     << endl
		 << "Im(z)\t= "  << input.GetImag()     << endl
		 << "|z|\t=  "   << input.GetModulus()  << endl
		 << "arg(z)\t= " << input.GetArgument() << " rad" << endl
		 << "z*\t=  "    << input.Conjugate()   << endl;

	return 0;
}