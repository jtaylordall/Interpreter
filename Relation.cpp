#include "Relation.h"

//Constructors
Relation::Relation(){}

Relation::Relation(string name_in, Scheme sch_in){
  name = name_in;
  sch = sch_in;
}


//Member Functions
string Relation::getName(){//Returns name of Relation
  return name;
}

void Relation::addTuple(Tuple t){//Adds new Tuple to relation
  tup.insert(t);
  return;
}

void Relation::print(){//couts Relation
  set<Tuple>::iterator it;
  cout << name << "\n";
  for (it = tup.begin(); it != tup.end(); ++it)
  {
    Tuple iter = *it;
    cout << iter.toString() << "\n";
  }
  cout << "\n";
}
