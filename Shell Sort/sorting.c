#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

int power(int, int);//power function used to create the sequence 2

//The function load data from the given filename
//It will get the first number of the file as the input size
//Then it will store all the numbers in the file to an array, which
//has already reserved a block of heap memory
long *Load_File(char *Filename, int *Size)
{
  int i;
  FILE *infile = fopen(Filename, "r");//open the file
  if(infile == NULL)
  {
    printf("Please enter the correct input file!\n");
    return NULL;
  }//check if the file has been successfully opened
  fscanf(infile, "%d", Size);
  long *input_array = malloc(sizeof(long) * (*Size));
  for(i = 0; i < (*Size); i++)//for loop scan in all the input data
  {
    fscanf(infile, "%ld", &input_array[i]);
  }
  fclose(infile);//close file in the end

  return input_array;
}
//This function saves all the data from the array to an output file
int Save_File(char *Filename, long *Array, int Size)
{
  FILE *outfile = fopen(Filename, "w+");
  if(outfile == NULL){return -1;}//if the output file cannot be opened, then return -1
  int i;
  fprintf(outfile, "%d\n", Size);
  for(i = 0; i < Size; i++)//use a loop to output all the files
  {
    fprintf(outfile, "%ld\n", Array[i]);
  }
  fclose(outfile);
  free(Array);
  return 1;
}

void Shell_Insertion_Sort_Seq1(long *Array, int Size, double *N_Comp, double *N_Move)
{
  int size1 = 1;//size1 is the lize of the sequence
  int *seq1 = Seq1_generator(&size1, Size);//array to store the first sequence
  int i;//the index to access the first sequence
  int j;//loop variable for every subarray
  int l;//first number for every subarray
  int temp1;//temp value to store the current sorted value for insertion sort
  int temp2;//temp value to do swap
  for(i = size1 - 1; i >= 0; i--){//first loop every element of k
    (*N_Comp)++;
    for(l = 0; l < seq1[i]; l++){//then loop the first number for every subarray
      (*N_Comp)++;
      for(j = seq1[i]+l; j < Size; j+=seq1[i]){//loop every element in the subarray
	(*N_Comp)++;
	temp1 = j;
	while(temp1 >= seq1[i] && Array[temp1 - seq1[i]] > Array[temp1]){//do the insertion sort
	  (*N_Comp)+=2;
	  temp2 = Array[temp1 - seq1[i]];
	  Array[temp1 - seq1[i]] = Array[temp1];
	  Array[temp1] = temp2;
	  (*N_Move) += 3;
	  temp1-=seq1[i];
	}
      }
    }
  }
  free(seq1);
}

//This function works the same way as the previous one, please refer to the previous one
void Shell_Insertion_Sort_Seq2(long *Array, int Size, double *N_Comp, double *N_Move)
{
  int size2 = 1;
  int *seq2 = Seq2_generator(&size2, Size);
  int i;
  int j;
  int l;
  int size2_real = (size2 + 1)*size2/2;
  int temp1;
  int temp2;
  for(i = size2_real - 1; i >= 0; i--){
    (*N_Comp)++;
    for(l = 0; l < seq2[i]; l++){
      (*N_Comp)++;
      for(j = seq2[i]+l; j < Size; j+=seq2[i]){
	(*N_Comp)++;
	temp1 = j;
	while(temp1 >= seq2[i] && Array[temp1 - seq2[i]] > Array[temp1]){
	  (*N_Comp)+=2;
	  temp2 = Array[temp1 - seq2[i]];
	  Array[temp1 - seq2[i]] = Array[temp1];
	  Array[temp1] = temp2;
	  (*N_Move) += 3;
	  temp1-=seq2[i];
	}
      }
    }
  }  
  free(seq2);
}

