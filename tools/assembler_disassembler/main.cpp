#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h> 
#include "asm8header.h"
#include "disass8header.h"

using namespace std;

// for the time being all the commandline UI functions will be in main
// eventually this will be moved into their own file
bool isCommand(string st);                              // return true if st is a commandline option
void printHelp();                                       // print out the help stuff
bool isCh8file(string fileName);                        // return true if the file has a .ch8 extention
bool isAsmFile(string fileName);                        // return true if the file has a .S, .asm, or .as extention
bool isValidCommand(string fileName,string directive);  // make sure that the directive and file extetion are valid

int main(int argc, char **argv)
{
  if(argc < 1)
  {
    printHelp();
  }
  else 
  {
    //cout << "number of args: " << argc << endl;
    //cout << "arg1: " << argv[1] << " file name: " << argv[2] << endl;
    string command = string();
    string fileName = string();
    for(size_t i = 1;i<argc;i++)
    {
      if(isCommand(argv[i])) // determine the string is a command, -a or -d
      {
        //cout << "argv: " << argv[i] << endl;
        command = argv[i];
      }
      else if(isCh8file(argv[i]) || isAsmFile(argv[i]))
      {
        fileName = argv[i];
      }
    }

    

    // print out some info
    //cout << "file name: " << command << " command: " << fileName << endl;
    if(isCh8file(fileName)) // disassemble a ch8 program
    {
      disassembler::Ch8file loadedch8File(fileName);
      loadedch8File.printOut();
    }
    
    if(isAsmFile(fileName)) // assemble a ch8 program
    {

    }
  }

  return 0;
}

void printHelp()
{
    cout << "usage: arg filename" << endl;
    cout << "assemble -a" << endl;
    cout << "disassemble -d" << endl;
}


bool isValidCommand(string fileName,string directive)
{
  bool isValid = false;

  if(isCh8file(fileName) && directive == "-d" || isAsmFile(fileName) && directive == "-a")
  {
    isValid = true;
  }

  return isValid;
}

bool isCh8file(string fileName)
{
  bool hasCh8 = false;

  if(fileName.find(".ch8") != string::npos)
  {
    hasCh8 = true;
  }

  return hasCh8;
}

bool isAsmFile(string fileName)
{
  bool hasAsm = false;

  if(fileName.find(".S") != string::npos || fileName.find(".asm") !=string::npos || fileName.find(".as") != string::npos)
  {
    hasAsm = true;
  }

  return hasAsm;
}

bool isCommand(string st)
{
  bool out = false;

  if(st == "-a" || st == "-d" || st == "-h")
  {
    out = true;
  }
  
  return out;
}
