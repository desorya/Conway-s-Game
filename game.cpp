#include "game.h"

// Initialize the universe with a glider pattern at top-left 
void init(bool universe[WIDTH][LENGTH]) {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			universe[i][j] = DEAD;
		}
	}

// Initial position
	universe[0][1] = ALIVE;
	universe[1][2] = ALIVE;
	universe[2][0] = ALIVE;
	universe[2][1] = ALIVE;
	universe[2][2] = ALIVE;
}


// Function to display the current state of the universe
void visualize(bool universe[WIDTH][LENGTH]) {
	
	system("cls"); // Clear the terminal

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			wprintf(L"%c ", universe[i][j]?'*':char(0x219)); // use ASCII and wprintf() to print the block element pattern			
		}
		printf("\n");
	}

	usleep(500000); // Delay for animation
}



// Function to apply the rules of the game to update the universe
void update(bool universe[WIDTH][LENGTH]) {

	bool newUniverse[WIDTH][LENGTH]; // Set up a cache universe to store the update in each loop 

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			int liveNeighbors = 0;

			// Count live neighbors for each element in the universe
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					if (x == 0 && y == 0) 
						continue; // Skip the current cell
					int ni = i + x;
					int nj = j + y;

					if (ni >= 0 && ni < WIDTH && nj >= 0 && nj < LENGTH && universe[ni][nj] == ALIVE) {
						liveNeighbors++;
					}
				}
			}

			// Apply rules
			if (universe[i][j] == ALIVE) {
				
				// Rule < 1 >
				if (liveNeighbors == 2 || liveNeighbors == 3) {
					newUniverse[i][j] = ALIVE;
				} else {
					newUniverse[i][j] = DEAD; // Rule < 3 >
				}
			} else {
				// Rule < 2 >
				if (liveNeighbors == 3) {
					newUniverse[i][j] = ALIVE;
				} else {
					newUniverse[i][j] = DEAD;  // Rule < 3 >
				}
			}
		}
	}


	/*
		Copy cache universe back to the original universe
		Check if the universe doesn't change anymore
		
	*/
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (universe[i][j] != newUniverse[i][j]) {
				universe[i][j] = newUniverse[i][j];
				trigger = 1; // Deactivate the trigger if any element in universe has been changed
			}
		}
	}
	
	trigger = trigger == 0 ? 2 : 0; // Activate trigger if universe doesn't change anymore, otherwise reset trigger
}



int main() {
	
	bool universe[WIDTH][LENGTH];


	init(universe);

	for (; trigger != 2;) {
		visualize(universe);
		update(universe);
	}

	system("pause");

	return 0;
}
