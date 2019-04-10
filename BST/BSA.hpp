/* Description: This is a program that defines and implements
 * methods used for binary search arrays, including bsearch,
 * find, insert, and iterator methods begin and end.
 *
 * Name: Luhao Wang
 * Account: luw055
 * Date: April 10, 2019
 */

#ifndef BSA_HPP
#define BSA_HPP

#include <vector>
using namespace std;

template<typename Data>

/** This class implements a binary search array */
class BSA {

	private:
		vector<Data> v;

		/** Helper method used to either find an element if it exists
		 * or else find where it should be inserted.
		 */
		virtual size_t binarySearch(const Data& item) const {
			//TODO
			return 0;
		}

	public:
		/** Return the position of item, otherwise v.cend() */
		virtual typename vector<Data>::const_iterator find(const Data& item) 
													const {
			//TODO
			return v.cend();
		}

		/** Insert item into sorted position */
		virtual bool insert(const Data& item) {
			//TODO
			return false;
		}

		typename vector<Data>::iterator begin() const {
			return v.begin();
		}

		typename vector<Data>::iterator end() const {
			return v.end();
		}
};

#endif
