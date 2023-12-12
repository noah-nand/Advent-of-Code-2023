#include <iostream>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <string>
#include <regex>

using namespace std;

bool vectorizeFile(string filename, vector<vector<char>>& map)
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
    vector<char> line;
    for (auto &ch : str)
    {
      line.push_back(ch);
    }
    
    map.push_back(line);
    
  }
  input.close();
  return true;
}

pair<int, int> findStartingCoordinate(vector<vector<char>>& map)
{
  for(int i = 0; i < map.size(); i++)
  {
    for(int j = 0; j < map[i].size(); j++)
    {
        if (map[i][j] == 'S')
      {
        return {i, j};
      }
    }
  }
  return {0,0};
}

pair<int, int> continuePath(pair<int, int> lastCoord, pair<int, int> coord, vector<vector<char>>& map)
{
  pair<int, int> newCoord;
  switch(map[coord.first][coord.second])
  {
    case '|':
    {
      cout << "| found" << endl;
      if (lastCoord.first < coord.first)
      {
        newCoord = {coord.first + 1, coord.second};
      } 
      else 
      {
        newCoord = {coord.first - 1, coord.second};
      }
      break;
    }
    
    case '-':
    {
      cout << "- found" << endl;
      if (lastCoord.second < coord.second)
      {
        newCoord = {coord.first, coord.second+1};
      } 
      else 
      {
        newCoord = {coord.first, coord.second-1};
      }
      break;
    }  
    
    case 'L':
    {
      cout << "L found" << endl;
      if (lastCoord.first == coord.first && lastCoord.second == (coord.second+1))
      {
        newCoord = {coord.first-1, coord.second};
      } 
      else 
      {
        newCoord = {coord.first, coord.second+1};
      }
      break;
    }
    
    case 'J':
    {
      cout << "J found" << endl;
      if (lastCoord.first == (coord.first-1) && lastCoord.second == coord.second)
      {
        newCoord = {coord.first, coord.second-1};
      } 
      else 
      {
        newCoord = {coord.first-1, coord.second};
      }
      break;
    }
    
    case 'F':
    {
      cout << "F found" << endl;
      if (lastCoord.first == (coord.first+1) && lastCoord.second == coord.second)
      {
        newCoord = {coord.first, coord.second+1};
      } 
      else 
      {
        newCoord = {coord.first+1, coord.second};
      }
      break;
    }
    
    case '7':
    {
      cout << "7 found" << endl;
      if (lastCoord.first == coord.first && lastCoord.second == (coord.second-1))
      {
        newCoord = {coord.first+1, coord.second};
      } 
      else 
      {
        newCoord = {coord.first, coord.second-1};
      }
      break;
    }
    
  }
  
  return newCoord;

}

int main(int argc, char* argv[]) 
{
  vector<vector<char>> map;
  
  if (argc == 2)
  {
    if (!vectorizeFile(argv[1], map))
    {
      return EXIT_FAILURE;
    }
  }
  
  auto startingCoords = findStartingCoordinate(map);
  cout << map[startingCoords.first][startingCoords.second] << endl;

  pair<int, int> firstPath = {startingCoords.first-1, startingCoords.second};
  pair<int, int> secondPath = {startingCoords.first+1, startingCoords.second};
  
  cout << map[firstPath.first][firstPath.second] << endl;
  cout << map[secondPath.first][secondPath.second] << endl;
  
  pair<int, int> lastFirstPath = startingCoords;
  pair<int, int> lastSecondPath = startingCoords;
  
  
  int counter{0};
  while(firstPath != secondPath)
  {
    counter++;
  
    cout << "Path 1: " << firstPath.first << "," << firstPath.second << endl;
    cout << "Path 2: " << secondPath.first << "," << secondPath.second << endl;
    cout << " " << endl;
  
    auto newFirstPath = continuePath(lastFirstPath, firstPath, map);
    auto newSecondPath = continuePath(lastSecondPath, secondPath, map);
    
    lastFirstPath = firstPath;
    lastSecondPath = secondPath;
    
    firstPath = newFirstPath;
    secondPath = newSecondPath;
  
  }
  
  cout << ++counter << endl;
  
}
