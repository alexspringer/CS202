//Alex Springer, Program 2, CS202, 2/10/17
#include "transport.h"
using namespace std;



//Default constructor for my base class.
transport::transport(){}



//Default constructor for my array of LLL. I only have 3 index in 
//the array because each index is a differeent form of transportation.
popularity::popularity()
{
  array = new transport*[3]; //Each index = type of transport.
  for(int i = 0; i < 3; ++i)
  {
    array[i] = NULL;
  }
}



//Default constructor for my node class.
node::node()
{
  next = NULL;
  exp = NULL;
}




//Default constructor for a derived form of transportation
MAX::MAX()
{
  head = NULL;
  p_head = NULL;
}



//Default constructor for a derived form of transportation
bus::bus()
{
  head = NULL;
  p_head = NULL;
}



//Default constructor for a derived form of transportation
uber::uber()
{
  head = NULL;
  p_head = NULL;
}



//Default constructor for a node in the array of LLL
transit_node::transit_node()
{
  next = NULL;
  time = NULL;
  busy = NULL;
}



//MAX copy constructor
MAX::MAX(const MAX & obj):transport()
{
  node * d_head = NULL;
  copy(head, d_head);
}



//bus copy constructor
bus::bus(const bus & obj):transport()
{
  node * d_head = NULL;
  copy(head, d_head);
}



//uber copy constructor
uber::uber(const uber & obj):transport()
{
  node * d_head = NULL;
  copy(head, d_head);
}



//
void node::copy_exp(char * temp)
{
  if(!exp)
    return;

  strcpy(temp, exp); //temp is going to be a static allocated array
  return;
}



//Called from the copy constructor. Makes a copy of the LLL of exp
void MAX::copy(node * s_head, node *& d_head)
{
  char temp[100];
  if(!s_head)
  {
    d_head = NULL;
    return;
  }

  d_head = new node;
  s_head -> copy_exp(temp); //exp data copied into temp.
  d_head -> add_exp(temp); //temp data added to new node.
  return copy(s_head -> get_next(), d_head -> get_next());
}



//Called from the copy constructor. Makes a copy of the LLL of exp
void bus::copy(node * s_head, node *& d_head)
{
  char temp[100];
  if(!s_head)
  {
    d_head = NULL;
    return;
  }

  d_head = new node;
  s_head -> copy_exp(temp); //exp data copied into temp.
  d_head -> add_exp(temp); //temp data added to new node.
  return copy(s_head -> get_next(), d_head -> get_next());
}



//Called from the copy constructor. Makes a copy of the LLL of exp
void uber::copy(node * s_head, node *& d_head)
{
  char temp[100];
  if(!s_head)
  {
    d_head = NULL;
    return;
  }

  d_head = new node;
  s_head -> copy_exp(temp); //exp data copied into temp.
  d_head -> add_exp(temp); //temp data added to new node.
  return copy(s_head -> get_next(), d_head -> get_next());
}



//Virtual functions:
void transport::add_experience(){}



//
void transport::display_experience(node * head){}



//
void transport::display_experienceWrap(){}



//
void transport::destroy_all(node *& head){}



//
void transport::delete_oneWrap(){}



//
void transport::delete_one(node *& head){}



//
//void transport::build_LLL(transit_node *& p_head, char * time, 
//	char * busy){}



//
void transport::build_LLLWrap(){}



//
void transport::display_popWrap(){}



//
void transport::destroy_popLLLWrap(){}



//Getter for my transit node class.
transit_node *& transit_node::get_next()
{
  return next;
}



//Setter for my transit node class
void transit_node::set_next(transit_node * head)
{
  next = head;
}



//Pass in a temp variable and allocate memory for time
void transit_node::add_time(char * temp)
{
  time = new char[strlen(temp)+1];
  strcpy(time,temp);
  return;
}



//Pass in a temp variable and allocate memory for how busy
//a certain form of transportation is.
void transit_node::add_busy(char * temp)
{
  busy = new char[strlen(temp)+1];
  strcpy(busy,temp);
  return;
}



