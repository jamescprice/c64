#include <c64/charwin.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stddef.h>
#include <c64/vic.h>
#define Screen  ((byte * ) 0xc800)
struct node {
   int data;
   int key;
   int    *p_array;
   struct node *next;  };
// declare a pointer variable to point to allocated heap space
int k;
int i, xpos, ypos;
char c;
char inputstring[25];
char tmpstring[25];


byte data[] = { 
#embed "apl.bin" 
}; 

struct node *head = NULL;
struct node *current = NULL;

void myfloor() {
//stub
}

void myceiling() {
//stub
}

//display the list
void printList() {
  int i;
  struct node * ptr = head;
  printf("\n[ ");

  //start from the beginning
  while (ptr != 0) {
    printf("(%d,%d) ", ptr -> key, ptr -> data);
    for (i = 0; i < 5; i++) {
      printf(" %d ,", ptr -> p_array[i]);
    }
    printf("\n");
    ptr = ptr -> next;

  }

  printf(" ]");
  return;
}


//insert link at the first location
void insertFirst(int key, int data, char tmpstring[25]) {
   //create a link
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
//	j = rand();
//        link->p_array[i] = j;
//   }

   for(i=0; i < 5; i++) {
      link->p_array[i] = tmpstring[i];
   }
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}

//insert link at the first location
void insertFirststring(int key, int data, char tmpstring[25]) {
   //create a link
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
	
   for(current = head; current != NULL; current = current->next) {
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
  int i, j, dummy;
  struct node * foundLink;
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

    printf("BEFORE REVERSING\n ");
    for (i = 0; i < 5; i++) {
      //      printf("in rotate loop1");
      printf("%d ", foundLink -> p_array[i]);
    }

    for (i = 0; i < 2; i++) { //only rotate the first half!!!!
      dummy = foundLink -> p_array[i];
      foundLink -> p_array[i] = foundLink -> p_array[4 - i]; //adjust later for general case
      foundLink -> p_array[4 - i] = dummy;

      //      printf("in rotate loop0");
    }
    //  printf(" rotating  ");
    foundLink -> p_array[5] = dummy;
    printf("\nAFTER REVERSING \n ");
    for (i = 0; i < 5; i++) {
      //      printf("in rotate loop1");
      printf("%d ", foundLink -> p_array[i]);
    }
    //  printf("in rotate loop2");
  }
  // printf("in rotate loop3");
}


void gradeup()
{
  int i, j, dummy;
  int n = 5;  //hardwired change later
  struct node * foundLink;
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

    printf("BEFORE GRADEUP \n ");
    for (i = 0; i < 5; i++) {
      printf("%d ", foundLink -> p_array[i]);
    }

     for (i = 0; i < n-1; i++) {
       for (j = 0; j < n-i-1; j++) {
           if (foundLink->p_array[j] > foundLink->p_array[j+1]){
              dummy =  foundLink->p_array[j];
              foundLink->p_array[j] = foundLink->p_array[j+1];
              foundLink->p_array[j+1]= dummy;
           }
       }
     }
        

    printf("\nAFTER GRADEUP \n ");
    for (i = 0; i < 5; i++) {
      printf("%d ", foundLink -> p_array[i]);
    }
  }
}

void gradedown()
{ 
  int i, j, dummy;
  int n = 5;  //hardwired change later
  struct node * foundLink;
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

    printf("BEFORE GRADEDOWN \n ");
    for (i = 0; i < 5; i++) {
      printf("%d ", foundLink -> p_array[i]);
    }

     for (i = 0; i < n-1; i++) {
       for (j = 0; j < n-i-1; j++) {
           if (foundLink->p_array[j] < foundLink->p_array[j+1]){
              dummy =  foundLink->p_array[j];
              foundLink->p_array[j] = foundLink->p_array[j+1];
              foundLink->p_array[j+1]= dummy;
           }
       }
     }


    printf("\nAFTER GRADEDOWN\n ");
    for (i = 0; i < 5; i++) {
      printf("%d ", foundLink -> p_array[i]);
    }
  }
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
  int i,val;
  strcpy(tmpstring, & inputstring[1]); //  to \0
  printf("\n\n\n\n IOTA  %s\n", tmpstring);
  val = atoi(tmpstring);
//  printf(" got value from atoi of %d \n", val);
  for (i=0; i<=val; i++)
  {printf(" %d",i);}
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
  *(char * ) 0xd021 = 0x06;
  for (i = 0; i < 120; i++) {
    ( * (char * )(0xd800 + i)) = 1;
  }
}

