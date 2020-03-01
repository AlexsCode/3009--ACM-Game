//Code written by Alex Tuddenham
//for Project 3009: Control & Embedded systems

#include <stdio.h>
//Takes game get char input and add delay of 30000us
int main()
{
 char c;  
 for(;;)
   {
     c=getc(stdin); 
     if (c == EOF) return 0;
     usleep(30000); // delay
     printf("%c",c); //The delay is made from the Game code usleep of 500,000 us (written in spec to move every 0.5s)
     fflush(stdout); // There are 3 instructions being implemented 20% of this 100,000 600,000/3= 200,000, However 20000 too responsive so using 30000 to create more noticable slowdown
   }
 return 0;
}