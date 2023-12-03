#include <iostream>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <string>
#include <regex>

using namespace std;

// Give a filename and vector pointer, will attempt to read and separate that file
// into the vector line by line. 
bool vectorizeFile(string filename, vector<string>& lines)
{
  ifstream input{filename};
  if (!input)
  {
      cout << "CAN'T OPEN FILE DUMMY: " << filename << endl;
      return false;
  }

  string str;
  while(getline(input, str)) 
  {
    lines.push_back(str);
  }
  
  input.close();
  return true;
  
}

int main(int argc, char* argv[]) 
{
  vector<string> lines{};
  if (argc == 2)
  {
    if (!vectorizeFile(argv[1], lines))
    {
      return EXIT_FAILURE;
    }
  }
  
  // Part One + Two
  {
    int sum{0};
    int sumOfPowers{0};
    int gameCounter{1};
  
    for (const auto& line : lines)
    {
      map<string, int> colourMap = 
      {
        {"red", 0},
        {"green", 0},
        {"blue", 0},
      };
      
      if (line.empty())
      {
        cout << sum << endl;
        cout << sumOfPowers << endl;
      } 
      else 
      {
        regex digitWordRegex("(red|blue|green|\\d{1,})");
        auto regexIterator = sregex_iterator(line.begin() + 8, line.end(), digitWordRegex); 
       
        for (auto it = regexIterator; it != sregex_iterator(); ++it) 
        {
          int numberOfBalls{0};
    	  string ballColour{};
          numberOfBalls = stoi((*it)[1].str());
          ballColour = (*(++it))[1].str();
          
          if (numberOfBalls > colourMap[ballColour])
          {
            colourMap[ballColour] = numberOfBalls;
          }
        }
        
	if ((colourMap["red"] <= 12) && (colourMap["blue"] <= 14) && (colourMap["green"] <= 13))
	{
	  sum += gameCounter;  
	  cout << "gameCounter: " << gameCounter << endl;
	  cout << "currentSum: " << sum << endl;
	}
	
	sumOfPowers += (colourMap["red"] * colourMap["blue"] * colourMap["green"]);
        ++gameCounter;
      }
    }
  }
}
