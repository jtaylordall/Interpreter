#include "myInterpreter.h"

using namespace std;

//Constructor
myInterpreter::myInterpreter(vector<Token> v_in){
  v = v_in;
  i = 0;
  readin(); //automatically reads tokens into database
}


//Database
void myInterpreter::readin(){//Reads Tokens into the Database
  int vSize = v.size();
  vector<Token> v_schemes;
  while(i < vSize && v.at(i).getTypeint() != _eof){
    readschemes();
    readfacts();
    db.print();
    break;
  }
  Database db2 = db.test();
  db2.print();
  return;
}

void myInterpreter::readschemes(){//Creates Relations from Schemes
  i++; //Skip Scheme;
  i++; //Skip colon;
  while(v.at(i).getTypeint() != _facts){
    string name = v.at(i).getValue();
    i++;
    vector<string> sch;
    if(v.at(i).getTypeint() == _left_paren){
      i++; //Skip left paren
      while(v.at(i).getTypeint() != _right_paren){
        if(v.at(i).getTypeint() == _id){
          sch.push_back(v.at(i).getValue());
        }
        i++;
      }
    }
    Scheme s(sch);
    Relation r(name, s);
    db.addRelation(r);
    i++;
  }
  return;
}

void myInterpreter::readfacts(){//Creates Tuples from Facts, adds to appropriate Relation
  i++; //Skip Facts;
  i++; //Skip colon;
  string name;
  std::map<string, Relation>::iterator it;
  while(v.at(i).getTypeint() != _rules){
    name = v.at(i).getValue();
    it = db.find(name); //matches iterator with the relation mapped with name
    i++;

    vector<string> tup;
    if(v.at(i).getTypeint() == _left_paren){
      i++;
      while(v.at(i).getTypeint() != _right_paren){
        if(v.at(i).getTypeint() == _id || v.at(i).getTypeint() == _string){
          tup.push_back(v.at(i).getValue());
        }
        i++;
      }
    }
    Tuple t(tup);
    it->second.addTuple(t); //adds tuple to the relation matched with iterator
    i++; //skip period
    i++;
  }
  return;
}


//Interpreter
void myInterpreter::readqueries(){
  i++; //Skip Queries;
  i++; //Skip colon;
  string name;
  std::map<string, Relation>::iterator it;
  while(v.at(i).getTypeint() != _rules){
    name = v.at(i).getValue();
    it = db.find(name); //matches iterator with the relation mapped with name
    i++;

    vector<string> tup;
    if(v.at(i).getTypeint() == _left_paren){
      i++;
      while(v.at(i).getTypeint() != _right_paren){
        if(v.at(i).getTypeint() == _id || v.at(i).getTypeint() == _string){
          tup.push_back(v.at(i).getValue());
        }
        i++;
      }
    }
    Tuple t(tup); //creates a tuple based on the query
    i++; //skip q_mark
    i++;
  }
  return;
}

bool myInterpreter::assessquery(Tuple t){
  return true;
}
