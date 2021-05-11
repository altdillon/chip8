#ifndef CHIP8_SYS
#define CHIP8_SYS
#include <iostream>
#include <exception>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <stdint.h>
#include "chip8emucfg.h"

using namespace std; 

namespace chip8sys
{
  class binfileExspection: public exception
  {
    public:
    virtual const char* what() const throw()
    {
      return "filed to read in ch8 file";
    }
  };

  // class for an assembled chip8 program
  class Ch8program
  {
    public:
      Ch8program(string path);
      //Ch8program();
      size_t fileSize();            // return the size of the file in bytes.  I hate getters, but this saves typing
      vector<uint8_t> chip8binData; // tbt in ideal OOP this should be private, but there's no good reason for this not be public
    private:
      void readfile(string path,vector<uint8_t>& buffer);
      string lastFile;
  };

  // class for the chip8's ram
  // I normally say "just let data be data" but I wanted to mess with operator overloading.
  class Ch8ram
  {
    public:
      Ch8ram(Ch8program starting); // start the ch8 ram with a given size    
      //Ch8ram(Ch8program starting,size_t memSize);
      uint8_t operator[] (int); // pointless but just becouse I can
      vector<uint8_t> ramData;
  };
}

#endif
