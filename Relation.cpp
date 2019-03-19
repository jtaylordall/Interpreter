#include "Relation.h"

//Constructors
Relation::Relation(){}

Relation::Relation(string name_in, Scheme sch_in){
  name = name_in;
  sch = sch_in;
}

Relation::Relation(string name_in, Scheme sch_in, set<Tuple> tup_in){
  name = name_in;
  sch = sch_in;
  tup = tup_in;
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
  cout << "Name: " << name << "\n";
  cout << "Scheme:" << sch.toString() << "\nTuples:\n";
  for (it = tup.begin(); it != tup.end(); ++it)
  {
    Tuple iter = *it;
    cout << "  " << iter.toString() << "\n";
  }
  cout << "\n";
}

//Relational Operations
Relation Relation::select_pv(int position, string value){//Finds tuples that have value at position, returns a vector of these tuples
  vector<string> test;
  Relation r(name, sch);
  for (it = tup.begin(); it != tup.end(); ++it){
    Tuple iter = *it;
    test = iter.getTuple();
    if (test.at(position) == value){
      Tuple t(test);
      r.addTuple(t);
    }
  }
  return r;
}

Relation Relation::select_pp(int position1, int position2){//Finds tuples that have same value at positions 1 and 2, returns a vector of these tuples
  vector<string> test;
  Relation r(name, sch);
  for (it = tup.begin(); it != tup.end(); ++it){
    Tuple iter = *it;
    test = iter.getTuple();
    if (test.at(position1) == test.at(position2)){
      Tuple t(test);
      r.addTuple(t);
    }
  }
  return r;
}

Relation Relation::project(vector<int> positions){//projects relation according to the positions vector

  it = tup.begin();
  Tuple iter = *it;
  int sizeTup = iter.getSize();
  vector<Tuple> listofcolumns;

  for(int i = 0; i < sizeTup; i++){ //store relation in vector of tuples
    vector<string> columncontents;
    for(it = tup.begin(); it != tup.end(); ++it){
      iter = *it;
      vector<string> row = iter.getTuple();
      string temp = row.at(i);
      columncontents.push_back(temp);
    }
    Tuple column(columncontents);
    listofcolumns.push_back(column);
  }


  vector<Tuple> listofcolumns2;
  int posSize = positions.size();

  for(int j = 0; j < posSize; j++){//rearranges columns according to positions vector
    int columnget = positions.at(j);
    Tuple t(listofcolumns.at(columnget));
    listofcolumns2.push_back(t);
  }

  int loc2Size = listofcolumns2.size();
  set<Tuple> newtup;
  int cbdSize = listofcolumns2.at(0).getTuple().size();

  for(int l = 0; l < cbdSize; l++){
    vector<string> rowbuild;
    for(int k = 0; k < loc2Size; k++){
      rowbuild.push_back(listofcolumns2.at(k).getTuple().at(l));
    }
    Tuple newt(rowbuild);
    newtup.insert(newt);
  }

  //tup = newtup;
  Relation r(name, project_scheme(positions), newtup);
  return r;
}

Scheme Relation::project_scheme(vector<int> positions){//rearranges scheme according to positions vector, supports project()
  vector<string> currentScheme = sch.getScheme();
  vector<string> newScheme;
  int posSize = positions.size();
  for(int i = 0; i < posSize; i++){
    int attget = positions.at(i);
    newScheme.push_back(currentScheme.at(attget));
  }
  Scheme s(newScheme);
  return s;
}

Relation Relation::rename(Scheme in){//replaces the scheme with inputed one
  Relation r(name, in, tup);
  return r;
}
