#include "disass8header.h"

using namespace std;

namespace disassembler
{
  Ch8file::Ch8file() // default header function
  {
    cout << "hey this is a the chip8 assemplied file" << endl;
  }

  Ch8file::Ch8file(string filePath)
  {
    if(filePath.length() > 0)
    {
      this->rawhex = new vector<uint8_t>();
      this->readRawHex(filePath,this->rawhex);
    }
  }

  size_t Ch8file::readRawHex(string filePath,vector<uint8_t> *rawdat)
  {
    // http://www.cplusplus.com/reference/fstream/ifstream/
    // define some instance variables 
    vector<uint8_t> rawHexBuff;
    
    size_t lenData = 0;
    // open the file and make sure that ifstream knows that we want it as bianry
    ifstream ch8file (filePath, ifstream::binary);
    if(ch8file)
    {
      // get the length of the file
      ch8file.seekg(0,ch8file.end);
      int length =  ch8file.tellg();
      ch8file.seekg(0,ch8file.beg);
      cout << "ch8file length: " << length << " bytes" << endl;
      // read the file as a block into a buffer
      char *buffer = new char[length]; // allocate buffer a dynamic array
      ch8file.read(buffer,length); // read the file in as a single block
      
      //delete [] buffer; // kill it before it lays eggs!
      // see if the file was actually read in  
      if(ch8file)
      {
        cout << "all bytes read in!" << endl;
        // copy all the bytes into the vector 
        for(int i=0;i<length;i++)
        {
          (*rawdat).push_back(buffer[i]);
        }
      }
      else
      {
        cout << "Error, only " << ch8file.gcount() << " bytes read in " << endl;
      }


      delete [] buffer;
    }
    else
    {
      cout << "file not found! " << endl;
    }

    return lenData;
  }

  Ch8file::~Ch8file()
  {
    delete this->rawhex;
  }

  void Ch8file::printOut()
  {
    int rawHexSize = this->rawhex->size();
    for(int i = 0;i<rawHexSize;i++)
    {
      unsigned char memvalue = this->rawhex->at(i);
      printf("%d : 0x%.2x \n",i,memvalue);
    }
  }

  vector<string> Ch8file::disAssembleCh8()
  {
    vector<string> asmPgm;

    // TODO make a big ol switch statement that takes in the assembled hex and converters it
    // ... to human readable assembley!!!
    for(int i = 0;i<this->rawhex->size();i++)
    {
      uint8_t opValue = this->rawhex->at(i);
      uint8_t firstNib = opValue >> 4; // shift the bits over to get the opcode
      // https://stackoverflow.com/questions/4983092/c-equivalent-of-sprintf
      // https://www.cplusplus.com/forum/windows/51591/

      // print out the memory address in hex, with the 0x200 offset
      cout << hex << "0x" << (i+0x200) << " ";

      // use switch to print out the 8bit command
      switch(firstNib)
      {
        case 0x00: cout << "op not handled" << endl;
        case 0x01: cout << "op not handled" << endl;
        case 0x02: cout << "op not handled" << endl;
        case 0x03: cout << "op not handled" << endl;
        case 0x04: cout << "op not handled" << endl;
        case 0x05: cout << "op not handled" << endl;
        case 0x06: cout << "op not handled" << endl;
        case 0x07: cout << "op not handled" << endl;
        case 0x08: cout << "op not handled" << endl;
        case 0x09: cout << "op not handled" << endl;
        case 0x0A: cout << "op not handled" << endl;
        case 0x0B: cout << "op not handled" << endl;
        case 0x0C: cout << "op not handled" << endl;
        case 0x0D: cout << "op not handled" << endl;
        case 0x0E: cout << "op not handled" << endl;
        case 0x0F: cout << "op not handled" << endl;
        default: cout << "unknown opcode" << endl;
      }
    }
    return asmPgm;
  }

}

