/*  Data Structures and Algorithms Assignment 1
    By: Nickolas Raghunath, Carter Folkes and Guneet Matharu

  Queue function implementation
*/

#include "Queues.h"
#include <stdlib.h>
#include <stdio.h>

static link pHead, pTail;

//Function to Initialize Queue
void InitQueue(void){
    pHead = pTail = NULL;
}
//Function to check if Queue is empty
int IsQueueEmpty(void){
    return(pHead == NULL);
}
//Function to add a new node to the queue
void AddToQueue(link pn){
    //If queue is empty, new node is the first node starting at the begginning, otherwise node is added at the end with tail pointing to it
    if(IsQueueEmpty()){
        pHead = pTail = pn;
    } else {
        //old tail now points to pn
        pTail->pNext = pn;
        //pTail points to pn          
        pTail = pn;                 
    }
    pTail->pNext = NULL;
}
//Function to deqeue a node from the queue
link DeQueue(void){
    //will hold current head
    link pTemp;                     
    if (IsQueueEmpty()){
        return(NULL);
    } else {
        //phead is returned and incremmented to next node in list
        pTemp = pHead;
        //pHead points to next node              
        pHead = pHead->pNext;
        //pTemp is original head       
        return(pTemp);              
    }
}


// Assignment #2 - Recursive traverse functions

link returnHead() {
    return pHead;
}

int count(link x) {
    if (x == NULL) return 0;
    return (1 + count(x->pNext));
}

link deleteR(link parent, link child, Item v) {
    if (child == NULL) return(NULL);
    if (child->Data.sid == v.sid) {
        parent->pNext = child->pNext;
        free(child);
        deleteR(parent, parent->pNext, v);
    }
    else {
        deleteR(child, child->pNext, v);
    }
}

void visit(link h) {
    printf("\nSID of node: %d\n", h->Data.sid);
}

void traverse(link h, void (*visit)(link)) {
    if (h == NULL) return;
    (*visit)(h);
    traverse(h->pNext, visit);
}

void traverseR(link h, void (*visit)(link)) {
    if (h == NULL) return;
    traverseR(h->pNext, visit);
    (*visit)(h);
}
