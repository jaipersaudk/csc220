#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

struct huffTreeNode
{
  // global variables
  int freq; // total frequency at given node
  unsigned char data;
  const huffTreeNode *left_child; // left and right child for the heap
  const huffTreeNode *right_child;


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
    //data = 0;
    freq = c1->freq + c2->freq; // the weight of node is the sum of the left and right child
    left_child = c1;
    right_child = c2;
  }

  // overloaded operator
  bool operator < (const huffTreeNode& htn) const
  {
    return freq > htn.freq;
  }


  void traversing (string binary_Value="") const //each data starts with blank binary_Value
  {
    if (left_child) //if there is a left child
    {
      // traverse the left subtree first
      left_child->traversing(binary_Value+'0'); //left subtree gets a binary_Value of 0
      right_child->traversing(binary_Value+'1'); //right subtrees get a binary_Value of 1
    }


    // since heap property must be maintained, if there is no left child, then print the data, the frequency and the binary_Value
    else
    {
      cout << "    " << data;
      cout << "\t\t    " << freq;
      cout << "\t\t " << binary_Value;
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

  // if(!myinputFile)
  // {
  //   cout << "Can't open input file" << endl;
  //   throw "abort";
  // }

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
  // declaring an empty array for the characters and using the array in the Count_characters function
  int counter[256] = {};
  Count_characters(counter);

  // implementing priority queue called pQ with data structure huffTreeNode
  priority_queue<huffTreeNode> pQ;
  for (int i = 0; i < 256; i++)
    if(counter[i])
      pQ.push(huffTreeNode(i,counter[i]));

  // implementing a heap for the huffman tree
  while(pQ.size() > 1)
  {
    huffTreeNode* left_child = new
    huffTreeNode(pQ.top());
    pQ.pop();
    huffTreeNode* right_child = new
    huffTreeNode(pQ.top());
    pQ.pop();
    pQ.push(huffTreeNode(left_child, right_child));
  }

  // printing the output values
  /* cout << "CHARACTER \t FREQUENCY \t HUFFMANCODE" << endl;
   cout << "--------- \t --------- \t -----------" << endl; */
  pQ.top().traversing();
  getchar();
  return 0;
}
