#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node{
  long value;
  struct _node *next;
}Node;

typedef struct{
  int size;
  Node *front;
  Node *tail;
}Head;

Head *Load_File(char*);
int Save_File(char*, Head*);
void Shell_Sort(Head*);
int power(int, int);//power function used to create the sequence 2

#endif
