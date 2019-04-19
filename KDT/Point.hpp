/* Description: A class representing a single item in the tree. 
 * It contains the name of the node as well as point data
 * about it including the value of each of its parameters
 * that will be used for sorting depending on the data
 * type.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: April 18, 2019
 * Sources: Piazza
 */

#ifndef Point_hpp
#define Point_hpp

#include <math.h>    // pow, abs
#include <vector>    // vector<typename>
#include <string>	 

using namespace std;

#define DELTA 0.00005
#define SQR 2

/** A single KDT tree data point with given features and label.
 *  This class also describes a method to calculate the 
 *  Euclidean distance between two Nodes
 */

class Point {
public:
    
    vector<double> features; // Array of feature values used in ordering
    int label; // item number and index
    int numDim; // Number of dimensions per node
    double squareDistToQuery; // 
    
    /** Default constructor */
    Point() {}
    
    /** Constructor that defines a data point with features and certain label, 
	 * takes in parameters features and label, then initializes point object
	 */
    Point(vector<double> features, int label):features(features), label(label){}
	
    /** Set the square distance to current query point 
	 * @param Takes in the point to find distance of*/
    
	void setSquareDistToQuery(const Point& queryPoint) {
		// Calculate square distance
		int currDist = 0;
		int totalSqrDist = 0;
		for (int i=0; i<numDim; i++) {
			// Calculate distance of current parameter
			currDist = features[i] - queryPoint.features[i];
			totalSqrDist += pow(currDist, SQR);
		}
		// set sum of squares
		squareDistToQuery = totalSqrDist;
    }
    
    /** Equals operator */
    bool operator == (const Point& other) const {
        if (numDim != other.numDim) return false;
        for (int i = 0; i < numDim; i++) {
            if (abs(features[i] - other.features[i]) > DELTA) {
                return false;
            }
        }
        return true;
    }
    
    /** Not-equals operator */
    bool operator != (const Point& other) const {
        return !((*this) == other);
    }
    
};

std::ostream& operator << (std::ostream& out, const Point& data) {
    std::string s = "(";
    for (int i = 0; i < data.numDim - 1; i++) {
        s += to_string(data.features[i]) + ", ";
    }
    s += to_string(data.features[data.numDim - 1]) + ") : " 
         + to_string(data.label);
    out << s;
    return out;
}

/** The comparator used in sorting points based on values on
    certain dimension */
struct CompareValueAt {
    int dimension;
    CompareValueAt(int dimension) {
        this->dimension = dimension;
    }
    bool operator() (const Point & p1, const Point & p2) {
        return p1.features[dimension] < p2.features[dimension];
    }
};

#endif /* Point_hpp */
