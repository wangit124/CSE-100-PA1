
#ifndef Point_hpp
#define Point_hpp

#include <math.h>    // pow, abs
#include <vector>    // vector<typename>
#include <string>

using namespace std;

#define DELTA 0.00005

/** The data point with given features and label **/
class Point {
public:
    
    vector<double> features;
    int label;
    int numDim;
    double squareDistToQuery;
    
    /** Default constructor */
    Point() {}
    
    /** TODO: Constructor that defines a data point with features and certain 
    label */
    Point(vector<double> features, int label) {}
    
    /** Set the square distance to current query point */
    void setSquareDistToQuery(const Point& queryPoint) {
        // TODO
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
