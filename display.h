//
// Created by cjournet on 15/05/2024.
//

#ifndef CLION_DISPLAY_H
#define CLION_DISPLAY_H
#include "game.h"

/**
 * Displays a welcome message to players
 */
void displayWelcomeScreen();
/**
 * Asks players what they want to do
 * @return the int corresponding of the player choice
 */
int main_menu();
/**
 * Allows players to choose between adding, editing or deleting a word
 * @return the int corresponding of the player choice
 */
int dictionary_menu();
/**
 * Displays all words in the dictionary
 */
void word_display();
/**
 * Requests the number of players in a game
 * @param array that will contain all the names of the players
 * @return int corresponding to the number of players
 */
int player_number(char [4][WORD_LENGTH]);
/**
 * Asks player how many categories they want to play with
 * @return int of how many category the players will play with
 */
int category_number();
/**
 * Ask player the difficulty they wanna play
 * @return int corresponding to the difficulty level
 */
int difficulty();

/**
 * Ask player how much time they will be able to answer
 * @return int corresponding to the time they'll be allowed to respond in seconds
 */
int timer();

/**
 * displays the different categories for this game and allows the player to enter the word equivalent to one of them
 * @param Table containing all the categories
 * @param the number of categories
 * @param The array of Answer struct that will contain all the response from the players during the game
 * @param The number of all the answer that have been filled
 * @param The number of players
 * @param The letter that the players have to play with
 */
void player_menu(char[][MAX_LENGTH],int, Answer[], int *, int, char);

/**
 * Subroutine allowing each player to validate or not the words of others (if they are not already in the dictionary)
 * @param The array of Answer struct that are not in the dictionnary
 * @param the number of answers
 * @param the array of scores of all the players
 * @param The number of players
 * @param Tell if more than the current player put this word
 * @param The array of all the accepted words for this game
 *
 */
void vote(Answer [], int , int [], int, int, char [][WORD_LENGTH]);


#endif //CLION_DISPLAY_H
