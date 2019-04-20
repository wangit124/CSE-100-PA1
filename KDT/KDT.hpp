/* Description: This program describes a tree data structure that
 * can store and sort data with multiple parameters. This might
 * be used to determine an objects location in 3D space, the
 * nearest color of an object on the primary color scale, or sort
 * objects based on a multitude of attributes.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: April 18, 2019
 * Sources: Piazza
 */

#ifndef KDT_HPP
#define KDT_HPP

#include <algorithm> // sort, max, min
#include <math.h>    // pow, abs
#include <vector>    // vector<typename>
#include <queue>	 // priority queue
#include <cfloat>	 // DBL_MAX
#include "Point.hpp"

using namespace std;

#define HALF 2 // Define 2 as half operator

/** A KD tree that can output K nearest neighbors of given query point.
 * This specific class describes the structure of a single node
 * in the tree, and contains methods which can be used to build
 * the tree, find the nearest neighbor of a node, and get its
 * height and size. 
 */

class KDT {
    
protected:
    
    /** Inner class that defines a KDNode with certain data point 
     *  and pointers to its children and parents. 
     */
    class KDNode {
        
    public:
        
        KDNode * left;
        KDNode * right;
        KDNode * parent;
        Point point;

        KDNode() {}
        
        KDNode(Point point) : point(point) {}
    };
     
    KDNode * root; // root of KD tree
    unsigned int numDim; // number of dimension of data points
    unsigned int k; // number of nearest neighbors to find
    double threshold; // largest distance to query point in current KNN
    unsigned int isize; // the size of the tree, number of nodes
    unsigned int iheight; // Height of the tree
    
	// priority queue to store K nearest neighbors of a KD node
	priority_queue <Point> nearest;

public:
    
    /** Default constructor of KD tree */
    KDT() : root(0), threshold(DBL_MAX), isize(0), iheight(-1) {}
   
	/* Destructor for KDT, deletes all nodes*/
    virtual ~KDT() {
        deleteAll(root);
    }


    /** Build the KD tree from the given vector of Point references */
    void build(vector<Point>& points) {
		// Set root to the return value of helper function
		root = buildSubtree(points, 0, points.size(), 0, iheight);
	}
    
    /** Find k nearest neighbors of the given query point */
    vector<Point> findKNearestNeighbors(Point queryPoint, unsigned int k) {
		// Set k to parameter k
		this->k = k;
        
		// Call find helper method
		findKNNHelper(root, queryPoint, 0);
		
		// Store k nearest in vector
		vector<Point> kNearest;
		while(nearest.size()) {
			kNearest.push_back(nearest.top());
			nearest.pop();
		}	

		return kNearest;
    }
    
    /** Return the size of the KD tree */
    unsigned int size() {
        return isize;
    }
    
    /** Return the height of the KD tree */
    unsigned int height() {
        return iheight;
    }
    
private:
    
    /** Helper method to recursively build the subtree of KD tree. */
    KDNode * buildSubtree(vector<Point>& points, unsigned int start, 
                    unsigned int end, unsigned int d, unsigned int height) {
        
		// Get current dimension
		unsigned int currDim = d%numDim;

		// Sort subarray on dimension d
		sort(points.begin()+start, points.begin()+end, CompareValueAt(currDim));
		
		// Find median of list
		unsigned int medInd = (end - start)/HALF + start;

		// Make a new node for median
		KDNode * median = new KDNode(points[medInd]);

		// Assign height and size of tree
		isize++;
		iheight = height;

		// If array size is 1, return median
		if (medInd == start) {
			return median;
		}

		// Assign left and right children
		median->left = buildSubtree(points, start, medInd, currDim+1, height+1);
		median->right = buildSubtree(points, medInd+1, end, currDim+1,height+1);

		// Assign parent
		median -> left -> parent = median;
		median -> right -> parent = median;

        return median;
    }
    
    /** Helper method to recursively find the K nearest neighbors */
    void findKNNHelper(KDNode *node, const Point & queryPoint, unsigned int d){
		// Get current point of node
		Point currPoint = node->point;

		// Get current dimension
		unsigned int currDim = d%numDim;

		// Set distance of current node to query point
		currPoint.setSquareDistToQuery(queryPoint);
		
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
		}
		
		// Decision flag, 1 for left, 0 for right
		int decisionFlag = 0;

		// Determine which child to search first
		if (queryPoint.features[currDim] >= currPoint.features[currDim]) {
			// check if exists
			if (node->right) {
				findKNNHelper(node->right, queryPoint, d+1);
			}
		}
		else {
			// Update decision flag and recurse left
			decisionFlag = 1;
			// check if exists
			if (node->left) {
				findKNNHelper(node->left, queryPoint, d+1);
			}
		}
		
		// Check if left/right branch is better than threshold
		if (decisionFlag == 0) {
			// check if exists
			if (node->left) {
				Point leftPoint = node->left->point;
				
				// Get distance to leftPoint
				leftPoint.setSquareDistToQuery(queryPoint);
				double distToLeft = leftPoint.squareDistToQuery;

				// If less than threshold, search
				if (distToLeft < threshold) {
					findKNNHelper(node->left, queryPoint, d+1);
				}
			}
		}
		else {
			// check if exists
			if (node->right) {
				Point rightPoint = node->right->point;
				
				// Get distance to rightPoint
				rightPoint.setSquareDistToQuery(queryPoint);
				double distToRight = rightPoint.squareDistToQuery;

				// If less than threshold, search
				if (distToRight < threshold) {
					findKNNHelper(node->right, queryPoint, d+1);
				}	
			}
		}
	}
    
	/* Delete method to deallocate all memory from the tree*/
	void deleteAll(KDNode * root) {
		// Set current node
		KDNode * curr = root;

		// if curr is null, return
		if (!curr) 
			return;
		
		// Traverse left subtree
		if (curr->left) 
			deleteAll(curr->left);
		
        // Traverse right subtree
		if (curr->right)
			deleteAll(curr->right);
        
		// Delete current node
		delete curr;
	}
	
};


#endif // KDT_HPP
