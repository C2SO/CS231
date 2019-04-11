/*
 * Dr. Vineyard
 * CS231 all sections
 * doublyLinkedList.c
 */

#include "myADT.h"
#define BAD_EXIT 1

listType * listCreate()
{
  listType * thisList;
  thisList = (listType *) malloc(sizeof(listType));
  if(! (thisList == NULL))
  {
    thisList -> first = NULL;
    thisList -> last = NULL;
  }
  return thisList;
}

listType * listInsertAtRear(listType * thisList, dataType data)
{
  nodeType * nodePtr;
  nodeType * lastNode;
  if (thisList == NULL) //something is wrong, we will just quit
  {
    fprintf(stderr, "Error: cannot insert into null list.\n");
    exit(BAD_EXIT);
  }
  else //We have a list to insert into
  {
    nodePtr = (nodeType *) malloc(sizeof(nodeType));
    if(nodePtr == NULL)
    {
      fprintf(stderr, "Error: cannot create node.\n");
      exit(BAD_EXIT);
    }
    else //We have a node and a list
    {
      nodePtr -> element = data;
      nodePtr -> next = NULL;
      nodePtr -> previous = NULL;
      if (isEmpty(thisList))
      {
        thisList -> last = nodePtr;
	thisList -> first = nodePtr;
      }
      else //list not empty
      {
        lastNode = thisList -> last;
	lastNode -> next = nodePtr;
	nodePtr -> previous = lastNode;
	thisList -> last = nodePtr;
      }
    }
  }
  return thisList;
}

void printList(listType *thisList)
{
  nodeType * currentNode;
  if (thisList == NULL) //something is wrong, we will just quit
  {
    fprintf(stderr, "Error: cannot print null list.\n");
    exit(BAD_EXIT);
  } 
  else if (isEmpty(thisList))
  {
    printf("The list is empty\n");
  }
  else
  {
    currentNode = thisList -> first;
    while(currentNode != NULL)
    {
      dataPrint(currentNode -> element);
      currentNode = currentNode -> next;
    }
  }
}

int isEmpty(listType * thisList)
{
  //omitting code for null list sent to this function
  return (thisList -> first == NULL);
}

listType * freeList(listType *thisList)
{
  //omitting code for null list sent to this function
  nodeType * currentNode;
  nodeType *nextNode;
  if (! isEmpty(thisList))
  {
    currentNode = thisList -> first;
    nextNode = currentNode -> next;
    while(nextNode != NULL)
    {
      free((void *) currentNode);
      currentNode = nextNode;
      nextNode = currentNode -> next;
    }
    free ((void *) currentNode);
  }
  free ((void *) thisList);
  thisList = NULL;
  return thisList;
}