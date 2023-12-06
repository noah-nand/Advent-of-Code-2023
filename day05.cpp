#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;

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
  
  // Part One
  {
    int lowestLocation{0};
    
    vector<long long int> seeds;
    string lineHolder;
    stringstream ss(lines.front());
    
    while(getline(ss, lineHolder, ' '))
    {
      seeds.push_back(stol(lineHolder));
    }
    
    lines.erase(lines.begin());
    lines.erase(lines.begin());
    
    for (const auto& seed : seeds) 
    {
      long int currentSeed = seed;
      cout << "---------------" << endl;
      
      bool finishedSection = false;
    
      for (const auto& line : lines)
      { 
    
        if (line == "end")
        {
          cout << "end of the line!" << endl;
 	  if (currentSeed < lowestLocation || lowestLocation == 0)
 	  {
 	    cout << "end of the line!" << endl;
 	    lowestLocation = currentSeed;
 	  }
        } 
        else if (line.empty())
        {
          finishedSection = false;
        } 
        else if (finishedSection)
        {
         // nothing
        }
        else 
        {
          vector<long long int> mapperNumbers;
          ss = stringstream(line);
          while(getline(ss, lineHolder, ' '))
          {
            mapperNumbers.push_back(stol(lineHolder));
          }
        
	  if ((currentSeed >= mapperNumbers[1]) && (currentSeed <= (mapperNumbers[1] + mapperNumbers[2] - 1)))
	  {
	     cout << "found matching mapper!" << endl;
	     cout << currentSeed << " is between " << mapperNumbers[1] << " and " << mapperNumbers[1] + mapperNumbers[2] << endl;
	     cout << "adding " << (mapperNumbers[0] - mapperNumbers[1]) << endl;
	     currentSeed = currentSeed + (mapperNumbers[0] - mapperNumbers[1]);
	     cout << currentSeed << " new current seed" << endl;
	     finishedSection = true;
	  }
        }
      }  
    }    
    cout << lowestLocation << endl; 
  }
}      
      
      
      
      
      