//Deletes any dynamic memory allocated. This is called when
//deleting the data struture.
void transit_node::delete_time()
{
  if(time)
  {
    delete [] time;
    time = NULL;
  }

  return;
}



//Also used for deleting dynamic memory in the array of LLL dest
//ructor.
void transit_node::delete_busy()
{
  if(busy)
  {
    delete [] busy;
    busy = NULL;
  }
  return;
}



//Displays the time data.
void transit_node::display_time()
{
  if(time)
  {
    cout << "Time: " << time << endl;
  }
  return;
}



//Displays the busy data.
void transit_node::display_busy()
{
  if(busy)
  {
    cout << "Popularity: " << busy << endl;
  }
  return;
}



//Wrapper function to  destroy the array of LLL. I have a wrapper
//just to pass in i but I probably could have done it in the destructor.
void popularity::destroy_popularityWrap()
{
  int i = 0;
  return destroy_popularity(array, i);
}



//Deletes the array of LLL. A function is called to delete the LLL in
//each index.
void popularity::destroy_popularity(transport **& array, int & i)
{
  if(i == 3) //Only 3 index
    return;

  if(!array[i])
    return;

  //call function to delete the LLL at the node.
  array[i] -> destroy_popLLLWrap();
  ++i; //increment i to go to the next index next time func called.
  return destroy_popularity(array, i);
}



//Wrapper function so we have availability to p_head.
void MAX::destroy_popLLLWrap()
{
  return destroy_popLLL(p_head);
}



//Recursive function to delete a LLL.
void MAX::destroy_popLLL(transit_node *& p_head)
{
  if(!p_head)
  {
    return;
  }

  destroy_popLLL(p_head -> get_next());
  p_head -> delete_time();
  p_head -> delete_busy();
  delete p_head;
  p_head = NULL;
  return;
}



//Wrapper function so we have accesss to p_head
void bus::destroy_popLLLWrap()
{
  return destroy_popLLL(p_head);
}



//Recursive function to delete a LLL.
void bus::destroy_popLLL(transit_node *& p_head)
{
  if(!p_head)
  {
    return;
  }

  destroy_popLLL(p_head -> get_next());
  p_head -> delete_time();
  p_head -> delete_busy();
  delete p_head;
  p_head = NULL;
  return;
}



//Wrapper to have access to p_head.
void uber::destroy_popLLLWrap()
{
  return destroy_popLLL(p_head);
}



//Recursive function to delete a LLL.
void uber::destroy_popLLL(transit_node *& p_head)
{
  if(!p_head)
  {
    return;
  }

  destroy_popLLL(p_head -> get_next());
  p_head -> delete_time();
  p_head -> delete_busy();
  delete p_head;
  p_head = NULL;
  return;
}



//Wrapper function to set i and display popularity data.
void popularity::display_popularityWrap()
{
  int i = 0;
  return display_popularity(array, i);
}



//Display all popularity data. Calls a function to display the LLL
//At each index.
void popularity::display_popularity(transport ** array, int & i)
{
  if(i == 3) //only 3 index
    return;

  if(!array[i]) //No data at index return
  {
    return;
  }

  array[i] -> display_popWrap(); //Display the LLL
  ++i; //increment i for next time we are in the func.
  return display_popularity(array, i);
}



//wrapper to get access to p_head.
void MAX::display_popWrap()
{
  return display_pop(p_head);
}



//Display all data in a LLL. Recursive.
void MAX::display_pop(transit_node * p_head)
{
  if(!p_head)
  {
    return;
  }

  p_head -> display_time();
  p_head -> display_busy();

  return display_pop(p_head -> get_next());
}



//wrapper to get access to p_head
void bus::display_popWrap()
{
  return display_pop(p_head);
}



//recursive display LLL function.
void bus::display_pop(transit_node * p_head)
{
  if(!p_head)
  {
    return;
  }

  p_head -> display_time();
  p_head -> display_busy();

  return display_pop(p_head -> get_next());
}



//wrapper to get access to p_head;
void uber::display_popWrap()
{
  return display_pop(p_head);
}



//recursive display LLL function
void uber::display_pop(transit_node * p_head)
{
  if(!p_head)
  {
    return;
  }

  p_head -> display_time();
  p_head -> display_busy();

  return display_pop(p_head -> get_next());
}



