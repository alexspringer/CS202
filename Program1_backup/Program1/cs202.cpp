//Alex Springer, Program 1, CS202
#include "node.h"
using namespace std;



//The constructors for my classes.
//stop constructor
stop::stop()
{
  name = NULL;
}



//streetcar constructor
streetcar::streetcar()
{
  car = NULL;
  car2 = NULL;
  pace = 1;
}



//cll constructor
cll::cll()
{
  next = NULL;
}



//dll constructor
dll::dll()
{
  next = NULL;
  previous = NULL;
}



//Instead of setting head and tail to null, the constructor
//builds the entire data structre by reading out of a .txt
//Also builds the graph by reading in from the same .txt files.
manager::manager()
{
  ifstream infile;
  char temp[100];
  int size = 20;

  infile.open("cll.txt");//Build the CLL1
  if(infile)
  {
    for(int i = 0; i < 10; ++i) //i < 10 because 10 total stops
    {
      infile.get(temp,100,':'); infile.ignore(100,':');
      add_cll(temp);
    }
    infile.close();
  }

  infile.open("dll.txt");//Build the DLL
  if(infile)
  {
    for(int i=0; i<10; ++i) //same reasoning as before.
    {
      infile.get(temp,100,':'); infile.ignore(100,':');
      add_dll(temp,head);
    }
    infile.close();
  }
  infile.clear();

  //BUILDING THE GRAPH AS AN ADJACENCY LIST.
  int list_size = 20;
  adjacency_list = new node*[list_size];
  infile.open("cll.txt");
  if(infile)
  {
    for(int i = 0;i < 10; ++i)
    {
      infile.get(temp,100,':'); infile.ignore(100,':');
      adjacency_list[i] = new node;
      adjacency_list[i] -> set_next(NULL);
      adjacency_list[i] -> add_location(temp,i);
    }
    infile.close();
  }
  infile.open("dll.txt");
  if(infile)
  {
    for(int i = 10; i < 20; ++i)
    {
      infile.get(temp,100,':'); infile.ignore(100,':');
      adjacency_list[i] = new node;
      adjacency_list[i] -> set_next(NULL);
      adjacency_list[i] -> add_location(temp,i);
    }
    infile.close();
  }
  infile.clear();
}



//Return the next value in the adjacency list
node *& node::get_next()
{
  return next;
}



//set the next value of the pointer passed into the function.
void node::set_next(node * head)
{
  next = head;
  return;
}



//Recursive delete function for the linked lists in the adj list.
void node::destroy(node *& head)
{
  if(!head)
    return;

  destroy(head -> next);
  delete [] location_name;
  location_name = NULL;
  delete head;
  head = NULL;
  return;
}



//Allows the user to display the graph from main and a for loop
//is implemented to see the data at the different indicies.
void manager::display_graph_wrap()
{
  int list_size = 20;
  for(int i = 0; i < list_size;++i)
  {
    node * head = adjacency_list[i] -> get_next();
    adjacency_list[i] -> display(head);
  }
  return;
}



//Displays the location data inside the graph
void node::display(node * head)
{
  cout << "Location: " << location_name << endl;
  traverse(head);
  return;
}



//Displays the location data in the adj list.
void node::traverse(node * head)
{
  if(!head)
    return;
  cout << "Location: " << location_name;
  return traverse(head -> next);
}



//deep copy of the location data from a temp to the adj list.
void node::add_location(char temp[], int i)
{
  location_name = new char[strlen(temp)+1];
  strcpy(location_name,temp);
  return;
}



//Checks the next node in the dll to see if there is a car there.
bool dll::peek_next(dll * head)
{
  if(!head)
    return false;
  if(head -> car)
  {
    return false;
  }

  return true;
}



//Checks the previous node in the dll to see if there is a car there.
bool dll::peek_previous(dll * head)
{
  if(!head)
    return false;
  if(head -> car2)
  {
    return false;
  }
  return true;
}



//A wrapper function to move the streetcars from main
void manager::move_car_wrap()
{
  tail -> move_car(tail);
  head -> move_car(head);
  return;
}



//If there is no node or a car is already in a node return false.
bool cll::peek(cll * tail)
{
  if(!tail)
    return false;
  if(tail -> car)
  {
    return false;
  }

  return true;
}



//Move cars in a circular linked list.
//ADD MOVING WITH DIFFERENT PACES.
void cll::move_car(cll * tail)
{
  char temp[100];
  int pace = tail -> pace;
  if(!tail)
    return;

  for(int i = 0; i < 10; ++i)
  {
    if(tail -> car && tail -> peek(tail -> go_next()))
    {
      strcpy(temp,tail -> car);
      tail -> destroy_car();
      tail = tail -> go_next();
      tail -> add_car(tail,temp);
      tail = tail -> go_next();
    }
    else
    {
      tail = tail -> go_next();
    }
  }
  return;
}



