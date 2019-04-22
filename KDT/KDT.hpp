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

#ifndef KDT_HPP
#define KDT_HPP

#include <algorithm> // sort, max, min
#include <math.h>    // pow, abs
#include <queue>	 // priority_queue
#include <vector>    // vector<typename>
#include <cfloat>	 // DBL_MAX
#include "Point.hpp"

using namespace std;

#define DELTA 0.00005 // within 0.00005 is equal
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
        
        KDNode(Point point) : point(point) {
			left = right = parent = nullptr;	
		}
    };
     
    KDNode * root; // root of KD tree
    unsigned int numDim; // number of dimension of data points
    unsigned int k; // number of nearest neighbors to find
    double threshold; // largest distance to query point in current KNN
    unsigned int isize; // the size of the tree, number of nodes
    unsigned int iheight; // Height of the tree
    
	// priority queue to store K nearest neighbors of a KD node
	priority_queue <Point, vector<Point>, CompareValuePQ> nearest;

public:
    /** Default constructor of KD tree */
    KDT() : root(0), isize(0), iheight(0) {}
   
	/* Destructor for KDT, deletes all nodes*/
    ~KDT() {
		deleteAll(root);
    }

    /** Build the KD tree from the given vector of Point references
	 *	@params takes in the points array to build the tree from  
	 */
    void build(vector<Point>& points) {
		// If array is empty, return
		if (points.size() == 0) {
			return;
		}
		// Set numDim to size of features
		numDim = points[0].numDim;
		
		// Set root to the return value of helper function
		root = buildSubtree(points, 0, points.size(), 0, iheight);
		
		// Increment size
		isize++;
	}
   	 
    /** Find k nearest neighbors of the given query point 
	 *  Takes in query points and calls the helper function 
	 *  to traverse the tree
	 */
    vector<Point> findKNearestNeighbors(Point queryPoint, unsigned int k) {
		// Define vector to find nearest k
		vector <Point> kNearest;
		if (isize == 0 || k <= 0) {	
			return kNearest;
		}

		// Empty the priority queue
		while (!nearest.empty()) {
			nearest.pop();
		}

		// Set k to parameter k
		this->k = k;
        
		// Set threshold to inf
		threshold = DBL_MAX;

		// Call find helper method
		findKNNHelper(root, queryPoint, 0);
		
		// Store k nearest in vector
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
    
    /** Helper method to recursively build the subtree of KD tree. 
	 *	@Params points to build tree from, start and end indicies, 
	 *	dimension, and height.
	 *	@Returns the median node each iteration, up to root
	 */
    KDNode * buildSubtree(vector<Point>& points, unsigned int start, 
                    unsigned int end, unsigned int d, unsigned int height) {
		
		// Get current dimension
		unsigned int currDim = d%numDim;
	
		// Sort subarray on dimension d
		sort(points.begin()+start, points.begin()+end, CompareValueAt(currDim));
			
		// If one element left, return it
		if ((end - start) == 1) {
			// Make a new node for single
			KDNode * single = new KDNode(points[start]);
			return single;	
		}
		// Two elements left, set children
		if ((end - start) == HALF) {
			// Make new nodes for the elements
			KDNode * right = new KDNode(points[start+1]);
			right->left = new KDNode(points[start]);
	
			// Update height and size
			isize++;
			height++;
				
			// Assign height and size of tree
			if (height > iheight) {
				iheight = height;
			}
		
			return right;
		}
		
		// Find median of list
		unsigned int medInd = (end - start)/HALF + start;

		// Make a new node for median
		KDNode * median = new KDNode(points[medInd]);
		
		// Assign height and size of tree
		if (height > iheight) {
			iheight = height;
		}
	
		// Check for duplicate
		if (points[medInd - 1] == points[medInd]) {
			delete median;
			median = new KDNode(points[medInd-1]);
			medInd--;
		}

		// Assign left and right children, and link parent
		median->left = buildSubtree(points, start, medInd, d+1, height+1);
		if (median->left) {
			median->left->parent = median;	
			isize++;
		}
		
		median->right = buildSubtree(points, medInd+1, end, d+1, height+1);
		if (median->right) {
			median->right->parent = median;
			isize++;
		}

       	return median;
    }
    
    /** Helper method to recursively find the K nearest neighbors
	 * @params, current node, the query, current dimension
	 */
    void findKNNHelper(KDNode *node, const Point & queryPoint, unsigned int d) {
		// Get current point of node
		Point currPoint = node->point;

		// set distance
		currPoint.setSquareDistToQuery(queryPoint);
	
		// Get current dimension
		unsigned int currDim = d%numDim;
	
		// Determine which child to search first
		double queryDim = queryPoint.features[currDim];
		double currPointDim = currPoint.features[currDim];

		// Go left if the query is less
		if (queryDim < currPointDim) {  
			// check if exists
			if (node->left) {
				findKNNHelper(node->left, queryPoint, d+1);
			}

			// If current node is closer, update 
			//updateKNN(currPoint);
			
			// Check if right exists
			if (node->right) {
				// Check for other potential points
				double distToRight = currPoint.features[currDim] -
									queryPoint.features[currDim];

				distToRight = pow(distToRight, HALF);

				// Check if lesser than threshold
				if (distToRight<threshold || abs(distToRight-threshold)<=DELTA){
					findKNNHelper(node->right, queryPoint, d+1);
				}
			}
		}
		else {
			// Check if needs to search right
			if (node->right) {
				findKNNHelper(node->right, queryPoint, d+1);
			}		
			
			// If current node is closer, update 
			//updateKNN(currPoint);
			
			// Check if left exists
			if (node->left) {
				// Check for other potential points
				double distToLeft = currPoint.features[currDim] -
									queryPoint.features[currDim];

				distToLeft = pow(distToLeft, HALF);

				// Check if lesser than threshold
				if (distToLeft<threshold || abs(distToLeft-threshold) <= DELTA){
					findKNNHelper(node->left, queryPoint, d+1);
				}
			}
		}
	
		// Update nearest k
		updateKNN(currPoint);
	}
   	
	/** Helper method to update your data structure storing KNN using 
     *  the given point.
	 *  @param Takes in a point to update and push onto queue
     */
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
 
	/* Delete method to deallocate all memory from the tree
	 * @param takes in a node to start at
	 */
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
