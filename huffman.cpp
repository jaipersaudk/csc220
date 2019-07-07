#include<iostream>
#include <fstream>
#include<vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

struct huffTreeNode
{
  int nodeWeight;
  unsigned char data;
  const huffTreeNode *child1;
  const huffTreeNode *child2;
  huffTreeNode(unsigned char d = 0, int inc = -1)
  {
    data = d;
    nodeWeight = inc;
    child1 = 0;
    child2 = 0;
  }

  huffTreeNode(const huffTreeNode* c1, const huffTreeNode* c2)
  {
    data = 0;
    nodeWeight = c1->nodeWeight + c2->nodeWeight;
    child1 = c1;
    child2 = c2;
  }

  bool operator< (const huffTreeNode& htn) const
  {
    return nodeWeight >htn.nodeWeight;
  }

  void traversing (string codeValue="") const
  {
    if (child1)
    {
      child1->traversing(codeValue+'0');
      child2->traversing(codeValue+'1');
    }

    else
    {
      cout << " " << data << "\t\t";
      cout << nodeWeight;
      cout << "\t\t" << codeValue << endl;
    }
  }
};

void characterCounting(int* counter)
{
  for (int inc = 0; inc < 256; inc++)
    counter[inc] = 0;

  ifstream myinputFile("theRaven.txt");
  if(!myinputFile)
  {
    cout << "Can't open input file" << endl;
    throw "abort";
  }

  myinputFile.setf(ios::skipws);
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
  int counter[256];
  characterCounting(counter);
  priority_queue < huffTreeNode > myQ;
  for (int inc = 0; inc < 256; inc++)
    if(counter[inc])
      myQ.push(huffTreeNode(inc,counter[inc]));

  while(myQ.size() > 1)
  {
    huffTreeNode* child1 = new
    huffTreeNode(myQ.top());
    myQ.pop();
    huffTreeNode* child2 = new
    huffTreeNode(myQ.top());
    myQ.pop();
    myQ.push(huffTreeNode(child1, child2));
  }

  cout << "CHARACTER \t FREQUENCY \t HUFFMANCODE" << endl;
  cout << "--------- \t --------- \t -----------" << endl;
  myQ.top().traversing();
  getchar();
  return 0;
}
