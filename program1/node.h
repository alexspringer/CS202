//Alex Springer, CS202, Program 1
#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>



//This is the LLL that represents the adj list.
class node
{
  public:
    void add_location(char temp[], int i);
    void display(node * head);
    void traverse(node * head);
    void destroy(node *& head);
    node *& get_next();
    void set_next(node *);
  protected:
    char * location_name;
    node * next; 
};



//This class represents the location and it is the base class in this
//Program
class stop
{
  public:
    stop();
    ~stop();
    void add_name(char temp[]);
    void display_name();
    void destroy_name();

  protected:
    char * name;
};



//This class represents a streetcar. A streetcar "is a" location
//plus more.
class streetcar:public stop
{
  public:
    streetcar();
    ~streetcar();
    void change_pace(int temp);
    void display_pace();
    void display_carname();
    void destroy_car(); //This is for the cll and one track of the dll.
    void destroy_car2(); //Only for the 2nd track of the dll.
    void name_car(char temp[]);
    void name_car2(char temp[]); //only for 2nd track of the dll


  protected:
    int pace;
    char * car;
    char * car2; //This is the streetcar returning on a dll.
};



//Has set and get functions aswell as display. This function has setters
//and getters because its one of my node classes. "Is a streetcar and 
//location".
class cll:public streetcar
{
  public:
    cll();
    ~cll();
    //cll(char * stop);
    void display(cll * tail);

    //Functions to move streetcars around.
    void add_pace(cll * tail, int temp);
    void add_car(cll * tail, char name[]);
    void remove_car(cll * tail, char temp[]);
    void move_car(cll * tail);
    bool peek(cll * tail);

    //Setters and getters only for my node classes.
    cll *& go_next();
    void set_next(cll*); 

  protected:
    cll * next;
};



//Has set and get functions and also display. This function has setters
//and getters just because its one of my node classes. "Is a streetcar
//and location".
class dll:public streetcar
{
  public:
    dll();
    ~dll();
    //dll(char * stop);
    //Display all stops
    void display(dll * head);
    
    //Functions that interact with streetcars.
    void add_pace(dll * head, int temp);
    void add_car(dll * head, char name[]);
    void add_car2(dll * head, char name[]);
    void remove_car(dll * head, char temp[]);
    void move_car(dll * head);
    bool peek_next(dll * head);
    bool peek_previous(dll * head);

    //Setters and getters only for my node classes.
    dll *& go_next();
    dll *& go_previous();
    void set_next(dll* head);
    void set_previous(dll* head);

  protected:
    dll * next;
    dll * previous;
};



//This class manages the data and has a relationship with my doubly
//linked list, circular linked list.
class manager
{
  public:
    manager();
    ~manager();
    //CLL functions.
    void add_cll(char temp[]);
    void destroy_cll(cll *& tail);
    void destroy_cllwrap();
    void displaycll_wrap();

    //DLL functions.
    void add_dll(char temp[], dll *& head);
    void display_dllwrap();
    void destroy_dll(dll *& head);

    //Streetcar wrappers.
    void add_car_wrap();
    void remove_car_wrap();
    void change_pace_wrap();
    void move_car_wrap();

    //Graph wrappers.
    void display_graph_wrap();


  protected:
    cll * tail; //"Has a" Circular linked list.
    dll * head; //"Has a doubly linked list.
    node ** adjacency_list;//"Has a" graph.
};
