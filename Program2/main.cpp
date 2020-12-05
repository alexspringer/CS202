//Alex Springer, Program 2, 2/10/17
#include "transport.h"
using namespace std;



//User interface for my program.
int main()
{
  transport * ptr; //Base class pointer

  MAX max_object; //derived object so we cam do ptr = & obj.
  bus bus_object; //derived obj
  uber uber_object; //derived obj.
  popularity pop_object; //array of LLL obj

  ptr = & max_object; //As default transport points at max_object.
  int response = 0; //Choose which option you want
  char temp[100]; //Temp array to determine what transportation type
  //is being worked on.

  cout << "The default transporation type is MAX. " << endl;
  while(response != 1)
  {
    cout << "Welcome! Here are you options. " << endl
    << "1. Quit. " << endl
    << "2. Add a new experience. " << endl
    << "3. Display all experiences " << endl
    << "4. Change Transportation Type " << endl
    << "5. Add Popularity of a Transport Type " << endl
    << "6. Display Popularity of all Transportation. " << endl
    << "Please select an option: ";
    cin >> response; cin.ignore(100,'\n');

    if(response == 2) //add exp
    {
      ptr -> add_experience();
    }

    if(response == 3) //display exp
    {
      ptr -> display_experienceWrap();
    }

    if(response == 4) //change transport type
    {
      cout << "What type of transportation do you want? "
      << endl << "Your options are MAX, bus, or uber: ";
      cin.get(temp,100,'\n'); cin.ignore(100,'\n');

      if(strcmp(temp,"MAX") == 0)
      {
        ptr = & max_object;
      }

      if(strcmp(temp,"bus") == 0)
      {
        ptr = & bus_object;
      }

      if(strcmp(temp,"uber") == 0)
      {
        ptr = & uber_object;
      }
    }

    if(response == 5) //build popularity array of LLL
    {
      pop_object.add_popularityWrap();
    }

    if(response == 6) //display popularity array of LLL.
    {
      pop_object.display_popularityWrap();
    }
  }


  return 0;
}
