#include "node.h"
using namespace std;



int main()
{
  //node * head = NULL;
  //for(int i = 0; i < 5; ++i)
 // head -> add(head);
 char temp[50];
 cin.get(temp,50,'\n'); cin.ignore(50,'\n');
 int size = 0;
 for(int i = 0; i < strlen(temp); ++i)
 {
   size += temp[i];
 }

 cout << size << endl;

  return 1;
}
