//Alex Springer, CS202, Program 3,2/24/17
#include "table.h"



///////////////////////////////////////////////////////////////////////////////

//Constructors

///////////////////////////////////////////////////////////////////////////////



//Table constructor.
table::table():root(NULL){}



//Constructor for bst tree node. Set pointer to NULL. Possibly need to add
//A head pointer to a LLL here.
node::node():left(NULL),right(NULL),head(NULL),last_name(NULL){}



//Constructor for a LLL, set next to NULL. Data members are in the 
//hierarchy.
lll_node::lll_node():next(NULL){}



//Since contact info is an array of three char * pointers. We create the array
//of size three and set each pointer to NULL.
contact_info::contact_info()
{
 contact = new char*[3];// size of three because there are three contacts.
 for(int i = 0; i < 3; ++i)
 {
   contact[i] = NULL;
 }
}



//Person constructor. This class stores a first and last name.
person::person():first_name(NULL),length(0){}



//Copy constructor for a lll_node, important of calling other constructors
//via the initialization list.
lll_node::lll_node(const lll_node & obj):contact_info(obj){}



//contact information copy constructor.
contact_info::contact_info(const contact_info & obj):person(obj)
{
  contact = new char*[3];

  for(int i = 0; i < 3; ++i)
  {
    contact[i] = new char[strlen(obj.contact[i]) +1];
    strcpy(contact[i],obj.contact[i]);
  }
}



//Person copy constructor.
person::person(const person & obj)
{
  first_name = new char[strlen(obj.first_name)];
  strcpy(first_name,obj.first_name);
}



//
table::table(const table & obj)
{
  //recursvie function to copy all data inside a BST node.
  copy_all(root,obj.root);
}



//node copy constructor.
node::node(const node & obj)
{
  last_name = new char[strlen(obj.last_name)+1];
  strcpy(last_name,obj.last_name);
  copy_all(head,obj.head);
}



///////////////////////////////////////////////////////////////////////////////

//Class Person functions

///////////////////////////////////////////////////////////////////////////////



//Deallocate dynamic memory for char * first_name
void person::delete_name()
{
  if(first_name)
  {
    delete [] first_name;
    first_name = NULL;
  }
  return;
}



//Compares the first name of a person to the other operator.
bool operator==(const person & op1, const char * op2)
{
  if(strcmp(op1.first_name,op2) == 0)
  {
    return true;
  }

  return false;
}



//Compares the first name of a person to the other operator.
bool operator!=(const person & op1, const char * op2)
{
  if(strcmp(op1.first_name,op2) != 0)
  {
    return true;
  }

  return false;
}



//Assignment operator overloaded to apply to objects of class person.
person & person::operator= (const person & op2)
{
  if(this == &op2)
  {
    return *this;
  }

  delete [] first_name;
  length = op2.length;
  first_name = new char[length + 1];
  strcpy(first_name,op2.first_name);
  return * this;
}



//Copies a persons first name.
person & person::operator= (const char * op2)
{
  if(first_name)
  {
    delete [] first_name;
  }

  length = strlen(op2);
  first_name = new char[length + 1];
  strcpy(first_name,op2);
  return *this;
}



//<< overloaded to display the data members of class person.
ostream & operator<< (ostream & op1, const person & op2)
{
  op1 << "First name: " << op2.first_name;
  return op1;
}



//>> overloaded op to cin >> first name.
istream & operator>> (istream & op1,person & op2)
{
  char temp[100];
  op1 >> temp;

  if(op2.first_name)
    delete [] op2.first_name;
  op2.length = strlen(temp);
  op2.first_name = new char[op2.length+1];
  strcpy(op2.first_name, temp);

  return op1;
}



///////////////////////////////////////////////////////////////////////////////

//Class contact_information functions.

///////////////////////////////////////////////////////////////////////////////



//Display all information for contact
void contact_info::display()
{
  cout << "Here are the ways you can contact this person: ";
  for(int i = 0;i < 3; ++i)
  {
    cout << contact[i] << " ";
  }
  cout << endl;
  return;
}



//Allocate all information for contact
void contact_info::add_info()
{
  char temp[100];
  for(int i = 0; i < 3; ++i)
  {
    if(!contact[i])
    {
      cout << "Please add a way to contact this person: ";
      cin.get(temp,100,'\n'); cin.ignore(100,'\n');
      contact[i] = new char[strlen(temp)+1];
      strcpy(contact[i],temp);
      //cin >> contact[i]; //overload this operator
    }
  }
  return;
}