//if there is not a second car in the node it calls a func to allo
//cate the memory for the southbound car.
void dll::add_car2(dll * head, char temp[])
{
  if(!head) //no nodes return
    return;

  //If there is no car at the first node we are free to add a car.
  if(!head -> car2)
  {
    head -> name_car2(temp);
    cout << "Car added. " << endl;
    return;
  }

  else
  {
    cout << "Sorry there is already a car at the first location. "
    << "Please move the streetcars to add a new one. " << endl;
    return;
  }
}



//allocates memeory for a car going the opposite direction
//in the doubly linked list.
void streetcar::name_car2(char temp[])
{
  car2 = new char[strlen(temp)+1];
  strcpy(car2,temp);
  return;
}



//Moves cars in a doubly linked list. Accounts for both cases where
//the cars need to flip track aswell as normal traversal of the cars.
void dll::move_car(dll * head)
{
  char temp[100];
  if(!head)
  {
    return;
  }
  if(head -> go_next() == NULL && head -> car) //flip directions.
  {
    strcpy(temp,head -> car);
    head -> destroy_car();
    head -> add_car2(head,temp);
  }
  if(head -> car && peek_next(head -> go_next())) //Going forward.
  {
    strcpy(temp,head -> car);
    head -> destroy_car();
    head = head -> go_next();
    head -> add_car(head,temp);
  }

  //Wasnt sure what order was best for these conditions.
  /*if(head -> go_next() == NULL && head -> car) //flip directions.
  {
    strcpy(temp,head -> car);
    head -> destroy_car();
    head -> add_car2(head,temp);
  }*/

  if(head -> car2 && peek_previous(head -> go_previous()))//going reverse
  {
    dll * south = head;
    strcpy(temp,head -> car2);
    head -> destroy_car2();
    south = south -> go_previous();
    south -> add_car2(south,temp);
  }

  if(head -> go_previous() == NULL && head -> car2)
  {
    strcpy(temp,head -> car2);
    head -> destroy_car2();
    head -> add_car(head,temp);
  }

  return move_car(head -> go_next());
}



//Ask the controller the name of the car they want to remove and 
//on what track we should look for the car.
void manager::remove_car_wrap()
{
  char temp[100];
  int response = 0;
  cout << "What is the name of the car you want to retire: ";
  cin.get(temp,100,'\n'); cin.ignore(100,'\n');

  cout << "Where are we searching for this car? " << endl
  << "Options: " << endl
  << "1. line " << endl
  << "2. loop " << endl
  << "Please type 1 or 2: ";
  cin >> response; cin.ignore(100,'\n');

  if(response == 1) //DLL
  {
    return head -> remove_car(head,temp);
  }

  if(response == 2) //CLL
  {
    cll * current = tail;
    tail = tail -> go_next();
    current -> set_next(NULL); //Break the list.

    tail -> remove_car(tail,temp);

    current -> set_next(tail);
    tail = current; //Reconnect.
    return;
  }
  return;
}



//remove a car given the name of he car that needs to be removed.
//removes from the circular linked list.
void cll::remove_car(cll * tail, char temp[])
{
  if(!tail) //No nodes = no data. return at this case.
    return;

  if(tail -> car)
  {
    if(strcmp(tail -> car,temp) == 0)
    {
      return tail -> destroy_car();
    }
  }
  return remove_car(tail -> go_next(),temp);
}



//Remove a car from a doubly linked list give the name of the car that 
//needs to be removed.
void dll::remove_car(dll * head, char temp[])
{
  if(!head)
    return;

  if(strcmp(head -> car,temp)==0)
  {
    return head -> destroy_car();
  }
  return remove_car(head -> go_next(),temp);
}



//Deallocates the dynamic memory for a car name. This is called when
//destroying the CLL and DLL.
void streetcar::destroy_car()
{
  if(car)
  {
    delete [] car;
    car = NULL;
    return;
  }
  return;
}



//Deallocates the dynamic memory for a car name. This is called when
//destroying the CLL and DLL.
void streetcar::destroy_car2()
{
  if(car2)
  {
    delete [] car2;
    car2 = NULL;
    return;
  }
  return;
}


//Mostly used for testing purposes but displays the pace.
void streetcar::display_pace()
{
  cout << "Here is the pace " << pace << endl;
  return;
}



//Mostly used for testing purposes but it displays the name of a car.
void streetcar::display_carname()
{
  cout << "Here is the name of the car " << car << endl;
  return;
}



