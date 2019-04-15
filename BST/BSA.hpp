/* Description: This is a program that defines and implements
 * methods used for binary search arrays, including bsearch,
 * find, insert, and iterator methods begin and end.
 *
 * Name: Luhao Wang
 * Account: luw055
 * Date: April 10, 2019
 * Source: Piazza
 */

#ifndef BSA_HPP
#define BSA_HPP

#include <vector>
using namespace std;

template<typename Data>

/** This class implements a binary search array with methods to
 * insert, search, and iterate the array.*/

class BSA {

	private:
		vector<Data> v;

		/** Helper method used to either find an element if it exists
		 * or else find where it should be inserted.
		 */
		virtual size_t binarySearch(const Data& item) const {
			
			return 0;
		}

	public:
		/** Return the position of item, otherwise v.cend() */
		virtual typename vector<Data>::const_iterator find(const Data& item) 
													const {
			// Search correct index for item
			int index = binarySearch(item);
				
			// If item exists, return iterator
			if (v[index] == item) {
				
				// Create an iterator pointing to first element
				vector<Data>::const_iterator itr = v.cbegin();

				// Advance to index
				advance(itr, index);

				return itr;
			}
			
			// If not found, return cend
			return v.cend();
		}

		/** Insert item into sorted position */
		virtual bool insert(const Data& item) {
			// Search correct index for item
			int index = binarySearch(item);
			
			// If item already exists, return false
			if (v[index] == item) {
				return false;
			}

			// Create a new iterator for v
			vector<Data>::const_iterator itr = v.cbegin();

			// Traverse to correct index
			advance(itr, index);
			
			// Insert item in vector
			v.insert(itr, item);
			
			return true;
		}

		typename vector<Data>::iterator begin() const {
			return v.begin();
		}

		typename vector<Data>::iterator end() const {
			return v.end();
		}
};

#endif
