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

      // clean up by closing the file and freeing up extra memory
      ch8file.close();
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
    // I will delete this in the future, but for the time being keep b/c there's some good ideas in this
/*
    // TODO make a big ol switch statement that takes in the assembled hex and converters it
    // ... to human readable assembley!!!
    for(int i = 0;i<this->rawhex->size();i++)
    {
      uint8_t opValue = this->rawhex->at(i);
      uint8_t firstNib = opValue >> 4; // shift the bits over to get the opcode
      // https://stackoverflow.com/questions/4983092/c-equivalent-of-sprintf
      // https://www.cplusplus.com/forum/windows/51591/

      // print out the memory address in hex, with the 0x200 offset
      //cout << hex << "0x" << (i+0x200) << " ";
      //cout << hex << "0x" << firstNib << endl;
      //printf("0x%.2x : 0x%.2x :> ",i+0x200,firstNib); // smh++  TODO: make this work in C++

      // use switch to print out the 8bit command
      
      
    }
*/

    /*
     TODO: clean up the iterator 
    */

   
    vector<string> asmPgm; // hold the disassembled chip8 program
    vector<uint8_t>::iterator itr; // iterator for the vector holding our chip8 program
    // use the interator and a while loop to list all the 16 bit values in the chip8 file
    uint16_t chip8mem;
    uint16_t chip8memcount = 0x0000;
    itr = this->rawhex->begin(); // start the iterator
    while(itr != this->rawhex->end())
    {
      // make two 8 bit values into a 16bit value 
      //chip8mem = *itr;
      uint8_t firstByte = *itr;
      //++ itr;
      uint8_t secondByte = *(++itr);
      //chip8mem = (chip8mem << 8) | (*itr & 0xff);
      chip8mem = (firstByte << 8) | secondByte;

      if(chip8mem != 0x000 ) // 0x0000 is just blank, so don't print anything out here
      {
        printf("0x%.3x : 0x%.4x  ",chip8memcount+0x200,chip8mem);
        //printf("0x%.3x : 0x%.4x  ",chip8memcount,chip8mem); // remove the offset     

        // use a switch statement to do some basic decoding.
        // start with the first byte, than do some extra stuff depending on the second byte
        uint8_t firstNib = firstByte >> 4; // get the first nibble
        switch(firstNib)
        {
          case 0x00: 
            {
              if(secondByte == 0xE0) // CLS
              {
                cout << "CLS" << endl;
              }
              else if(secondByte == 0xEE) // REG
              {
                cout << "RET" << endl;
              }
              else // this might print out a new line if the thing is data? It might also have to do with the sys adder function, which should be ignored
              {
                //printf("hi: 0x%.2x lo: 0x%.2x firstnib: 0x%.2x \n",firstByte,secondByte,firstNib);
                cout << "data?" << endl;
              }
            } 
          break;
          case 0x01: // JP (jump) to address nnn
            { 
              // get the address info from the last 3 bytes
              uint16_t addr =  chip8mem & 0x0FFF; 
              printf("JP 0x%.3x \n",addr);           
            }
            break;
          case 0x02: // Call adder
            {
              uint16_t addr = chip8mem & 0x0FFF;
              printf("Call 0x%.3x \n",addr);
            } 
            break;
          case 0x03: 
            {
              uint8_t reg = firstByte & 0x0F;
              printf("SE V%d, 0x%.2x \n",reg,secondByte);
            }
            break;
          case 0x04: 
            {
              uint8_t reg = firstByte & 0x0F;
              printf("SNE V%d, 0x%.2x \n",reg,secondByte);     
            } 
            break;
          case 0x05: 
            {
              // pull out VX and VY
              uint8_t VX = firstByte & 0x0F;
              uint8_t VY = secondByte >> 4;
              printf("SE V%d , V%d \n",VX,VY); 
            }
            break;
          case 0x06: 
            {
              uint8_t VX = firstByte & 0x0F;
              printf("LD V%d, 0x%.2x \n",VX,secondByte);
            }
            break;
          case 0x07: 
            {
              uint8_t VX = firstByte & 0x0F;
              printf("ADD V%d, 0x%.2x \n",VX,secondByte);
            } 
            break;
          case 0x08: 
            {
              // get the values for VX and VY
              uint8_t VX = firstByte & 0x0F;
              uint8_t VY = secondByte >> 4;
              // get the last byte, which are basicly ALU stuff
              uint8_t aluOp = secondByte & 0x0F;
              // now figure out which value to print out
              switch(aluOp)
              {
                case 0x00: printf("LD V%d, V%d \n",VX,VY); break;
                case 0x01: printf("OR V%d, V%d \n",VX,VY); break;
                case 0x02: printf("AND V%d, V%d \n",VX,VY); break;
                case 0x03: printf("XOR V%d, V%d \n",VX,VY); break;
                case 0x04: printf("ADD V%d, V%d \n",VX,VY); break;
                case 0x05: printf("SUB V%d, V%d \n",VX,VY); break;
                case 0x06: printf("SHR V%d, {V%d} \n",VX,VY); break;
                case 0x07: printf("SUBN V%d, V%d \n",VX,VY); break;
                case 0x0E: printf("SHL V%d, {V%d} \n",VX,VY); break;
                
                default: printf("%s\n","ALU operation not handled"); break;
              }
            } 
            break;
          case 0x09: 
            {
              uint8_t VX = firstByte & 0x0F;
              uint8_t VY = secondByte >> 4;
              printf("SNE V%d, V%d \n",VX,VY);
            }
            break;
          case 0x0A: // ANNN, LD, I think this instruction sets a value called I to NNN.  I is used for indirect addressing?
            {
              uint16_t ivalue = chip8mem & 0x0FFF; // mask out the values 
              printf("LD I, 0x%.3x \n",ivalue);
            }
            break;
          case 0x0B: 
           {
              uint16_t ivalue = chip8mem & 0x0FFF; // mask out the values 
              printf("JP V0, 0x%.3x \n",ivalue);            
           }
           break;
          case 0x0C: 
            {
              uint8_t VX = firstByte & 0x0F;
              printf("RND V%d, 0x%.2x \n",VX,secondByte);
            }
            break;
          case 0x0D: 
            {
              // get the values for VX and VY and the nibble.  Use a mask
              uint8_t VX = firstByte & 0x0F;
              uint8_t VY = (secondByte & 0xF0) >> 4;
              uint8_t nibble = secondByte & 0x0F; // nibble is a 4 bit value.  Byte... Nibble lol 
              printf("DRW V%d, V%d, %.1x \n",VX,VY,nibble); 
            }
            break;
          case 0x0E: 
            {
              uint8_t VX = firstByte & 0x0F;

              if(secondByte == 0x9E) // SKP
              {
                printf("SKP V%d \n",VX);
              }
              else if(secondByte == 0xA1) // SKNP
              {
                printf("SKNP V%d \n",VX);
              }
              else
              {
                cout << endl; // this fixes a newline error caused by some un handed commands
              }
            } 
            break;
          case 0x0F: 
            {
              uint8_t VX = firstByte & 0x0F;
              // use a switch statment to look for other bytes
              switch(secondByte)
              {
                case 0x07: printf("LD V%d, DT\n",VX); break;
                case 0x0A: printf("LD V%d, K\n",VX); break;
                case 0x15: printf("LD DT, V%d \n",VX); break;
                case 0x1E: printf("ADD I, V%d \n",VX); break;
                case 0x29: printf("LD F, V%d \n",VX); break;
                case 0x33: printf("LD B, V%d \n",VX); break;
                case 0x55: printf("LD [I], V%d \n",VX); break;
                case 0x65: printf("LD V%d, [I] \n",VX); break;
                default: cout << "unknown command" << endl; break;
              }
            }    
            break;
          default: cout << "unknown command" << endl; break;
        }
      }
      

      //cout << endl;
      chip8memcount++;
      ++itr; // get the next element in the vector
    }

    return asmPgm;
  }

}

