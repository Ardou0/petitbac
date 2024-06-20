//
// Created by cjournet on 15/05/2024.
//
#include "database.h"
#include "display.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <time.h>


void gameplay(int playerNumber, int level, int duration, int numberCategories, char players_name[4][WORD_LENGTH]) {
    char definitive_categories[numberCategories][MAX_LENGTH];
    category_choice(level, numberCategories, definitive_categories);

    // Define the random letter
    char letter;
    letter = rand() % 26 + 97;

    // Initialize the array that will contain all the answers
    int max_possible_answer = numberCategories * playerNumber;
    int current_answer = 0;
    Answer AnswerArray[max_possible_answer];

    // Process of each round for each players
    for (int j = 0; j < playerNumber; j++) {
        if (j == 0) {
            printf("============================\n");
        }
        if (j != 0) {
            // Using time.c to make a pause during the game to handle player changing
            nanosleep((const struct timespec[]){{5, 0}}, NULL);
        }

        printf("La lettre est  %c\n============================\n", letter);

        // Keep the starting time in mind
        time_t start_time = time(NULL);
        printf("Joueur %d, c'est parti !\n", j + 1);
        do {
            // Let the player answer one category at the time
            player_menu(definitive_categories, numberCategories, AnswerArray, &current_answer, j, letter);
        } while (duration > difftime(time(NULL), start_time));
        printf("============================\nLe temps est ecoule ! \n============================\n");
    }

    int score[playerNumber];
    for (int i = 0; i < playerNumber; ++i) {
        // At the begining every player has 0 point
        score[i] = 0;
    }

    // Process all the answer to get the final score of all the players
    responseProcessing(AnswerArray, current_answer, score, playerNumber, letter);

    for (int i = 0; i < playerNumber; ++i) {
        printf("Joueur %d (%s), tu as %d points !\n", i + 1,players_name[i], score[i]);
    }

    // Wait before comming back to the home page
    nanosleep((const struct timespec[]){{5, 0}}, NULL);
}


void responseProcessing(Answer AnswerArray[], int current_answer, int score[], int playerNumber, char letter) {

    // Get all the words from the words.csv file starting with the corresponding letter
    Term *words = NULL;
    int wordCount = 0;
    parseWordsFromFile(letter, &words, &wordCount);

    // Create an history array to prevent from asking player verification twice
    char alreadyAccepted[current_answer][WORD_LENGTH];

    // For each answer process the verification
    for (int i = 0; i < current_answer; ++i) {

        // Testing if the word already exist in the words.csv
        int exist = 0;
        for (int j = 0; j < wordCount; ++j) {
            if (strcmp(AnswerArray[i].word,words[j].word) == 0) {
                exist = 1;
            }
        }

        // Process to find out if a word been already used
        int usedByOtherPlayer = 0;
        for (int j = 0; j < current_answer; j++) {
            if (j != i && strcmp(AnswerArray[j].word, AnswerArray[i].word) == 0) {  // is used by another player
                usedByOtherPlayer = 1;
                break;
            }
        }

        if (exist == 1) {
            if (usedByOtherPlayer == 1) {
                score[AnswerArray[i].player] += 1;
            }
            if(usedByOtherPlayer == 0) {
                score[AnswerArray[i].player] += 2;
            }
        }


        else {
            // word is unknow so ask player by the vote function
            vote(AnswerArray, i, score, playerNumber, usedByOtherPlayer, alreadyAccepted);
        }
    }

    free(words);

}


void category_choice(int difficulty, int category, char list[][MAX_LENGTH]) {

    // Get all the categories for the corresponding difficulty
    char categories[MAX_CATEGORIES][MAX_LENGTH];
    gameMode(difficulty, categories);

    int random_category;
    int memory[category];

    for (int i = 0; i < category; i++) {
        int is_unique;

        do {
            is_unique = 1;
            random_category = rand() % MAX_CATEGORIES;

            // Check if the random category number is already in memory
            for (int j = 0; j < i; j++) {
                if (memory[j] == random_category) {
                    is_unique = 0;
                    break;
                }
            }
        } while (!is_unique);

        memory[i] = random_category;
    }

    // Copying the category into the final list
    for (int i = 0; i < category; i++) {
        strcpy(list[i], categories[memory[i]]);
    }
}
