#include "myInterpreter.h"

using namespace std;

//Constructor
myInterpreter::myInterpreter(vector<Token> v_in){
  v = v_in; //reads in vector of tokens
  i = 0;
  readin(); //automatically reads tokens into database
}


//Database
void myInterpreter::readin(){//Reads Tokens into the Database
  int vSize = v.size();
  vector<Token> v_schemes;
  while(i < vSize && v.at(i).getTypeint() != _eof){
    readschemes(); //builds database
    readfacts();
    readrules();
  //  db.print(); //for debugging
  //  cout << "-------------\n\n"; //for debugging
    readqueries(); //interprets queries according to contents of database
    break;
  }
  print_output(); //outputs formatted interpreter data
  return;
}

void myInterpreter::readschemes(){//Creates Relations from Schemes, called by readin()
  i++; //Skip Scheme;
  i++; //Skip colon;
  while(v.at(i).getTypeint() != _facts){
    string name = v.at(i).getValue(); //read in name of predicate
    i++; //moves past it
    vector<string> sch;
    if(v.at(i).getTypeint() == _left_paren){
      i++; //Skip left paren
      while(v.at(i).getTypeint() != _right_paren){ //reads in parameters, skiping commas
        if(v.at(i).getTypeint() == _id){
          sch.push_back(v.at(i).getValue());
        }
        i++; //iterates to next token (id, commas, right paren)
      }
    }
    Scheme s(sch);
    Relation r(name, s);
    db.addRelation(r); //adds scheme to database with a unique relation
    i++;
  }
  return;
}

void myInterpreter::readfacts(){//Creates Tuples from Facts, adds Tuples to appropriate Relation, called by readin()
  i++; //Skip Facts;
  i++; //Skip colon;
  string name;
  std::map<string, Relation>::iterator it;
  while(v.at(i).getTypeint() != _rules){
    name = v.at(i).getValue(); //gets predicate name of fact
    it = db.find(name); //finds relation with name matching the fact
    i++;

    vector<string> tup;
    if(v.at(i).getTypeint() == _left_paren){ //reads in tuples and stores them as a tuple
      i++;
      while(v.at(i).getTypeint() != _right_paren){
        if(v.at(i).getTypeint() == _id || v.at(i).getTypeint() == _string){
          tup.push_back(v.at(i).getValue());
        }
        i++;
      }
    }
    Tuple t(tup);
    it->second.addTuple(t); //adds tuple to the relation
    i++; //skip period
    i++; //iterates to next id (predicate name) or to rules
  }
  return;
}

void myInterpreter::readrules(){//Skips past all rules, called by readin()
  i++; //Skip Rules;
  i++; //Skip colon;
  while(v.at(i).getTypeint() != _queries){
    i++; //iterates past rules
  }
  return;
}


//Interpreter
void myInterpreter::readqueries(){//Reads in queries, assesses them, and stores product in output vector, called by readin()
  i++; //Skip Queries;
  i++; //Skip colon;
  map<string, Relation>::iterator it;
  while(v.at(i).getTypeint() != _eof){
    string name;
    name = v.at(i).getValue(); //stores name of query
    it = db.find(name); //finds relation with name matching the query
    i++;
    vector<string> tup;
    bool lpar = v.at(i).getTypeint() == _left_paren;
    if(lpar){ //reads in parameters
      i++;
      bool rpar = v.at(i).getTypeint() == _right_paren;
      while(!rpar){
        rpar = v.at(i).getTypeint() == _right_paren;
        int tok_type = v.at(i).getTypeint();
        if(tok_type == _id){
          tup.push_back(v.at(i).getValue());
        }
        else if(tok_type == _string){
          tup.push_back(v.at(i).getValue());
        }
        i++;
      }
    }
    Tuple t(tup); //stores query parameters in a tuple
    Relation assessed = assessquery(t, it->second); //assesses the query and stores results in a relation
    output.push_back(assessed); //adds assessed relation to output vector
    while(v.at(i).getTypeint() != _id){ //iterate i until new id or eof
      if(v.at(i).getTypeint() == _eof){
        return;
      }
      i++;
    }
  }
  return;
}

