#include "Database.h"

//Constructor
Database::Database(){}


//Member Functions
void Database::addRelation(Relation r){//adds Relation with linked name to Database
  db.insert(pair<string, Relation>(r.getName(), r));
  return;
}

void Database::print(){//couts Database by relations
  for(map<string, Relation>::iterator it = db.begin(); it !=db.end(); it++){
    it->second.print();
  }
  return;
}

map<string, Relation>::iterator Database::find(string in){//Returns iterator of relation with desired name
  return db.find(in);
}

Database Database::test(){
  Database local;
  vector<int> a;
  a.push_back(2);
  a.push_back(1);
  a.push_back(0);
  for(map<string, Relation>::iterator it = db.begin(); it !=db.end(); it++){
    vector<string> b;
    b.push_back("X");
    b.push_back("Y");
    b.push_back("Z");
    Scheme s(b);
    Relation r1 = it->second.rename(s);
    Relation r2 = r1.project(a);
    local.addRelation(r2);
  }
  return local;
}
