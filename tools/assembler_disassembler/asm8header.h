#ifndef ASM8HEADER
#define ASM8HEADER
#include <iostream>
#include <vector>
#include <stdint.h>
#include "disass8header.h"

using namespace std;

namespace assembler
{

  struct opCode
  {
    string opcode; 
    uint8_t reg;
  };

  class Ch8asmCode
  {
    public:
      Ch8asmCode(); // defult constructor
      Ch8asmCode(string filePath); // load an assemly program from a file
      disassembler::Ch8file getByteCode(); // return the byte code

    private:
      vector<string> rawAsm; // raw asm test
      int lines;
      int loadFromSource(vector<string>& buffer,string& path); // read in a souce file
  };

}

#endif
