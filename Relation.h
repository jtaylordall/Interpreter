#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation{
private:
  string name;
  Scheme sch;
  set<Tuple> tup;


public:
  //Constructors
  Relation();
  Relation(string name_in, Scheme sch_in);

  //Member Functions
  string getName(); //Returns name of Relation
  void addTuple(Tuple t); //Adds new Tuple to relation
  void print(); //couts Relation

  //Relational Operations
  void select(); //not yet implemented
  void project(); //not yet implemented
  void rename(); //not yet implemented
};
