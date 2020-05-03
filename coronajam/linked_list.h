
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct node {
   int data;
   struct node* next;
};

struct cursors {
   node* previous = nullptr;
   node* match = nullptr;
};

node* createNode();

void freeNode(node* link);

node* createList(int value) ;

void destroyList(node* head) ;

cursors findEnd(node* head) ;

cursors findValue(node* head, int searchVal) ;

void addToStart(node* &head, int value) ;

void addToEnd(node* head, int value) ;

int findLength(node* head) ;

void deleteByValue(node* &head, int value) ;

int popStart(node* &head) ;

int popEnd(node* head) ;

void printList(node* head) ;

void testListFuncs() ;

#endif // !LINKED_LIST_H