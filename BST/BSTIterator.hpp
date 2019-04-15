/* Description: This program defines an Iterator which can be used
 * to traverse a BST. The iterator can point to the current tree
 * node, increment forwards and backwards, and retrieve the data in
 * the node.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: April 10, 2019
 * Sources: Piazza
 */

#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include "BSTNode.hpp"
#include <list>
#include <iterator>
using namespace std;

template<typename Data>
/* Iterator class defines methods to traverse, equate, and
 * dereference BST nodes. It also contains a pointer to the node
 * that it is currently on. 
 */

class BSTIterator : public iterator<input_iterator_tag,Data> {

   private:
	  // The node this iterator is pointing to
      BSTNode<Data>* curr;

   public:

      /** Constructor.  Use the argument to initialize the current BSTNode
       *  in this BSTIterator.
       */
      BSTIterator(BSTNode<Data>* curr): curr(curr) { }

      /** Dereference operator.
	   *  @returns the data of the node it is pointing to
	   */
      Data operator*() const {
         return curr->data;
      }

      /** Pre-increment operator.
	   *  @returns next smallest node in the tree in order
	   */
      BSTIterator<Data>& operator++() {
         curr = curr->successor();
         return *this;
      }

      /** Post-increment operator.
	   *  @returns previous node in the tree in order
	   */
      BSTIterator<Data> operator++(int) {
         BSTIterator before = BSTIterator(curr);
         ++(*this);
         return before;
      }

      /** Equality test operator.
	   *  Checks if two iterators are pointing to the same node
	   *  @returns true if they are 
	   */
	  bool operator==(BSTIterator<Data> const & other) const {
		 // Check if other equals this
		 if (other == (*this)) 
			return true;

         return false;
      }
 
      /** Equality test operator.
	   *  Checks if two iterators are pointing to the same node
	   *  @returns true if they are NOT
	   */
      bool operator!=(BSTIterator<Data> const & other) const {
		 // Check if other equals this
		 if (other == (*this))
			return false;

         return true;
      }

};

#endif //BSTITERATOR_HPP
