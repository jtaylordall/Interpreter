#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include "Relation.h"

using namespace std;

class Database{
private:
  map<string, Relation> db;

public:
  //Constructor
  Database();

  //Member Funtions
  void addRelation(Relation r); //adds Relation with linked name to Database
  void print(); //couts Database by relations
  map<string, Relation>::iterator find(string in); //Returns iterator of relation with desired name
};
