#include<iostream>
using namespace std;


// Problem 1 - Write	an	algorithm	that	finds	the	largest	number	in	a	list	(an	array)	of	n numbers.
// Sequential search algorithm

  int maximum(int n, int arr[])
  {
  int max = arr[0]; //max element
  for (int i = 0; i < n; i++)
  {
    if (arr[i] > max)
      max = arr[i];
  }
  return max;
  }

// Problem 2 - Write	an	algorithm	that	finds	the	m	smallest	numbers	in	a	list	of	n	numbers
// first sort the array and then print the first m values

  void minimums(int arr[], int m, int n)
  {
    sort 
  }
