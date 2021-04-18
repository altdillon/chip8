#ifndef DIS8HEADER
#define DIS8HEADER
#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h> 
#include <stdio.h>
#include "asm8header.h"

using namespace std;

namespace disassembler
{
  class Ch8file
  {
  public:
    // constructors 
    Ch8file();
    Ch8file(string filePath);
    ~Ch8file();
   // public methods 
   void printOut();
   assembler::Ch8asmCode disAssembleCh8();

  private:
    vector<char> *rawhex;                      // the read in raw hex
    size_t readRawHex(string filePath,vector<char> *rawdat); // helper function for reading in raw hex
  };
}

#endif
