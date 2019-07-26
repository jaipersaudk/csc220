#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

struct huffTreeNode
{
  // global variables
  int freq; // frequency of given data
  unsigned char data;
  const huffTreeNode *left_child; // left and right child for the heap
  const huffTreeNode *right_child;

  // constructor
  huffTreeNode(unsigned char d = 0, int i = -1)
  {
    // inital values for global variables
    data = d;
    freq = i;
    left_child = 0;
    right_child = 0;
  }

  huffTreeNode(const huffTreeNode* c1, const huffTreeNode* c2)
  {
    data = 0;
    freq = c1->freq + c2->freq; // the weight of node is the sum of the left and right child
    left_child = c1;
    right_child = c2;
  }

  // overloaded operator
  bool operator < (const huffTreeNode& htn) const
  {
    return freq > htn.freq;
  }


  void traversing (string codeValue="") const //each data starts with blank codevalue
  {
    if (left_child) //if there is a left child
    {
      // traverse the left subtree first
      left_child->traversing(codeValue+'0'); //left subtree gets a codevalue of 0
      right_child->traversing(codeValue+'1'); //right subtrees get a codevalue of 1
    }


    // since heap property must be maintained, if there is no left child, then print the data, the frequency and the codevalue
    else
    {
      cout << "    " << data;
      cout << "\t\t    " << freq;
      cout << "\t\t " << codeValue;
      cout << "\n";
    }
  }
};

// input the poem and count the characters in the file
void Count_characters(int* counter)
{
  // initializing all indices in the counter array to 0
  // for (int i = 0; i < 256; i++)
  //   counter[i] = 0;

  //inputting the raven poem
  ifstream myinputFile("Raven_poem.txt");

  if(!myinputFile)
  {
    cout << "Can't open input file" << endl;
    throw "abort";
  }

  myinputFile.setf(ios::skipws); // needed to skip the whitespace of the file

  // endless loop to count the characters in the poem
  for ( ; ; )
  {
    unsigned char d;
    myinputFile >> d;
    if (myinputFile)
      counter[d]++;
    else
      break;
  }
}

int main()
{
  // declaring an array for the characters and using the array in Count_characters function
  int counter[256] = {};
  Count_characters(counter);

  // implementing priority queue
  priority_queue < huffTreeNode > myQ;
  for (int i = 0; i < 256; i++)
    if(counter[i])
      myQ.push(huffTreeNode(i,counter[i]));

  // pushing values from priority onto the min heap
  while(myQ.size() > 1)
  {
    huffTreeNode* left_child = new
    huffTreeNode(myQ.top());
    myQ.pop();
    huffTreeNode* right_child = new
    huffTreeNode(myQ.top());
    myQ.pop();
    myQ.push(huffTreeNode(left_child, right_child));
  }

  // output
  cout << "CHARACTER \t FREQUENCY \t HUFFMANCODE" << endl;
  cout << "--------- \t --------- \t -----------" << endl;
  myQ.top().traversing();
  getchar();
  return 0;
}
