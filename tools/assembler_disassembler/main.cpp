#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h> 
#include "asm8header.h"
#include "disass8header.h"

using namespace std;
using namespace assembler;

// for the time being all the commandline UI functions will be in main
// eventually this will be moved into their own file
/*
bool isCommand(string st);                              // return true if st is a commandline option
void printHelp();                                       // print out the help stuff
bool isCh8file(string fileName);                        // return true if the file has a .ch8 extention
bool isAsmFile(string fileName);                        // return true if the file has a .S, .asm, or .as extention
bool isValidCommand(string fileName,string directive);  // make sure that the directive and file extetion are valid
*/

// struct for UI options and commands and also some options
enum asmOpt_t { assemble,dissable,object};

struct toolOpt_t
{
  vector <asmOpt_t> controlOptions;
  vector <string> ch8FileNames;
  vector <string> asmFileNames;
};


// prototypes for functions we're actually using
int parseCommand(toolOpt_t &opts);
void printHelp();

int main(int argc, char **argv)
{
  toolOpt_t toolopt; // hold the tools

  if(argc <= 1)
  {
    printHelp();
  }
  else
  {
    for(int i = 0;i<argc;i++)
    {
      string argstr = string(argv[i]);
      if(argstr == "-a") // assemble
      {
        cout << "assemble" << endl;
        toolopt.controlOptions.push_back(asmOpt_t::assemble);
      }
      else if(argstr == "-d") // disssemble
      {
        cout << "disassemble" << endl;
        toolopt.controlOptions.push_back(asmOpt_t::dissable);
      }
      else if(argstr == "-o") // name of object
      {
        cout << "object" << endl;
        toolopt.controlOptions.push_back(asmOpt_t::object);
      }
      else
      {
        if(argstr.find(".ch8") != string::npos)// || argstr.find(".ch8") != string::npos || argstr.find(".ch8") != string::npos || argstr.find(".S") != string::npos)     
        {
          cout << "ch8 file" << endl; 
          toolopt.ch8FileNames.push_back(argstr);
        }
        else if(argstr.find(".S") != string::npos || argstr.find(".asm") != string::npos)
        {
          cout << "assembley file" << endl;
          toolopt.asmFileNames.push_back(argstr);
        }
//        else if(argstr.find(".asm") != string::npos)
//        {
//          cout << "asm file" << endl;
//        }
      }
      
      // ok now that we've parsed all the options actually do assembler stuff
      parseCommand(toolopt);
      
    }
  }

  /*

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
      loadedch8File.disAssembleCh8();
    }
    
    if(isAsmFile(fileName)) // assemble a ch8 program
    {

    }
  }
  */
  return 0;
}

int parseCommand(toolOpt_t &opts)
{
  for(int i = 0;i < opts.controlOptions.size();i++)
  {
    if(opts.controlOptions.at(i) == assemble)
    {

    }
    else if(opts.controlOptions.at(i) == dissable)
    {
      // disassemble all the listed files in a list
      for(int j = 0;j<opts.ch8FileNames.size();j++)
      {
        string ch8path = opts.ch8FileNames.at(j);
        disassembler::Ch8file loadedch8File(ch8path);
        //loadedch8File.printOut();
        vector<string> asmch8 = loadedch8File.disAssembleCh8();
      }
    }
    else if(opts.controlOptions.at(i) == object)
    {

    }
  }

  return -1;
}

void printHelp()
{
    cout << "usage: args filenames" << endl;
    cout << "assemble -a" << endl;
    cout << "disassemble -d" << endl;
    cout << "object -o" << endl;
}

/*

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
*/
