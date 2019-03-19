#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

class Tuple{
private:
  vector<string> v; //vector containing Tuple elements as strings
//  string v0; //first element of Tuple, used for ordering Tuples in a set; no longer needed

public:
  //Constructors
  Tuple();
  Tuple(vector<string> v_in);

  //Member Functions
  string toString(); //Returns Tuple as a strin
  vector<string> getTuple(); //Returns Tuple as a vector of strings
  int getSize();

  //Operators
  bool operator <(const Tuple &right) const{//Compares Tuples by vectors
    return v < right.v;
  }
};
