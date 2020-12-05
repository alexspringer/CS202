//Alex Springer, Program 2, 2/10/17
#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>



//This node is part of the array of linear linked list. Has a time
//and location char * array.
class transit_node
{
  public:
  
    transit_node();
    ~transit_node();

    transit_node *& get_next();
    void set_next(transit_node *);
    void add_time(char * temp);
    void add_busy(char * temp);
    void delete_time();
    void delete_busy();
    void display_time();
    void display_busy();

  protected:
    transit_node * next;
    char * time;
    char * busy;

};



//This is the node for the linear linked list of experiences. Only has
//a char * experience
class node
{
  public:
    node();
    ~node();


    node *& get_next();
    void set_next(node *);
    
    void display_exp();
    void add_exp(char * temp);
    void copy_exp(char * temp);
    char *& get_exp();
    void delete_exp();
    
  private:
    node * next;
    char * exp;
};



//Base class I am pretty sure that some of these virtual functions are
//not needed. Only the wrapper functions defined in this class need to be
//virtual because they are the only ones called by the transport pointer.
class transport
{
  public:
    transport();
    virtual ~transport();

    //Linear linked list of experiences functions.
    virtual void add_experience();
    virtual void display_experience(node * head);
    virtual void display_experienceWrap();
    virtual void destroy_all(node *& head);
    virtual void delete_oneWrap();
    virtual void delete_one(node *& head);

    //Array of LLL functions
//    virtual void build_LLL(transit_node *& p_head,char * time, char * busy);
    virtual void build_LLLWrap();

    virtual void display_popWrap();
    virtual void destroy_popLLLWrap();

  protected:
};



//This class has a array of points to the base class and serves as the
//array of linear linked lists used for popularity of a transportation
//at certain times in the day.
class popularity
{
  public:
    popularity();
    ~popularity();
    void add_popularityWrap();
    void display_popularityWrap();
    void destroy_popularityWrap();

  protected:
    transport ** array;

    void display_popularity(transport ** array, int & i);
    void destroy_popularity(transport **& array, int & i);
    void add_popularity(transport **& array, int & i);
};



//Derived form of public transporation. Has a head pointer and a p_head
//head is for experiences and p_head is for popularity
class MAX: public transport
{
  public:
    MAX();
    ~MAX();
    MAX(const MAX & obj);
    //LLL of experience functions
    void add_experience();
    void display_experienceWrap();
    void delete_oneWrap();

    //LLL of time of day / busy fucntions
    void build_LLLWrap();
    void display_popWrap();
    void destroy_popLLLWrap();

  protected:
    node * head; //For experience LLL
    transit_node * p_head; //Time / busy LLL.

    void display_experience(node * head);
    void destroy_all(node *& head);
    void delete_one(node*& head);
    void copy(node * s_head, node *& d_head);

    void display_pop(transit_node * p_head);
    void destroy_popLLL(transit_node *& p_head);
    void build_LLL(transit_node *& p_head, char * time, char * busy);

};



//Derived form of public transporation. Has a head pointer and a p_head
//head is for experiences and p_head is for popularity
class bus: public transport
{
  public:
    bus();
    ~bus();
    bus(const bus & obj);

    //LLL of experiences
    void add_experience();
    void display_experienceWrap();
    void delete_oneWrap();

    //LLL of time of day / busy
    void build_LLLWrap();
    void display_popWrap();
    void destroy_popLLLWrap();


  protected:
    node * head; //For experience LLL
    transit_node * p_head; //Time / busy LLL

    void display_experience(node * head);
    void destroy_all(node *& head);
    void delete_one(node*& head);
    void copy(node * s_head, node *& d_head);

    void display_pop(transit_node * p_head);
    void destroy_popLLL(transit_node *& p_head);
    void build_LLL(transit_node *& p_head,char * time,char * busy);
};



//Derived form of public transporation. Has a head pointer and a p_head
//head is for experiences and p_head is for popularity
class uber: public transport
{
  public:
    uber();
    ~uber();
    uber(const uber & obj);

    //LLL of expreiences
    void add_experience();
    void display_experienceWrap();
    void delete_oneWrap();

    //LLL of time of day / busy
    void build_LLLWrap();
    void display_popWrap();
    void destroy_popLLLWrap();

  protected:
    node * head; //head ptr for LLL of exp
    transit_node * p_head; //Head ptr for LLL of time / busy

    void display_experience(node * head);
    void destroy_all(node *& head);
    void delete_one(node*& head);
    void copy(node * s_head, node *& d_head);

    void display_pop(transit_node * p_head);
    void destroy_popLLL(transit_node *& p_head);
    void build_LLL(transit_node *& p_head, char * time, char * busy);
};
