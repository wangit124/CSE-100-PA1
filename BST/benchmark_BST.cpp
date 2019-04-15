/* Description: This is a program that can be used to test the runtime
 * of different insertion, sort-and-search methods including BST and BSA.
 * It prints out the average time taken for each operation for each 
 * method.
 *
 * Name: Luhao Wang
 * Account: luw055
 * Date: April 15, 2019
 * Source: Piazza
 */

#include <iostream>
#include "BSA.hpp"
#include "BST.hpp"
#include "Timer.hpp"

using namespace std;

/** Returns a vector of random double values with range [min, max]
 *  Note that rand() returns bad random numbers, but for simplicity,
 *  we use it to serve our purpose here.
 */
vector<double> randNums(unsigned int size, int min, int max) {
    vector<double> result;
    for (unsigned int i = 0; i < size; i++) {
        result.push_back((max - min) * ( (double)rand() /
                                        (double)RAND_MAX ) + min);
    }
    return result;
}

/* Method to compute the total and average runtimes of insert and find for 
 * BST, and BSA. Prints out this comparison*/

int main () {
    const int MIN = 0; // min value of random data
    const int MAX = 100; // max value of random data
    const int NUM_INSERT = 30000; // number of random data to insert
    const int NUM_FIND = 30000; // number of random data to find
    const int NUM_RUN = 10; // Number of tests to run
    
	// Define insert and find arrays with random values
    vector<double> insertData = randNums(NUM_INSERT, MIN, MAX);
    vector<double> findData = randNums(NUM_FIND, MIN, MAX);
    
	// Initialize bsa and bst
    BSA<double> bsa;
    BST<double> bst;
    
    cout << "Insert benchmarking for BSA and BST: " << endl;
    cout << "Number of data to insert: " << NUM_INSERT << endl;
    
	// Compute runtime for bsa insert
    Timer t;
    long long sumTime = 0;
    long long averageTime = 0;
	 
	// Start timer
	t.begin_timer();
	
	// Insert all the data from insertData into bsa NUM_RUN times
	for (int i=0; i<NUM_RUN; i++) {
		for (unsigned int index=0; index<insertData.size(); index++) {
			bsa.insert(insertData[index]);
		}
	}
	
	// End timer
	sumTime = t.end_timer();

	// Compute average time
	averageTime = sumTime/NUM_RUN;

    cout << "Average time taken to insert for BSA: " << averageTime
    << " nanoseconds" << endl;
    
	// Compute runtime for bst insert
    sumTime = 0;
    averageTime = 0;
    
	// Start timer
	t.begin_timer();
	
	// Insert all the data from insertData into bst NUM_RUN times
	for (int i=0; i<NUM_RUN; i++) {
		for (unsigned int index=0; index<insertData.size(); index++) {
			bst.insert(insertData[index]);
		}
	}
	
	// End timer
	sumTime = t.end_timer();

	// Compute average time
	averageTime = sumTime/NUM_RUN;
 
    cout << "Average time taken to insert for BST: " << averageTime
    << " nanoseconds" << endl;
    
    cout << endl; // new line

    cout << "Find benchmarking for BSA and BST: " << endl;
    cout << "Number of data in BSA/BST: " << NUM_INSERT << endl;
    cout << "Number of data to find: " << NUM_FIND << endl;
    
	// Compute runtime for bsa find
    sumTime = 0;
    averageTime = 0; 
    
	// Start timer
	t.begin_timer();
	
	// find all the data from findData NUM_RUN times
	for (int i=0; i<NUM_RUN; i++) {
		for (unsigned int index=0; index<findData.size(); index++) {
			bsa.find(findData[index]);
		}
	}
	
	// End timer
	sumTime = t.end_timer();

	// Compute average time
	averageTime = sumTime/NUM_RUN;
 
    cout << "Average time taken to find for BSA: " << averageTime
    << " nanoseconds" << endl;
    
	// Compute runtime for bst find
    sumTime = 0;
    averageTime = 0;

	// Start timer
	t.begin_timer();
	
	// Search in bst NUM_RUN times
	for (int i=0; i<NUM_RUN; i++) {
		for (unsigned int index=0; index<findData.size(); index++) {
			bst.find(findData[index]);
		}
	}
	
	// End timer
	sumTime = t.end_timer();

	// Compute average time
	averageTime = sumTime/NUM_RUN;
    
    cout << "Average time taken to find for BST: " << averageTime
    << " nanoseconds" << endl;	
}