//Create the array of LLL wrapper.
void popularity::add_popularityWrap()
{
  int i = 0;
  return add_popularity(array, i);
}



//Creates and array of LLL by calling functions to build LLL at each
//index.
void popularity::add_popularity(transport **& array, int & i)
{
  char response; //ASk user if they want to add more times / busy.
  if(i == 3) //only 3 index.
    return;

  if(i == 0) //first index = MAX
  {
    do
    {
      cout << "We are adding to the MAX popularity. " << endl;
      if(!array[i])
        array[i] = new MAX;
      array[i] -> build_LLLWrap();
      cout << "Would you like to add more times? (y/n)  ";
      cin >> response; cin.ignore(100,'\n');
    } while(response != 'n');
  }

  if(i == 1) //2nd index = bus
  {
    do
    {
      cout << "We are adding to the bus popularity. " << endl;
      if(!array[i])
        array[i] = new bus;
      array[i] -> build_LLLWrap();
      cout << "Would you like to add more times? (y/n)  ";
      cin >> response; cin.ignore(100,'\n');
    } while(response != 'n');
  }

  if(i == 2) //3rd indx = uber.
  {
    do
    {
      cout << "We are adding to the uber popularity. " << endl;
      if(!array[i])
        array[i] = new uber;
      array[i] -> build_LLLWrap();
      cout << "Would you like to add more times? (y/n)  ";
      cin >> response; cin.ignore(100,'\n');
    } while(response != 'n');
  }

  ++i; //increment i for the next call of the function. 
  return add_popularity(array, i);
}



//Ask the user what time of day and how busy then pass that information
//to the build function so that data can be added to the node.
void bus::build_LLLWrap()
{
  char time[100];
  char busy[100];

  cout << "What is the time of day: ";
  cin.get(time,100,'\n'); cin.ignore(100,'\n');

  cout << "How busy is the transportation at this time: ";
  cin.get(busy,100,'\n'); cin.ignore(100,'\n');

  return build_LLL(p_head,time,busy);
}



//Builds a LLL recursively
void bus::build_LLL(transit_node *& p_head, char * time, char * busy)
{
  if(!p_head)
  {
    p_head = new transit_node;
    p_head -> add_time(time);
    p_head -> add_busy(busy);
    p_head -> set_next(NULL);
    return;
  }

  return build_LLL(p_head -> get_next(),time,busy);
}
    


//
void bus::delete_oneWrap()
{
  return;
}



void bus::delete_one(node *& head)
{
  return;
}



//delete all data in a LLL called in destructor.
void bus::destroy_all(node *& head)
{
  if(!head)
    return;

  destroy_all(head -> get_next());
  head -> delete_exp();
  delete head;
  head = NULL;
  return;
}


//display wrapper because called from main.
void bus::display_experienceWrap()
{
  return display_experience(head);
}



//Recursive display function.
void bus::display_experience(node * head)
{
  if(!head)
    return;

  cout << "bus experience: ";
  head -> display_exp();
  return display_experience(head -> get_next());


  return;
}



//Add new data at the head. Not a recursive problem.
void bus::add_experience()
{
  char temp[100];
  cout << "How was your last bus experience? " << endl;
  cin.get(temp,100,'\n'); cin.ignore(100,'\n');

  node * current = head;
  head = new node;
  head -> add_exp(temp);
  head -> set_next(current);
  return;
}



//Same as the bus version
void MAX::build_LLLWrap()
{
  char time[100];
  char busy[100];

  cout << "What is the time of day: ";
  cin.get(time,100,'\n'); cin.ignore(100,'\n');

  cout << "How busy is the transportation at this time: ";
  cin.get(busy,100,'\n'); cin.ignore(100,'\n');

  return build_LLL(p_head,time,busy);
}



//Same as the bus version
void MAX::build_LLL(transit_node *& p_head, char * time, char * busy)
{
  if(!p_head)
  {
    p_head = new transit_node;
    p_head -> add_time(time);
    p_head -> add_busy(busy);
    p_head -> set_next(NULL);
    return;
  }

  return build_LLL(p_head -> get_next(),time,busy);
}



