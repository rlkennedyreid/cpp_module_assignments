#millikan

Program to calculate the mean, standard deviation and standard error of a list of values (in this case the electron charge, see .dat files).

Data is read from files in the local directory; user must give file name in terminal.

#Specification:
  - Read data from files
  - Calculate mean, std dev and std error correctly
  - EXTENSION: Handle bad data in files (See millikan2.dat)
  
Above specification was met. Bad data is ignored, a warning given to user, and calculation still performed.

Opening and storing of file data is done locally to functions to protect data. Data points are also counted and printed for user to check.

#Key features:
  - ifstreams
  - Exception handling
  - Passing by reference
  - Dynamic memory allocation
