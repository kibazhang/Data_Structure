#include "sorting.h"
//Function used to find the node based on the index
Node *find_node(Node *temp, int index){
  int i = 1;
  Node *wanted = temp;//wanted return node
  while(i <= index){
    wanted = temp -> next;
    i++;
  }
  return wanted;
}
//constructor used to create a node with the long input
Node *node_constructor(long input){
  Node *node = malloc(sizeof(Node));
  node -> value = input;
  node -> next = NULL;
  return node;
}
//function used to free all the memory
void destory(Node *head){
  if(head -> next != NULL){
    destory(head -> next);
  }
  free(head);
}
//The function load data from the given filename
//It will get the first number of the file as the input size
//Then it will store all the numbers in the file to an array, which
//has already reserved a block of heap memory
Head *Load_File(char *Filename)
{
  long temp;//size of the input list
  FILE *infile = fopen(Filename, "r");//open the file
  if(infile == NULL)
  {
    printf("Please enter the correct input file!\n");
    return NULL;
  }//check if the file has been successfully opened
  Head *head = malloc(sizeof(Head));
  head -> size = 0;
  head -> front = NULL;//use front pointing to front
  head -> tail = NULL;//use tail pointing to tail
  while(fscanf(infile, "%ld", &temp) == 1)
  {
    (head -> size)++;
    Node *temp_node = node_constructor(temp);
    if(head -> tail != NULL){
      (head -> tail) -> next = temp_node;
      head -> tail = temp_node;
    }
    else{
      head -> front =temp_node;
      head -> tail = temp_node;
    }
  }
  fclose(infile);//close file in the end

  return head;
}
//This function saves all the data from the array to an output file
int Save_File(char *Filename, Head *head)
{
  FILE *outfile = fopen(Filename, "w+");
  if(outfile == NULL){return -1;}//if the output file cannot be opened, then return -1
  Node *temp = head -> front;
  while(temp -> next != NULL)//use a loop to output all the files
  {
    fprintf(outfile, "%ld\n", temp -> value);
    temp = temp -> next;
  }
  fprintf(outfile, "%ld\n", temp -> value);
  fclose(outfile);
  destory(head -> front);
  return head->size;
}

//This function implement bubble sort with the shell sequence 1
void Shell_Sort(Head *head)
{
  int size_seq = 1;
  int last = 1;//last element in the sequence
  while((2*last + 1) < (head -> size))
  {
    last = 2*last + 1;
    size_seq++;
  }
  last = 2*last + 1;

  //all the variable declarations can refer to the first sorting function
  int i;//the loop variable to loop every element in the first sequence
  int j;//loop to sort the pass of listed list
  int temp1;//loop to do the comparisions
  long temp_value;//used in swap function
  Node *temp_node1;
  Node *temp_node2;

  for(i = size_seq; i >= 1; i--){
    last = (last - 1) / 2;
    for(j = last; j < ((head -> size) - last); j+=last){//The following two for loops solves for the bubble sort
      temp_node1 = head -> front;
      temp_node2 = find_node(temp_node1, last);
      for(temp1 = 0; temp1 < (head -> size - j); temp1+=1){
	if(temp_node1 -> value  > temp_node2 -> value){
	  temp_value = temp_node2 -> value;
	  temp_node2 -> value = temp_node1 -> value;
	  temp_node1 -> value = temp_value;
	}
	temp_node1 = temp_node1 -> next;
	temp_node2 = temp_node2 -> next;
      }
    }
  }
}
