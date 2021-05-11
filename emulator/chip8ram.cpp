#include "chip8sys.h"

namespace chip8sys
{
  Ch8ram::Ch8ram(Ch8program starting)
  {
    this->ramData = starting.chip8binData; // assignment operator can be used to copy
    //copy(starting.begin(), starting.end(), back_inserter(ramData));
  }
  
  // this is pointless, but I think operator overloading is neat
  // and I never get to do it
  // and it's something that'll make my code look cleaner down the line
  // ... fite me!
  uint8_t Ch8ram::operator[] (int index)
  {
    return this->ramData.at(index);
  }

}