//Ask the user if they want to add a car to a loop or a line and
//ask the user what the want to name the car.
void manager::add_car_wrap()
{
   char name[100];
   int num = 0;
   cout << "What would you like the streectar to be named? " << endl
   << "Please choose name the car: ";
   cin.get(name,100,'\n'); cin.ignore(100,'\n');

   cout << "Options: " << endl
   << "1. Add a car to a line " << endl
   << "2. Add a car to a loop " << endl
   << "Please choose: ";
   cin >> num; cin.ignore(100,'\n');

   if(num == 1)
     return head -> add_car(head,name);
   if(num == 2)
     return tail -> add_car(tail,name);
  return;
}



//Adds a streetcar to the first node of the doubly linked list.
void dll::add_car(dll * head, char name[])
{
  if(!head) //no nodes return
    return;

  //If there is no car at the first node we are free to add a car.
  if(!head -> car)
  {
    head -> name_car(name);
    cout << "Car added. " << endl;
    return;
  }

  else
  {
    cout << "Sorry there is already a car at the first location. "
    << "Please move the streetcars to add a new one. " << endl;
    return;
  }
}



//Add a car to the CLL. This car is added at the end of the cll
//because thats where tail is pointing.
void cll::add_car(cll * tail, char name[])
{
  if(!tail) //No node just return
    return;

  if(!tail -> car)
  {
    tail -> name_car(name);
    cout << "Car added. " << endl;
    return;
  }

  else
  {
    cout << "Sorry there is already a car at this location. "
    <<"Please move the streetcars to add a new one. " << endl;
    return;
  }
  return;
}



//Simple function that takes in a temp array and dynamically allocates
//a streetcar name.
void streetcar::name_car(char temp[])
{
  car = new char[strlen(temp)+1];
  strcpy(car,temp);
  return;
}



//Changes the pace for the DLL track.
void dll::add_pace(dll * head, int temp)
{
  if(!head)
    return;

  head -> change_pace(temp);
  return add_pace(head -> go_next(), temp);
}



//Changes the pace for the CLL track.
void cll::add_pace(cll * tail, int temp)
{
  if(!tail)
    return;

  tail -> change_pace(temp);
  return add_pace(tail -> go_next(), temp);
}



//Wrapper function to ask the user what they want the new pace to be,
//and what track they want to change the pace on.
void manager::change_pace_wrap()
{
  int temp = 0;
  char response[50];
  cout << "We are going to change the pace. " << endl
  << "What will the new pace be? ";
  cin >> temp; cin.ignore(100,'\n');

  cout << "Are we changing the pace of a loop or a line? ";
  cin.get(response,100,'\n'); cin.ignore(100,'\n');

  if(strcmp(response,"line") == 0)
  {
    return head -> add_pace(head,temp); //change the dll pace.
  }

  if(strcmp(response,"loop")== 0)
  {
    cll * current = tail;
    tail = tail -> go_next();
    current -> set_next(NULL); //Break the list.

    tail -> add_pace(tail,temp); //Recursive function that adds new pace.

    current -> set_next(tail);
    tail = current; //Reconnect.
    return;
  }
  return;
}



//Simple function that head or tail will call to change the pace in each
//node of the list.
void streetcar::change_pace(int temp)
{
  pace = temp;
  return;
}



//Destorys all dynamic memory in the dll recursively.
void manager::destroy_dll(dll *& head)
{
  if(!head)
    return;
  destroy_dll(head -> go_next());
  head -> destroy_name();
  head -> destroy_car();
  delete head;
  head = NULL;
  return;
}




//Break the cll and destroy it like a linear linked list.
//So it can be destroyed in the destructor.
void manager::destroy_cllwrap()
{
  cll * temp = tail;
  tail = tail -> go_next();
  temp -> set_next(NULL);
  return destroy_cll(tail);
}



//Destroy the entire CLL. This function calls destroy_name to deallocate
//the dynamic data held in the cll. This entire function takes place
//in the destructor.
void manager::destroy_cll(cll *& tail)
{
  if(!tail)
    return;

  destroy_cll(tail -> go_next());
  tail -> destroy_name();
  tail -> destroy_car();
  delete tail;
  tail = NULL;
  return;
}



//Need a wrapper because manager has a cll but does not have access
//to the parents protected data members.
void manager::displaycll_wrap()
{
  cll * temp = tail;
  tail = tail -> go_next();
  temp -> set_next(NULL); //Break the list.

  tail -> display(tail);//Call the display function.

  temp -> set_next(tail);
  tail = temp; //Reconnect.
  return;
}



//This funtion recursivly displays all stops in a circular linked list.
void cll::display(cll * tail)
{
  if(!tail)
    return;

  //CHANGE THE INTERFACE IT LOOKS BAD.
  cout << " -> " << tail -> name << " ";
  //<< "Pace: " << tail -> pace << " ";
  if(tail -> car) //check so no segfault.
  {
    cout << "CAR: " << tail -> car << endl;
  }
  else //If tail -> car is NULL meaning no streetcar at that location.
  {
    cout << "CAR: None" << endl;
  }

  return display(tail -> next);//In cll scope so tail -> next is fine.
}



