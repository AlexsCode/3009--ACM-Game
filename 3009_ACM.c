//Code written by Alex Tuddenham
//for Project 3009: Control & Embedded systems

//set the liberaries.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//"\033[2J\033[%d;%dH@\033[%d;%dH*" Frame Sample Size
// Maximum Total frame size is 22

char slots[3][22]; // 3 slots, set max frame to 22 
int w=1, r=2, l=3; // define each slot and give it a value in the array.

void
reader_thread ()
{
  

  while(1)  // reader loop; includes a delay to reduce the output data rate
    {
		if(l!=r) 
			return;			//
		else
			r=l; 		//wait until l<>r ()when values not equal;
		
		printf ("%s", slots[r]); // access slot; slots[i] is a pointer to slots[i][0]
		fflush(stdout);
		usleep(500000);     // limit output rate; calculate your own value (>500000) (20% used)
    }
}

char inp() // getchar() wrapper which checks for End Of File EOF //input
{
  char c;
  c=getchar();
  if(c==EOF) exit(0); // exit the whole process if input ends
  return c;
}

int j;
int main () // main function for the AC Mechanism
{
   // set creation of pthread
  pthread_t p;
  pthread_create(&p,NULL,(void*)&reader_thread,NULL); // create reader thread

  while (1)  // writer loop searches the writing slot and sets writing slot dependant on read and buffer slot
    {
      w=l;
	  j = 0; // Counter
      while ((slots[w][j++] = inp ()) != '*'); // the actual computation takes place inside the condition
      slots[w][j] = 0; // appends the terminating symbol to the string

	if (r!=2&&l!=3)
		{w=2;}
	if (r!=2&&l==3)
		{w=3;}
	else if (r=2&&l==3)
		{w=1;}
	
	}
	pthread_cancel (p); // end the thread
  return 0;
}
