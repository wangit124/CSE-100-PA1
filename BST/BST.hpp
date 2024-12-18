/* Description: This is a program that allows you to efficiently search,
 * insert, delete, and find the height and size of a tree structure. The
 * tree automatically sorts what you insert into it so you can find
 * items easily later. 
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: April 10, 2019
 * Sources: Piazza
 */

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
using namespace std;

template<typename Data>

/* BST class defines and implements methods used for binary search trees, 
 * including height, size insert, delete, find, first, etc.
 */

class BST {

   protected:

      /** Pointer to the root of this BST, or 0 if the BST is empty */
      BSTNode<Data>* root;

      /** Number of Data items stored in this BST. */
      unsigned int isize;

      /** Height of this BST. */
      unsigned int iheight;

   public:

      /** define iterator as an aliased typename for BSTIterator<Data>. */
      typedef BSTIterator<Data> iterator;

      /** Default constructor.
        * Initialize an empty BST.
        */
      BST() : root(0), isize(0), iheight(0) {  }


      /** Default destructor.
        * Delete every node in this BST.
        */
      virtual ~BST() {
         deleteAll(root);
      }

      /** Given a reference to a Data item, insert a copy of it in this BST.
       *  @param item The reference to the data item to insert a copy of
	   *  @return true if the item was added to this BST as a result of this 
	   *  call to insert, false if an item equal to this one was already in 
	   *  this BST.
       */
      virtual bool insert(const Data& item) {
		 // Set current node to root, and store parent pointer
		 BSTNode<Data> * curr = root;
		 BSTNode<Data> * currParent;

		 // Define height counter
		 int heightCount = 0;

		 // If root is null, insert new node
		 if (!curr) {
			// Create new node and insert at root
			BSTNode<Data> * newRoot = new BSTNode<Data>(item);
			root = newRoot;
			
			// update size and height
			iheight = 0;
			isize++;
			return true;
		 }

         // Start from root and iterate
		 while(curr) {
		    // Compare insert with current
		    if (item < (curr->data)) {
				// If left, then go left and store parent
				currParent = curr;
				curr = curr->left;
			}
			else if((curr->data) < item) {
				currParent = curr;
				curr = curr->right;
            }
			// If duplicate, return false
			else {
				return false;
			}
			// Increment height counter
			heightCount++;
		 }
		
		 // Create new node to insert
		 BSTNode<Data> * newNode = new BSTNode<Data>(item);
			 
		 // Confirm if left or right child insert
		 if (item < (currParent -> data)) {
			currParent -> left = newNode;
			newNode -> parent = currParent;
		 }
		 else if ((currParent->data) < item) {
			currParent -> right = newNode;
			newNode -> parent = currParent;
		 }
	
		 // Update size and height of tree
		 if (heightCount > iheight) {
			iheight = heightCount;
		 }
		 isize++;
		 return true;
	  }


      /** Find a Data item in the BST.
       *  @param item The data item to search for 
	   *  @return an iterator pointing to the item, or pointing past
       *  the last node in the BST if not found.
       */
      virtual iterator find(const Data& item) const {
         // Get current node
		 BSTNode<Data> * curr = root;
		 while (curr) {
		    // Compare find with root
		    if (item < (curr->data)) {
                curr = curr->left;
		    }
			else if((curr->data) < item) {
				curr = curr->right;
			}
			else {
				return BST::iterator(curr);
			}
		 }
         return typename BST<Data>::iterator(0);
      }


      /** @return the number of items currently in the BST.
       */
      unsigned int size() const {
         return isize;
      }

      /** @return the height of the BST.
       * The height of an empty tree is -1 and the height of a tree
       * with only one node is 0.
       */
      unsigned int height() const {
         return iheight;
      }

      /** @return true if the BST is empty, else false.
       */
      bool empty() const {
         return isize == 0;
      }

      /** Return an iterator pointing to the first item in the BST 
	   * (not the root).
       */
      iterator begin() const {
         return BST::iterator(first(root));
      }

      /** Return an iterator pointing past the last item in the BST.
       */
      iterator end() const {
         return typename BST<Data>::iterator(0);
      }


      /** Inorder traverse BST, print out the data of each node in ascending 
	   * order. 
       * @param n, The starting node to print in order 
       */
      void inorder() const {
		// Set current node
		BSTNode<Data> * curr = root;

		// if curr is null, return
		if (!curr) 
			return;
		
		// Traverse left subtree
		if (curr->left) 
			inorder(curr->left);
		
        // Print data
		cout << curr << endl;

		// Traverse right subtree
		if (curr->right)
			inorder(curr->right);

      }


   private:

      /** Find the first element of the BST.
	   * @param root The root of the BST to search
	   * @return returns the node representing first element
       */ 
      static BSTNode<Data>* first(BSTNode<Data>* root) {
         // Get minimum element, AKA leftmost element
		 if (!root) {
			return root;
		 }

		 // Set curr to root and find minimum AKA leftmost node
		 BSTNode<Data> * curr = root;
		 while (curr->left) {
		     curr = curr->left;
		 }
		 return curr;
      }

      /** Do a postorder traversal, deleting nodes
       *  @param n The current node
       */
      static void deleteAll(BSTNode<Data>* n) {
		// Set current node
		BSTNode<Data> * curr = n;

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

#endif //BST_HPP
