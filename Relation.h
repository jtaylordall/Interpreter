#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <vector>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation{
private:
  string name;
  Scheme sch;
  set<Tuple> tup;
  set<Tuple>::iterator it;

public:
  //Constructors
  Relation();
  Relation(string name_in, Scheme sch_in);
  Relation(string name_in, Scheme sch_in, set<Tuple> tup_in);

  //Member Functions
  string getName(); //Returns name of Relation
  void addTuple(Tuple t); //Adds new Tuple to relation
  void print(); //couts Relation

  //Relational Operations
  Relation select_pv(int position, string value); //not yet implemented
  Relation select_pp(int position1, int position2); //not yet implemented
  Relation project(vector<int> positions); //projects relation according to the positions vector
  Scheme project_scheme(vector<int> positions); //rearranges scheme according to positions vector, supports project()

  Relation rename(Scheme in); //replaces the scheme with inputed one
};
