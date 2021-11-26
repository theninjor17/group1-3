/*  Data Structures and Algorithms Assignment 1
    By: Nickolas Raghunath, Carter Folkes and Guneet Matharu

  interface for queues functionality
*/


#ifndef BLOCK
#define BLOCK
//constants
#define userLen 140
//typedef of struct items and nodes
typedef struct node Node;
typedef struct item Item;
typedef Node* link;

//struct item vars
struct item{
    char message[userLen];
    short int sid;      //Sender ID
    short int rid;      //Receiever ID
    char priority;      //priority of message
    short int seqNum;   //sequence number of the message
    char later[25];     //char we might use later

};

struct node{
    link pNext;
    Item Data;
};

//Queue function prototypes
void InitQueue(void);
int IsQueueEmpty(void);
void AddToQueue(link);
link DeQueue(void);

//Recursive Queue functions
link returnHead();
int count(link x);
link deleteR(link parent, link child, Item v);
void visit(link h);
void traverse(link h, void (*visit)(link));
void traverseR(link h, void (*visit)(link));

#endif