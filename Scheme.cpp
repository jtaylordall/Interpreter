#include "Scheme.h"

//Constructors
Scheme::Scheme(vector<string> att_in){
  att = att_in;
}

Scheme::Scheme(){}


//Member Functions
vector<string> Scheme::getScheme(){//Returns Scheme as a vector
  return att;
}