Relation myInterpreter::assessquery(Tuple t, Relation r){//runs relational operators on a query, assists readqueries()
  vector<string> t_vec = t.getTuple();
  Relation local = r;

  //Step 1: Rename according to query
  local = local.rename(Scheme(t.getTuple())); //rename to be assessed relation according to query parameters

//Step 2: Find positions of parameters
  map<string, vector<int>> linked = checkSameness(t); //find any duplicates variables or constants in query
  vector<int> varpos = varPositions(t.getTuple()); //finds positions of variables in the query

  //Step 3: Select according to constants
  //Constants
  for(map<string, vector<int>>::iterator it = linked.begin(); it != linked.end(); it++){ //performs selects on constants
    if((int)it->first.at(0) == 39){ //checks to see if string starts with single quote
      int msize = it->second.size();
      for(int a = 0; a < msize; a++) //iterates through constant's position vector
      {
        local = local.select_pv(it->second.at(a), it->first); //performs select based on value and postion
      }
    }
  }

  //Step 4: Select according to variables
  //Variables
  if(varpos.size() > 0){ //only assess if there are variables
    for(map<string, vector<int>>::iterator it = linked.begin(); it != linked.end(); it++){ //performs selects on variables
      if((int)it->first.at(0) != 39) //checks to make sure string doesn't start with single quote
      {
        local = local.select_pp(it->second); //performs select based on position vector
      }
    }

    //Step 4.5: project according to variable positions
    varpos = removeDuplicates_pos(t.getTuple()); //finds positions of variables after removing duplicates
    local = local.project(varpos); //projects columns linked to variables
  }

  //Step 5: Return new assessed relation
  local.addQuery(t); //stores query in relation, for outputing
  return local; //returns query-assessed relation
}

map<string,vector<int>> myInterpreter::checkSameness(Tuple t){//evaluates common parameters in aquery, assists assessquery()
  map<string, vector<int>> m;
  vector<string> t_vec = t.getTuple();
  int t_vecSize = t_vec.size();
  vector<int> positions;

  //put strings from t into a map
  for(int a = 0; a < t_vecSize; a++){
    m.insert(pair<string, vector<int>>(t_vec.at(a), positions));
  }

  //find positions of t strings and stores in its associated vector
  for(map<string, vector<int>>::iterator it = m.begin(); it != m.end(); it++){
    for(int a = 0; a < t_vecSize; a++){ //iterates through tuple's vector
    if(it->first ==t_vec.at(a)){ //if the variable/constant matches the tuples value then stores position
      it->second.push_back(a);
    }
  }
}
return m; //returns map containing variables with a vector of their respective positions
}

vector<int> myInterpreter::varPositions(vector<string> vsch){//finds and returns position of variables within a query, assists assessquery()
  vector<int> vout;
  int vschSize = vsch.size();
  for(int a = 0; a < vschSize; a++){ //iterates through vector of strings
    if(vsch.at(a).at(0) != 39){ //if element is a variable (doesn't start with single quote), stores position
    vout.push_back(a);
  }
}
return vout;
}

vector<string> myInterpreter::removeDuplicates(vector<string> in){//removes duplicates in vector of strings,  assists projection stage in assessquery()
  vector<string> out;
  int inSize = in.size();
  for(int a = 0; a < inSize; a++){ //iterates through vector in
    int outSize = out.size();
    bool exists = false;
    for(int b = 0; b < outSize; b++){ //iterates through vector in again
      if(in.at(a) == out.at(b)){ //compares two elements, if it is not itself and it matchs then does not add to new vector
        exists = true;
      }
    }
    if(!exists){
      out.push_back(in.at(a)); //if element does not already exist in vector, adds it to new vector
    }
  }
  return out; //returns new vector without duplicates
}

vector<int> myInterpreter::removeDuplicates_pos(vector<string> in){//returns positions of vector without duplicates, assists projection stage in assessquery()
  vector<string> out;
  vector<int> out_int;
  int inSize = in.size();
  for(int a = 0; a < inSize; a++){ //iterates through vector in
    int outSize = out.size();
    bool exists = false;
    for(int b = 0; b < outSize; b++){ //iterates through vector in again
      if(in.at(a) == out.at(b)){ //compares two elements, if it is not itself and it matchs then does not add to new vector
        exists = true;
      }
    }
    if(!exists){
      out.push_back(in.at(a)); //if element does not already exist in vector, stores position
      out_int.push_back(a);
    }
  }
  return out_int; //returns vector of positions excluding duplicates
}

void myInterpreter::print_output(){//iterates through output vector and format-prints each Relation, called by readin()
  int outputSize = output.size();
  for(int a = 0; a < outputSize; a++){ //iterates through output vector
    output.at(a).print_output(); //format-prints each relation in output vector
  }
  return;
}
