
#ifndef BruteForceKNN_hpp
#define BruteForceKNN_hpp

#include <algorithm> // sort, max, min
#include <math.h>    // pow, abs
#include <vector>    // vector<typename>
#include <limits>    // numeric_limits<type>::max()
#include "Point.hpp"

/** A brute force approach to find K nearest neighbors */
class BruteForceKNN {
    
protected:
    
    vector<Point> trainingPoints;
    int k;
    double threshold;
    
    // TODO: define a data structure to store current K nearest neighbors
    
public:
    
    /** Default constructor */
    BruteForceKNN() {}
    
    /** Initialize the training data points */
    void build(vector<Point>& points) {
        // TODO
    }
    
    /** Find k nearest neighbors of the given query point */
    vector<Point> findKNearestNeighbors(Point & queryPoint, unsigned int k) {
        // TODO
        return {};
    }
    
    /** Helper method to update your data structure storing KNN using
     * the given point. */
    void updateKNN(Point & point) {
        // TODO
    }
    
};

#endif /* BruteForceKNN_hpp */
