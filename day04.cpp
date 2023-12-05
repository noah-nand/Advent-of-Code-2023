#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <math.h>

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

int doublethis(int times){
    int result;
    if (times == 0){
        result = 1;
    }
    if(times > 0) {
        result = 2 * doublethis(times - 1);
    }
    return result;
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
    int cardNum{0};
    
    for (const auto& line : lines)
    { 
      cardNum++;
    
      if (line.empty())
      {
        cout << sum << endl;

      } 
      else 
      {
        int points{0};
      
        string winningNumbers = line.substr(10, 29);
	vector<string> winningNumberVector;
	stringstream winningStream(winningNumbers);
	
	string scratchedNumbers = line.substr(42, 74);
        vector<string> scratchedNumbersVector;
	stringstream scratchedStream(scratchedNumbers);
	
	string numberHolder;
	
	while(getline(winningStream, numberHolder, ' '))
	{
	  if(!numberHolder.empty())
	  {
	    winningNumberVector.push_back(numberHolder);
	  }
	}
	
	while(getline(scratchedStream, numberHolder, ' '))
	{
	  if(!numberHolder.empty())
	  {
	    scratchedNumbersVector.push_back(numberHolder);
	  }
	}
	
	for (int i = 0; i < scratchedNumbersVector.size(); i++) 
	{
          if(find(winningNumberVector.begin(), winningNumberVector.end(), scratchedNumbersVector[i]) !=  winningNumberVector.end())
          {
	    ++points;	
          }
        }
        
        if (points != 0) 
        {
          sum += doublethis(points-1);
        }
      } 
    }
  }
}
