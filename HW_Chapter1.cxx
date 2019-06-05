#include<iostream>
#include<algorithm>
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
// First sort the array and then print the first m values

  void minimums(int arr[], int m, int n)
  {
    sort(arr,arr+n); //sorts the array in ascending order
    for (int i = 0; i<m; i++)
    {
      cout << arr[i] << endl;
    }
  }

/* Problem 4: Write	an	Insertion	Sort	algorithm	(Insertion	Sort	is	discussed	in	Section	7.2) that	uses
* Binary	Search	to	find	the	position	where	the	next	insertion	should take	place */
// doing a binary insertion sort - searching the sorted side of the array to find where to insert the next element

    int binarySearch(int arr[], int start, int end, int target)
    {
      if (end >= start)
      {
        int mid = (start+(end/2)); //the middle term of the array

        if (arr[mid] == target) //if the middle term is what your are looking for
          return mid;

        else if (target < arr[mid]) //search the left side of the array
          binarySearch(arr, start, mid-1,target);

        else if (target > arr[mid]) //if target is bigger than the middle term, search the right side of the array
          binarySearch(arr, mid+1, end, target);

        return -1; //if not found
      }

      // insertion sort algorithm

    }
