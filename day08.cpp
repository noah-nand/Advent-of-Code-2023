#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool mapperizeFile(string filename, map<string, pair<string, string>>& instructionMap, string& leftRightString)
{
  ifstream input{filename};
  if (!input)
  {
    cout << "CAN'T OPEN FILE DUMMY: " << filename << endl;
    return false;
  }

  string str;
  
  getline(input, str);
  leftRightString = str;
  getline(input, str);
  
  while(getline(input, str)) 
  {
    instructionMap.insert({str.substr(0,3), {str.substr(7,3), str.substr(12,3)}});
  }
  
  input.close();
  return true;
}


int main(int argc, char* argv[]) 
{
  map<string, pair<string, string>> instructionMap{};
  string leftRightString;

  if (argc == 2)
  {
    if (!mapperizeFile(argv[1], instructionMap, leftRightString))
    {
      return EXIT_FAILURE;
    }
  }
  
  int maxCounter = leftRightString.size()-1;
  int stepCounter{0};
  string currentInstruction{"AAA"};
  int leftRightCounter{0};
  
  while(currentInstruction != "ZZZ")
  {
  
    cout << leftRightCounter << endl;
    stepCounter++;
 
    switch(leftRightString[leftRightCounter])
    {
      case 'L':
      {
        currentInstruction = instructionMap[currentInstruction].first;
        break;
      }
      case 'R':
      {
        currentInstruction = instructionMap[currentInstruction].second;
        break;
      }
    }
  
    cout << currentInstruction << endl;
  
    if (leftRightCounter == maxCounter)
    {
      leftRightCounter = 0;
    } 
    else 
    {
      leftRightCounter++;
    }
  }
  
  cout << stepCounter << endl;
  
}
