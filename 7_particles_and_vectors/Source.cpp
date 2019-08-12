// PHYS 30762 Programming in C++
// Assignment 7
// Robin Leaf kennedy-Reid (9436360)

/*
This program is to test the implementation of the 'CartesianVector', 'FourVector'
and 'Particle' classes, each test is defined as a separate function.
*/
#include "particleclass.h"

using std::cout;
using std::cin;
using std::cerr;
using std::swap;
using std::endl;
using std::move;
using std::endl;

void CartesianVectorTest();
void FourVectorTest();
void ParticleTest();


int main(){
    CartesianVectorTest();
    FourVectorTest();
    ParticleTest();

    return 0;
}

void CartesianVectorTest(){
    cout << "CARTESIAN VECTOR TEST\n";

    // Demonstrate default constructor and parameterized constructor
    const int elements(3);
    CartesianVector a0;
    CartesianVector a1{ elements };
    CartesianVector a2{ elements };


    // Set values for a1 and a2 here
    for (int i{ 0 }; i < a1.GetNumElements(); i++)
        a1[i] = 1; // vector of 1s

    for (int i{ 0 }; i < a2.GetNumElements(); i++)
        a2[i] = 2; // vector of 2s

    // Print matrices
    cout << "Printing a0: " << a0
        << "\nPrinting a1: " << a1
        << "\nPrinting a2: " << a2;

    // Deep copy by assignment: define new vector a3 then copy from a1 to a3
    CartesianVector a3; a3 = a1;
    cout << "\nDeep copy of a1 using assignment copy to a3.\n";
    cout << "Printing a3: " << a3;

    // Modify contents of original vector and show assigned vector is unchanged here
    for (int i{ 0 }; i < a1.GetNumElements(); i++)
        a1[i] = 0; // vector of 0s

    cout << "\nModified a1 to vector of 0s: " << a1 << "\na3 remains: " << a3;

    // Deep copy using copy constructor
    cout << "\nDeep copy of a2 using copy constructor to a4.\n"; CartesianVector a4{ a2 };
    cout << "Printing a4: " << a4;

    // Modify contents of original vector and show copied vector is unchanged here
    for (int i{ 0 }; i < a2.GetNumElements(); i++)
        a2[i] = 0; // vector of 0s
    cout << "\nModified a2 to a vector of 0s: " << a2 << "\na4 remains: " << a4;

    // Move copy construction demonstration
    cout << "\nMove copy of a4 onto a5.\n"; CartesianVector a5{ move(a4) };
    cout << "Printing a5: " << a5 << "\nPrinting a4: " << a4;

    // Move assignment demonstration
    CartesianVector a6;
    cout << "\nMove assignment of a5 onto a6.\n";  a6 = move(a4);
    cout << "Printing a6: " << a5 << "\nPrinting a5: " << a4;

    // Set values for a1 and a2 here
    for (int i{ 0 }; i < a1.GetNumElements(); i++)
        a1[i] = 1; // vector of 1s

    for (int i{ 0 }; i < a2.GetNumElements(); i++)
        a2[i] = 2; // vector of 2s

    cout << "\nPrinting a1: " << a1
        << "\nPrinting a2: " << a2;

    // Addition and subtraction of 2 matrices
    CartesianVector add = a1 + a2;
    CartesianVector sub = a2 - a1;

    cout << "\nPrinting a2+a1: " << add;
    cout << "\nPrinting a2-a1 " << sub;

    // dotproduct
    double dot_product = a1.GetDotProductWith(a2);

    cout << "\nPrinting a1.a2: " << dot_product << endl;

    return;
}

void FourVectorTest(){
    cout << "\nFOUR VECTOR TEST\n";

    // Demonstrate default constructor and parameterized constructor
    FourVector a0;
    FourVector a1{ 1, 1, 1, 1 };

    //Parameters for a2
    double zeroth{ 2 }; CartesianVector spatial{ 3 };
    for (int i{ 0 }; i < spatial.GetNumElements(); i++)
        spatial[i] = 2; // vector of 1s

    FourVector a2{ zeroth, spatial }; // vector of 2s

    // Print matrices
    cout << "Printing a0: " << a0
        << "\nPrinting a1: " << a1
        << "\nPrinting a2: " << a2;

    // Deep copy by assignment: define new vector a3 then copy from a1 to a3
    FourVector a3; a3 = a1;
    cout << "\nDeep copy of a1 using assignment copy to a3.\n";
    cout << "Printing a3: " << a3;

    // Modify contents of original vector and show assigned vector is unchanged here
    for (int i{ 0 }; i < 4; i++)
        a1[i] = 0; // vector of 0s

    cout << "\nModified a1 to vector of 0s: " << a1 << "\na3 remains: " << a3;

    // Deep copy using copy constructor
    cout << "\nDeep copy of a2 using copy constructor to a4.\n"; FourVector a4{ a2 };
    cout << "Printing a4: " << a4;

    // Modify contents of original vector and show copied vector is unchanged here
    for (int i{ 0 }; i < 4; i++)
        a2[i] = 0; // vector of 0s
    cout << "\nModified a2 to a vector of 0s: " << a2 << "\na4 remains: " << a4;

    // Move copy construction demonstration
    cout << "\nMove copy of a4 onto a5.\n"; FourVector a5{ move(a4) };
    cout << "Printing a5: " << a5 << "\nPrinting a4: " << a4;

    // Move assignment demonstration
    FourVector a6;
    cout << "Move assignment of a5 onto a6.\n";  a6 = move(a4);
    cout << "Printing a6: " << a5 << "\nPrinting a5: " << a4;

    // Set values for a1 and a2 here
    for (int i{ 0 }; i < 4; i++)
        a1[i] = 1; // vector of 1s

    for (int i{ 0 }; i < 4; i++)
        a2[i] = 2; // vector of 2s

    cout << "\nPrinting a1: " << a1
        << "\nPrinting a2: " << a2;

    // Addition and subtraction of 2 matrices
    FourVector add = a1 + a2;
    FourVector sub = a2 - a1;

    cout << "\nPrinting a2+a1: " << add;
    cout << "\nPrinting a2-a1 " << sub;

    // dotproduct
    double dot_product = a1.GetDotProductWith(a2);

    cout << "\nPrinting a1.a2: " << dot_product;

    FourVector position{ 3, 3, 3, 3 };
    CartesianVector beta{ 3 };
    for (int i{ 0 }; i < beta.GetNumElements(); i++)
        beta[i] = .1; // vector of .1s

    cout << "\nThe lorentz boost of " << position << " with beta = " << beta << " is " << position.GetLorentzBoost(beta) << endl;
    return;
}

void ParticleTest(){
    cout << "\n\nPARTICLE TEST\n";
    FourVector position{ 3, 3, 3, 3 };
    CartesianVector beta{ 3 };
    double mass{ 938. };

    for (int i{ 0 }; i < beta.GetNumElements(); i++)
        beta[i] = .1; // vector of .1s

    Particle test{ mass, position, beta };
    cout << "Gamma is " << test.GetGamma() << endl;
    cout << "Total energy is " << test.GetTotalEnergy() << " MeV" << endl;
    cout << "Momentum is " << test.GetMomentum() << " Mev/c" << endl;

    return;
}
