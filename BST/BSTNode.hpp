/* Description: This is a program that defines a node in a tree
 * structure, and allows you to find the next smallest element in 
 * sorted order, relative to the current node.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: April 10, 2019
 * Sources: Piazza
 */

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>
using namespace std;

template<typename Data>

/* BSTNode class defines the parent, left, and right children of the
 * current node, as well as the data stored in the node and the 
 * method to find the node in the tree with the next smallest element.
 */
class BSTNode {

	public:

		/** Constructor.  Initialize a BSTNode with the given Data item,
		 *  no parent, and no children.
		 *  @param d The data to initialize the node with.
		 */
		BSTNode(const Data & d) : data(d) {
		    parent = left = right = nullptr;	
		}

		BSTNode<Data>* left;
		BSTNode<Data>* right;
		BSTNode<Data>* parent;
		Data const data;   // the const Data in this node.

		/** Return the successor of this BSTNode in a BST, or 0 if none.
		 *  PRECONDITION: this BSTNode is a node in a BST.
		 *  POSTCONDITION:  the BST is unchanged.
		 *  RETURNS: the BSTNode that is the successor of this BSTNode,
		 *  or 0 if there is none. 
		 */
		BSTNode<Data>* successor() {
			// Make a traversal node
			BSTNode<Data> * currNode = this;
			
			// Check right subtree
			if (currNode->right) {
				
				// go to right
				currNode = currNode->right;
				
				// Return minimum node
				while(currNode->left) {
					currNode=currNode->left;
				}
				
				return currNode;
			}
			else {
				
				// Loop through and find successor
				while(currNode) {
					
					BSTNode<Data> * currParent = currNode->parent;
				    // If root, return null
					if (!currParent) {
						return 0;
					}
				    // If current node is left child of parent, return parent
					if ((currNode->data) < (currParent->data)) {
						return currParent;
					}
					// Otherwise climb up to next parent
					else {
						currNode = currParent;
					}
				}

				// If not found, return 0
				return 0;
			}
		}
}; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
ostream & operator<<(ostream& stm, const BSTNode<Data> & n) {
	stm << '[';
	stm << setw(10) << &n;                 // address of the BSTNode
	stm << "; p:" << setw(10) << n.parent; // address of its parent
	stm << "; l:" << setw(10) << n.left;   // address of its left child
	stm << "; r:" << setw(10) << n.right;  // address of its right child
	stm << "; d:" << n.data;               // its data field
	stm << ']';
	return stm;
}

#endif // BSTNODE_HPP