//Deallocate all dynamic memory for contact
void contact_info::destroy()
{
  for(int i = 0; i < 3; ++i)
  {
    if(contact[i])
    {
      delete [] contact[i];
      contact[i] = NULL;
    }
  }
  return;
}



///////////////////////////////////////////////////////////////////////////////

//Class lll_node functions

///////////////////////////////////////////////////////////////////////////////



//Return the next pointer for a LLL.
lll_node *& lll_node::get_next()
{
  return next;
}



//Set the next pointer.
void lll_node::set_next(lll_node * head)
{
  next = head;
}



///////////////////////////////////////////////////////////////////////////////

//Class node functions

///////////////////////////////////////////////////////////////////////////////



//Copies all data inside a node.
node & node::operator = (const node & op2)
{
  if(last_name)
  {
    delete [] last_name;
    last_name = NULL;
  }

  if(head)
  {
    destroy_all(head); //Recursive function to delete the LLL.
  }

  last_name = new char[strlen(op2.last_name)+1];
  strcpy(last_name,op2.last_name);

  copy_all(head,op2.head); //Recursive function to copy a LLL.
}



//Deleta all wrapper
void node::delete_allWrap()
{
  return destroy_all(head);
}



//Deallocate all dynamic memory for a linear linked list. Deallocates a char *
//and a char **.
void node::destroy_all(lll_node *& head)
{
  if(!head)
  {
    return;
  }

  destroy_all(head -> get_next());
  head -> destroy(); //A func with a for loop to deallocate char ** contact.
  head -> delete_name(); //A function to delete a char * first_name.
  delete head;
  head = NULL;
  return;
}



//Wrapper to display a char * first_name and a char ** contact info where
//there are there ways to contact a person.
void node::displayWrap()
{
  return display(head);
}



//Display the first name and contact information
void node::display(lll_node * head) const
{
  if(!head)
  {
    return;
  }

  cout << *head << endl;
  head -> display();

  return display(head -> get_next());
}



//Add a name to the linear linked list *CHANGE THIS TO INSERT BY NAME SORT*
//wraps aslong as the user wants to enter another person.
void node::buildWrap()
{
  int success = 0;
  char response = ' ';
  while(response != 'n')
  {
    success = build(head);
    if(success)
    {
      cout << "Success! " << endl;
    }

    cout << "Would you like to add another person? (y / n) ";
    cin >> response; cin.ignore(100,'\n');
  }
  return;
}



//Adds a new node to a LLL and adds a char * name and a char ** contact.
int node::build(lll_node *& head)
{
  if(!head)
  {
    head = new lll_node;
    head -> set_next(NULL);
    cout << "What is the persons first name? ";
    cin >> *head; cin.ignore(100,'\n');
    head -> add_info(); 
    return 1;
  }

  return build(head -> get_next()) + 1;
}



//Overloaded operator to display the last name;
ostream & operator << (ostream & op1, node & op2)
{
  op1 << "Last name: " << op2.last_name << endl;
  return op1;
}



//given a char * copies it into the last name of a node.
node & node::operator= (const char * op2)
{
  if(last_name)
  {
    delete [] last_name;
  }

  //length = strlen(op2);
  last_name = new char[strlen(op2) + 1];
  strcpy(last_name,op2);
  return *this;
}



//Determines if a node should be inserted right of a node.
bool node::is_greater(char * temp)
{
  int size_op1 = 0;
  int size_op2 = 0;

  if(!last_name)
  {
    return false;
  }

  for(int i = 0; i < strlen(last_name); ++i)
  {
    size_op1 += last_name[i]; //add ascii values of the last name
  }

  for(int i = 0; i< strlen(temp); ++i)
  {
    size_op2 += temp[i];
  }

  return (size_op1 > size_op2);
}



//Determines if a node should be inserted left of a node.
bool node::is_less(char * temp)
{
  int size_op1 = 0;
  int size_op2 = 0;

  if(!last_name)
  {
    return false;
  }

  for(int i = 0; i < strlen(last_name); ++i)
  {
    size_op1 += last_name[i];
  }

  for(int i = 0; i< strlen(temp); ++i)
  {
    size_op2 += temp[i];
  }

  return (size_op1 < size_op2);
}



//Determines if a node has a match for a last name. Used when deleting one node
//or displaying only one node.
bool node::is_same(char * temp)
{
  if(strcmp(last_name,temp)==0)
  {
    return true;
  }

  return false;
}



