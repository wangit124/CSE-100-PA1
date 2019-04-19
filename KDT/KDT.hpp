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
#include "Point.hpp"

#define HALF 2 // Define 2 as half operator

using namespace std;

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
    
	// Array to store K nearest neighbors of a KD node
	vector <Point> nearest;

public:
    
    /** Default constructor of KD tree */
    KDT() : root(0), isize(0), iheight(-1) {}
    
    /** Build the KD tree from the given vector of Point references */
    void build(vector<Point>& points) {
		// Set root to the return value of helper function
		root = buildSubtree(points, 0, points.size(), 0, iheight);
	}
    
    /** Find k nearest neighbors of the given query point */
    vector<Point> findKNearestNeighbors(Point queryPoint, unsigned int k) {
        // TODO
        return {};
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
		int currDim = d%numDim;

		// Sort subarray on dimension d
		sort(points.begin()+start, points.begin()+end, CompareValueAt(currDim));
		
		// Find median of list
		int medInd = (end - start + 1)/HALF + start;

		// Make a new node for median
		KDNode * median = new KDNode(points[medInd]);

		// Assign height and size of tree
		isize++;
		iheight = height;

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
        // TODO
    }
    
    /** Helper method to update your data structure storing KNN using 
     *  the given point.
     */
    void updateKNN(Point & point) {
        // TODO
    }
    
};


#endif // KDT_HPP
