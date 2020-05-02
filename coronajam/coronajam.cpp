// coronajam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>

struct node {
   int data;
   struct node* next;
};

struct cursors {
   node* previous = nullptr;
   node* match = nullptr;
};

node* createNode() {
   node* newNode = (node*)malloc(sizeof(node));

   if (newNode == NULL) {
      fprintf(stdout, "There was an error making the node.");
      exit(0);
   }

   newNode->next = nullptr;
   return newNode;
}

void freeNode(node* link) {
   free(link);
}

node* createList(int value) {
   node* newList = createNode();
   newList->data = value;
   return newList;
}


void destroyList(node* head) {
   node* target = nullptr;

   while (head != nullptr) {
      target = head;
      head = head->next;
      freeNode(target);
   }
}

cursors findEnd(node* head) {
   cursors out;

   while (head != nullptr) {
      if (head->next == nullptr) {
         out.match = head;
         return out;
      }
      out.previous = head;
      head = head->next;
   }
}

cursors findValue(node* head, int searchVal){
   cursors out;

   while (head != nullptr) {
      if (searchVal == head->data) {
         out.match = head;
         return out;
      }
      out.previous = head;
      head = head->next;

   }
   return out; 
}

void addToStart(node* &head, int value) {
   node* newNode = createNode();
   newNode->data = value;
   newNode->next = head;

   head = newNode;
}


void addToEnd(node* head, int value) {
   node* newNode = createNode();

   newNode->data = value;
   cursors end = findEnd(head);
   end.match->next = newNode;
}

int findLength(node* head) {
   int count = 0;
   while (head != nullptr) {
      count++;
      head = head->next;
   }
   return count;
}

void deleteByValue(node* &head, int value){
   cursors target = findValue(head, value);
   if (! target.match) { 
      fprintf(stdout, "Attempted to delete %d \nNo matching value in list.\n", value);
      return; 
   }

   if (target.previous == nullptr) {
      head = target.match->next;
      freeNode(target.match);
   }

   else if (target.match->next == nullptr) {
      target.previous->next = nullptr;
      freeNode(target.match);
   }

   else {
      target.previous->next = target.match->next;
      freeNode(target.match);
   }
}

int popStart(node* &head) {
   int out = head->data;
   deleteByValue(head, out);
   return out;
}

int popEnd(node* head) {
   cursors target = findEnd(head);
   int out = target.match->data;
   freeNode(target.match);
   target.previous->next = nullptr;
   return out;

}

void printList(node* head){
   fprintf(stdout, "----BEGIN LIST-----\n");
   int count = 0;
   while (head != nullptr) {
      count++;
      fprintf(stdout, "%d %d\n", count, head->data);
      head = head->next;
   }
}


int main()
{
   node* head = createList(3);

   addToStart(head, 2);
   addToStart(head, 5);

   printList(head);

   addToEnd(head, 3);
   addToEnd(head, 8);

   printList(head);

   deleteByValue(head, 2);
   deleteByValue(head, 8);
   deleteByValue(head, NULL);

   printList(head);

   findValue(head, 3);

   addToStart(head, 2);
   addToStart(head, 5);

   printList(head);

   fprintf(stdout, "POP START: %d \n", popStart(head));

   printList(head);

   fprintf(stdout, "POP END: %d \n", popEnd(head));

   printList(head);

   fprintf(stdout, "List length: %d \n", findLength(head) );

   destroyList(head);

}
