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
// Should be about O(nlogn)

  void m_smallest (int arr[], int m)
  {
    mergesort(arr, n); //sorted array from smallest to greatest
    // print the first m numbers of the list
    for (int i = 0; i < m; i++)
      cout << arr[i] << endl;
  }
  void mergesort(int arr[], size_t n)
  {
    size_t n1; // size of first subarray
    size_t n2; // size of second subarray

    if (n > 1)
    {
      // computed sizes of subarrays
      n1 = n/2;
      n2 = n-n1;

      // sort arr[0] to arr[n1-1]
      mergesort(arr,n1);
      // sort arr[n1] to arr[n]
      mergesort(arr+n1,n2);

      // merge the two halves
      merge(arr,n1,n2);
    }
  }

    void merge(int arr[], size_t n1, size_t n2)
    {
      int* temp; // points to dynamic array for the sorted elements

      size_t c = 0; //number of elements copied from arr to temp (index of the temp arr)
      size_t c1 = 0; // number copied from first half; (index of first subarray)
      size_t c2 = 0; // number copied from second half (index of second subarray)

      // allocate memory for dynamic array
      temp = new int[n1+n2];

      // merge elements from arr to temp array
      // ++ allows to use the current value of the variable and then increment by 1
      while ((c1 < n1) && (c2 < n2))
      {
        if (arr[c1] < (arr + n1)[c2])
          temp[c++] = arr[c1++]; //copy from the first half
        else
          temp[c++] = (arr+n1)[c2++];
      }

        // copy remaining elements in left and right subarrays (if one subarray was bigger than the other)
        while (c1 < n1)
          temp[c++] = arr[c1++];
        while (c2 < n2)
          temp[c++] = (arr+n1)[c2++];

        // copy temp into arr and release temp
        for (int i = 0; i < n1+n2; i++)
          arr[i] = temp[i];

        delete [] temp;
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
// If the list is completely out of order, then exchange sort is impractical because it will take O(n^2) time. Exchange sort works best if the list
// somewhat organized.

/************************************************** Problem 12 ********************************************************/
/* Write	a	Θ(n)	algorithm	that	sorts	n	distinct	integers,	ranging	in	size	between 1	and	kn	inclusive,	where	k	is
 * a	constant	positive	integer.	(Hint:	Use	a knelement	array.) */



/************************************************** Problem 33 ********************************************************/
/*Give	an	algorithm	for	the	following	problem	and	determine	its	time complexity.	Given	a	list	of	n	distinct
 *positive	integers,	partition	the	list	into two	sublists,	each	of	size	n/2,	such	that	the	difference between	the	sums	of the	integers
 *in	the	two	sublists	is	maximized.	You	may	assume	that	n	is	a multiple	of	2.*/




}
