#include<iostream>
#include<algorithm>
using namespace std;


/************************************************** Problem 1 ********************************************************/
/*Write	an	algorithm	that	finds	the	largest	number	in	a	list	(an	array)	of	n numbers.*/
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

/************************************************** Problem 2 ********************************************************/
/*Write	an	algorithm	that	finds	the	m	smallest	numbers	in	a	list	of	n	numbers */
// First sort the array and then print the first m values

  void minimums(int arr[], int m, int n)
  {
    sort(arr,arr+n); //sorts the array in ascending order
    for (int i = 0; i<m; i++)
    {
      cout << arr[i] << endl;
    }
  }

/************************************************** Problem 4 ********************************************************/
/* Write	an	Insertion	Sort	algorithm	(Insertion	Sort	is	discussed	in	Section	7.2) that	uses
 * Binary	Search	to	find	the	position	where	the	next	insertion	should take	place */
// doing a binary insertion sort - searching the sorted side of the array to find where to insert the next element

    int binarySearch(int arr[], int start, int end, int target)
    {
      if (end >= start)
      {
        int mid = (start+end)/2; //the middle term of the array

        if (arr[mid] == target) //if the middle term is what your are looking for
          return mid;

        else if (target < arr[mid]) //search the left side of the array
          binarySearch(arr, start, mid-1,target);

        else if (target > arr[mid]) //if target is bigger than the middle term, search the right side of the array
          binarySearch(arr, mid+1, end, target);

        return -1; //if not found
      }

      // insertion sort algorithm
      void insertionsort(int arr[], int n)
      {
        int location, selected, j;
        for (int i = 1; i < n; ++i) //the first element is always sorted so we start with second element
        {
          j = i-1;
          selected = a[i];

          // find where to inserted the selected element
          location = binarySearch(a,0, j, selected);

          // move elements to create space
          while (j >= location)
          {
            a[j+1] = a[j];
            j--;
          }
          a[j+1] = selected;
        }

      }


/************************************************** Problem 6 ********************************************************/
/* Write	an	algorithm	that	finds	both	the	smallest	and	largest	numbers	in	a	list of	n	numbers.
 * Try	to	find	a	method	that	does	at	most	1.5n	comparisons	of array	items. */


/************************************************** Problem 7 ********************************************************/
/* Write	an	algorithm	that	determines	whether	or	not	an	almost	complete	binary tree	is	a	heap */
// since the binary tree is not complete, we wont check to see if it is a complete binary tree

  bool is_complete()
  {

  }
  bool is_heap(int root, int left, int right)
  {

  }

/************************************************** Problem 8 ********************************************************/
/* Under	what	circumstances,	when	a	searching	operation	is	needed,	would Sequential	Search	(Algorithm	1.1)	not	be	appropriate?*/
// Sequential Searching is not appropriate when a list is sorted and you search for a big number in the list. If there are many numbers in the list
// then the algorithm would take about O(n) time to find the number at the end of the list



/************************************************** Problem 9 ********************************************************/
/*Give	a	practical	example	in	which	you	would	not	use	Exchange	Sort (Algorithm	1.3)	to	do	a	sorting	task.*/
// If the list is completely out of order, then exchange sort is impractical because it will take O(n^2) time



/************************************************** Problem 12 ********************************************************/
/* Write	a	Θ(n)	algorithm	that	sorts	n	distinct	integers,	ranging	in	size	between 1	and	kn	inclusive,	where	k	is
 * a	constant	positive	integer.	(Hint:	Use	a knelement	array.) */



/************************************************** Problem 19 ********************************************************/
	// f(x)	=	3n^2	+ 10nlogn + 1000n + 4logn + 9999 --> belongs to O(n^2)


/************************************************** Problem 21 ********************************************************/
// 	f(x)	=	n	+	n^2	+	2^n	+	n^4 --> belongs to O(n^4)



    }
