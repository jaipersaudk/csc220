#include <bits/stdc++.h>
using namespace std;

int N,M;

void getAns(int step, int sum, vector<int> &stamps, set<int> &ans)
{
  // Add current value to the set
  ans.insert(sum);
  // If we have no more steps left end proccess
  if(step > M)
  return;

  // For each step call recursion
  for(int stamp : stamps)
  getAns(step+1, sum+stamp, stamps, ans);

  return;
}

int main()
{
  // Input
  cout << "Value of n: ";
  cin >> N;
  cout << "\n";
  cout << "Value of m: ";
  cin >> M;
  cout << "\n";
  vector<int> stamps(N);
  for(int i = 0; i < N; i++)
  {
    cout << "Insert stamp face value: ";
    cin >> stamps[i];
    cout << "\n";
  }

  set<int> ans;
  // All valid prices will be stored in ans set
  getAns(1, 0, stamps, ans);

  for(int x : ans)
  cout << x << " ";
}
