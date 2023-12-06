#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

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
  
  int sum{1};
  vector<int> times;
  vector<int> distances;
  
  istringstream timesStream((lines.front()));
  istringstream distancesStream(lines.back());
  
  string megaDistance{" "};
  string megaTime{" "};
  
  string tempNumber;
  timesStream >> tempNumber;
  while (timesStream >> tempNumber)
  {
    times.push_back(stoi(tempNumber));
    megaTime += tempNumber;
  }
  
  distancesStream >> tempNumber;
  while (distancesStream >> tempNumber)
  {
    distances.push_back(stoi(tempNumber));
    megaDistance += tempNumber;
  }
  
  long long int kernedTime = stol(megaTime);
  long long int kernedDistance = stol(megaDistance);
  long long int winsKerned{0};
  
  for(int i = 0; i <= times.size()-1; i++)
  {
    int timesBeat{0};
    for(int timeHoldingButton = 0; timeHoldingButton <= times[i]; timeHoldingButton++)
    {
      int timeRacing = times[i] - timeHoldingButton;
      int myDistance = timeHoldingButton * timeRacing;
      if (myDistance > distances[i])
      {
        timesBeat += 1;
      }
    }
    sum *= timesBeat;
  }
  
  for(int timeHoldingButton = 0; timeHoldingButton <= kernedTime; timeHoldingButton++)
  {	   
    long long int timeRacing = kernedTime - timeHoldingButton;
    long long int myDistance = timeHoldingButton * timeRacing;
    
    cout << "I get " << myDistance << " millimeters with holding the button " 
    << timeHoldingButton << " milliseconds" << endl; 
	      
    if (myDistance > kernedDistance)
    {	     
      winsKerned += 1;
    }
  }
  
  cout << sum << endl;
  cout << winsKerned << endl;
     
}
