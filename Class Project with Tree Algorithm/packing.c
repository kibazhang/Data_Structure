#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Tree structure for the input and output tree nodes
typedef struct tree_node{
  struct tree_node* left;
  struct tree_node* right;
  int thisnode;
  int parnode;
  int lcnode;
  int rcnode;
  char cutline;
  double width;
  double height;
  double xcoord;
  double ycoord;
}input;

//stack type definition for the stack with tree nodes
typedef struct sp1{
  struct sp1* next;
  input* node;
}stack1;

//stack type definition for the stack with the width and height of the tree nodes
typedef struct sp2{
  struct sp2* next;
  double width;
  double height;
}stack2;

//Global definition for stack1 and stack2
stack1* Stack1 = NULL;
stack2* Stack2 = NULL;

//Tree operations for stack1 and stack2
stack1* stack1_construct(input* Node){
  stack1* temp = malloc(sizeof(stack1));
  temp -> node = Node;
  temp -> next = NULL;
  return temp;
}

stack2* stack2_construct(double temp1, double temp2){
  stack2* temp = malloc(sizeof(stack2));
  temp -> width = temp1;
  temp -> height = temp2;
  temp -> next = NULL;
  return temp;
}

void free_Stack1(){
  stack1* temp;
  while(Stack1){
    temp = Stack1;
    Stack1 = temp -> next;
    free(temp);
  }
}

void free_Stack2(){
  stack2* temp;
  while(Stack2){
    temp = Stack2;
    Stack2 = temp -> next;
    free(temp);
  }
}

int max_cal(double temp1, double temp2){
  if(temp1 >= temp2){
    return temp1;
  }else{
    return temp2;
  }
}

//stack operations for the main stack1
void Push(input* node){
  stack1* temp = stack1_construct(node);
  if(!Stack1){
    Stack1 = temp;
  }else{
    temp -> next = Stack1;
    Stack1 = temp;
  }
}

input* Pop(){
  if(Stack1 == NULL){
    return NULL;
  }
  stack1* temp1 = Stack1 -> next;
  input* temp2 = Stack1-> node;
  free(Stack1);
  Stack1 = temp1;
  return temp2;
}

//stack operations for the sub stack, which is used to track all the block size
void Push_sub(double temp1, double temp2){
  stack2* temp = stack2_construct(temp1, temp2);
  if(!Stack2){
    Stack2 = temp;
  }else{
    temp -> next = Stack2;
    Stack2 = temp;
  }  
}

void Pop_sub(double temp[]){
  temp[2] = Stack2 -> width;
  temp[3] = Stack2 -> height;
  stack2* temp1 = Stack2 -> next;
  free(Stack2);
  temp[0] = temp1 -> width;
  temp[1] = temp1 -> height;
  stack2* temp2 = temp1 -> next;
  free(temp1);
  Stack2 = temp2;
}

input* Tree_construct(input* i_arr, int n_node, int n_block){
  int i;//loop invariant
  int temp1;//temp variables to store the left node
  int temp2;//temp variables to store the left node
  for(i = n_node - 1; i >= n_block; i--){
    temp1 = i_arr[i].lcnode;
    temp2 = i_arr[i].rcnode;
    if(temp1 != -1){
      temp1 -= 1;
      i_arr[i].left = &i_arr[temp1];
    }
    if(temp2 != -1){
      temp2 -= 1;
      i_arr[i].right = &i_arr[temp2];
    }
  }
  temp1 = n_node - 1;
  return &i_arr[temp1];
}

//Main function to calculate the total block size and block size for separate node blocks
//This function uses the post-order traversal 
void Pack_compute(input* root){
  Push(root);
  input* previous = NULL;
  input* current;
  double temp[4];
  while(Stack1){
    current = Stack1 -> node;
    if(!previous || previous -> left == current || previous->right == current){
      if(current -> left){
	Push(current -> left);
      }
      else if(current -> right){
	Push(current -> right);
      }
    }else if(current -> left == previous){
      if(current -> right){
	Push(current->right);
      }
    }else{
      if(current -> lcnode == -1 && current -> rcnode == -1){
	Push_sub(current -> width, current -> height);
      }else if(current -> lcnode != -1 && current -> rcnode != -1){
	Pop_sub(temp);
	if(current -> cutline == 'H'){
	  temp[0] = max_cal(temp[0], temp[2]);//get the largest width
	  temp[1] += temp[3];//get the total height
	  current -> width = temp[0];
 	  current -> height = temp[1];
	}else if(current -> cutline == 'V'){
	  temp[0] += temp[2];//get the total width
	  temp[1] = max_cal(temp[1], temp[3]);//get the largest width
	  current -> width = temp[0];
	  current -> height = temp[1];
	}
	Push_sub(current -> width, current -> height);
      }
      Pop();
    }
    previous = current;
  }
}

