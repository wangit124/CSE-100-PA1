#include <iostream>
#include <stdlib.h>
#include <vector>

#include "KDT.hpp" 
#include "BruteForceKNN.hpp"
#include "Point.hpp"
#include "Timer.hpp"

/** Returns a vector of random double values with range [min, max]
 *  Note that rand() returns bad random numbers, but for simplicity,
 *  we use it to serve our purpose here.
 */
vector<double> randNums(unsigned int size, int min, int max) {
    vector<double> result;
    for (unsigned int i = 0; i < size; i++) {
        result.push_back((max - min) * ( (double)rand() /
                                        (double)RAND_MAX ) + min);
    }
    return result;
}

/** Returns a vector of points with given dimensions of given size */
vector<Point> buildRandPoints(unsigned int numPoints, unsigned int numDim) {
    vector<Point> result;
    for (unsigned int i = 0; i < numPoints; i++) {
        result.push_back(Point(randNums(numDim, 0, 100), 0));
    }
    return result;
}

int main(int argc, const char * argv[]) {
    
    // TODO: value to change to do experiments
    const int NUM_TRA = 10000; // number of random training data
    const int NUM_TEST = 10000; // number of random validation data
    const int NUM_DIM = 2;
    const int K = 1;
    
    KDT kdtree;
    BruteForceKNN bfknn;
    
    vector<Point> training = buildRandPoints(NUM_TRA, NUM_DIM);
    vector<Point> test = buildRandPoints(NUM_TEST, NUM_DIM);
    
    kdtree.build(training);
    bfknn.build(training);
    
    Timer t;
    long long sumTime = 0;
    t.begin_timer();
    for (Point & p : test) {
        kdtree.findKNearestNeighbors(p, K);
    }
    sumTime = t.end_timer();
    cout << "Training data size: " << NUM_TRA << "; Test data size: "
    << NUM_TEST << "; Dimension size: " << NUM_DIM << "; K: " << K <<
    "; Time taken for KD tree to find KNN: " << sumTime <<
    " milliseconds" << endl;
    
    
    sumTime = 0;
    t.begin_timer();
    for (Point & p : test) {
        bfknn.findKNearestNeighbors(p, K);
    }
    sumTime = t.end_timer();
    cout << "Training data size: " << NUM_TRA << "; Test data size: "
    << NUM_TEST << "; Dimension size: " << NUM_DIM << "; K: " << K <<
    "; Time taken for brute force approach to find KNN: " << sumTime <<
    " milliseconds" << endl;
    
    return 0;
}

