/* description: this program describes a program that
 * can store and determine the most frequent data point
 * in the nearest neighbors of a given data point
 *
 * name: luhao wang
 * email: luw055@ucsd.edu
 * date: april 18, 2019
 * sources: piazza
 */

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <climits>

#include "KDT.hpp"
#include "Point.hpp"
#include "BruteForceKNN.hpp"

#define KARG 1
#define TRAINARG 2
#define INPUTARG 3
#define FLAG 4

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

/** Find the most frequent label in the given set of points 
  * @param points to search for most frequent label
  * @return the most frequent label
  */
int mostFreqLabel(vector<Point>& points) {
	// Sort the array
	sort(points.begin(), points.end(), CompareLabel());

	// Store max frequency
	int maxCount = 1;
	
	// Store current point
	Point currPoint = points[0];

	// Store current count
	int currCount = 1;

	// Iterate through array and store labels
	for (unsigned int i=1; i<points.size(); i++) {
		if (points[i].label == points[i-1].label) {
			currCount++;
		}
		else {
			if (currCount > maxCount) {
				maxCount = currCount;
				currPoint = points[i-1];
			}
			currCount = 1;
		}
	}

	// If last element is most frequent
	if (currCount > maxCount) {
		maxCount = currCount;
		currPoint = points[points.size()-1];
	}

    return currPoint.label;
}

/** Check if a given data file is valid. Note that his does not 
  * check if the data file is in correct format
  * @param the file to check for validity
  * @return true if file is valid
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
    
    // Parse command line arguments
	int k = atoi(argv[KARG]);

	const char * trainingFile = argv[TRAINARG];

	const char * inputFile = argv[INPUTARG];
	
	const char * flag = argv[FLAG];

	const char * valid = "validation";

	const char * test = "test";

	// Check if files are valid
	if (!fileValid(trainingFile) || !fileValid(inputFile)) {
		return 0;
	}
	
	// Create a KD tree
	KDT* tree = new KDT();
	
	// If argument 4 is "validation"
	if (!strcmp(flag, valid)) {
		// Count up label mismatches
		int mismatches = 0;
		
		// Parse files and get points
		vector <Point> buildPoint = readData(trainingFile, true);
		vector <Point> queryPoint = readData(inputFile, true);
		
		// Array to store knearest neighbors
		vector <Point> kNearest;

		// Build KDTree		
		tree->build(buildPoint);
		
		// For each query point, calculate the most frequent label
		for (unsigned int i=0; i<queryPoint.size(); i++) {
			kNearest = tree->findKNearestNeighbors(queryPoint[i], k);
		
			// Calculate most frequent
			int freqLabel = mostFreqLabel(kNearest);
			// Count mismatch
			if (freqLabel != queryPoint[i].label) {
				mismatches++;
			}
		}
	
		// Get validation error
		double validErr = mismatches / (double)queryPoint.size();


		// Write data to a file
	//	string writeData = "K: " + to_string(k) + ", Validation Error: " 
	//						+ to_string(validErr) + "\n";

		// Open file to write to 
		ofstream outputData;
		outputData.open("result.txt", ios_base::app);
		outputData << "K: " << k << ", Validation Error: " << validErr << "\n";
		outputData.close();
		
		return 0;
	}
	else if (!strcmp(flag, test)) {
		// Open file to write to 
		ofstream outputData;
		outputData.open("result.txt", ios_base::app);
		
		// Parse files and get points
		vector <Point> buildPoint = readData(trainingFile, false);
		vector <Point> queryPoint = readData(inputFile, false);
	
		// Array to store knearest neighbors
		vector <Point> kNearest;

		// Build KDTree		
		tree->build(buildPoint);
		
		// For each query point, calculate the most frequent label
		for (unsigned int i=0; i<queryPoint.size(); i++) {
			kNearest = tree->findKNearestNeighbors(queryPoint[i], k);
			
			// Calculate most frequent
			int freqLabel = mostFreqLabel(kNearest);

			// Write data to a file
			string writeData = to_string(freqLabel) + "\n";
			outputData << writeData;			
		}

		// close stream
		outputData.close();
	}
	// If fourth argument invalid, return 0
	else {
		// Delete tree
		delete tree;		
		return 0;
	}

	// Delete tree
	delete tree;
    return 0;
}


