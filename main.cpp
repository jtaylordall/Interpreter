#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "myScanner.h"
#include "Token.h"
#include "myParser.h"
#include "myInterpreter.h"

using namespace std;

int main(int argc, char *argv[]) //pass in arguments (file name) from command line
{
  myScanner s(argv[1]); //create scanner object, opens file and scans automatically
  vector<Token> v = s.getTokens();
  myParser p(v); //creates parser object, passes in vector of Tokens from s
  myInterpreter i(v);
  return 0;
}
