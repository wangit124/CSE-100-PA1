#ifndef KDT_HPP
#define KDT_HPP

#include <algorithm> // sort, max, min
#include <math.h>    // pow, abs
#include <vector>    // vector<typename>
#include "Point.hpp"

using namespace std;

/** A KD tree that can output K nearest neighbors of given query point */
class KDT {
    
protected:
    
    /** Inner class that defines a KDNode with certain data point 
     *  and pointers to its children and parent
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
    unsigned int isize;
    unsigned int iheight;
    
    // TODO: define a data structure to store current K nearest neighbors
    
public:
    
    /** TODO: Default constructor of KD tree */
    KDT() {}
    
    /** Build the KD tree from the given vector of Point references */
    void build(vector<Point>& points) {
        // TODO
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
        // TODO
        return nullptr;
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
