/*
 * Dr. Vineyard
 * CS231 all sections
 * charMain.c
 *
 */

#include "myADT.h"


int main()
{
  dataType data;
  listType *list;
  listType *returnedList;

  printf("\t\tOutput from charMain.c\n\n");
  list = listCreate();
  printList(list);
  data = 'x';
  returnedList = listInsertAtRear(list, data);
  if(returnedList != list)
    {
      fprintf(stderr, "Error in return from listInsertAtRear(%d)\n", data);
      exit(BAD_EXIT);
    }
  data = 'y';
  returnedList = listInsertAtRear(list, data);
  if(returnedList != list)
    {
      fprintf(stderr, "Error in return from listInsertAtRear(%d)\n", data);
      exit(BAD_EXIT);
    }
  data = 'z';
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