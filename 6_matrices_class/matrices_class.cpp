// PHYS 30762 Programming in C++
// Assignment 6
// Robin Leaf kennedy-Reid (9436360)

/* 
	A C++ class for Matrices: The class contains the element data of the matrices
	(stored in a 1D array of doubles), as well as the number of rows and columns.

	Copy and move constructors have been defined, as well as overloads
	for the assignment operators that create deep copies of data from lvalues or
	steal data from rvalues.

	Destructor is defined and deletes memory allocated for array.

	A friend function has been defined to overload insertion and insertion
	operators that print Matrix data and take in manually input matrices

	The class has defined within it a member functions to calculate the determinant
	of the calling Matrix recursively using method of minors.

	int main() here demonstrates the use of all of these features.
*/

#include<iostream>
#include<cmath>
#include<string>

using namespace std;

class Matrix
{
	// friend function overloads insertion to output stream
	friend ostream& operator<<(ostream &os, const Matrix&);
	friend istream& operator>>(istream &is, Matrix&);
private:
	double* elements_;
	int rows_, columns_;
public:
	// Default constructor
	Matrix() : elements_(nullptr), rows_(0), columns_(0){
		cout << "Default constructor called\n";
	}
	Matrix(int, int); // Parameterized constructor
	Matrix(Matrix&); // Copy constructor
	Matrix(Matrix&&); // Move constructor
	~Matrix(){ cout << "Destructor called\n"; delete[] elements_; } // Destructor

	// Access functions
	int GetRows() const{ return rows_; }
	int GetColumns() const { return columns_; }
	int Index(const int,const int) const;

	// Overload () to access elements of Matrix
	double& operator()(const int i, const int j) const{
		return elements_[(j-1) + (i-1)*columns_];
		}

	Matrix& operator=(Matrix&); // Copy  Assignment operator
	Matrix& operator=(Matrix&&); // Move Assignment operator

	// Addition, subtraction and multiplication (prototypes)
	Matrix operator+(const Matrix&) const;
	Matrix operator-(const Matrix&) const;
	Matrix operator*(const Matrix&) const;

	// determinant
	double GetDeterminant() const;
	// Function to calculate minor, assumes removal of first row
	Matrix GetMinorMatrix(const int, const int) const;
};

//--------------Member functions defined outside class ------------------------

// Function to return 1D array index given standard matrix (i,j) index
// used to shorten code in some member functions, and also bounds check
int Matrix::Index(const int i, const int j) const {
	// check valid input
	if(i <= rows_ && j <= columns_ && i > 0 && j > 0)
		return (j-1) + (i-1)*columns_;
	// abort otherwise
	else {
		cerr << "Matrix::Index called out of range" << endl;
		exit(1);
	}
}

// Parameterized constructor, matrix of zeros dimension
Matrix::Matrix(int rows, int columns) {
	cout << "Parameterized constructor called" << endl;
	// check valid input
	if(rows >= 1 && columns >= 1){
		// Create array
		rows_ = rows; columns_ = columns; elements_ = new double[rows*columns];
		// Initialise zeros for the array
		for(int i{0}; i < (rows*columns); i++)
			elements_[i] = .0;
	}
	// Abort otherwise
	else{
		cerr << "Error: rows/columns < 1 in parameterized constructor" << endl;
		exit(1);
		}

}

// Copy constructor for deep copying
Matrix::Matrix(Matrix& mat){
	cout << "Copy constructor called" << endl;
	delete[] elements_; elements_ = nullptr; // clear
	// Deep copy assign
	rows_ = mat.rows_; columns_ = mat.columns_;
	if(rows_ > 0 && columns_ > 0){
		elements_ = new double[rows_*columns_];
		for (int i{0}; i < rows_*columns_; i++)
			elements_[i] = mat.elements_[i];
	}
}

// Move constructor
Matrix::Matrix(Matrix&& mat){
	// Steal data
	cout << "Move constructor called" << endl;
	swap(rows_, mat.rows_);
	swap(columns_, mat.columns_);
	swap(elements_, mat.elements_);
}

// Assignment operator for deep copying
Matrix& Matrix::operator=(Matrix& mat){
	cout << "Assignment copy called" << endl;
	// avoid self-assignment
	if(&mat != this){
		// clear data
		delete[] elements_; elements_ = nullptr;
		rows_ = 0; columns_ = 0;
		// deep copy from mat
		rows_ = mat.rows_; columns_ = mat.columns_;
		if (rows_ > 0 && columns_ > 0){
			elements_ = new double[rows_*columns_];
			for (int i{0}; i < rows_*columns_; i++)
				elements_[i] = mat.elements_[i];
		}
	}
	return *this;
}

// Move assignment operator
Matrix& Matrix::operator=(Matrix&& mat){
	// Steal data
	cout << "Move assignment operator called" << endl;
	swap(rows_, mat.rows_);
	swap(columns_, mat.columns_);
	swap(elements_, mat.elements_);
	return *this;
}

