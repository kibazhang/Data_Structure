#include "sorting.h"

int main(int argc, char **argv){
  if(argc != 3) //check if there are enough input arguments
  {
    return EXIT_FAILURE;
  }
  clock_t S_time;//the sorting time
  clock_t I_time = clock();//the I/O time
  clock_t temp;
  Head *head = Load_File(argv[1]);
  temp = clock() - I_time;
  //calling different function depends on the input
  S_time = clock();
  Shell_Sort(head);
  S_time = clock() - S_time;
  I_time = clock();
  if(Save_File(argv[2], head) != head -> size)
  {
    printf("error");
    return EXIT_FAILURE;
  }
  I_time = clock() - I_time + temp;
  free(head);
  //print all the necessary result
  printf("\nI/O time:  %le\n", ((double)I_time) / CLOCKS_PER_SEC);
  printf("Sorting time:  %le\n\n", ((double)S_time) / CLOCKS_PER_SEC);
  
  return EXIT_SUCCESS;//if reaches here, safe return
}
 
