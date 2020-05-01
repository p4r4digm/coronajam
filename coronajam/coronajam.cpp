// coronajam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>

struct node {
   int data;
   struct node* next;
};

node* createNode(int value, node* next = nullptr) {
   node* newNode = (node*)malloc(sizeof(node));

   if (newNode == NULL) {
      fprintf(stdout, "There was an error making the node.");
      exit(0);
   }

   newNode->data = value;
   newNode->next = next;
   return newNode;
};

void freeNode(node* link) {
   free(link);
};

node* addToStart(node* head, int value) {
   node* newNode = createNode(value, head);
   head = newNode;

   return head;
};

node* findValue(node* head, int searchVal = NULL){
   node* position = head;
   int count = 1;
   while (position != nullptr) {
      if (searchVal == position->data) {
         //fprintf(stdout, "%d %p \n", position->data, position->next);
         return position;
      }
      if (position->next == nullptr) {
         return position;
      }
      position = position->next;
      count++;

   }
   return position; //this seems bad
};

int findLength(node* head) {
   node* position = head;
   int count = 1;
   while (position != nullptr) {
      if (position->next == nullptr) {
         fprintf(stdout, "Length is %d \n", count);
         return count;
      }
      position = position->next;
      count++;

   }
};


void addToEnd(node* head, int value) {
   node* newNode = createNode(value);

   node* end = findValue(head, NULL);
   end->next = newNode;
};

node* deleteNode(node* head, int value){
   node* position = head;
   node* previous = nullptr;
   int count = 1;

   while (position != nullptr) {
      if (value == position->data) {
         if (previous == nullptr) { //at the start
            head = position->next;
            freeNode(position);
            return head;
         }
         else if(position->next == nullptr) { //at the end
            previous->next = nullptr;
            freeNode(position);
            return head;
         }
         else { //hopefully in the middle
            previous->next = position->next;
            freeNode(position);
            return head;
         }
      }

      previous = position;
      position = position->next;
      count++;

   }
   
};

void printList(node* head){
   node* position = head;
   int count = 1;
   fprintf(stdout, "----BEGIN LIST-----\n");
   while (position != nullptr) {
      fprintf(stdout, "%d %d\n", count, position->data);
      position = position->next;
      count ++;
   }
};


int main()
{
   node* head = createNode(7);

   printList(head);

   head = addToStart(head, 2);

   printList(head);

   head = addToStart(head, 5);

   printList(head);

   addToEnd(head, 8);

   printList(head);

   head = deleteNode(head, 2);

   printList(head);

   head = deleteNode(head, 8);

   printList(head);

   findLength(head);

}