int main(void) {

//  char inputstring[25];
 // char tmpstring[25];

  int notassignment = 0;
  struct node * foundLink;
  struct node * foundLink2;
  size_t size;
  int val;

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
//          LDA $381C
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
          sta $c8f0
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
          loc1efe: RTS
          loc1eff: LDA #$00
          STA $CC
//          RTS
          done:
        }
        c = * (char * ) 0xc8f0;
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
          if (ypos > 2) {
            ypos = 0;
          }
          gotoxy(xpos, ypos);
        } else if (c == 145) {
          ypos--;
          if (ypos < 0) {
            ypos = 2;
          }
          gotoxy(xpos, ypos);
        } else if (c == 13) {
          ypos = 0;
          xpos = 0;
          __asm {
            lda $ce
            sta $c8f3
          }
          storechar = * (char * ) 51443; //$c8f3
          if (storechar == 0) {
            linenotdone = 0;
            gotoxy(12, 12);
//            printf("GOT NULL PARSE THIS %s \n", inputstring);
    break;
          }

          *(char * )(52992 + storeindex) = storechar; //52992 = cf00
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
          gotoxy(10, 10);
          printf("%s", inputstring);
          gotoxy(xpos, ypos);
        }
        c = 1; //reset from 13
      } 
    } 
    storeindex = 0;
 
    __asm {
      lda $ce
      sta $c8f1
        }

switch (inputstring[1]) {

    case 95: { // 1F assignment  arrow
      printf(" assignment\n");
      strcpy(tmpstring, & inputstring[2]); //  to \0
      printf("\n\n\n\n\n\n\n\n CASE 95 %s\n", tmpstring);
      if (inputstring[0] == 65) {
         if (inputstring[2] == ''') 
           printf("QUOTE\n");
         else printf("NOTQUOTE\n");
         insertFirst(inputstring[0], 26, tmpstring); //HARDWIRED FOR 1 = A revisit    
      }
      else if (inputstring[0] == 66) {
         insertFirst(inputstring[0], 27, tmpstring); //HARDWIRED FOR 1 = A revisit    
      }

      printf(" TMPSTRING IS %s ", tmpstring);
      printList();
      notassignment = 0;
      break;
    }

     case 43: {
	printf("add \n");
	if ((inputstring[0] == 65) && (inputstring[2] == 66))
	  {
	   printf("add a plus b\n");
           foundLink = find(65);      	 
           foundLink2 = find(66); 
	  
           for(i=0; i < 5; i++) {   
             printf("(%d) ", (foundLink->p_array[i])+(foundLink2->p_array[i] ));
             }
	      
           }
      	break;
     	}


    default: {
      notassignment = 1;
//      printf("FIRST SWITCH NO MATCH\n");
     }

    } /////////switch


    if (notassignment == 0) {printf("NOTASSIGNMENT IS 0 \n"); }  //skip it
    else {
    printf("INPUTSTRING0 IS %d \n", inputstring[0]);
    switch (inputstring[0]) {
    case 108  : { //reverse
      printf(" REVERSE\n");
      reversem();
      break;
    }

    case 104  : { //gradeup
      printf(" GRADEUP\n");
      gradeup();
      break;
    }

    case 105  : { //gradedown
      printf(" GRADEDOWN\n");
      gradeup();
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

   case 98  : { //98 is iota
      //printf(" iota\n");
      iota();
      break; /* optional */
    }
   case 125 : {   // ceiling
     printf("CEILING\n");
     myceiling();
     break;
     }

    case 126 : {   // floor
     printf("FLOOR\n");
     myfloor();
     break;
     }
   
    case 38: {
      printf(" IBEAMS\n");
      if ((inputstring[1] == 50) && (inputstring[2] == 48))   
      {  
         ibeam20(); 
      }
      if ((inputstring[1] == 50) && (inputstring[2] == 49)) 
      {  ibeam21(); } 
      break;
      }
    case 36: { //empty box is clear screen
//      CLRSCR
        for (i = 0; i < 1024; i++) Screen[i] = 32;
        corral();
        break; /* optional */
    }
    default:
       { printf("NO MATCH SECOND SWITCH\n"); }
    }  //switch  
  
  
   }  
   // printList(); 
   if (inputstring[0] == 65) { 
       // is an A
     if (inputstring[1] == 0) {
        printf("CHECKING FOR MATCH ON A  \n");
        foundLink = find(65);  
        if(foundLink == 0) {
           printf("FOUNDLINK WAS NULL ELEMENT NOT FOUND\n ");
           }
        if(foundLink != 0) {
           printf("FOUNDLINK LINK WAS FOUND \n");
           printf("(%d,%d) ",foundLink->key,foundLink->data);
           for(i=0; i < 5; i++) {
             printf("%d ", foundLink->p_array[i]);
           }

         }
      }   
      
     }  //if (inputstring[0] == 65)

  } //while 1
}  // main