//------------------------overloads for Matrices class-------------------------

// Overload + for matrix addition
Matrix Matrix::operator+(const Matrix& mat) const{
	Matrix temp(rows_, columns_); // new matrix
	// check matrices same size
	if (rows_ == mat.rows_ && columns_ == mat.columns_){
		for (int i {0}; i < rows_*columns_; i++)
			temp.elements_[i] = (*this).elements_[i] + mat.elements_[i];
		return temp;
	}
	else{
		cerr << "Error: Adding matrices of different sizes" << endl;
		exit(1);
	}
}

// Overload - for matrix addition
Matrix Matrix::operator-(const Matrix& mat) const{
	Matrix temp(rows_, columns_);// new matrix
	// check matrices same size
	if (rows_ == mat.rows_ && columns_ == mat.columns_){
		for (int i = 0; i < rows_*columns_; i++)
			temp.elements_[i] = (*this).elements_[i] - mat.elements_[i];
		return temp;
	}
	else{
		cerr << "Error: Subtracting matrices of different sizes" << endl;
		exit(1);
	}
}

// Overload * for matrix multiplication
Matrix Matrix::operator*(const Matrix &mat) const{
	// Create temp matrix for result with valid dimensions
	Matrix temp(rows_, mat.columns_);
	// Check multiplication is possible
	if (columns_ == mat.rows_){
		for (int i {1}; i <= temp.rows_; i++){
			for (int j {1}; j <= temp.columns_; j++){
				double sum = .0; // variable to store element data, reset each element
				for (int k {1}; k <= columns_; k++)
					// Index used to bounds check multiplication
					sum += elements_[(*this).Index(i, k)] * mat.elements_[mat.Index(k, i)];
				temp(i, j) = sum; // apply element, carry on to next
			}
		}
	}
	else{
		cout << "Error: columns of A do not match rows of B in Matrix::operator*()" << endl;
		exit(1);
	}
	return temp;
}

// Function to return matrix with row input row and column removed
// used in GetDeterminant() recursive calculation
Matrix Matrix::GetMinorMatrix(const int removed_i, const int removed_j) const{
	// Check for square matrix with more than 1 element

    if (rows_ == columns_ || rows_ != 1 || columns_ !=1){
		// Create the minor matrix; row/column removed by ignoring with continue
		Matrix minor_matrix(rows_ - 1, columns_ - 1);
		// assign elements
		for (int i {1}; i <= rows_; i++){
			for (int j {1}; j <= columns_; j++){
				if(i == removed_i || j == removed_j)
					continue;
				// Different quadrants require different assignment
				else if (i > removed_i){
					if(j < removed_j)
						minor_matrix(i-1,j) = (*this)(i,j);
					if (j > removed_j)
						minor_matrix(i-1,j-1) = (*this)(i,j);
				}
				else if (i < removed_i){
					if(j < removed_j)
						minor_matrix(i,j) = (*this)(i,j);
					if (j > removed_j)
						minor_matrix(i,j-1) = (*this)(i,j);
				}
			}
		}
	return minor_matrix;
	}
	// abort for invalid inputs
	else {
		cerr << "Error: Invalid input given to Matrix::GetMinor" << endl;
		exit(1);
	}
}

double Matrix::GetDeterminant() const{
	// Check square matrix
	if(rows_ == columns_){
		// Calculate for simple matrices, ending recursive calc
		// 1D array locations are called instead of Index
		if (rows_ == 1)
			return elements_[0];
		else if(rows_ == 2)
			return elements_[0]*elements_[3] - elements_[1]*elements_[2];
		else{
			//Matrix minor_matrix;
			// recursive calculation
			double determinant{.0}; // stores summation
			int i{1}; // Picks row to be removed, allows portability + testing
			for(int j{1}; j <= rows_; j++){
				Matrix minor_matrix = (*this).GetMinorMatrix(i, j); // create our minor for this row

				determinant += pow(-1., (double)(i+j))* // cofactor sign
				(*this)(i,j) *	// X element of current matrix
				minor_matrix.GetDeterminant(); // X minor
			}
			return determinant;
		}
	}
    else{
		cerr << "Error: Calculating determinant of a non-square matrix" << endl;
		exit(1);
	}
}

// Overload insertion to output stream for matrices
ostream& operator<<(ostream& os, const Matrix& mat){
	// Check there is an element to print
	if(mat.rows_ >= 1 && mat.columns_ >= 1){
		for(int i{1}; i <= mat.rows_; i++){
			os << '|';
			for (int j{1}; j <= mat.columns_; j++)
				os << mat(i,j) << '\t';
			os << '|' << endl;
		}
	}
	// print error if invalid
	else
		os << "Error: Printing an empty/invalid matrix" << endl;
	os << endl;
	return os;	
}

