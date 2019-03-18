#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include "Token.h"
#include "Predicate.h"
#include "Parameter.h"

using namespace std;

class Rule
{
private:
  string headP; //Head predicate
  vector<string> p; //Vector list of predicates

public:
  Rule();
  Rule(string in_headP);
  void addPred(string in_pred);
  string toString();
};
