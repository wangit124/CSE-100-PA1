#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "KDT.hpp"
#include "Point.hpp"
#include "BruteForceKNN.hpp"

using namespace std;

/** Read the data from file and convert them to vector of points.
 *  Each line of the file contains data in each dimension of the
 *  features (and potentially label) of one data point.
 *  The boolean withLabel indicates if the last value in a line
 *  is a label of the data point.
 */
vector<Point> readData(const char * fileName, bool withLabel) {
    
    vector<Point> result;
    string line;
    int numDim = 0;
    double data = 0;
    
    ifstream in;
    in.open(fileName, ios::binary);
    
    // count number of dimensions
    getline(in, line);
    stringstream lineStream(line);
    while (lineStream >> data) numDim++;
    if (withLabel) numDim--;
    
    //Resets the stream to beginning of file
    in.seekg(0, ios_base::beg);
    
    // read the data and convert them to data points
    while (!in.eof()) {
        vector<double> features;
        int label = 0;
        for (int i = 0; i < numDim; i++) {
            in >> data;
            if (!in.fail()) {
                features.push_back(data);
            }
        }
        if (withLabel) {
            in >> label;
        }
        if (!in.fail()) {
            result.push_back(Point(features, label));
        }
    }
    
    in.close();
    return result;
}

/** Find the most frequent label in the given set of points */
int mostFreqLabel(vector<Point>& points) {
    // TODO
    return 0;
}

/** Check if a given data file is valid. Note that his does not 
  * check if the data file is in correct format
  */
bool fileValid(const char * fileName) {
    
    ifstream in;
    in.open(fileName, ios::binary);
    
    // Check if input file was actually opened
    if(!in.is_open()) {
        cout<< "Invalid input file. No file was opened. Please try again.\n";
        in.close();
        return false;
    }
    
    // Check for empty file
    in.seekg(0, ios_base::end);
    int len = (int) in.tellg();
    if(len == 0) {
        cout << "The file is empty. \n";
        in.close();
        return false;
    }
    
    in.close();
    return true;
}

int main(int argc, const char * argv[]) {
    
    // TODO
    
    return 0;
}


