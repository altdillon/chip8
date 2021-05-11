#include <iostream>
#include<GL/glut.h>
#include "chip8emucfg.h"
#include "chip8sys.h"

using namespace chip8sys;

int main(int argc, char** argv)
{
  // testing stuff...
  Ch8program fishie8("./roms/Fishie.ch8");
  Ch8ram ram(fishie8);

  return 0;
}
