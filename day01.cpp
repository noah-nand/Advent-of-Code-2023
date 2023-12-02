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

// Take a string, see if it exists in the map. If it does, 
// return mapped string. Otherwise, return original string
string transformString(string& input) 
{
    map<string, string> digitMap = 
    {
        {"one", "1"},
        {"two", "2"},
        {"three", "3"},
        {"four", "4"},
        {"five", "5"},
        {"six", "6"},
        {"seven", "7"},
        {"eight", "8"},
        {"nine", "9"}
    };

    auto searchResult = digitMap.find(input);

    if (searchResult != digitMap.end()) 
    {
        return searchResult->second;
    } 
    else 
    {
        return input;
    }
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

  // Part One
  {
    int sum{0};

    for (const auto& line : lines)
    {
      if (line.empty())
      {
        cout << "The first sum is: " << sum << endl;
      }
      else 
      {
      	char firstDigit{};
      	char secondDigit{};
      	string number{};
      
      	for (auto &ch : line)
      	{
       	  if (isdigit(ch))
          { 
            firstDigit = ch;  
            break;
          }
        }

        for (auto &ch : string(line.rbegin(), line.rend()))
        {
          if (isdigit(ch)) 
          {
            secondDigit = ch;
            break;
          }
         }

         number += firstDigit;
         number += secondDigit;
         sum += stoi(number);

      }
    }
  }

  // Part Two
  {
    int sum{0};
    
    for (const auto& line : lines)
    {
      string number{};
      
      if (line.empty())
      {
        cout << "The second sum is: " << sum << endl;
      } 
      else 
      {
        regex digitWordRegex("(?=(one|two|three|four|five|six|seven|eight|nine|\\d))");
        auto regexIterator = sregex_iterator(line.begin(), line.end(), digitWordRegex);  
        auto lastMatch = sregex_iterator();   
   
   	// Whatever, blow me 
        for (auto it = regexIterator; it != sregex_iterator(); ++it) 
        {
          lastMatch = it;
        }

	// I don't really follow this part, but it's
	// what I found online to extract the value from the
	// iterator.
        smatch firstMatchResult = *regexIterator;
        string firstValue = firstMatchResult[1].str();
        
        smatch lastMatchResult = *lastMatch;
        string lastValue = lastMatchResult[1].str();
	
	number += transformString(firstValue);
	number += transformString(lastValue);
	
	sum += stoi(number);
      }
    }
  }
}
