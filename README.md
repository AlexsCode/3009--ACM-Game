# 3009: ACM-Game
 A Project to utilise ACM (Asynchronous communication mechanisms) to reduce delay in game situation.

Includes:
1. 3009_Chasing_Game.c - Main Game code written in C
2. 3009_Delay.c - Additional code to induce a delay to the game.
3. 3009_ACM.c - Additional code to reduce affect of delay on game.


Set as a University project.
 
The specification: 
Game:
The game is played on the alphanumerical terminal and 4 directional buttons are used to control the movements.
Two objects are displayed: the moving target(rabbit) and the chaser (fox).
Both are represented as a single character and moved at the speed of 1 position every 0.5 seconds.
The rabbit makes random turns and never leaves the screen. 
The turns of the fox are controlled by the player. 
The game ends when the fox is placed at the same coordinates as the rabbit.
Implement the keyboard reading function as a concurrent thread in order to make it independent from the animation.
The output of the game is produced on the standard output stream.
Use escape characters to position symbols on the screen.
Use the example code to set up the appropriate keyboard mode.
Use a separate thread to read the keyboard. 
Use a global variable to store the current direction of the fox.
Derive a Petri net model describing the communication between the keyboard and the animation part of the game.


Slow interface emulation program:
Add a delay to slow down character inputs.


ACM:
Design it using the appropriate number of slots and the slot size. 
In the report explain and discuss the operation and the effect of ACM on the system performance.
Derive a Petri net model of the ACM.

