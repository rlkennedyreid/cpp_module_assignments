// PHYS 30762 Programming in C++
// Assignment 2 - 2018

// Program to compute mean, standard deviation and standard
// error of the mean electronic charge. Data is read from file.

#include<iostream>
#include<string>
#include<fstream>


using namespace std;

// Function to test a given string successfully converts to double
bool ValidDouble(const string& input){
    try{ stod(input); }
    catch (...){ return false; }
    return true;
}

// Opens a file into give ifstream using user input, checks success
void OpenFile(ifstream& input_file){

    string file_name; // input variable
    cout << "Please input the name of your data file." << endl;

    getline(cin, file_name);
    input_file.open(file_name);

    while (!input_file.is_open()){ // error handling, forces re-attempt
        input_file.close(); input_file.clear(); // close and clear
        cerr << "Error reading file, please check file name and directory." << endl;
        cout << "Please input the name of your data file." << endl;

        getline(cin, file_name);
        input_file.open(file_name);
    } // passed succesfully at this point
    
    cout << "File opened successfully." << endl;
}

// Function to count data points and errors, using counters passed by reference
void CountData(ifstream& input_file, int& points, int& errors){

    string data_point;
    if (input_file.is_open()){
        while (getline(input_file, data_point)){ // loop through each line of the file
            if (ValidDouble(data_point)) // test
                points++; // count good data
            else
                errors++; // count bad data, clear error
        }
        input_file.clear(); input_file.seekg(ios::beg); // clear eof, return to start
    }
    else
        cerr << "Error in CountData: File is not open." << endl; // shouldn't be called if OpenFile used, added for portability

    if (errors != 0)
        cerr << "Warning! " << errors << " error(s) found" << endl; // warning
}

// Function to store points from fstream into array of doubles
// Does not check for size of array; works by similarity with CountData
void StoreData(ifstream& input_file, double data_array[]){

    string data_point;
    int i{ 0 };
    while (getline(input_file, data_point)){ // same loop as in CountData
        if (ValidDouble(data_point)){
            data_array[i] = stod(data_point); // good input now stored
            i++;
        }
    }
    input_file.clear(); input_file.seekg(ios::beg); // clear eof, return to start
}

// Function to calculate mean of an array of doubles of size num_elements
double CalcMean(const int& num_elements, const double array[]){
    double sum{ .0 };
    for (int i{ 0 }; i < num_elements; i++)
        sum += array[i];

    return (sum / num_elements);
}

// Function to calculate the std dev. of DISTRIBUTION using array of doubles and the mean
double CalcStdDev(const int& num_elements, const double array[], double mean){
    double sum{ .0 };
    for (int i = 0; i < num_elements; i++)
        sum += pow((array[i] - mean), 2.);

    return pow((sum / (static_cast<double>(num_elements-1))), 0.5);
}

int main(){

    // INITIALISE VARIABLES
    int num_points{ 0 }, num_errors{ 0 };
    double mean, std_dev;
    ifstream input_file;
    
    // OPEN AND VALIDATE FILE
    OpenFile(input_file);
    
    // COUNT POINTS & ERRORS
    CountData(input_file, num_points, num_errors);
    
    // ALLOCATE MEMORY AND STORE DATA
    double* data_points = new double[num_points];

    StoreData(input_file, data_points);

    // CLOSE FILE
    input_file.close();

    // CALCULATE & GARBAGE COLLECTION
    mean = CalcMean(num_points, data_points);
    std_dev = CalcStdDev(num_points, data_points, mean);

    delete[] data_points;

    // DISPLAY RESULTS
    cout << num_points << " points were read." << endl
    << endl << "Mean = " << mean << endl
    << "Standard Deviation = " << std_dev << endl
    << "Standard Error = " << std_dev / sqrt(static_cast<double>(num_points)) << endl;

    return 0;
}