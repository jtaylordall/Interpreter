#include <iostream>
#include <vector>
#include <cstdlib>
#include "myScanner.h"
#include "Token.h"
#include "myParser.h"
#include "myInterpreter.h"

using namespace std;

int main(int argc, char *argv[]) //pass in arguments (file name) from command line
{
  myScanner s(argv[1]); //create scanner object, opens file and scans automatically
  vector<Token> v = s.getTokens();

  if(s.success()){ //only parses if Scanner succeeds
    myParser p(v); //creates parser object, passes in vector of Tokens from s
    if(p.success()){ //only interprets if Parser succeeds
      myInterpreter i(v);
    }
  }
  return 0;
}