//
void MAX::delete_oneWrap()
{
  return;
}



void MAX::delete_one(node *& head)
{
  return;
}



//Same as bus
void MAX::display_experienceWrap()
{
  return display_experience(head);
}



//same as bus
void MAX::display_experience(node * head)
{
  if(!head)
    return;

  cout << "MAX experience: ";
  head -> display_exp();
  return display_experience(head -> get_next());


  return;
}



//same as bus
void MAX::add_experience()
{
  char temp[100];
  cout << "How was your last MAX experience? " << endl;
  cin.get(temp,100,'\n'); cin.ignore(100,'\n');

  node * current = head;
  head = new node;
  head -> add_exp(temp);
  head -> set_next(current);
  return;
}



//same as bus
void MAX::destroy_all(node *& head)
{
  if(!head)
    return;

  destroy_all(head -> get_next());
  head -> delete_exp();
  delete head;
  head = NULL;
  return;
}



//same as bus
void uber::build_LLLWrap()
{
  char time[100];
  char busy[100];

  cout << "What is the time of day: ";
  cin.get(time,100,'\n'); cin.ignore(100,'\n');

  cout << "How busy is the transportation at this time: ";
  cin.get(busy,100,'\n'); cin.ignore(100,'\n');

  return build_LLL(p_head,time,busy);
}



//same as bus
void uber::build_LLL(transit_node *& p_head, char * time, char * busy)
{
  if(!p_head)
  {
    p_head = new transit_node;
    p_head -> add_time(time);
    p_head -> add_busy(busy);
    p_head -> set_next(NULL);
    return;
  }

  return build_LLL(p_head -> get_next(),time,busy);
}



//
void uber::delete_oneWrap()
{
  return;
}



//
void uber::delete_one(node *& head)
{
  return;
}



//same as bus
void uber::display_experienceWrap()
{
  return display_experience(head);
}



//same as bus
void uber::display_experience(node * head)
{
  if(!head)
    return;

  cout << "uber experience: ";
  head -> display_exp();
  return display_experience(head -> get_next());


  return;
}



//same as bus
void uber::add_experience()
{
  char temp[100];
  cout << "How was your last uber experience? " << endl;
  cin.get(temp,100,'\n'); cin.ignore(100,'\n');

  node * current = head;
  head = new node;
  head -> add_exp(temp);
  head -> set_next(current);
  return;
}



//same as bus
void uber::destroy_all(node *& head)
{
  if(!head)
    return;

  destroy_all(head -> get_next());
  head -> delete_exp();
  delete head;
  head = NULL;
  return;
}



//Getter for my node class
node *& node::get_next()
{
  return next;
}



//setter for my node class
void node::set_next(node * head)
{
  next = head;
}



//dynamicall allocate experience data.
void node::add_exp(char * temp)
{
  exp = new char[strlen(temp)+1];
  strcpy(exp,temp);
  return;
}



//Display experience data.
void node::display_exp()
{
  if(exp)
  {
    cout << exp << endl;
  }
  return;
}



//Delete any dynamic experience data.
void node::delete_exp()
{
  if(exp)
  {
    delete [] exp;
    exp = NULL;
  }
  return;
}



//Base class destructor
transport::~transport(){}



//node destructor
node::~node()
{
  next = NULL;
  exp = NULL;
}



//Max desctructor. Calls recursive delete function.
MAX::~MAX()
{
  destroy_all(head);
  head = NULL;
}



//bus destructor. Calls recursive delete function
bus::~bus()
{
  destroy_all(head);
  head = NULL;
}



//uber destructor. Calls recursive delete function.
uber::~uber()
{
  destroy_all(head);
  head = NULL;
}



//Calls recursive delete function and after that executes delete the 
//array and set it to NULL.
popularity::~popularity()
{
  //call recursive delete fucntion;
  destroy_popularityWrap();
  delete [] array;
  array = NULL;
}



//Set transit node pointers to NULL.
transit_node::~transit_node()
{
  next = NULL;
  time = NULL;
  busy = NULL;
}