//This function updates all the correct coordinates values for the leaf nodes
//This function uses pre-order tree traversal
void Cal_coords(input* root){
  input* temp;
  Push(root);
  while(Stack1){
    temp = Pop();
    if(temp != NULL){
      if(temp -> lcnode != -1 && temp -> rcnode != -1){
	temp -> left -> xcoord = temp -> xcoord;//update the coords values to the left and right child
	temp -> left -> ycoord = temp -> ycoord;
	temp -> right -> xcoord = temp -> xcoord;
	temp -> right -> ycoord = temp -> ycoord;
	if(temp -> cutline == 'H'){
	  temp -> left -> ycoord += temp -> right -> height;//update the height to the left child
	}else if(temp -> cutline == 'V'){
	  temp -> right -> xcoord += temp -> left -> width;//update the width to the right child
	}
      }
      Push(temp -> right);
      Push(temp -> left);
    }
  }
}

int main(int argc, char **argv){
  if(argc != 3) //check if there are enough input arguments
  {
    return EXIT_FAILURE;
  }
  FILE* input_file = fopen(argv[1],"r");
  if(input_file == NULL){
    return EXIT_FAILURE;
  }

  //get the input data
  int n_node;
  int n_block;
  char temp_char;//to skip some useless part
  int i; //loop invariant 
  fscanf(input_file, "%d", &n_block);
  fscanf(input_file, "%d", &n_node);
  input *i_arr = malloc(sizeof(input) * n_node);//input data array
  for(i = 0; i < n_block; i++){//input data for leaf nodes
    fscanf(input_file, "%d %d %d %d %c %lf %lf", &(i_arr[i].thisnode), &(i_arr[i].parnode), &(i_arr[i].lcnode), &(i_arr[i].rcnode), &(i_arr[i].cutline), &(i_arr[i].width), &(i_arr[i].height));
    i_arr[i].left = NULL;
    i_arr[i].right = NULL;
    i_arr[i].xcoord = 0;
    i_arr[i].ycoord = 0;
  }
  
  for(i = n_block; i < n_node; i++){//input data for non-leaf nodes
    fscanf(input_file, "%d %d %d %d %c", &(i_arr[i].thisnode), &(i_arr[i].parnode), &(i_arr[i].lcnode), &(i_arr[i].rcnode), &(i_arr[i].cutline));
  
    temp_char = fgetc(input_file);
    while(temp_char != '\n'){
      temp_char = fgetc(input_file);
    }
    i_arr[i].width = 0;
    i_arr[i].height = 0;
    i_arr[i].left = NULL;
    i_arr[i].right = NULL;
    i_arr[i].xcoord = 0;
    i_arr[i].ycoord = 0;
  }
  
  fclose(input_file);

  input* tree_root = Tree_construct(i_arr, n_node, n_block);

  //print out the screen output
  clock_t time_temp = clock();//the Elapsed time
  Pack_compute(tree_root);
  free_Stack1();
  Cal_coords(tree_root);
  clock_t Elapsed_time = clock() - time_temp;
  printf("\nWidth: %le\n", i_arr[n_node - 1].width);
  printf("Height: %le\n", i_arr[n_node - 1].height);
  printf("\nX-coordinate: %le\n", i_arr[n_block - 1].xcoord);
  printf("Y-coordinate: %le\n", i_arr[n_block - 1].ycoord);
  printf("\nElapsed time: %le\n\n", ((double)Elapsed_time) / CLOCKS_PER_SEC);
  
  //free all the used stack memory for Stack1, Stack2
  free_Stack1();
  free_Stack2();

  //print out the output
  FILE* output_file = fopen(argv[2],"w+");
  if(output_file == NULL){return EXIT_FAILURE;}
  fprintf(output_file, "%d\n", n_block);  
  for(i = 0; i < n_block; i++){
    fprintf(output_file, "%d %le %le %le %le\n", i_arr[i].thisnode, i_arr[i].width, i_arr[i].height, i_arr[i].xcoord, i_arr[i].ycoord);
  }
  fclose(output_file);

  //free the memory used by the input array
  free(i_arr);

  return EXIT_SUCCESS;//if reaches here, safe return
}
 
