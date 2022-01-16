#include <conio.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <c64/charwin.h>
#include <c64/kernalio.h>
#include <c64/vic.h>
#include <gfx/vector3d.h>

#define Screen  ((byte * ) 0xc800)
struct VectorV
{
  unsigned size;
  int  * v;
};
struct node {
   int data;
   int key;
   int rows, cols;
   int    *p_array;
   struct node *next;  };
// declare a pointer variable to point to allocated heap space

int k;
int i,j, xpos, ypos;
int listlength;
char c;
char inputstring[25];
char tmpstring[25];
char tempstring[25];

char charstring[25];
char spaces[41];
CharWin * win;

struct CharWin cwin;
struct CharWin inputwin;
struct CharWin msgwin;
struct CharWin outputwin;

struct Score
{
        char            name[5];
        unsigned        score;
};

Score   score[] = {
        {"AAA", 10000},
        {"BBB", 9000},
        {"CCC", 8000},
        {"DDD", 4000}
};

byte data[] = { 
#embed "apl.bin" 
}; 
char  oxpos = 0;
char nl[3];  
char newl = 13;
struct node *head = NULL;
struct node *current = NULL;
struct node *temp = NULL;
void myfloor() {
//stub
}

void myceiling() {
//stub
}

//https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm
//display the list
void printList() {
  int i;
  struct node * ptr = head;
  printf("\n");

  //start from the beginning
  while (ptr != 0) {
    putchar(ptr -> key);
    printf(" (%d,%d) ", ptr -> rows, ptr -> cols);
    for (i = 0; i < 5; i++) {
      printf(" %d ,", ptr -> p_array[i]);
    }
    printf("\n");
    ptr = ptr -> next;

  }

  return;
}


void checkScroll(CharWin * win)
{
        if (win->cy == win->wy)
        {
                win->cy--;
                cwin_scroll_up(win, 1);
                cwin_fill_rect(win, 0, win->wy - 1, win->wx, 1, ' ', 1);
        }
}

void printLn(CharWin * win)
{
        win->cy++;
        win->cx = 0;
        checkScroll(win);
}

void print(CharWin * win, const char * str, char color)
{
        char len = strlen(str);
        if (win->cx + len > 40)
                printLn(win);

        cwin_put_string(win, str, color);
        checkScroll(win);
}



//insert link at the first location
void insertFirst(int key, int data, char tmpstring[25]) {
   //create a link
   int i,j;
   int ischar, counter;
   char parsestring[25];
   char onenum[25];
/*
//struct VectorV
//{
//  unsigned size;
//  float * v;
//};
*/
struct VectorV *vec = (struct VectorV*) malloc(sizeof(struct VectorV));
//struct VectorV *vec = (struct VectorV*) malloc(sizeof(struct VectorV));

   vec->size = 5;
   vec->v = (int *) calloc(vec->size, sizeof(int ));



 // Get the elements of the array
        for (i = 0; i < 5; ++i) {
            vec->v[i] = i + 1;
        }
 
        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < 5; ++i) {
            printf("%f, ", vec->v[i]);
        }



//   v = pointer to   /  address of   float
///ptr = (float*) calloc(25, sizeof(float));
//https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
//This statement allocates contiguous space in memory for 25 elements each with the size of the float.
//C only supports fixed size 2D arrays, if you need dynamic, you have to use 1D array and index with [i * stride + j]


///    v = (float*) calloc(size, sizeof(float));

   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->key = key;
   link->data = data;
   link->rows = 1;
   link->cols = 1;
// call malloc to allocate that appropriate number of bytes for the array
    link-> p_array = (int *)malloc(sizeof(int)*5);      // allocate 50 ints 
     if(link->p_array == 0) {
         printf("malloc of size %d failed!\n", 5);   // could also call perror here
      }
   // use [] notation to access array buckets 


//parse numbers from string

// is it a char string?  assume not
   ischar = 0;
   if ( tmpstring[0] == ''') {
            ischar = 1;  // first char is ' so its string
//        cwin_putat_string(&msgwin,0,0,"IS A ' QUOTED  STRING  ",3);
//            printf("IS A ' QUOTED  STRING\n");
            //so just copy each element directly as text even quotes
            for(i=0; i < 5; i++) {
              link->p_array[i] = tmpstring[i];
            }
   }
   else  {  // wasnt quote so parse it as numbers
           counter = 0;
           j=0;

// add handling for negatives at front of num  164
// todo add space handling for extra spaces 
           for(i=0; i < 5; i++) {
              while((tmpstring[counter] >= 48) && (tmpstring[counter] <= 57)) {
              onenum[j] = tmpstring[counter];
              counter++;
              j++;
           }
           onenum[j] = 0;  //close string then convert
           link->p_array[i] = atoi(onenum);
           j=0;
           counter++;

        }
   }  //end else its numbers needing parsing

   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}

//insert link at the first location
void insertFirststring(int key, int data, char tmpstring[25]) {
   //create a link
   char parsestring[25];
   int i;
   struct node *link = (struct node*) malloc(sizeof(struct node));

   link->key = key;
   link->data = data;
// call malloc to allocate that appropriate number of bytes for the array
    link-> p_array = (int *)malloc(sizeof(int)*5);      // allocate 50 ints
      /// if(p_array == NULL) {
     ///     printf("malloc of size %d failed!\n", 5);   // could also call perror here
   // use [] notation to access array buckets
// fill with randoms
//   for(i=0; i < 5; i++) {
//        int j;
//      j = rand();
//        link->p_array[i] = j;
//   }

   for(i=1; i < 5; i++) {
      if (link->p_array[i] != ''')
         link->p_array[i] = tmpstring[i];
   }
   //point it to old first node
   link->next = head;

   //point first to new first node
   head = link;
}



