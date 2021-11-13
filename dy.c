#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
void main()
{
// declare a pointer variable to point to allocated heap space
int    *p_array;
double *d_array;

// call malloc to allocate that appropriate number of bytes for the array

p_array = (int *)malloc(sizeof(int)*50);      // allocate 50 ints
//d_array = (int *)malloc(sizeof(double)*100);  // allocate 100 doubles

// always CHECK RETURN VALUE of functions and HANDLE ERROR return values
// here is one example of handling an unrecoverable malloc error 
// (other error handling code is removed from this document for readability):
if(p_array == NULL) {
  printf("malloc of size %d failed!\n", 50);   // could also call perror here
  exit(1);   // or return an error to caller
}

}