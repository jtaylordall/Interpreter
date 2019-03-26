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
  string name; //name of relation
  Scheme sch; //contains list of scheme attributes
  Tuple que; //contains the query being assessed, for interpreter (because renames/projects change scheme), not database
  set<Tuple> tup; //set of tuples
  set<Tuple>::iterator it; //iterator for navigating through set of tuples

public:
  //Constructors
  Relation();
  Relation(string name_in, Scheme sch_in);
  Relation(string name_in, Scheme sch_in, set<Tuple> tup_in);

  //Push Functions
  void changename(string in); //changes the name(data member) of the Relation
  void addTuple(Tuple t); //Adds new Tuple to relation
  void addQuery(Tuple q); //returns contents of query

  //Pull Functions
  string getName(); //Returns name of Relation
  int getSize(); //returns number of tuples in the relation
  vector<string> getQuery(); //returns contents of query
  void print(); //prints out relation, unformatted
  void print_output(); //prints out relation, formatted for Interpreter

  //Relational Operations
  Relation select_pv(int position, string value); //Finds tuples that have value at position, for assessing constants
  Relation select_pp(vector<int> positions); //Finds tuples that have same value at specified positions, for assessing variables
  Relation project(vector<int> positions); //projects relation according to the positions vector
  Scheme project_scheme(vector<int> positions); //rearranges scheme according to positions vector, assists project()
  Relation rename(Scheme in); //replaces the scheme with inputed one
};
