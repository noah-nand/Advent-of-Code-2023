#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
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

int predictNextValue(vector<long int> numbers)
{
  cout << "------" << endl;

  if (all_of(numbers.begin(), numbers.end(), [](long int x) { return x == 0; }))
  {
    return 0;
  }
  
  vector<long int> differences;
  for(int i = 0; i < numbers.size()-1; i++)
  {
    differences.push_back(numbers[i+1] - numbers[i]);
  }
 
  for(const auto& num : differences)
  {
    cout << num << endl;
  }
 
  return numbers.back() + predictNextValue(differences);

}

int predictPreviousValue(vector<long int> numbers)
{
  cout << "------" << endl;

  if (all_of(numbers.begin(), numbers.end(), [](long int x) { return x == 0; }))
  {
    return 0;
  }
  
  vector<long int> differences;
  
  for(int i = 0; i < numbers.size()-1; i++)
  {
    differences.push_back(numbers[i+1] - numbers[i]);
  }
 
  for(const auto& num : differences)
  {
    cout << num << endl;
  }
 
  return numbers.front() - predictPreviousValue(differences);

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
  
  int sumNextValue{0};
  int sumPreviousValue{0};
  
  for(string& line: lines)
  {
  
  vector<long int> numbers;
  
  string str;
  stringstream ss(line);
  while(getline(ss, str, ' '))
  {
    numbers.push_back(stoi(str));
  }
  
  int predictedLastValue = predictNextValue(numbers);
  int predictedPreviousValue = predictPreviousValue(numbers);
  
  sumNextValue += predictedLastValue;
  sumPreviousValue += predictedPreviousValue;
  
  }
  
  cout << sumNextValue << endl;
  cout << sumPreviousValue << endl;
  
}
