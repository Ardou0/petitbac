//
// Created by cjournet on 15/05/2024.
//

#ifndef CLION_GAME_H
#define CLION_GAME_H


typedef struct{
    int player;
    char category[WORD_LENGTH];
    char word[WORD_LENGTH];
} Answer;

/**
 * The main process of the game itself that call every functions needed to play the game
 * @param The number of players in the game
 * @param The difficulty level of the game
 * @param The duration (in seconds) each player has to enter their words during their turn
 * @param The number of categories each player needs to fill
 * @param An array of strings containing the names of the players
 */
void gameplay(int, int, int, int, char [4][WORD_LENGTH]);

/**
 * The function that pick randomly categories form a list corresponding to a difficulty
 * @param The difficulty level of the game
 * @param The number of unique categories to select
 * @param A 2D array of strings where the selected categories will be stored
 */
void category_choice(int,int, char [][MAX_LENGTH]);

/**
 * Analysis if the words put by the players are already existing and if they are put by other players
 * @param An array of Answer structs containing the words submitted by the players
 * @param The current number of answers that have been submitted and need to be processed.
 * @param An array of integers representing the scores of each player
 * @param The total number of players participating in the game
 * @param The specific letter that each word is required to start with
 */
void responseProcessing(Answer [], int , int [], int , char);

#endif //CLION_GAME_H
