#include "node.h"
using namespace std;



node::node()
{
  next = NULL;
}



linear_list::linear_list()
{
  data = 0;
}



void node::add(node *& head)
{
  if(!head)
  {
    head = new node;
    head -> data = 1;
    cout << head -> data << endl;
    head -> next = NULL;
    return;
  }
  
  return add(head -> next);
}



node::~node(){}
linear_list::~linear_list(){}