//This function implement bubble sort with the shell sequence 1
void Shell_Bubble_Sort_Seq1(long *Array, int Size, double *N_Comp, double *N_Move)
{
  //all the variable declarations can refer to the first sorting function
  int size1 = 1;
  int *seq1 = Seq1_generator(&size1, Size);
  int i;
  int j;
  int l;
  int temp1;
  int temp2;
  int temp3;
  for(i = size1 - 1; i >= 0; i--){
    (*N_Comp)++;
    for(l = 0; l < seq1[i]; l++){
      (*N_Comp)++;
      for(j = l; j < (Size - seq1[i]); j+=seq1[i]){//The following two for loops solves for the bubble sort
	(*N_Comp)++;
	temp3 = j - l + seq1[i];
	for(temp1 = l; temp1 < (Size - temp3); temp1+=seq1[i]){
	  (*N_Comp)+=2;
	  if(Array[temp1] > Array[temp1 + seq1[i]]){
	    temp2 = Array[temp1 + seq1[i]];
	    Array[temp1 + seq1[i]] = Array[temp1];
	    Array[temp1] = temp2;
	  }
	  (*N_Move) += 3;
	}
      }
    }
  }
  free(seq1);
} 
//This function works the same way as the previous one, please refer to the previous one
void Shell_Bubble_Sort_Seq2(long *Array, int Size, double *N_Comp, double *N_Move)
{
  int size2 = 1;
  int *seq2 = Seq2_generator(&size2, Size);
  int i;
  int j;
  int l;
  int size2_real = (size2 + 1)*size2/2;
  int temp1;
  int temp2;
  int temp3;
  for(i = size2_real - 1; i >= 0; i--){
    (*N_Comp)++;
    for(l = 0; l < seq2[i]; l++){
      (*N_Comp)++;
      for(j = l; j < (Size - seq2[i]); j+=seq2[i]){
	(*N_Comp)++;
	temp3 = j - l + seq2[i];
	for(temp1 = l; temp1 < (Size - temp3); temp1+=seq2[i]){
	  (*N_Comp)+=2;
	  if(Array[temp1] > Array[temp1 + seq2[i]]){
	    temp2 = Array[temp1 + seq2[i]];
	    Array[temp1 + seq2[i]] = Array[temp1];
	    Array[temp1] = temp2;
	  }
	  (*N_Move) += 3;
	}
      }
    }
  }
  free(seq2);
}
//This function will generate the first sequence
int *Seq1_generator(int *size1, int Size)
{
  int i = 1;
  int m = 1;
  while((2*i + 1) < Size)
  {
    i = 2*i + 1;
    (*size1)++;
  }
  int *arr = malloc(sizeof(int) * (*size1));
  arr[0] = 1;
  i = 1;
  while((2*i + 1) < Size)
  {
    arr[m] = 2*i + 1;
    i = 2*i + 1;
    m++;
  }
  return arr;
}

//This is the power function to generate to the power of three
int power(int base, int upper){
  int temp = base;

  if(upper == 0){
    return 1;
  }
  if(upper == 1){
    return 3;
  }
  while(upper > 1){
    base *= temp;
    upper--;
  }
  return base;
}

//This function generate the second sequence
int *Seq2_generator(int *size2, int Size)
{
  int i = 1;
  int l = 1;
  int m;
  while(i*3 < Size)
  {
    (*size2)++;
    i *= 3;
  }
  int *arr = malloc(sizeof(int) * ((1+(*size2))*(*size2)/2));
  while(l <= (*size2)){
    for(m = (l - 1)*l/2; m < (1 + l)* l / 2; m++){
      if(m == ((1 + l) * l / 2 - 1)){
	arr[m] = power(3, l - 1);
      }
      else{
	arr[m] = arr[m - (l - 1)] * 2;
      }
    }
    l++;
  }
  return arr;
}
//This function print the first sequence
int Print_Seq_1(char* Filename, int Size)
{
  FILE *outfile = fopen(Filename, "w+");
  if(outfile == NULL){return -1;}
  int i;
  int size1 = 1;
  int *arr1 = Seq1_generator(&size1, Size);
  fprintf(outfile, "%d\n", Size);
  for(i = 0; i < size1; i++)
  {
    fprintf(outfile, "%d\n", arr1[i]);
  }
  fclose(outfile);
  free(arr1);
  return 1;
}
//This function print the second sequence
int Print_Seq_2(char* Filename, int Size)
{
  FILE *outfile = fopen(Filename, "w+");
  if(outfile == NULL){return -1;}
  int i;
  int l;
  int size2 = 1;
  int *arr2 = Seq2_generator(&size2, Size);
  fprintf(outfile, "%d\n", Size);
  for(i = 1; i <= size2; i++)
  {
    for(l = i*(i - 1)/2; l < ((i + 1)* i / 2); l++){
      fprintf(outfile, "%d ", arr2[l]);
    }
    fprintf(outfile, "\n");
  }
  fclose(outfile);
  free(arr2);
  return 1;
}
