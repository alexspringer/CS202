//Alex Springer, CS202, Program 3, 2/24/17
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std;



//A class to handle the first name of a person. The first name is used
//in the LLL of names. The last name however, is in the node class because
//The last name is shared by everyone in the same node.
class person
{
  public:
    person();
    person(const person & obj);
    ~person();

    void delete_name();

    //Overloaded operators
    person & operator= (const person &);
    person & operator= (const char *);
    friend ostream & operator<< (ostream &, const person &);
    friend istream & operator>> (istream &, person &);
    friend bool operator== (const person &, const char *);
    friend bool operator!= (const person &, const char *);

  protected:
    char * first_name;
    int length;

};



//A class with an array of size three of character pointers.
class contact_info:public person
{
  public:
    contact_info();
    contact_info(const contact_info & obj);
    ~contact_info();

    void add_info();
    void destroy();
    void display();

  protected:
    char ** contact;
};



//node for a LLL of names
class lll_node:public contact_info
{
  public:
    lll_node();
    ~lll_node();
    lll_node(const lll_node & obj);

    lll_node *& get_next();
    void set_next(lll_node * head);


    //overloaded operators.
    //we need to compare first names. so == and !=
    //bool & operator== (const char *);
    //bool & operator!= (const char *);
    //friend istream & operator >> (istream & op1, node &);

  private:
    lll_node * next;
};



//node for a BST
class node
{
  public:
    node();
    node(const node & obj);
    ~node();

    //Linear linked list functions.
    void buildWrap();
    void displayWrap();
    void delete_allWrap();
    void copy_allWrap();
    void copy_allWrap(node *& root, node * op2);

    //getters and setters.
    node *& get_left();
    node *& get_right();
    void set_last_name(char * temp);
    void set_left(node * root);
    void set_right(node * root);
    void delete_lastName();
    void get_lastName(char * temp);

    //Used for deciding whether to go left or right in the bst.
    bool is_greater(char * temp);
    bool is_less(char * temp);
    bool is_same(char * temp);
    bool compare(node * root, node * rootTwo) const;


    //overloaded operators.
    node & operator= (const char *);
    node & operator= (const node & op2);
    friend istream & operator >> (istream & op1, node &); 
    friend ostream & operator << (ostream & op1, node & op2);



  private:
    //left and right pointer + a last name. Also has a linear linked list.
    node * left;
    node * right;
    char * last_name;
    lll_node * head;

    //Private functions that deal with the lll in each node.
    int build(lll_node *& head);
    void display(lll_node * head) const;
    void destroy_all(lll_node *& head);
    void copy_all(lll_node *& d_head, lll_node * s_head);
};



//Manager class. Holds a BST
class table
{
  public:
    table();
    table(const table & obj);
    ~table();

    //Wrappers for private functions.
    void buildWrap();
    void displayWrap();
    void searchWrap();
    void search_destroyWrap();
    void copy_allWrap();
    void find_iosWrap();

    //overloaded operators.
    friend table operator + (const table & op1, const table & op2);
    table & operator += (const table & op2);
    table & operator = (const table & op2);
    bool operator == (const table & table2) const;
    bool operator != (const table & table2) const;

  private:
    
    node * root;

    int build(node *& root, char * temp);
    void display(node * root) const;
    void search(node * root, char * temp) const;
    void search_destroy(node *& root, char * temp, node *& previous);
    void destroy_all(node *& root);
    void copy_all(node *& d_root, node * s_root);
    void find_ios(node *& root, node *& current, node *& previous);
    bool compare_all(node * root, node * root2) const;
};