//This function is called by the constructor of my manager class
//In addition this function builds the circular linked list.
void manager::add_cll(char temp[])
{
  if(!tail) //No nodes.
  {
    tail = new cll;
    tail -> add_name(temp);
    tail -> set_next(tail);
    return;
  }

  if(tail -> go_next() == tail) //One node.
  {
    cll * current = tail;
    tail = new cll;

    tail -> add_name(temp);
    current -> set_next(tail);
    tail -> set_next(current);

    return;
  }

  else //Many nodes. This case is kind of redunant I think.
  {
    cll * current = tail;
    cll * ptr = tail;
    ptr = ptr -> go_next();
    tail = new cll;
    tail -> add_name(temp);
    tail -> set_next(ptr);
    current -> set_next(tail);
    return;
  }
}



//Called from the manager constructor to build the entire doubly linked
//list.
void manager::add_dll(char temp[], dll*&head)
{
  if(!head)//No nodes.
  {
    head = new dll;
    head -> set_previous(NULL);
    head -> set_next(NULL);
    //add the data
    head -> add_name(temp);
    return;
  }
  if(!head -> go_next()) //Is this right?
  {
    dll * current = head;
    current = new dll;
    head -> set_next(current);
    current -> set_previous(head);
    current -> set_next(NULL);
    current -> add_name(temp);
    return; 
  }
  return add_dll(temp, head -> go_next());
}



//Since manager does not have access to stops protected data. A wrapper
//function is needed to 1. protect the data structure from main and 2.
//get accesss to the stop name data.
void manager::display_dllwrap()
{
  return head -> display(head);
}



//Display all stops in the dll.
void dll::display(dll * head)
{
  if(!head)
    return;

  //CHANGE THE INTERFACE LOOKS BAD.
  cout << " -> " << head -> name << " ";
  //<< "Pace: " << head -> pace << " "
  if(head -> car) //check so no segfault.
  {
    cout << "CAR: " << head -> car << endl;
  }
  if(head -> car2)
  {
    cout << "CAR2: " << head -> car2 << endl;
  }
  if(!head -> car && !head -> car2) 
  {
    cout << "CAR: none " << endl;
  }
  return display(head -> go_next());
}




//returns the value of the next pointer. Make sure to catch the value
//through ptr = ptr -> go_next();
cll *& cll::go_next()
{
  return next;
}



//set the next point to the pointer you paass in.
void cll::set_next(cll* tail)
{
  next = tail;
}



//return the next pointer. Catch the value by doing ptr = ptr -> go_next();
dll *& dll::go_next()
{
  return next;
}



//return the previous pointer. Make sure to catch the value so
//ptr = ptr -> go_previous();
dll *& dll::go_previous()
{
  return previous;
}



//Pass in a pointer to set the next ptr = to the one passed in.
void dll::set_next(dll* head)
{
  next = head;
}



//Pass in a pointer to set the previous ptr = to the one passed in.
void dll::set_previous(dll* head)
{
  previous = head;
}



//Pass in a temp array and dynamically allocate name.
//Need a destructor for it.
void stop::add_name(char temp[])
{
  name = new char[strlen(temp)+1];
  strcpy(name,temp);
  return;
}



//Called by head or tail from their display functions.
//Manager has a tail and head ptr.
void stop::display_name()
{
  cout << name << endl;
  return;
}



//Deallocates the dynamic memory for name. THis function is called by
//head and tail via head -> destroy_name() or tail -> destroy_name();
//In the manager destructor.
void stop::destroy_name()
{
  if(name)
  {
    delete [] name;
    name = NULL;
    return;
  }
  return;
}



//Destructors this class holds dynamic data so data needs to be deleted.
manager::~manager()
{
  destroy_cllwrap();
  destroy_dll(head);
  //destroy_graph();
  for(int i = 0; i < 20; ++i)
  {
    node * head = adjacency_list[i];
    adjacency_list[i] -> destroy(head);
  }
  delete [] adjacency_list;
  adjacency_list = NULL;
  head = NULL;
}



//cll destructor. No dynamic memory.
cll::~cll()
{
  next = NULL;
}



//Streetcar destructor.
streetcar::~streetcar()
{
  pace = 0;
  car = NULL;
  car2 = NULL;
}



//stop destructor.
stop::~stop()
{
  name = NULL;
}



//doubly linked list destructor. No dynamic memeory.
dll::~dll()
{
  next = NULL;
  previous = NULL;
}
