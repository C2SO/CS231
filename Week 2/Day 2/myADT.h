/*
 * Dr. Vineyard
 * CS231 all sections
 * myADT.h
 * create API for doubly linked list
 * main program using list will not know the implementation
 * type of item in list is determined by an include statement
 */

#include <stdio.h>
#include <stdlib.h>
#define BAD_EXIT 1
 
#include "myCharType.h"

// #include "myIntType.h"

typedef struct node
{
  struct node *next;
  struct node *previous;
  dataType element;
} nodeType;

typedef struct listHeader
{
  struct node *first;
  struct node *last;
}listType;

listType *listCreate();
listType *listInsertAtRear(listType *, dataType);
void printList(listType *);
int isEmpty(listType *);
listType * freeList(listType *);