//Alex Springer, CS202, Program 3, 2/24/17
#include "table.h"



//Client program
int main()
{
  table obj;
  int response = 0;
  while(response != 1)
  {
    cout << "\nWelcome to the emergency broadcast system. \n \n"
    << "Here are your options: " << endl
    << "1. Quit. " << endl
    << "2. Add last name, first name and contact info. " << endl
    << "3. Display all information. " << endl
    << "4. Search a name. " << endl
    << "5. Delete a name. " << endl
    << "Enter your option: ";

    cin >> response; cin.ignore(100,'\n');


    if(response == 2)
    {
      obj.buildWrap();
    }

    if(response == 3)
    {
      obj.displayWrap();
    }

    if(response == 4)
    {
      obj.searchWrap();
    }

    if(response == 5)
    {
      obj.search_destroyWrap();
    }
  }


  return 0;
}
