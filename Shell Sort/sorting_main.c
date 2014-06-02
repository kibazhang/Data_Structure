#include <stdio.h>
#include "sorting.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
  if(argc != 6) //check if there are enough input arguments
  {
    return EXIT_FAILURE;
  }
  int Size;//Size of the array
  double N_Comp = 0;//number of comparisions
  double N_Move = 0;//number of moves
  clock_t S_time = clock();//the sorting time
  clock_t I_time = clock();//the I/O time
  clock_t temp;
  long *Array = Load_File(argv[3], &Size);
  I_time = clock() - I_time;
  //calling different function depends on the input
  if(atoi(argv[1]) == 1 && argv[2][0] == 'i')
  {
    S_time = clock();
    Shell_Insertion_Sort_Seq1(Array, Size, &N_Comp, &N_Move);
    S_time = clock() - S_time;
    temp = I_time;
    I_time = clock();
    if(Print_Seq_1(argv[4], Size) == -1)
    {
      return -1;
    }
    I_time = clock() - I_time + temp;
  }
  else if(atoi(argv[1]) == 1 && argv[2][0] == 'b')
  {
    S_time = clock();
    Shell_Bubble_Sort_Seq1(Array, Size, &N_Comp, &N_Move);
    S_time = clock() - S_time;
    temp = I_time;
    I_time = clock();
    if(Print_Seq_1(argv[4], Size) == -1)
    {
      return -1;
    }
    I_time = clock() - I_time + temp;
  }
  else if(atoi(argv[1]) == 2 && argv[2][0] == 'i')
  {
    S_time = clock();
    Shell_Insertion_Sort_Seq2(Array, Size, &N_Comp, &N_Move);
    S_time = clock() - S_time;    
    temp = I_time;
    I_time = clock();
    if(Print_Seq_2(argv[4], Size) == -1)
    {
      return -1;
    }
    I_time = clock() - I_time + temp;
  }
  else if(atoi(argv[1]) == 2 && argv[2][0] == 'b')
  {
    S_time = clock();
    Shell_Bubble_Sort_Seq2(Array, Size, &N_Comp, &N_Move);
    S_time = clock() - S_time;    
    temp = I_time;
    I_time = clock();
    if(Print_Seq_2(argv[4], Size) == -1)
    {
      return -1;
    }
    I_time = clock() - I_time + temp;
  }
  temp = I_time;
  I_time = clock();
  if(Save_File(argv[5], Array, Size) == -1)
  {
    return -1;
  }
  I_time = clock() - I_time + temp;
  //print all the necessary result
  printf("\nNumber of comparisons:  %le\n", N_Comp);
  printf("Number of moves:  %le\n", N_Move);
  printf("I/O time:  %le\n", ((double)I_time) / CLOCKS_PER_SEC);
  printf("Sorting time:  %le\n\n", ((double)S_time) / CLOCKS_PER_SEC);

  return 1;//if reaches here, safe return
}
 
