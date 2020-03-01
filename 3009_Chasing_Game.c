//Code written by Alex Tuddenham
//for Project 3009: Control & Embedded systems

//Sets libraries to include
#include <stdio.h>
#include <termios.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// defines the size of the window of the game,buffer size,starting positions and directions
#define width  40
#define height 18
#define buf_length (width*height)
#define fox_init_x (width/3*2)
#define fox_init_y (height/2)
#define fox_init_dir 'd'
#define rabbit_init_x 5
#define rabbit_init_y 5
#define rabbit_init_dir 'l'


//structure to create the keyboard input mode, using terminal OI Header
struct termios
tty_prepare ()
{
  struct termios tty_attr_old, tty_attr;
  tcgetattr (0, &tty_attr);
  tty_attr_old = tty_attr;
  tty_attr.c_lflag &= ~(ECHO | ICANON);
  tty_attr.c_cc[VMIN] = 1;
  tcsetattr (0, TCSAFLUSH, &tty_attr);
  return tty_attr_old;
}

//restores keyboard mode, saves attributes when output has drained and flushes pending input.
void
tty_restore (struct termios tty_attr)
{
  tcsetattr (0, TCSAFLUSH, &tty_attr);
}

//---- fox direction
char fox_dir = fox_init_dir;

//keyboard thread function, takes input at this stage.
void
keys_thread()
{
while (1)
 {char key = getchar() ;

 if (key == 'w') {fox_dir = 'u';} //Set the key used to be the direction up
 if (key == 's') {fox_dir = 'd';} //Set the key used to be the direction down
 if (key == 'd') {fox_dir = 'r';} //Set the key used to be the direction right
 if (key == 'a') {fox_dir = 'l';} //Set the key used to be the direction left
 }
	}
 



//Updates the co-ordinates of the fox or rabbit through pointer, if new position exceeds window size, then end loop.
void
update_coord (int *x_ptr, int *y_ptr, char dir) // calls by reference to x and y
{
  switch (dir) //key press sets direction via pointer
    {
    case 'u': if (*y_ptr > 1) (*y_ptr)--; break; 
	case 'd': if (*y_ptr < 18) (*y_ptr)++;break;
	case 'r': if (*x_ptr <40) (*x_ptr)++;break;
	case 'l': if (*x_ptr >1) (*x_ptr)--;break; 

    }
}

//Main thread starts here
main ()
{   //sets position and direction using the defined initial (could be randomised)
	int fox_x=fox_init_x;
	int fox_y=fox_init_y;
	int rabbit_x = rabbit_init_x;
	int rabbit_y=rabbit_init_y;
	char rabbit_dir = rabbit_init_dir;
	
	
   // calls the keyboard thread and sets keyboard inputs from the terminal structure.
   pthread_t threadlocation;
   struct termios term_back = tty_prepare (); //
   pthread_create (&threadlocation, NULL, (void *)keys_thread, NULL); //create the keyboard thread
   
   //Main constant loop for updating  screen from pointer values.
  while (1)
    {
      usleep (500000); //delay to set polling rate

      update_coord ( &fox_x, &fox_y, fox_dir); //main updater of values from pointer locations, keyboard input

      //RNG code
	  int CurrentRand = rand()%4; //Assigns new generated random number to current
	
	  
	  //Calls the rabbit direction through switch, should be random change each loop.
	  switch (CurrentRand)
	  { 
	  case 0:  rabbit_dir = 'u';break;
	  case 1 : rabbit_dir = 'd';break;
	  case 2 : rabbit_dir = 'r';break;
	  case 3 : rabbit_dir = 'l';break;
	  }
		
      update_coord (&rabbit_x, &rabbit_y, rabbit_dir); //updates the location and direction of the rabbit
      printf ("\033[2J\033[%d;%dH@\033[%d;%dH*", fox_y, fox_x, rabbit_y, rabbit_x); //prints to screen the two characters for the game in their current locations
      fflush (stdout); // flush output

      if (fox_y == rabbit_y &&fox_x==rabbit_x) break; // game terminates if they occupy same co ordinated.
    }


  pthread_cancel (threadlocation); //()() //game thread close location
  tty_restore (term_back); // restores keyboard mode

  return 0;
}

