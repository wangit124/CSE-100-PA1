/* description: this program describes a tree data structure that
 * can store and sort data with multiple parameters. this might
 * be used to determine an objects location in 3d space, the
 * nearest color of an object on the primary color scale, or sort
 * objects based on a multitude of attributes.
 *
 * name: luhao wang
 * email: luw055@ucsd.edu
 * date: april 18, 2019
 * sources: piazza
 */

#ifndef BruteForceKNN_hpp
#define BruteForceKNN_hpp

#include <algorithm> // sort, max, min
#include <math.h>    // pow, abs
#include <queue>	 // priority_queue
#include <vector>    // vector<typename>
#include <limits>    // numeric_limits<type>::max()
#include "Point.hpp"

/** A brute force approach to a KD tree.
 * This specific class describes the structure of a single node
 * in the tree, and contains methods which can be used to build
 * the tree, find the nearest neighbor of a node, and get its
 * height and size. 
 */

class BruteForceKNN {
    
protected:
    
    vector<Point> trainingPoints;
    unsigned int k;
    double threshold;
    
    // Define a data structure to store current K nearest neighbors
	priority_queue <Point, vector<Point>, CompareValuePQ> nearest;

public:
    
    /** Default constructor */
    BruteForceKNN() {}
    
    /** Initialize the training data points */
    void build(vector<Point>& points) {
        trainingPoints = points;
    }
    
    /** Find k nearest neighbors of the given query point */
    vector<Point> findKNearestNeighbors(Point & queryPoint, unsigned int k) {
		// Define vector to find nearest k
		vector <Point> kNearest;

		// Empty the priority queue
		while (!nearest.empty()) {
			nearest.pop();
		}

		// Set k to parameter k
		this->k = k;
        
		// Set threshold to inf
		threshold = DBL_MAX;

		// Iterate through training points and compare each distance
		for (unsigned int i=0; i<trainingPoints.size(); i++) {
			// Get current point
			Point currPoint = trainingPoints[i];
			
			// Get distance to query
			currPoint.setSquareDistToQuery(queryPoint);

			updateKNN(currPoint);
		}
		// Store k nearest in vector
		while(nearest.size()) {
			kNearest.push_back(nearest.top());
			nearest.pop();
		}	

		return kNearest;
    }
    
    /** Helper method to update your data structure storing KNN using
     * the given point. */
    void updateKNN(Point & point) {
	
		// Get current point
		Point currPoint = point;

		// Get dist to query
		double currDistToQuery = currPoint.squareDistToQuery;
	
		// Check if size of array is equal to k
		if (nearest.size() == k) {
		
			// Update threshold if better
			if (currDistToQuery < threshold) {
				// If so, remove max element and push current
				nearest.pop();
				nearest.push(currPoint);
			}

			// Set threshold
			Point maxDist = nearest.top();
			threshold = maxDist.squareDistToQuery;
		}
		else {
			// If k nodes haven't been reached, push node 
			nearest.push(currPoint);
			
			// If reached k items, set threshold
			if (nearest.size() == k) {
				// Set threshold
				Point maxDist = nearest.top();
				threshold = maxDist.squareDistToQuery;
			}
		} 
    }
    
};

#endif /* BruteForceKNN_hpp */
