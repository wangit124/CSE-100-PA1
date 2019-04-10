
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

int main () {
    // TODO: value to change to do benchmarking
    const int MIN = 0; // min value of random data
    const int MAX = 100; // max value of random data
    const int NUM_INSERT = 30000; // number of random data to insert
    const int NUM_FIND = 30000; // number of random data to find
    const int NUM_RUN = 10;
    
    vector<double> insertData = randNums(NUM_INSERT, MIN, MAX);
    vector<double> findData = randNums(NUM_FIND, MIN, MAX);
    
    BSA<double> bsa;
    BST<double> bst;
    
    cout << "Insert benchmarking for BSA and BST: " << endl;
    cout << "Number of data to insert: " << NUM_INSERT << endl;
    
    Timer t;
    long long sumTime = 0;
    long long averageTime = 0;
    
    // TODO
    
    cout << "Average time taken to insert for BSA: " << averageTime
    << " milliseconds" << endl;
    
    sumTime = 0;
    averageTime = 0;
    
    // TODO
    
    cout << "Average time taken to insert for BST: " << averageTime
    << " milliseconds" << endl;
    
    cout << endl; // new line
    
    cout << "Find benchmarking for BSA and BST: " << endl;
    cout << "Number of data in BSA/BST: " << NUM_INSERT << endl;
    cout << "Number of data to find: " << NUM_FIND << endl;
    
    sumTime = 0;
    averageTime = 0;
    
    // TODO
    
    cout << "Average time taken to find for BSA: " << averageTime
    << " milliseconds" << endl;
    
    sumTime = 0;
    averageTime = 0;
    
    // TODO
    
    cout << "Average time taken to find for BST: " << averageTime
    << " milliseconds" << endl;
    
}
