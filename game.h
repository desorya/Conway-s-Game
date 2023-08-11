#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <math.h>
#include <unistd.h> // for thread-sleep to delay the animation

/*
	Universe shape
	The least size of the universe should be 3 * 3 to show the full glider pattern
	
*/
#define WIDTH 9
#define LENGTH 16

// Visualize pattern
#define ALIVE 1
#define DEAD 0

// Universe function frame
void init();
void update();
void visualize();

// I/O
void readFromFile();
void writeToFile();

/* 
	Use a trigger to break the loop if the pattern doesn't change anymore
	The trigger has 3 status:
		0 - stand-by, no specific meaning, reset before each update cycle
		1 - not triggered, which means that the pattern has been changed
		2 - triggered, which means that the pattern keeps it as it is after update, mainly occurs at the border
			of the universe(in this case), meaningless if the universe has an infinite shape
		
*/
int trigger;
