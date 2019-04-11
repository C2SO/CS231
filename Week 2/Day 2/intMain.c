/*
 * Dr. Vineyard
 * CS231 all sections
 * intMain.c
 *
 */

#include "myADT.h"


int main()
{
  dataType data;
  listType *list;
  listType *returnedList;

  printf("\t\tOutput from intMain.c\n\n");
  list = listCreate();
  printList(list);
  data = 17;
  returnedList = listInsertAtRear(list, data);
  if(returnedList != list)
    {
      fprintf(stderr, "Error in return from listInsertAtRear(%d)\n", data);
      exit(BAD_EXIT);
    }
  data = 12;
  returnedList = listInsertAtRear(list, data);
  if(returnedList != list)
    {
      fprintf(stderr, "Error in return from listInsertAtRear(%d)\n", data);
      exit(BAD_EXIT);
    }
  data = 42;
  returnedList = listInsertAtRear(list, data);
  if(returnedList != list)
    {
      fprintf(stderr, "Error in return from listInsertAtRear(%d)\n", data);
      exit(BAD_EXIT);
    }
  printList(list);
  printf("\n\n");
  list = freeList(list);
  printList(list);
}