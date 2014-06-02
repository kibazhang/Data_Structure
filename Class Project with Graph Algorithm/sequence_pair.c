#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
  int thisnode;
  double width;
  double height;
  double xcoord;
  double ycoord;
  int* right;
  int* above;
  char xcolor;
  char ycolor;
}input;

double Final_Width = 0;
double Final_Height = 0;

//Helper Function
int numof(int* arr, int NumBlock){
  int i;
  for(i = 0; i < (NumBlock - 1); i++){
    if(arr[i] == 0){
      return i;
    }
  }
  return i;
}

void recur_xcoord(input* input_array, int right, int left, int node, int NumBlock){
  if(left != 0){
    if((input_array[(left - 1)].xcoord + input_array[(left - 1)].width) > input_array[(node - 1)].xcoord){ 
      input_array[(node - 1)].xcoord = input_array[(left - 1)].xcoord + input_array[(left - 1)].width;
    }else{
      if(input_array[(node - 1)].xcolor != 'W'){
	return;
      }
    }
  }
  
  //color the node
  input_array[(node - 1)].xcolor = 'B'; 

  if(numof(input_array[(node - 1)].right, NumBlock) == 0){
    //Stop and Compare for the largest Width and Height
    if((input_array[(node - 1)].xcoord + input_array[(node - 1)].width) > Final_Width){
      Final_Width = input_array[(node - 1)].xcoord + input_array[(node - 1)].width;
    }
    return;
  }      
      
  int i;
  for(i = 0; i < right; i++){
    recur_xcoord(input_array, numof(input_array[(input_array[(node - 1)].right[i] - 1)].right, NumBlock), node, input_array[(node - 1)].right[i], NumBlock);
  }
}

void recur_ycoord(input* input_array, int above, int below, int node, int NumBlock){
  if(below != 0){
    if((input_array[(below - 1)].ycoord + input_array[(below - 1)].height) > input_array[(node - 1)].ycoord){
      input_array[(node - 1)].ycoord = input_array[(below - 1)].ycoord + input_array[(below - 1)].height;
    }else{
      if(input_array[(node - 1)].ycolor != 'W'){
	return;
      }
    }
  }

  //color the node
  input_array[(node - 1)].ycolor = 'B';

  if(numof(input_array[(node - 1)].above, NumBlock) == 0){
    //Stop and Compare for the largest Width and Height
    if((input_array[(node - 1)].ycoord + input_array[(node - 1)].height) > Final_Height){
      Final_Height = input_array[(node - 1)].ycoord + input_array[(node - 1)].height;
    }
    return;
  }      
      
  int i;
  for(i = 0; i < above; i++){
    recur_ycoord(input_array, numof(input_array[(input_array[(node - 1)].above[i] - 1)].above, NumBlock), node, input_array[(node - 1)].above[i], NumBlock);
  }
}

void findright(input* input_array, int* sequence1, int* sequence2, int NumBlock){
  int i = 0;
  int j = 0;
  int k = 0;
  int v = 0;
  int temp1 = 0;
  int temp2 = 0;
  int counter = 0;
  for(i = 0; i < NumBlock; i++){
    j = 0;
    counter = 0;
    while(sequence1[i] != sequence2[j++]);
    for(k = j; k < NumBlock; k++){
      v = i + 1;
      while(v < NumBlock && sequence1[v++] != sequence2[k]);
      if(sequence1[--v] == sequence2[k]){
	input_array[(sequence1[i] - 1)].right[counter++] = sequence2[k];
	if((counter - 1) == 0){
	  temp1 = v;
	  temp2 = k;
	}
	if(v > temp1 && k > temp2){
	  input_array[(sequence1[i] - 1)].right[--counter] = 0;
	} 
      }
    }
    recur_xcoord(input_array, counter, 0, sequence1[i], NumBlock);
  }
}

