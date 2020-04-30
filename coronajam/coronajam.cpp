// coronajam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>



struct node {
   int data;
   struct node* next;
};

node* createNode(node* next, int value) {
   node* newNode = (node*)malloc(sizeof(node));

   if (newNode == NULL) {
      fprintf(stdout, "There was an error making the node.");
      exit(0);
   }

   newNode->data = value;
   newNode->next = next;
   return newNode;
};

node* addToStart(node* head, int value) {
   node* newNode = createNode(head, value);
   head = newNode;
   newNode->data = value;
   return head;
};

void printList(node* head) {
   node* temp = head;
   int count = 1;
   while (temp != nullptr && temp->data != NULL) {
      fprintf(stdout, "%d %d\n", count, temp->data);
      temp = temp->next;
      count ++;
   }
};


int main()
{
   node* head = createNode(nullptr, NULL);

   head = addToStart(head, 2);

   fprintf(stdout, "%d %p \n", head->data, head->next);

   head = addToStart(head, 5);

   fprintf(stdout, "%d %p \n", head->data, head->next);

   printList(head);

   //node* head = nullptr;

   //node* first = (node*)malloc(sizeof(node));
   //node* second = (node*)malloc(sizeof(node));

   //head = first;
   //first->next = second;
   //first->data = 3;

   //second->next = nullptr;
   //second->data = 5;

   //fprintf(stdout, "%d %p \n", head->data, head->next);
   //fprintf(stdout, "%d %p \n", head->next->data, head->next->next);

   //printList(head);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