// Function to overload >> operator for for ComplexNumber class
// Assumes the form a+ib or a-ib
istream& operator>>(istream &is, Matrix& mat){
	string input;

	delete[] mat.elements_; mat.elements_ = nullptr;

	cout << "Please give number of rows, then columns (space separated): " << endl;
	is >> mat.rows_;
	is >> mat.columns_;

	mat.elements_ = new double[(mat.rows_)*(mat.columns_)];

	cout << "Please input each row (elements space separated):" << endl;

	for (int i{1}; i <= mat.rows_; i++ ){
		cout << "Row " << i << ":" << endl;
		for(int j{1}; j <= mat.columns_; j++){
			is >> input; mat(i,j) = stod(input);
		}
	}
	return is;
}

int main(){
	// DEMONSTRATE DEFAULT CONSTRUCTOR AND PARAMETERIZD CONSTRUCTOR
	const int m(3), n(3);
	cout << "Creating a0: "; Matrix a0;
	cout << "Creating a1: "; Matrix a1(m,n);
	cout << "Creating a2: "; Matrix a2(m,n);

	// SET VALUES FOR a1 AND a2
	for (int i = 1; i <= a1.GetRows(); i++){
		for (int j = 1; j <= a1.GetColumns(); j++)
			a1(i, j) = 1; // Matrix of 1s
		}

	for (int i = 1; i <= a2.GetRows(); i++){
		for (int j = 1; j <= a2.GetColumns(); j++)
			a2(i, j) = 2; // Matrix of 2s
	}

	// PRINT MATRIX WITH OVERLOADED <<
	cout << "Printing a0: " << a0 << "Printing a1:\n" << a1 << "Printing a2:\n" << a2;

	// DEEP COPY BY ASSIGNMENT: DEFINE NEW MATRIX THEN COPY FROM a1
	cout << "Creating a3: "; Matrix a3;

	cout << "Deep copy of a1 using assignment copy to a3: "; a3 = a1;

	cout << "Printing a3:\n" << a3;

	// MODIFY a1 TO DEMONSTRATE a3 UNCHANGED
	for (int i = 1; i <= a1.GetRows(); i++){
		for (int j = 1; j <= a1.GetRows(); j++){
			a1(i, j) = 0; // Matrix of 0s
		}
	}

	cout << "Modified a1 to matrix of 0s:\n" << a1 << "a3 remains:\n" << a3;

	// DEEP COPY USING COPY CONSTUCTOR
	cout << "Deep copy of a2 using copy constructor to a4: "; Matrix a4(a2);
	cout << "Printing a4:\n" << a4;

	// MODIFY a2 TO SHOW a4 UNCHANGED
	for (int i = 1; i <= a2.GetRows(); i++){
		for (int j = 1; j <= a2.GetColumns(); j++){
			a2(i, j) = 0; // matrix of 0s
		}
	}

	cout << "Modified a2 to a matrix of 0s:\n" << a2 << "a4 remains:\n" << a4;

	// MOVE COPY CONSTRUCTION
	cout << "Move copy of a4 onto a5: "; Matrix a5(move(a4));
	cout << "Printing a5:\n" << a5 << "Printing a4:\n" << a4;

	// MOVE ASSIGMENT
	cout << "Creating a6: "; Matrix a6;
	cout << "Move assignment of a5 onto a6: "; a6 = move(a4);

	cout << "Printing a6:\n" << a5 << "Printing a5: " << a4;

    // INPUT MATRIX USING OVERLOADED >>
    cin >> a4;
    cout << "Your matrix is:\n" << a4;

    // ----------------  MATRIX OPERATIONS ------------------------------------

    // Set values for a1 and a2 here
    for (int i = 1; i <= a1.GetRows(); i++){
        for (int j = 1; j <= a1.GetColumns(); j++){
            if (i == j)
                a1(i, j) = 1; // identity matrix
            else
                a1(i, j) = .0;
        }
    }

    for (int i = 1; i <= a2.GetRows(); i++){
        for (int j = 1; j <= a2.GetColumns(); j++)
            a2(i, j) = 2; // Matrix of 2s
    }
    cout << "Printing a1:\n" << a1 << "Printing a2:\n" << a2;
    // Addition and subtraction of 2 matrices
    Matrix add(a1 + a2);
    Matrix sub(a2 - a1);

    cout << "Printing a1 + a2:\n" << add;
    cout << "Printing a2 - a1\n" << sub;

    // Multiplication of 2 matrices
    Matrix multiply = a1*a2;

    cout << "Printing a1*a2\n" << multiply;

	/*for (int i{ 1 }; i <= a4.GetRows(); i++){
		for (int j{ 1 }; j <= a4.GetColumns(); j++){
			Matrix poo = a4.GetMinorMatrix(i, j);
			cout << poo;
		}
	}*/

    // Determinant
    cout << "Determinant of a4 is: " << a4.GetDeterminant() << endl;
	system("PAUSE");

	return 0;
}