void findabove(input* input_array, int* sequence1, int* sequence2, int NumBlock){
  int i = 0;
  int j = 0;
  int k = 0;
  int v = 0;
  int temp1 = 0;
  int temp2 = 0;
  int counter = 0;
  for(i = NumBlock - 1; i >= 0; i--){
    j = 0;
    counter = 0;
    while(sequence1[i] != sequence2[j++]);
    for(k = j; k < NumBlock; k++){
      v = i - 1;
      while(v >= 0 && sequence1[v--] != sequence2[k]);
      if(sequence1[++v] == sequence2[k]){
	input_array[(sequence1[i] - 1)].above[counter++] = sequence2[k];
	if((counter - 1) == 0){
	  temp1 = v;
	  temp2 = k;
	}
	if(v < temp1 && k > temp2){
	  input_array[(sequence1[i] - 1)].above[--counter] = 0;
	}
      }
    }
    recur_ycoord(input_array, counter, 0, sequence1[i], NumBlock);
  }
}

//Main function
int main(int argc, char **argv){
  if(argc != 3) //check if there are enough input arguments
  {
    return EXIT_FAILURE;
  }

  //Input
  FILE* input_file = fopen(argv[1],"r");
  if(input_file == NULL){
    return EXIT_FAILURE;
  }
  
  int NumBlock;
  int i;//lcv
  int j;//lcv
  fscanf(input_file, "%d", &NumBlock);
  input* input_array = malloc(sizeof(input)*NumBlock);
  int* sequence1 = malloc(sizeof(int)*NumBlock);
  int* sequence2 = malloc(sizeof(int)*NumBlock);
  for(i = 0; i < NumBlock; i++){
    fscanf(input_file, "%d", &(input_array[i].thisnode));
    fscanf(input_file, "%lf", &(input_array[i].width));
    fscanf(input_file, "%lf", &(input_array[i].height));
    input_array[i].right = malloc(sizeof(int) * (NumBlock - 1));
    for(j = 0; j < (NumBlock - 1); j++){
      input_array[i].right[j] = 0;
    }
    input_array[i].above = malloc(sizeof(int) * (NumBlock - 1));
    for(j = 0; j < (NumBlock - 1); j++){
      input_array[i].above[j] = 0;
    } 
    input_array[i].xcoord = 0;
    input_array[i].ycoord = 0;
    input_array[i].xcolor = 'W';
    input_array[i].ycolor = 'W';
  }
  for(i = 0; i < NumBlock; i++){
    fscanf(input_file, "%d", &(sequence1[i]));
  }
  for(i = 0; i < NumBlock; i++){
    fscanf(input_file, "%d", &(sequence2[i]));
  }
  fclose(input_file);

  //Calculate the position map
  clock_t time_temp = clock();//the Elapsed time
  findright(input_array, sequence1, sequence2, NumBlock);
  findabove(input_array, sequence1, sequence2, NumBlock);
  time_temp = clock() - time_temp;//the Elapsed time

  printf("Width: %le\n", Final_Width);
  printf("Height: %le\n", Final_Height);
  printf("\nX-coordinate: %le\n", input_array[NumBlock - 1].xcoord);
  printf("Y-coordinate: %le\n", input_array[NumBlock - 1].ycoord);
  printf("\nElapsed Time: %le\n", ((double)time_temp) / CLOCKS_PER_SEC);
  
  //Output
  FILE* output_file = fopen(argv[2], "w+");
  if(output_file == NULL){
    return EXIT_FAILURE;
  }  
  //int j;
  fprintf(output_file, "%d\n", NumBlock);
  for(i = 0; i < NumBlock; i++){
    fprintf(output_file, "%d %le %le %le %le\n", input_array[i].thisnode, input_array[i].width, input_array[i].height, input_array[i].xcoord, input_array[i].ycoord);
  }
  fclose(output_file);

  //free all the memory used
  for(i = 0; i < NumBlock; i++){
    free(input_array[i].right);
    free(input_array[i].above);
  }
  free(input_array);
  free(sequence1);
  free(sequence2);

  return EXIT_SUCCESS;
}