//delete first item
struct node* deleteFirst() {

   //save reference to first link
   struct node *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   return tempLink;
}


int length() {
   int length = 0;
   struct node *current;
	
   for(current = head; current != 0; current = current->next) {
      length++;
   }
	
   return length;
}

//is list empty
bool isEmpty() {
   return head == NULL;
}


//find a link with given key
struct node* find(int key) {
   //start from the first link
   struct node* current = head;
   //if list is empty
   if(head == 0) {
      return NULL;
   }
   //navigate through list
   while(current->key != key) {
      //if it is last node
      if(current->next == 0) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
   //if data found, return the current Link
   return current;
}


//delete a link with given key
struct node* delete(int key) {

   //start from the first link
   struct node* current = head;
   struct node* previous = NULL;
	
   //if list is empty
   if(head == 0) {
      return NULL;
   }

   //navigate through list
   while(current->key != key) {

      //if it is last node
      if(current->next == 0) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
	
   return current;
}

void sort() {

   int i, j, k, tempKey, tempData;
   struct node *current;
   struct node *next;
	
   int size = length();
   k = size ;
	
   for ( i = 0 ; i < size - 1 ; i++ ) {
      k--;
   current = head;
      next = head->next;
		
      for ( j = 1 ; j < k ; j++ ) {   

         if ( current->data > next->data ) {
            tempData = current->data;
            current->data = next->data;
            next->data = tempData;

            tempKey = current->key;
            current->key = next->key;
            next->key = tempKey;
         }
			
         current = current->next;
         next = next->next;
      }
   }   
}
void reverse(struct node** head_ref) {
   struct node* prev   = NULL;
   struct node* current = *head_ref;
   struct node* next;
	
   while (current != NULL) {
      next  = current->next;
      current->next = prev;   
      prev = current;
      current = next;
   }
	
   *head_ref = prev;
}



void reversem()
{
  int i, j, dummy, ischar;
char reversemtmpstring[25];
  struct node * foundLink;
  ischar = 0;
  if (inputstring[1] == 65) { // is an A
    foundLink = find(65);
  }
  if (inputstring[1] == 66) { // is a B
    foundLink = find(66);
  }
  if (inputstring[1] == 39) { // is a string
  ischar = 1;
  }
   print(&outputwin, "      ", 7);
  print(&outputwin,inputstring,7);
  printLn(&outputwin);

  if (foundLink == 0) {
    cwin_putat_string(&msgwin,0,1,"FOUNDLINK WAS NULL ELEMENT NOT FOUND  ",10);
  }
  if (foundLink != 0) {
cwin_putat_string(&msgwin,0,1,"BEFORE REVERSING  ",10);
    for (i = 0; i < 5; i++) {
       reversemtmpstring[i] = foundLink -> p_array[i];
    }  //saves a copy

//    printf("BEFORE REVERSING\n ");
    if (!ischar){
    for (i = 0; i < 5; i++) {
      //      printf("in rotate loop1");
//      printf("%d ", foundLink -> p_array[i]);
    }
    }
    if (ischar) { printf("%s ", &inputstring[1]);}
    for (i = 0; i < 2; i++) { //only rotate the first half!!!!
      dummy = foundLink -> p_array[i];
      foundLink -> p_array[i] = foundLink -> p_array[4 - i]; //adjust later for general case
      foundLink -> p_array[4 - i] = dummy;

      //      printf("in rotate loop0");
    }
    //  printf(" rotating  ");
    foundLink -> p_array[5] = dummy;
cwin_putat_string(&msgwin,0,1,"AFTER REVERSING  ",10);
//    printf("\nAFTER REVERSING \n ");
    if (!ischar) {
       for (i = 0; i < 5; i++) {
       //      printf("in rotate loop1");
       //printf("%d ", foundLink -> p_array[i]);
           
           itoa(foundLink -> p_array[i],charstring,10);
           print(&outputwin, charstring, 3);
           print(&outputwin, " ", 3);
       }
       printLn(&outputwin);

    }
    
    if (ischar) { 
       for (i = 0; i < 5; i++) {
          tmpstring[i] = (foundLink -> p_array[i]);
       }
       //beware 0
       printf("%s ", tmpstring);
       }

    //  printf("in rotate loop2");
     //restore copy

    for (i = 0; i < 5; i++) {
       foundLink -> p_array[i] = reversemtmpstring[i] ;  //undo skip minus
    }  //restores copy


  }
  // printf("in rotate loop3");
}

void gradedown()
{
  int i, j, dummy, lookfor;
  int n = 5;  //hardwired change later
  struct node * foundLink;

  char gradedowntmpstring[25];
  char indexstring[25];

  if (inputstring[1] == 65) { // is an A
    foundLink = find(65);
  }
  if (inputstring[1] == 66) { // is a B
    foundLink = find(66);
  }
  print(&outputwin, "      ",7);
  print(&outputwin, inputstring,7);
  printLn(&outputwin);
  if (foundLink == 0) {
    printf("foundlink was null, element not found \n ");
  }
  if (foundLink != 0) {
    for (i = 0; i < 5; i++) {
       gradedowntmpstring[i] = foundLink -> p_array[i];
    }  //saves a copy
     for (i = 0; i < n-1; i++) {
       for (j = 0; j < n-i-1; j++) {
           if (foundLink->p_array[j] < foundLink->p_array[j+1]){
              dummy =  foundLink->p_array[j];
              foundLink->p_array[j] = foundLink->p_array[j+1];
              foundLink->p_array[j+1]= dummy;
           }
       }
     }


//make index array
 //   printf("\nGRADEDOWN \n ");

    for (i = 0; i < 5; i++) {
       lookfor = foundLink -> p_array[i];
       for (j = 0; j < 5; j++) {
          if (gradedowntmpstring[j] == lookfor){
//            printf("%d ", j+1);
              itoa(j+1, tempstring, 10);
              print(&outputwin, tempstring, 3);
              print(&outputwin, " ", 3);
            gradedowntmpstring[j] = gradedowntmpstring[j]-1; // skip it next time
            break;
          }
       }
    }
    printLn(&outputwin);


//restore copy

    for (i = 0; i < 5; i++) {
       foundLink -> p_array[i] = gradedowntmpstring[i]  + 1;  //undo skip minus
    }  //restores copy





  } //foundlink != 0
}

void oldgradedown()
{
  int i, j, dummy, lookfor;
  int n = 5;  //hardwired change later
  struct node * foundLink;

  char gradedowntmpstring[25];
  char indexstring[25];

  if (inputstring[1] == 65) { // is an A
    foundLink = find(65);
  }
  if (inputstring[1] == 66) { // is a B
    foundLink = find(66);
  }

  if (foundLink == 0) {
    printf("foundlink was null, element not found \n ");
  }
  if (foundLink != 0) {
    printf("ARRAY TO GRADEDOWN \n ");
    for (i = 0; i < 5; i++) {
      printf("%d ", foundLink -> p_array[i]);
    }
    for (i = 0; i < 5; i++) {
       gradedowntmpstring[i] = foundLink -> p_array[i];
    }  //saves a copy
     for (i = 0; i < n-1; i++) {
       for (j = 0; j < n-i-1; j++) {
           if (foundLink->p_array[j] < foundLink->p_array[j+1]){
              dummy =  foundLink->p_array[j];
              foundLink->p_array[j] = foundLink->p_array[j+1];
              foundLink->p_array[j+1]= dummy;
           }
       }
     }
// first sort the array then index from sorted array
//    printf("\nAFTER GRADEDOWN \n ");
//    for (i = 0; i < 5; i++) {
//      printf("%d ", foundLink -> p_array[i]);
//    }


//make index array
//    printf("\nGRADEDOWN \n ");
cwin_putat_string(&msgwin,0,1,"GRADE DOWN  ",10);
    for (i = 0; i < 5; i++) {
       lookfor = foundLink -> p_array[i];
       for (j = 0; j < 5; j++) {
          if (gradedowntmpstring[j] == lookfor){
            printf("%d ", j+1);
            gradedowntmpstring[j] = gradedowntmpstring[j]-1; // skip it next time
            break;
          }
       }
    }

//restore copy

    for (i = 0; i < 5; i++) {
       foundLink -> p_array[i] = gradedowntmpstring[i];
    }  //restores copy





  } //foundlink != 0
}


void gradeup()
{
  int i, j, dummy, lookfor;
  int n = 5;  //hardwired change later
  struct node * foundLink;

  char gradeuptmpstring[25];
  char indexstring[25];

  if (inputstring[1] == 65) { // is an A
    foundLink = find(65);
  }
  if (inputstring[1] == 66) { // is a B
    foundLink = find(66);
  }
  print(&outputwin, "      ",7);
  print(&outputwin, inputstring,7);
  printLn(&outputwin);
  if (foundLink == 0) {
    printf("foundlink was null, element not found \n ");
  }
  if (foundLink != 0) {
//    printf("ARRAY TO GRADEUP \n ");
 //   for (i = 0; i < 5; i++) {
//      printf("%d ", foundLink -> p_array[i]);
//    }
    for (i = 0; i < 5; i++) {
       gradeuptmpstring[i] = foundLink -> p_array[i];
    }  //saves a copy
     for (i = 0; i < n-1; i++) {
       for (j = 0; j < n-i-1; j++) {
           if (foundLink->p_array[j] > foundLink->p_array[j+1]){
              dummy =  foundLink->p_array[j];
              foundLink->p_array[j] = foundLink->p_array[j+1];
              foundLink->p_array[j+1]= dummy;
           }
       }
     }
// first sort the array then index from sorted array
//    printf("\nAFTER GRADEUP \n ");
//    for (i = 0; i < 5; i++) {
//      printf("%d ", foundLink -> p_array[i]);
//    }


//make index array 
 //   printf("\nGRADEUP \n ");

    for (i = 0; i < 5; i++) {
       lookfor = foundLink -> p_array[i];
       for (j = 0; j < 5; j++) {
          if (gradeuptmpstring[j] == lookfor){
//            printf("%d ", j+1);
              itoa(j+1, tempstring, 10);
              print(&outputwin, tempstring, 3);
              print(&outputwin, " ", 3);
            gradeuptmpstring[j] = gradeuptmpstring[j]-1; // skip it next time
            break;
          }
       }
    }
    printLn(&outputwin);


//restore copy
   
    for (i = 0; i < 5; i++) {
       foundLink -> p_array[i] = gradeuptmpstring[i]  + 1;  //undo skip minus
    }  //restores copy





  } //foundlink != 0
}


//https://www.geeksforgeeks.org/c-program-for-bubble-sort/
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
  
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}





void ibeam21()
{
clock_t clocktime;
clocktime = clock();
printf("clock time unsigned long int %ul\n", clocktime);
printf("size of clock_t %i\n", sizeof(clock_t));
}



void ibeam20()
{    
	int a2, a1, a0;
	 unsigned  int retTime;
	printf("\n\n\n\n\nin IBEAM20 SYS TIME\n");
	   __asm {
          LDA $A2
          LDX $A1
          LDY $A0
         }
	   printf("ZERO PAGE JIFFY A 2 A 1 A 0 = \n");
	   a2 = *(char *)162;
	   printf("%d   ", a2);
	    a1 = *(char *) 161;
	   printf("%d   ", a1);
	    a0 = *(char *) 160;
	   printf("%d \n", a0);
       retTime	  = clock() + 1;
       retTime       = clock();
	   printf("%u RETTIME \n", retTime);
	   
	  return;	   
}


	
void roll()
{
// printf as %d because %i doesnt work just shows delta
	int i;
	i = rand() ;
	printf("%d\n", i);
        i = rand() ;
        printf("%d\n", i);
	return;
}

void iota()
{
CharWin * win;
  win = &outputwin;

  int i,val,len;
  cwin_clear(&msgwin);
  cwin_put_string(&msgwin,"IOTA",3);

  strcpy(tmpstring, & inputstring[1]); //  to \0
  print(&outputwin, "      ", 7);
  print(win,inputstring,7);
  printLn(win);
  val = atoi(tmpstring);
  for (i=0; i<=val; i++){
     itoa(i,charstring,10);
     print(win, charstring, 3);
     print(win, " ", 3);
   }
  printLn(win);

struct VectorV *vec = (struct VectorV*) malloc(sizeof(struct VectorV));
   vec->size = val;
   vec->v = (int *) calloc(vec->size, sizeof(int ));


 // set the elements of the array  [0]=1;[1]=2,..
        for (i = 0; i < val; i++) {
            vec->v[i] = i + 1;
        }

        // Print the elements of the array
        printf("ELEMENTS  ");
        for (i = 0; i < val; i++) {
            printf("%d, ", vec->v[i]);
        }
   


}

void iotaold()
{
CharWin * win;
  int i,val,len;
  strcpy(tmpstring, & inputstring[1]); //  to \0
  val = atoi(tmpstring);
  cwin_putat_string(&outputwin, oxpos, 1,inputstring , 5);
  oxpos = oxpos + strlen(inputstring);
   for (i=0; i<=val; i++){
       itoa(i,charstring,10);
       len = strlen(charstring);
       charstring[len] = 32; charstring[++len]=0;
       cwin_putat_chars(&outputwin, oxpos, 1,  charstring , len, 5);
       oxpos = oxpos + len +1 ;
   }
   cwin_putat_string(&outputwin, oxpos, 1, spaces,5);
   oxpos = oxpos + 40;
   printf(" %d %d ", outputwin.cx, outputwin.cy);
//   printf(" %d %d ", &outputwin.cx, &outputwin.cy);
   printf(" %d %d ", *(char *) outputwin.cx, *(char *)outputwin.cy);
   win = &outputwin;
   printf("%d %d", win->cx, win->cy);
   printLn(&outputwin);
   printLn(&outputwin);
   printLn(&outputwin);
   printLn(&outputwin);

//ZZZ
}	

void atomicvector()
{
  int i,val,len;
cwin_clear(&msgwin);
  cwin_put_string(&msgwin,"ATOMIC VECTOR",3);
//     printf("ATOMIC VECTOR\n");

   for (i = 0; i < 40; i++)
    ( *(char *)(0xd938 + i)) = 3;

    gotoxy(0,9);
    for (i=32; i<128; i++) {  putch(i); }
    for (i=160; i<184; i++) {  putch(i); }
    for (i=0; i<120; i++) { cwin_put_char(&outputwin,i,5); }
}

	
void mylog()
{
  float f;
  int i;
  strcpy(tmpstring, &inputstring[1]); //  to \0
  printf("\n\n NATURAL LOG  %s\n", tmpstring);
  f = atof(tmpstring);
  f = log(f);
  printf("%f",f);
  printf("\n");
}

void fact()
{
  int fact;
  int i, n;
  strcpy(tmpstring, &inputstring[1]); //  to \0
cwin_putat_string(&msgwin,0,1,"FACTORIAL  ",10);
  printf("\n\n FACTORIAL  %s\n", tmpstring);
  n = atoi(tmpstring);
  fact = 1;
  if (n < 0)
        printf("Error! Factorial of a negative number doesn't exist.");
    else {
        for (i = 1; i <= n; ++i) {
            fact *= i;
        }
        printf("FACTORIAL OF %d = %d  \n", n, fact);
    }
}

void circlepi()
{
  float f;
  int i;
  strcpy(tmpstring, &inputstring[1]); //  to \0
  printf("\n\n CIRCLEPI  %s\n", tmpstring);
  f = atof(tmpstring);
  f = f *  3.141592653589;
  printf("%f",f);
  printf("\n");
}



void initsidrandom(){
//https://stackoverflow.com/questions/44937759/getting-random-number-from-6502-assembler

//The SID chip can actually generate numbers that are more random
//than BASIC's pseudo-random numbers. Start the generator with:
      __asm{
        LDA #$FF  // maximum frequency value
        STA $D40E // voice 3 frequency low byte
        STA $D40F // voice 3 frequency high byte
        LDA #$80  // noise waveform, gate bit off
        STA $D412 // voice 3 control register
       }
//Then you can get random numbers whenever you want with:
//LDA $D41B ; get random value from 0-255
 return;
}


void corral(){
  for (i = 0; i < 120; i++) Screen[i] = i;

//  for (i = 120; i < 160; i++) Screen[i] = 35;  //box character
  *(char *) 0xd021 = 0x06;  //border color
  for (i = 0; i < 120; i++) { ( * (char * )(0xd800 + i)) = 1; }
// color boxes for palette
  //for (i = 0; i < 40; i++) { ( * (char * )(0xd878 + i)) = i; } 
}

int main(void) {
struct VectorV *vec = (struct VectorV*) malloc(sizeof(struct VectorV));

//  char inputstring[25];
 // char tmpstring[25];
strcpy(spaces, "                                        ");
nl[0] = 13;
nl[1] = 10;
nl[2] = 0;

  int notassignment = 0;
  struct node * foundLink;
  struct node * foundLink2;
  size_t size;
  int val,len;

  int storeindex = 0;
  int linenotdone = 1;
  char storechar = 0;
  xpos = 0;
  ypos = 0;
  memcpy((char * ) 0xe000, data, 1024); //APL charset loads into $e000
  *(char * ) 648 = 0xc8; // POKE 648,40;
  vic_setbank(3); // nice high-level way to move the sundry charset
  vic.memptr = 0x28; // settings into place in oscar64!
  for (i = 0; i < 1024; i++) Screen[i] = 32;
//create output charwin
//draw output bench  border on line 7
   cwin_init(&outputwin, (char *)0xc800, 0, 10, 40, 15);
   cwin_clear(&outputwin);
//   cwin_fill(&outputwin, 15, 5);

   cwin_init(&inputwin, (char *)0xc800, 0, 4, 40, 2);
   cwin_clear(&inputwin);
   cwin_fill(&inputwin, 32, 5);


   cwin_init(&msgwin, (char *)0xc800, 0, 7, 40, 2);
   cwin_clear(&msgwin);


  initsidrandom();

  while (1) {
    corral();

    linenotdone = 1;
    c = 1; //dummy not 0 value
    for (i=0; i<25; i++) {
    tmpstring[i] = 0;
    inputstring[i]=0;
    } //clean up for next run

    while (linenotdone) {
      while (c != 13) { ////exit chargetting loop if return key hit

        //cgetc
//
//;$00C6	Number of characters in keyboard buffer
//;$00CC	Flag	Flash cursor 0 = yes, otherwise no
//;$00CD	for cursor flashing, default 20, decreased every jiffy
//;$00CE        Character at cursor position
//;$00CF        Flag	Cursor flash phase 0 = visible, >0 invisible
        __asm {
          loc1ebd: LDA $C6      //Number of characters in keyboard buffer
          loc1ebf: BNE loc1ed8  //if  chars in buffer jump to charsinbuffer
          loc1ec1: LDA $CC      //Flash cursor 0 = yes, otherwise no
          PHA
          LDA #$01
          JSR loc1ede
          loc1eca: LDA $C6      //# of chars waiting in buffer
          loc1ecc: BEQ loc1eca
          LDX #$00
          PLA
          BNE loc1ed4
          INX
          loc1ed4: TXA
          JSR loc1ede
          loc1ed8: JSR $e5b4
          sta $c878           //stores to $c878   line 4 first car
          LDX #$00
//          RTS
          JMP done
          loc1ede: TAX
          BNE loc1eff
          LDA $CC                //Flash cursor 0 = yes, otherwise no
          BNE loc1efe            //its flashing go to RTS
          LDA #$01               // not flashing
          STA $CC                // turn off cursor
          LDA $CF                //get cursor phase
          BEQ loc1efa           
          LDY $D3
          LDA($D1), Y
          EOR #$80
          STA($D1), Y
          LDA $0287              //color under the cursor
          STA($F3), Y
          loc1efa: LDA #$00
          STA $CF                //0 into $cf makes cursor visible
          loc1efe: // RTS
          jmp done
          loc1eff: LDA #$00
          STA $CC
//          RTS
          done:
        }
        c = * (char * ) 0xc878;   // the magic location stored char into c
        * (char * ) 0xc878   = 32;  //then blank  magic location
        //printf("C IS %c %d ", c, c);
        if (c == 157) {
          xpos--;
          xpos--;
          if (xpos < 0) {
            xpos = 39;
          }

          gotoxy(xpos, ypos);
        } else if (c == 29) {
          xpos++;
          if (xpos > 39) {
            xpos = 0;
          }

          gotoxy(xpos, ypos);
        } else if (c == 17) {
          ypos++;
          if (ypos > 3) {
            ypos = 0;
          }
          gotoxy(xpos, ypos);


        } else if (c == 145) {
          ypos--;
          if (ypos < 0) {
            ypos = 2;
          }
          gotoxy(xpos, ypos);

        } else if (c == 35) {
              inputstring[storeindex] = 0;
              storeindex--;

        } else if ( ((c >= 48) && (c <= 57))  ||
                    ((c >= 65) && (c <= 90))  ||
                    ((c == 32)             )  ||
                    ((c>45)  )    //any key but some break it
                  )
          {
          inputstring[storeindex++] = c;
          //terminate it with null
          inputstring[storeindex + 1] = 0;
          gotoxy(0, 5);
          printf("%s", inputstring);
//   cwin_clear(&msgwin);
//   cwin_putat_string(&msgwin, 0, 0, inputstring,3);





        } else if (c == 13) {
          ypos = 0;
          xpos = 0;
          __asm {
            lda $ce
            sta $c8f3
          }
          storechar = * (char * ) 0xc8f3;
* (char * ) 0xc8f3 = 32;  //blank it
          if (storechar == 0) {
            linenotdone = 0;
            gotoxy(12, 12);
//            printf("GOT NULL PARSE THIS %s \n", inputstring);
  cwin_clear(&inputwin);
   cwin_fill(&inputwin, 32, 5);

  cwin_putat_string(&inputwin, 0, 0, inputstring,13);
    break;
          }

          *(char * )(1400 + storeindex) = storechar;
          if ((storechar >= 1) && (storechar <= 31)) //char, add 64
          {
            storechar += 64;
          } else if ((storechar >= 64) && (storechar <= 94)) //char, add 64
          {
            storechar += 32;
          } else if ((storechar >= 95) && (storechar <= 119)) //char, add 64
          {
            storechar += 64;
          }

          inputstring[storeindex++] = storechar;
          //terminate it with null
          inputstring[storeindex + 1] = 0;
          gotoxy(0, 5);
          printf("%s", inputstring);
          gotoxy(xpos, ypos);
        }
        c = 1; //reset from 13
      } 
    } 
    storeindex = 0;
 
//    __asm {
//      lda $ce
//      sta $c8f1
//        }

switch (inputstring[1]) {

    case 95: { // 1F assignment  arrow
//      printf(" ASSIGNMENT\n");
      strcpy(tmpstring, & inputstring[2]); //  to \0
      if ((inputstring[0] >= 65) &&  (inputstring[0] <= 90)) {  //A-Z
//         if (inputstring[2] == ''') printf("QUOTE\n");
//         else printf("NOTQUOTE\n");
      delete(inputstring[0]);  // if it exists get rid of it
      insertFirst(inputstring[0], inputstring[0]-39  ,tmpstring);
      }
cwin_clear(&msgwin);
cwin_putat_string(&msgwin,0,0,"ASSIGNMENT TMPSTRING IS ",10);
cwin_putat_string(&msgwin,0,1,tmpstring ,10);
///cwin_put_string(&outputwin,inputstring,10);
print(&outputwin,"      ",10);

print(&outputwin,inputstring,7);

printLn(&outputwin);
//      printf(" TMPSTRING IS %s ", tmpstring);
//      printList();
      notassignment = 0;
      break;
    }


    case 181  : { // } select
      printf(" SELECT\n");
//      gradedown();
      break;
    }


     case 43: {
//	printf("ADD \n");
	if ((inputstring[0] == 65) && (inputstring[2] == 66))
	  {
cwin_clear(&msgwin);
cwin_putat_string(&msgwin,0,1,"ADD A PLUS B",10);
           foundLink = find(65);      	 
           foundLink2 = find(66); 
	   print(&outputwin,"      ",7);
           print(&outputwin, inputstring,7);
           printLn(&outputwin); 
           for(i=0; i < 5; i++) {   
           j =  (foundLink->p_array[i])+(foundLink2->p_array[i]);
           itoa(j,tempstring,10);
//         printf("%d ", (foundLink->p_array[i])+(foundLink2->p_array[i] ));
               print(&outputwin, tempstring, 3);
               print(&outputwin, " ", 3);
             }
           printLn(&outputwin);
	      
           }
      	break;
     	}

      case 162: {
//      printf("MULTIPLY \n");
        if ((inputstring[0] == 65) && (inputstring[2] == 66))
          {
cwin_clear(&msgwin);
cwin_putat_string(&msgwin,0,1,"MULTIPLY A TIMES B",10);
           foundLink = find(65);
           foundLink2 = find(66);
           print(&outputwin,"      ",7);
           print(&outputwin, inputstring,7);
           printLn(&outputwin);
           for(i=0; i < 5; i++) {
           j =  (foundLink->p_array[i])*(foundLink2->p_array[i]);
           itoa(j,tempstring,10);
//         printf("%d ", (foundLink->p_array[i])*(foundLink2->p_array[i] ));
               print(&outputwin, tempstring, 3);
               print(&outputwin, " ", 3);
             }
           printLn(&outputwin);

           }
        break;
        }



    default: {
      notassignment = 1;
//      printf("FIRST SWITCH NO MATCH\n");
     }
    } /////////switch

    if (notassignment == 0) {
       //printf("NOTASSIGNMENT IS 0 \n"); 
    }  //skip it
    else {
//    printf("INPUTSTRING0 IS %d \n", inputstring[0]);
//    printf("INPUTSTRING1 IS %d \n", inputstring[1]);

    switch (inputstring[0]) {
    case 108  : { //reverse
//      printf(" REVERSE\n");
      reversem();
      break;
    }

    case 104  : { //gradeup
//      printf(" GRADEUP\n");
      gradeup();
      break;
    }

    case 105  : { //gradedown
      printf(" GRADEDOWN\n");
      gradedown();
      break;
    }


    case 41  : { //  ) system
      printf(" SYS \n");
      if (inputstring[1] == 83 )  {   // )S  save
        krnio_setnam("@0:WORKSPACE,P,W");
        if (krnio_open(2, 8, 2))
        {
          krnio_putch(2, head->key);
          krnio_putch(2, head->data);
          for(char i=0; i<5; i++)
	       krnio_putch(2, head->p_array[i]);
    //             krnio_write(2, (char*)score, sizeof(score));
    //             krnio_write(2, (char  * ) head, sizeof(head->key));
               krnio_close(2);
        } 
      }  // )S  save

      if (inputstring[1] == 69 )  {   // )E erase one or more vars
          printf("ERASE A VAR    TO DO\n");
      }  // )E  erase

      if (inputstring[1] == 67 )  {   // )C lear workspace
      printf("CLEAR WORKSPACE  LINKED LIST LENGTH %d", length()  );
      listlength = length();
      for (i=0 ; i<listlength; i++ )
        deleteFirst();
      }  // )Clear

      if (inputstring[1] == 86 )  {   // )VARS
        printList();
      }  // )VARS

       
      if ((inputstring[1] == 76 ) && (inputstring[2] == 73 ))  {   // )LIB
          // Set name for directory
        krnio_setnam("$");
        // Open #2 on drive 9 (or 8)
        if (krnio_open(2, 8, 0))
        {
                // Switch input to file #2
                if (krnio_chkin(2))
                {
                        // Skip BASIC load address
                        krnio_chrin();
                        krnio_chrin();
                        // Loop while we have more lines
                        int ch;
                        while((ch = krnio_chrin()) > 0)
                        {
                                unsigned line;
                                char    buff[40];
                                // Skip second basic link byte
                                krnio_chrin();
                                // Read line number (size in blocks)
                                ch = krnio_chrin();
                                line = ch;
                                ch = krnio_chrin();
                                line += 256 * ch;

                                int n = 0;
                                while ((ch = krnio_chrin()) > 0)
                                        buff[n++] = ch;
                                buff[n] = 0;
                                // Print size and name
                                printf("%u %s\n", line, buff);
                        }
                        // Reset channels
                        krnio_clrchn();
                }
                // Close file #2
                krnio_close(2);
        }
      }
        if ((inputstring[1] == 76 ) && (inputstring[2] == 79 ))  {   // )LOAD
        krnio_setnam("WORKSPACE,P,R");
        if (krnio_open(2, 8, 2))
        {
                int ch1, k1 = 0;
		while ((ch1 = krnio_getch(2)) >= 0)
		{
			printf("%d : %d\n", k1, ch1)
			k1++;
			if (ch1 & 0x100)
				break;
		}
                krnio_close(2);
        }

          } // )LOAD

      break;
    }

    case 107  : { //upset
      printf(" UPSET\n");
      break;
    }
    case 110  : { //cant
      printf(" CANT\n");
      break;
    }
    case 111  : { //natural log
      printf(" LOG\n");
      mylog();
      break;
    }

    case 112  : { //execute
      printf(" EXECUTE\n");
      break;
    }
    case 113  : { //format
      printf(" FORMAT\n");
      break;
    }

    case 115  : { //circle
      printf(" PI TIMES \n");
      circlepi();
      break;
    }
    case 119  : { // WORDS  BASE
      printf(" WORDS \n");
      break;
    }
    case 120  : { //  inversebase
      printf(" INVERSEBASE \n");
      break;
    }
    case 122  : { // LEFT 
      printf(" LEFT  \n");
      break;
    }
    case 121  : { //RIGHT
      printf(" RIGHT \n");
      break;
    }
    case 123  : { // size |
      printf(" SIZE \n");
      break;
    }
    case 33  : { // factorial !
      printf(" FACTORIAL \n");
     fact();
      break;
    }
    case 37  : { //  inverse
      printf(" INVERSE\n");
      break;
    }
    case 175  : { //  ~ not
      printf(" NOT\n");
      break;
    }
    case 176  : { //   AND
      printf(" AND\n");
      break;
    }
    case 177  : { //   OR
      printf(" OR\n");
      break;
    }
    case 178  : { //   NAND
      printf(" NAND\n");
      break;
    }
    case 179  : { //   NOR
      printf(" NOR\n");
      break;
    }
    case 180  : { //   ALL  {
      printf(" ALL\n");
      break;
    }
    case 44  : { //   , 
      printf(" RAVEL\n");
      break;
    }
    case 63: { //#$3F is ? roll
      printf(" ? ROLL\n");
      __asm{
        LDA $D41B 
        sta $c8f7
           }
     int z = *(char *) 0xc8f7;
// %i and %s dont work!  not a bug   printf(" ROLLED %d %i %s \n", z, z, z);
      printf(" ROLLED %d  \n",   z);
      roll();
      break; /* optional */
    }
   case 94  : { //nub/raze
      printf(" NUB\n");
      break; /* optional */
    }
   case 159  : { //take/drop
      printf(" TAKE\n");
      break; /* optional */
    }
   case 97  : { // e  raze in
      printf(" E RAZE IN\n");
      break; /* optional */
    }
   case 98  : { //98 is iota
      iota();
       // Print the elements of the array

      break; /* optional */
    }
   case 99  : { //  p
      printf(" SHAPE\n");
      break; /* optional */
    }
   case 166 : {   // ceiling
     printf("CEILING\n");
     myceiling();
     break;
     }
    case 167 : {   // floor
     printf("FLOOR\n");
     myfloor();
     break;
     }
    case 169 : {   //  mix index U
     printf("MIX INDEX\n");
     break;
     }
    case 171 : {   //  box open
     printf("BOX OPEN\n");
     break;
     }
    case 38: {
  cwin_putat_string(&msgwin,0,0,"I-BEAMS ",3);

      if ((inputstring[1] == 50) && (inputstring[2] == 48))   
      {  ibeam20(); }
      if ((inputstring[1] == 50) && (inputstring[2] == 49)) 
      {  ibeam21(); } 
      if ((inputstring[1] == 50) && (inputstring[2] == 65)) 
      {  atomicvector();  }
      break;
      }
    case 35: { //filled box is clear screen
//      CLRSCR
        for (i = 0; i < 1024; i++) Screen[i] = 32;
        corral();
        break; /* optional */
    }
    default:
       {                //printf("NO MATCH SECOND SWITCH\n");
       }
    }  //switch  
   }  
   // printList(); 
      if ((inputstring[4] >= 65) && (inputstring[4] <= 90) && inputstring[3] == 99 ) {   // reshape var
        cwin_putat_string(&msgwin,0,0,"RESHAPE ",3);

         foundLink = find(inputstring[4]);

         tempstring[0] =inputstring[0];
         tempstring[1] = 0;   
         foundLink->rows = atoi(tempstring);
      
         tempstring[0] =inputstring[2];
         tempstring[1] = 0;
         foundLink->cols = atoi(tempstring);
 
      }  
       // is an A-Z

   if ((inputstring[0] >= 65) && (inputstring[0] <= 90)) { 
       // is an A-Z
     if ((inputstring[1] == 0) || (inputstring[1] == 32)) {
//        printf("CHECKING FOR MATCH ON VAR   \n");
  cwin_fill(&msgwin,32,3);
  cwin_putat_string(&msgwin,0,0,"CHECKING FOR MATCH ON VAR ",3);

//        foundLink = find(65);  
   foundLink = find(inputstring[0]  );
        if(foundLink == 0) {
cwin_putat_string(&msgwin,0,1,"FOUNDLINK WAS NULL ELEMENT NOT FOUND  ",10);
           }
        if(foundLink != 0) {

        print(&outputwin,"      ",7);
        print(&outputwin,inputstring , 7);
        printLn(&outputwin);
           cwin_putat_string(&msgwin,0,1,"FOUNDLINK LINK WAS FOUND  ",13);


   for (i=0; i<5; i++){
       itoa(foundLink->p_array[i],charstring,10);
       print(&outputwin,charstring , 3);
       print(&outputwin," ",3);
           }
    printLn(&outputwin);
         }

      }   
      
     }  //if  A-Z
  } //while 1
}  // main
//addfiles https://stackoverflow.com/questions/43356211/writing-a-disk-file-using-assembly-on-commodore-64
//https://codebase64.org/doku.php?id=base:dos_examples
