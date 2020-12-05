//Alex Springer, CS202, Program 1
#include "node.h"
using namespace std;



//Probably should learn how to do switch statements for assignments like
//this one. Anyways, main is the basic user interface for my program.
//each option is labeled one through eight. select the number you want
//and that operation happens.
int main()
{
  manager obj;
  //obj.add_location_wrap();
  int response = 0;
  while(response != 1)
  {
    cout << '\n' <<"Welcome controller. " << endl
    << "Here are your options: " << endl
    << "1. Quit " << endl
    << "2. Add a streetcar " << endl
    << "3. Remove a streetcar " << endl
    << "4. Display map " << endl
    << "5. Display a loop " << endl
    << "6. Display a line " << endl
    << "7. Change the pace " << endl
    << "8. Move cars " << endl
    << "Select your option: ";
    cin >> response; cin.ignore(100,'\n');

    if(response == 2)
    {
      obj.add_car_wrap();
    }
    if(response == 3)
    {
      obj.remove_car_wrap();
    }

    if(response == 4)
    {
      obj.display_graph_wrap();
    }

    if(response == 5) //Display the CLL.
    {
      obj.displaycll_wrap(); //Break into LLL to read.
    }

    if(response == 6) //Display the DLL.
    {
      obj.display_dllwrap(); //Not sure if wrapper is 100% needed.
    }

    if(response == 7)
    {
      obj.change_pace_wrap();
    }

    if(response == 8)
    {
      obj.move_car_wrap();
    }
  }
  return 0;
}
