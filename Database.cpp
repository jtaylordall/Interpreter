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
