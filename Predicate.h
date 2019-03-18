#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include "Token.h"
#include "Parameter.h"

using namespace std;

class Predicate
{
private:
  string p_id; //Predicate id name
  vector<string> parlist; //Vector list of parameters

public:
  //Constructors
  Predicate(string in_id);
  Predicate();

  //addParam Functions
  void addParam(string p);
  void addParam_D(string p);
  void sort_D();

  //toString Functions
  string toString();
  string toString_exp();
  string toString_Q();
  string toString_High();

  enum Tokentype{
    _comma,
    _period,
    _q_mark,
    _left_paren,
    _right_paren,
    _colon,
    _colon_dash,
    _multiply,
    _add,
    _schemes,
    _facts,
    _rules,
    _queries,
    _id,
    _string,
    _comment,
    _undefined,
    _eof
  };

};