//Return the left pointer
node *& node::get_left()
{
  return left;
}



//Return the right pointer
node *& node::get_right()
{
  return right;
}



//sets the left pointer
void node::set_left(node * root)
{
  left = root;
}



//sets the right pointer
void node::set_right(node * root)
{
  right = root;
}



//Sets a char * last_name
void node::set_last_name(char * temp)
{
  if(last_name)
  {
    delete [] last_name;
  }

  last_name = new char[strlen(temp)+1];
  strcpy(last_name,temp);
  return;
}



//Deallocates memory for a last name.
void node::delete_lastName()
{
  if(last_name)
  {
    delete [] last_name;
    last_name = NULL;
  }

  return;
}



//Not sure if this wrapper is needed.
void node::copy_allWrap()
{
  lll_node * d_head = NULL;
  return copy_all(d_head, head);
}



//called from my assignment operator overloader to copy the linear linked list
//portion of the node.
void node::copy_allWrap(node *& root, node * op2)
{
  copy_all(root -> head,op2 -> head);
  return;
}



//Calls copy constructor to copy all data for a lll_node.
void node::copy_all(lll_node *& d_head, lll_node * s_head)
{
  if(!s_head)
  {
    d_head = NULL;
    return;
  }

  d_head = new lll_node(*s_head);
  return copy_all(d_head -> get_next(), s_head -> get_next());
}



//Getter for the lastname data member
void node::get_lastName(char * temp)
{
  if(!last_name)
  {
    return;
  }

  strcpy(temp,last_name);  //temp is a char[100] temp.
  return;
}



//Checks to see if the two last names are the same.
bool node::compare(node * root, node * rootTwo) const
{
  if(strcmp(root -> last_name, rootTwo -> last_name)==0)
  {
    return true;
  }
  else
    return false;
}



///////////////////////////////////////////////////////////////////////////////

//Class table functions

///////////////////////////////////////////////////////////////////////////////



//+ operator overload
table operator + (const table & op1, const table & op2)
{
  table temp(op1);
  if(!temp.root)
  {
    temp = op2;
  }
  else
  {
    node * d_root = temp.root;
    node * s_root = op2.root;
    //op1.copy_all(d_root, s_root);
  }
  return temp;
}



//+= overload.
table & table::operator += (const table & op2)
{
  if(!root)
  {
    *this = op2;
  }

  else
  {
    node * d_root = root;
    node * s_root = op2.root;
    copy_all(d_root,s_root);
  }
  return *this;
}


//Calls a function to see if two node are the same.
bool table::compare_all(node * root, node * root2) const
{
  if(root -> compare(root,root2))
  {
    return true;
  }
  return false;
}



//Calls a function to see if two trees are the same.
bool table::operator ==(const table & table2) const
{
  node * first = root;
  node * second = table2.root;
  
  return compare_all(root, second);
}



//Checks if trees are not the same
bool table::operator !=(const table & table2) const
{
  return !(*this == table2);
}



//Copies the entire bst;
void table::copy_all(node *& d_root, node * s_root)
{
  if(!s_root -> get_left())
  {
    d_root -> set_left(NULL);
    return;
  }

  if(!s_root -> get_right())
  {
    d_root -> set_right(NULL);
    return;
  }

  d_root = new node;
  //The following deletes any data in d_root if it exists, it doesn't,
  //and then it copies all of s_roots data into it.
  *d_root = *s_root;
  copy_all(d_root -> get_left(), s_root -> get_left());
  copy_all(d_root -> get_right(), s_root -> get_right());
  return;
}



//Copies a bst.
table & table::operator = (const table & op2)
{
  if(this == &op2)
    return *this;
    
  if(root)
  {
    destroy_all(root);
  }

  copy_all(root,op2.root);
}




//User inputs a name. Searchs for the name and deletes it from a bst.
void table::search_destroyWrap()
{
  char temp[100];
  node * previous = root;
  cout << "What last name would you like to remove? ";
  cin.get(temp,100,'\n'); cin.ignore(100,'\n');
  return search_destroy(root, temp, previous);
}



