#ifndef HEADER_FILE
#define HEADER_FILE

long *Load_File(char*, int*);
int Save_File(char*, long*, int);
void Shell_Insertion_Sort_Seq1(long*, int, double*, double*);
void Shell_Insertion_Sort_Seq2(long*, int, double*, double*);
void Shell_Bubble_Sort_Seq1(long*, int, double*, double*);
void Shell_Bubble_Sort_Seq2(long*, int, double*, double*);
int *Seq1_generator(int*, int);
int *Seq2_generator(int*, int);
int Print_Seq_1(char*, int);
int Print_Seq_2(char*, int);

#endif
