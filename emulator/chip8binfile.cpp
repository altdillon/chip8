#include "chip8sys.h"

namespace chip8sys
{
  Ch8program::Ch8program(string path)
  {
    try
    {
      readfile(path,this->chip8binData);
      //cout << "size: " << chip8binData.size() << endl;
    }
    catch(binfileExspection& ex)
    {
      cout << ex.what() << endl;
    }
  }

  void Ch8program::readfile(string path,vector<uint8_t>& buffer)
  {
    streampos size; // size of the bianry file (8bit bytes)
    char *block; // block buffer
    ifstream ch8file (path, ios::in|ios::binary|ios::ate); // chip8 file opened as a binary
    // start reading in the file
    if(ch8file.is_open())
    {
      size = ch8file.tellg();
      size_t streamSize = (size_t)size; // we need to cast this to size_t
      block = new char[size];
      // find the start and end of the file and read it into memblock
      ch8file.seekg (0, ios::beg);
      ch8file.read(block,size);
      ch8file.close();
      // now copy mem block into the buffer vector
      // do it the dumb way... for now...
      for(size_t i = 0;i<size;i++)
      {
        buffer.push_back(block[i]);
      }   

      delete [] block;
    }
    else
    {
      throw new binfileExspection;
    }
  }
}
