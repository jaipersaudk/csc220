#include <bits/stdc++.h>
#include <vector>
using namespace std;

// global variables for n and m
// n - denominations of stamps
// m - amounts of stamps on letter

int N, M;

void compute(int num, int sum, vector<int> &stamps, set<int> &ans)
{
  // Add current value to the set
  ans.insert(sum);
  // If we have no more steps left end proccess
  if (num > M)
    return;

  // For each # of denominations of stamps, call the recursive function
  // looping through the entire vector
  for(int stamp : stamps)
    compute(num+1, sum+stamp, stamps, ans);

  return;
}

int main()
{
  // Input
  cout << "How many stamps do you have? ";
  cin >> N;
  // cout << "\n";
  cout << "How many stamps can you put on the letter? ";
  cin >> M;
  cout << "\n";

  // create a vector of integers to store the values of the stamps
  vector<int> stamps(N);
  for(int i = 0; i < N; i++)
  {
    cout << "What is the stamps' face value? ";
    cin >> stamps[i];
    // cout << "\n";
  }

  // create a set of integers to store the answer
  set<int> ans;
  // All valid prices will be stored in ans set
  compute(1, 0, stamps, ans);

  cout << "\n";
  // looping through the entire set to print the answers
  for(int x : ans)
    cout << x << " ";

  cout << "\n";
}
