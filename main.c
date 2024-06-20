#include "database.h"
#include "display.h"
#include "game.h"
#include "dictionary.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main() {

    int response,choice,players,category,level,duration;
    int playing=1;

    // Initialize the random seed
    srand(time(NULL));

    while (playing==1){
        // Show the Display
        displayWelcomeScreen();
        response=main_menu();

        char players_name[4][WORD_LENGTH];
        switch (response) {
            case 1:
                // Get the global variable
                players=player_number(players_name);
                category=category_number();
                level=difficulty();
                duration=timer();

                // Start the game
                gameplay(players,level,duration,category, players_name);
                break;
            case 2:
                // Show the dictionnary stuff
                word_display();
                choice=dictionary_menu();
                switch(choice){
                    case 1:
                        addword();
                        break;
                    case 2:
                        modification();
                        break;
                    case 3:
                        delete();
                        break;
                    case 4:
                        break;
                }
                break;
            case 3:
                printf("\n============================\nA bientot\n============================\n");
                playing=0;
                break;
            default:
                // Handle non planned interaction
                break;
        }
    }
    return 0;
}
