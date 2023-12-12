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

vector<pair<int, int>> findAllGalaxies(vector<vector<char>>& map)
{
  vector<pair<int, int>> coords;
  for(int i = 0; i < map.size(); i++)
  {
      for(int j = 0; j < map[i].size(); j++)
      {
        if (map[i][j] == '#')
        {
          coords.push_back({i, j});
        }
      }
  }
  return coords;
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
  
  vector<char> emptyVector(map[0].size(), '.');  
  vector<vector<char>> newMap;
  for (auto row = map.begin(); row != map.end(); ++row)
    {
      if (all_of(row->begin(), row->end(), [](char x) { return x == '.'; }))
        {
          newMap.insert(newMap.end(), emptyVector); 
        }
        newMap.insert(newMap.end(), *row);
    }

    map = move(newMap);

  for (int column = 0; column != map[0].size(); column++)
    {
      bool galaxyFound = false;
      for(int row = 0; row != map.size(); row++)
	{
	  if (map[row][column] != '.')
	  {  
	    galaxyFound = true;
	  }	
	}
	
	if (!galaxyFound)
        {
          for(int row = 0; row != map.size(); row++)
          {
            map[row].insert(map[row].begin() + column, '.');
          }
          
          column++; 
        }	
    }
  
  auto galaxyCoords = findAllGalaxies(map);
  int sum{0};
    
  for(int i = 0; i != galaxyCoords.size()-1; i++)
  {
    for(int j = i+1; j != galaxyCoords.size(); j++)
      {
        cout << "coordOne is " << galaxyCoords[i].first << " " << galaxyCoords[i].second << endl;
        cout << "coordTwo is " << galaxyCoords[j].first << " " << galaxyCoords[j].second << endl;
        sum += (abs(galaxyCoords[i].first - galaxyCoords[j].first) + abs(galaxyCoords[i].second - galaxyCoords[j].second));
      }
    cout << "------" << endl;   
  }
    
  cout << sum << endl;
     
}
