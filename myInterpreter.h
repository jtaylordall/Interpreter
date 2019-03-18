#ifndef MY_INTERPRETER_H
#define MY_INTERPRETER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Token.h"
#include "myParser.h"
#include "Database.h"
#include "Relation.h"
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class myInterpreter
{

private:
  vector<Token> v;
  int i;
  Database db;

public:
  //Constructor
  myInterpreter(vector<Token> v_in);

  //Database
  void readin(); //Reads Tokens into the Database
  void readschemes(); //Creates Relations from Schemes
  void readfacts(); //Creates Tuples from Facts, adds to appropriate Relation

  //Interpreter
  void readqueries(); //not yet implemented
  bool assessquery(Tuple t); //not yet implemented

  //Tokentype Enum
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

#endif