//Search for a last name and delete it from the bst.
void table::search_destroy(node *& root, char * temp, node *& previous)
{
  if(!root)
    return;

  if(root -> is_same(temp))
  {
    if(!root -> get_left() && !root -> get_right()) //if leaf.
    {
      root -> delete_lastName();
      root -> delete_allWrap();
      if(previous -> get_left() == root)
      {
        previous -> set_left(NULL);
      }

      else
      {
        previous -> set_right(NULL);
      }
      delete root;
      root = NULL;
      return;
    }

    if(!root -> get_left() && root -> get_right()) //1 right child
    {
      node * current = root -> get_right();
      //copy currents data into root.
      *root = *current; //Uses the overloaded assignment of node.
      root -> set_left(current -> get_left());
      root -> set_right(current -> get_right());      
      current -> delete_lastName();
      current -> delete_allWrap();
      delete current;
      current = NULL;
      return;
    }

    if(root -> get_left() && !root -> get_right()) //1 left child
    {
      node * current = root -> get_left();
      //root -> delete_lastName();
      //root -> delete_allWrap();
      //copy like in the previous if
      //root = current;
      *root = *current; //Uses the overloaded assignment of node.
      root -> set_left(current -> get_left());
      root -> set_right(current -> get_right());
      current -> delete_lastName();
      current -> delete_allWrap();
      delete current;
      current = NULL;
      return;
    }

    if(root -> get_left() && root -> get_right()) //2 childs, find IOS.
    {
      node * current = root;
      node * previous = root;
      //call ios function.
      find_ios(root, current -> get_left(), previous);
    }
  }
  search_destroy(root -> get_left(), temp, root);
  search_destroy(root -> get_right(), temp, root);
  return;
}     



//Find the in order successer
void table::find_ios(node *& root, node *& current, node *& previous)
{
  if(!current -> get_right()) //if all the way right
  {
    *root = *current; //copy currents data into root.
    previous -> set_right(current -> get_left()); //if ios has a left reconnect.
    delete current;
    current = NULL;
  }
  return find_ios(root, current -> get_right(), current);
}



//Searches for a name to display it.
void table::searchWrap()
{
  char temp[100];
  cout << "What last name would you like to search for? ";
  cin.get(temp,100,'\n'); cin.ignore(100,'\n');
  return search(root,temp);
}



//Searches for a name to display it.
void table::search(node * root, char * temp) const
{
  if(!root)
  {
    return;
  }

  if(root -> is_same(temp))
  {
    cout << *root;
    root -> displayWrap();
  }
  search(root -> get_left(),temp);
  search(root -> get_right(),temp);
  return;
}



//Recursive function to delete every node in the BST. Calls functions to delete
//the data members.
void table::destroy_all(node *& root)
{
  if(!root)
    return;

  destroy_all(root -> get_left());
  destroy_all(root -> get_right());
  root -> delete_lastName();
  root -> delete_allWrap();
  delete root;
  root = NULL;
  return;
}



//Display wrapper
void table::displayWrap()
{
  return display(root);
}



//Displays all data held in each node of the bst.
void table::display(node * root) const
{
  if(!root)
  {
    return;
  }

  //root -> display(); This does the same thing as the overloaded op.
  cout << *root;
  root -> displayWrap();
  //will need to add first name and contact info eventually.

  display(root -> get_left());
  display(root -> get_right());
  return;
}



//Wrapper for my build function for bst.
void table::buildWrap()
{
  char temp[100];
  cout << "What last name are we adding? ";
  cin.get(temp,100,'\n'); cin.ignore(100,'\n');
  build(root, temp);

  return;
}



//Build a binary search tree. calls functions to set the last name
//calls a function that builds a lll aswell.
int table::build(node *& root, char * temp)
{
  if(!root)
  {
    //root += node;
    root = new node;
    root -> set_last_name(temp);
    root -> buildWrap(); //build the LLL
    root -> set_right(NULL);
    root -> set_left(NULL);
  }

  if(root -> is_greater(temp))
  {
    build(root -> get_right(), temp);
  }

  if(root -> is_less(temp))
  {
    build(root -> get_left(), temp);
  }

  return 1;
}



///////////////////////////////////////////////////////////////////////////////

//Destructors

///////////////////////////////////////////////////////////////////////////////



//Destructor for a 2-3 tree node. Set pointers to NULL
node::~node()
{
  right = NULL;
  left = NULL;
}



//Destructor for LLL node. Set next to NULL
lll_node::~lll_node()
{
  next = NULL;
}



//destructor serves as a wrapper for a recursive function to destroy the tree.
table::~table()
{
  destroy_all(root);
}



//Calls function to deallocate if there memory existing.
contact_info::~contact_info()
{
  contact = NULL;
}



//Calls function to deallocate if there is memory existing.
person::~person()
{
  length = 0;
  first_name = NULL;
}
