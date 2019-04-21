#include "KDT.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<Point> vector_from_file(string filename) {
    
  //Open file
  ifstream in;
  in.open(filename, ios::binary);

  //Check if input file was actually opened
  if(!in.is_open()) {
    cout << "Invalid input file. No file was opened. Please try again.\n";
    exit(-1);
  }

  //Check for empty file
  in.seekg(0, ios_base::end); 
  auto len = in.tellg();
  if(len == 0) {
    cout << "The file is empty. \n";
    exit(-1);
  }

  //Resets the stream to beginning of file
  in.seekg(0, ios_base::beg);
 
  KDT tree;
  string line;

  vector<Point> points;
  int label = 1;
  while (in.good()) {
    double x, y;
    in >> x;
    in >> y;
    points.push_back(Point({x, y}, label++));
  }
  
  if(in.is_open()) {
    in.close();
  }

  return points;
}

int run_tests(vector<Point>& kdt_build_points,
              vector<Point>& test_cases, vector<Point>& solutions) {
	
	kdt_build_points.erase(kdt_build_points.begin()+kdt_build_points.size()-1);
  if (test_cases.size() != solutions.size()) {
    cerr << "Number of test cases and solutions must be equivalent" << endl;
    exit(-1);
  }

  int error_count = 0;

  KDT* tree = new KDT();
  tree->build(kdt_build_points);

 // tree->printAll(tree->getRoot());
	
 // cout <<"hi"<<endl;
 // vector<Point> list = tree->returnList();

 // for (unsigned int i=0; i< list.size(); i++) {
//	cout << list[i] << endl;
//  }

  if ( (unsigned int)tree->size() != (unsigned int)kdt_build_points.size()) {
    cerr << "Test failed for tree size" << endl;
    cerr << "\tExpected: " << kdt_build_points.size() << endl;
    cerr << "\tActual: " << tree->size() << endl;
    error_count++;
  }

  unsigned int targetHeight = kdt_build_points.size() == 0 ?
            0 : (unsigned int)log2(kdt_build_points.size());

  if ((unsigned int)tree->height() != (unsigned int)targetHeight) {
    cerr << "Test failed for tree height" << endl;
    cerr << "\tExpected: " << targetHeight << endl;
    cerr << "\tActual: " << tree->height() << endl;
    error_count++;
  }


  vector<Point>::iterator test_it = test_cases.begin();
  vector<Point>::iterator solution_it = solutions.begin();
  for (; test_it != test_cases.end() && solution_it != solutions.end();
       test_it++, solution_it++) {
    auto result = tree->findKNearestNeighbors(*test_it, 1);
   for (unsigned int i=0; i<result.size(); i++) { 
	cout << result[i] << endl;
	cout << endl;
}
    if (result.size() == 0 || result[0] != *solution_it) {
      cerr << "Test failed for find of point " << *test_it << endl;
      cerr << "\tExpected: " << *solution_it << endl;
      if (result.size() == 0) {
        cerr << "\tActual: " << "(none found)" << endl;
      } 
      else {
        cerr << "\tActual: " << result[0] << endl;
      }
      error_count++;
    }
  /*else {
	cout << "test passed" << endl;
 cerr << "\tExpected: " << *solution_it << endl;
      if (result.size() == 0) {
        cerr << "\tActual: " << "(none found)" << endl;
      } 
      else {
        cerr << "\tActual: " << result[0] << endl;
      }*/
}  

  delete tree;
  return error_count;
}

int custom_tests() {

  cout << "Running custom tests" << endl;

  vector<Point> points = vector_from_file("./test/custom_points.txt");
  int error_count = 0;

  vector<Point> test_cases;
  test_cases.push_back(Point({1,4}, 1));
  //test_cases.push_back(Point({4.5, 5}, 2));
  //test_cases.push_back(Point({100, 100}, 3));
  //test_cases.push_back(Point({6, 13}, 4));

  vector<Point> solutions;
  solutions.push_back(Point({6, 9}, 5));
  //solutions.push_back(Point({4, 5}, 1));
  //solutions.push_back(Point({-1, 50}, 3));
  //solutions.push_back(Point({5, 12}, 4));

  error_count += run_tests(points, test_cases, solutions);
  return error_count;
}

// Exhaustive testing
int exhaustive_tests() {
  cout << "Running exhaustive tests" << endl;

  int error_count = 0;

  vector<Point> points = vector_from_file("./test/test_points.txt");
  //for (unsigned int i=0; i<points.size(); i++) {
//	cout << points[i].features[0] << endl;
 // }
  vector<Point> test_cases = vector_from_file("./test/queryPoints.txt");
  vector<Point> solutions = vector_from_file("./test/solutionPoints.txt");

  error_count += run_tests(points, test_cases, solutions);

  return error_count;
}

// DO NOT ADD ANY CHARACTERS AFTER THE BACKSLASHES!
#define ASSERT_NOTHING_FOUND(T, P) if (T.findKNearestNeighbors(P, 1).size() != 0) \
{ \
  cerr << "Incorrect value on empty tree for point " << P << endl; \
  error_count++; \
}

int empty_test() {
  
  cout << "Running tests on empty tree" << endl;

  int error_count = 0;

  KDT tree;
  vector<Point> points;
  tree.build(points);

  if (tree.size() != 0) {
    cerr << "Test failed for tree size" << endl;
    cerr << "\tExpected: " << 0 << endl;
    cerr << "\tActual: " << tree.size() << endl;
    error_count++;
  }
  if (tree.height() != 0) {
    cerr << "Test failed for tree height" << endl;
    cerr << "\tExpected: " << 0 << endl;
    cerr << "\tActual: " << tree.height() << endl;
    error_count++;
  }

  ASSERT_NOTHING_FOUND(tree, Point({-1, -1}, 1))
  ASSERT_NOTHING_FOUND(tree, Point({2, 3}, 1))
  ASSERT_NOTHING_FOUND(tree, Point({2000, -3000}, 1))
  ASSERT_NOTHING_FOUND(tree, Point({-23.5692, 34.762}, 1))

  return error_count;
}


int main(int argc, char* argv[])
{
	//Check for Arguments
  if (argc != 1){
    cout << "Invalid number of arguments.\n";
    return -1;
  }

  int error_count = custom_tests() + empty_test() + exhaustive_tests();

  if (error_count == 0) {
    cout << "Tests passed" << endl;
    return 0;
  }
  else {
    cout << endl << "Failed " << error_count << " tests" << endl;
    return 1;
  }
}
