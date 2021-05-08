#include "asm8header.h"
//#include "disass8header.h"

namespace assembler
{
  // public stuff

  Ch8asmCode::Ch8asmCode()
  {
    lines = 0;
  }

  Ch8asmCode::Ch8asmCode(string filePath)
  {
    if(this->loadFromSource(this->rawAsm,filePath) < 0)
    {

    }
  }

  // private stuff
  int Ch8asmCode::loadFromSource(vector<string>& buffer,string& path)
  {
    // open the souce file and see if it's open
    ifstream asmFile(path);
    if(asmFile.is_open())
    {
      // read the file in
      string line;
      while(getline(asmFile,line))
      {
        buffer.push_back(line);
      }

      asmFile.close(); 
    }
    else
    {
      cout << "can't open file: " << path << endl;
    }

    return buffer.size();
  }
}
