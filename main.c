/*
 * Pranav and Stratton
 * Escape Room
 * 1/6/25
 * Extra:
 */

/*
1. Start in lunch room
	a. Eat
		I. You go up to the food line, and get food. On your way back, the gaurd asks for food and spoon, and he allows you to leave. This message only shows if you have a spoon.
	b. Try to go to the bathroom
		I. If you attempt to go to the bathroom, the door opens, revealing a grimy mirror with a scrambled message (random string of 4 chars) written in condensation. Reoptionsange the letters or solve the cipher to reveal a clue about how to unlock the main exit.
	c. Get eating utensiles
		I. While trying to get eating utensils, you notice they're locked in a drawer. A sticky note with a cryptic riddle hints at the code to open it. Solve the riddle to unlock the drawer and retrieve the utensils, a critical tool for future challenges. This spoon can be used in combination with getting food, to bribe the gaurd and leave.
	d. Try to sneak out
		I. If you try to sneak out, you stumble upon a locked side door. A combination lock blocks the way, and the key to solving it is hidden in characters etched on various lunch trays. Matching these symbols to their ascii number provides the combination.
			I. You trigger a timed system. If you run out of time before getting the answer, you get caught.
*/

#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

char* options[] = {
	"Eat",
	"Try to go to the bathroom",
	"Get eating utensils",
	"Try to sneak out"
};

int code[] = { 1, 2, 3, 4 };

int length = 4;
int option;

bool hasFork;
char food;

void countdown_timer(int seconds) {
    while (seconds > 0) {
        int minutesRemaining = (seconds % 3600) / 60;
        int secondsRemaining = seconds % 60;
        printf("\rTime remaining: %02d:%02d", minutesRemaining, secondsRemaining);
        fflush(stdout);
        sleep(1); 
        seconds--;
    }
    printf("\nTime's up! You've been caught!\n");
    exit(0); 
}

int main() {
	srand( time( NULL ) );

	for ( int i = 0; i < 4; i++ ) {
		int temp = code[i];
		int rand_number = (int)( (float)rand() / RAND_MAX * 4 );
		code[i] = code[rand_number];
		code[rand_number] = temp;
	}

	// Introducing the story
	printf( "It's currently 10:40 in the morning, right in time for lunch!\nYou walk into the packed lunchroom and notice the smell of the food.\n\e[1mHowever, you forgot your backpack in class! You try to return and go get it, but the guard stops you!\e[0m\nYou think of a few options on how to escape the lunch room:\n" );

	// Getting all possible options
	for ( int i = 0; i < length; i++ ) {
		printf( "%d. %s\n", i + 1, options[i] );
	}

	while ( 1 ) {
		// Input validation
		do {
			printf( "\n\e[1mWhat will you do? \e[0m" );
			scanf( "%d", &option );

			while ( getc( stdin ) != '\n' );

			if ( option <= 0 || option > length )
				printf( "\e[31mInvalid input. Try again.\e[0m" );
		} while ( option <= 0 || option > length );

		switch ( option ) {
			case 1:
				printf( "\nYou make your way to the busy food line, navigating through the crowd of people.\nYou buy chicken parm and a grilled cheese sandwhich.\e[0m\n" );

				if ( hasFork ) {
					printf( "\nA strange kid walks up to you and says, \"Gimme that food and gimme dat fork and ill get u outa here\"\nGive the strange kid the food and fork [Y/n]? " );

					char ch = getc( stdin );
					if ( ch != '\n' ) { while ( getc( stdin ) != '\n' ); }

					if ( ch == 'y' || ch == 'Y' || ch == '\n' ) {
						printf("You hand the strange kid the food and fork, he swollows the plate whole and in one swift motion gives the fork to the guard. You walk out without resistance.\n");
						exit(0);
					} else {
						printf("The kid scowls at you and walks away.\n");
					}
				}
				break;
			case 2:
				printf( "\nIn an attempt to escape, you ask the guard to go to the bathroom. They say that you have to use the locker rooms so you go and see a mirror with writing on it.\n"
"  _________________\n"
" / _______________ \\\n"
"| |⠉⠉⠉⠑⠒⠒⠒⠤⠤⠤⠤⠤⠄⠄⠄| |\n"
"| |⠈⠉⠁⠉⠉⠁⠄⠄⠒⠒⠒⠓⠗⠗⠗| |\n"
"| |⠆⠆⠆⠄⠄⠤⠤%c⠴⠖⠒⠒⠋⠋⠋| |\n"
"| |⠁⠁⠁⠨⠩⠭⠭⠭⠦⠤⠤⠄⠄⠄⠅| |\n"
"| |⠘⠁⠈⠂⠤⠤⠖%c⠉⠉⠁⠅⠅⠉⠉| |\n"
"| |⠇⠉⠐⠒⠒⠖⠤⠤⠒⠉⠁⠉⠐⠓⠆| |\n"
"| |⠛⠛⠷⠶⠶⠦⠤%c⠖⠒⠓⠓⠒⠒⠇| |\n"
"| |⠽⠿⠇⠇⠦⠬⠤⠔⠋⠋⠉⠉⠉⠱⠒| |\n"
"| |⠈⠉⠉⠙⠂⠆⠂%c⠤⠒⠒⠲⠷⠸⠁| |\n"
"| |⠐⠒⠉⠁⠂⠔⠒⠦⠤⠴⠬⠉⠭⠷⠗| |\n"
"| |\e[4m⠛⠛⠷⠶⠶⠦⠤⠒⠖⠒⠓⠓⠒⠒⠇\e[0m| |\n"
" \\_________________/\n", 'A' + code[0], 'A' + code[1], 'A' + code[2], 'A' + code[3] );
				break;
			case 3:
				printf( "\nYou walk to the silverware container, which houses spoons, knives, and forks. You pick up a fork and go on your way.\n" );
				hasFork = true;
				break;
			case 4:
				printf( "You walk on your tippy toes over to the side door but find a padlock with a four digit numeric keypad and four plates. You try out a combination when suddenly, you have just activitated a timed system! If you don't get the code within two minutes. You will be caught!\n"
"    x  x          x  x          x  x          x  x    \n"
" x        x    x        x    x        x    x        x \n"
"x          x  x          x  x          x  x          x\n"
"x          x  x          x  x          x  x          x\n"
" x        x    x        x    x        x    x        x \n"
"    x  x          x  x          x  x          x  x    \n" );

				countdown_timer(120);

				printf("Hi");
				break;
		}
	}

    return 0;
}
