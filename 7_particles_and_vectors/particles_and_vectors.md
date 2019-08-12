# particles_and_vectors

## Specification
  *vectorclasses.h*
  - Class heirarchy for cartesian vectors of general dimension, as well as Lorentzian 4-vectors
    - 4-vector class inherits a Cartesian vector for the space-components
    - Member functions for expected behavior; arithmetic, dot products etc.
    - copy and move assigment implemented
  *particleclass.h*
  - Class for a relativistic particle implemented (
    - Has a 4-vector for position
    - Cartesian vector for velocity ("beta")
    - various member functions
  - See .h files for more documentation

*Source.cpp* provides a demonstration of all the features of these classes, as well as a demonstration of the correct definitions of copy and move assignment etc. for all classes.

# Key features:
  - Classes:
   - Inheritance
   - Encapsulation
   - Move semantics
  - Header files
   - Include guards
