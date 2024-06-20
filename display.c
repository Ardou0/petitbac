//
// Created by cjournet on 15/05/2024.
//
#include "database.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void displayWelcomeScreen() {
    printf("\n******************************************\n");
    printf("*                                        *\n");
    printf("*   Bienvenue dans le jeu du petit bac   *\n");
    printf("*                                        *\n");
    printf("******************************************\n\n");
}

int main_menu(){
    int response;
        printf("============================\n1) Demarrer une partie\n2) Editer le dictionnaire\n3) Quitter\n============================\n Que voulez-vous faire? ");
        scanf("%d",&response);
    while (response<1 || response>3){
        printf("============================\nAttention veuillez choisir entre 1 et 3\n");
        printf("============================\n1) Demarrer une partie\n2) Editer le dictionnaire\n3) Quitter\n============================\n Que voulez-vous faire? ");
        scanf("%d",&response);
    }
    return response;
}

int dictionary_menu(){
    int choice;
    printf("============================\n1) Ajouter\n2) Modifier\n3) Supprimer\n4) Retour\n============================\n Que voulez-vous faire? ");
    scanf("%d",&choice);
    while (choice<1 || choice>4){
        printf("============================\nAttention veuillez choisir entre 1 et 4\n");
        printf("============================\n1) Ajouter\n2) Modifier\n3) Supprimer\n4) Retour\n============================\n Que voulez-vous faire? ");
        scanf("%d",&choice);
    }
    return choice;
}

void word_display(){
    char letter=97;
    printf("============================\n");

    // For each ASCII lowercase letter
    while (letter>96 && letter<123){

        // Initialize the words list
        Term *words = NULL;
        int wordCount = 0;
        parseWordsFromFile(letter, &words, &wordCount);

        // Display the word list
        for (int i = 0; i < wordCount; i++) {
            printf("Mot: %s, Categorie: %s, Numero: %d\n", words[i].word, words[i].category, words[i].id);
        }

        free(words);
        letter=letter+1;
    }
}

int player_number(char player_names[4][WORD_LENGTH]){
    int player;
    printf("============================\nCombien de joueurs etes-vous?(2 a 4) ");
    scanf("%d",&player);
    while (player<1 || player>4){
        printf("Attention le jeu se joue entre 2 et 4\n============================\n");
        printf("============================\nCombien de joueurs etes-vous?(2 a 4) ");
        scanf("%d",&player);
    }
    printf("============================\nQui sont-ils ?\n============================");
    for (int i = 0; i < player; ++i) {
        printf("\nJoueur %d)", i+1);
        scanf(" %s", &player_names[i]);
    }
    return player;
}

int category_number(){
    int categories;
    printf("============================\nAvec combien de categories voulez-vous jouer (4 a 8)? ");
    scanf("%d",&categories);
    while (categories<4 || categories>8){
        printf("Attention vous devez jouer avec 4 a 8 categories\n============================\n");
        printf("============================\nAvec combien de categories voulez-vous jouer (4 a 8)? ");
        scanf("%d",&categories);
    }
    return categories;
}


int difficulty(){
    int level;
    printf("============================\nAvec quel niveau de difficulte voulez-vous jouer (1=Facile; 2=Moyen; 3=Difficile)? ");
    scanf("%d",&level);
    while (level<1 || level>3){
        printf("============================\nAttention vous devez selectionner 1 ou 2 ou 3 selon le niveau de difficulte voulu\n");
        printf("============================\nAvec quel niveau de difficulte voulez-vous jouer (1=Facile; 2=Moyen; 3=Difficile)? ");
        scanf("%d",&level);
    }
    return level;
}


int timer() {
    int duration;
    printf("============================\nCombien de temps joue chaque joueur (minimum 20 secondes)? ");
    scanf("%d", &duration);
    while (duration < 20) {
        printf("Attention une partie dure au minimum 20 secondes\n============================\n");
        printf("============================\nCombien de temps joue chaque joueur (minimum 20 secondes)?");
        scanf("%d", &duration);

    }
    return duration;
}

void player_menu(char definitive_categories[][MAX_LENGTH], int numberCategories, Answer AnswerArray[], int *current_answer, int player, char letter) {

    printf("============================\n");

    // Displaying all the chosen categories by order
    for (int i = 0; i < numberCategories; i++) {
        printf("%d) %s\n", i + 1, definitive_categories[i]);
    }
    printf("============================\nVeuillez choisir la categorie que vous remplir (rentrez le chiffre equivalent) ? ");

    int player_choice;
    scanf("%d", &player_choice);

    while (player_choice > numberCategories || player_choice <= 0) {
        printf("Attention ce numero de categorie n'existe pas!\nRentrez le chiffre equivalent a la categorie voulue: ");
        scanf("%d", &player_choice);
    }

    player_choice = player_choice - 1;
    printf("============================\n%s :\n", definitive_categories[player_choice]);

    // Get the answer
    char temporaryword[MAX_LENGTH];
    scanf(" %s", temporaryword);

    // Process the answer if the first letter of the answer doesn't match the game letter
    while (temporaryword[0] != letter && temporaryword[0] != letter - 32) {
        printf("Votre premiere lettre doit etre %c, veuillez reecrire votre mot: ", letter);
        scanf(" %s", temporaryword);
    }

    int character = 0;

    // Parse all the word into lowercase
    while (temporaryword[character] != '\0') {
        temporaryword[character] = tolower(temporaryword[character]);
        character++;
    }

    // If the category already been filled then upadte the word in
    int edited = 0;
    for (int i = 0; i < *current_answer; ++i) {
        if (strcmp(AnswerArray[i].category, definitive_categories[player_choice]) == 0 && AnswerArray[i].player == player) {
            strcpy(AnswerArray[i].word, temporaryword);
            edited = 1;
            break;
        }
    }

    // if the answer for this category is new then create a new answer
    if (edited == 0) {
        strcpy(AnswerArray[*current_answer].word, temporaryword);
        AnswerArray[*current_answer].player = player;
        strcpy(AnswerArray[*current_answer].category, definitive_categories[player_choice]);
        (*current_answer)++;
    }
}


void vote(Answer AnswerArray[], int current_answer, int score[], int playerNumber, int usedByOtherPlayer, char alreadyAccepted[][WORD_LENGTH]) {

    int response[playerNumber];
    int isAccepted=0, alreadyDone = 0;

    // Check if the word that is going to be process has already been processed
    for (int i = 0; i < current_answer; ++i) {
        if (strcmp(alreadyAccepted[i], AnswerArray[current_answer].word) == 0) {
            alreadyDone = 1;
        }
    }
    if(alreadyDone == 0) {
        printf("Le joueur %d a entre le mot \"%s\" pour la categorie %s\n============================\n", AnswerArray[current_answer].player+1,AnswerArray[current_answer].word,AnswerArray[current_answer].category);

        for (int k = 0; k < playerNumber; ++k) {
            // Permit for the rest of the players to vote about a player response
            if(k != AnswerArray[current_answer].player) {
                printf("Joueur %d, acceptez vous le mot ?\n1) Oui\n2) Non\n", k+1);
                scanf("%d", &response[k]);
                while(response[k] < 1 || response[k] > 2) {
                    printf("Entrez 1 ou 2");
                    scanf("%d", &response[k]);
                }
                if (response[k] == 1) {
                    isAccepted = 1;
                    strcpy(alreadyAccepted[current_answer], AnswerArray[current_answer].word);
                    addWordToFile(AnswerArray[current_answer].word, AnswerArray[current_answer].category);
                }

            }
        }



        // Scoring the players by their answers
        for (int k = 0; k < playerNumber; ++k) {

            // If someone disagree with the word even if it has been accepted then remove 1 point
            if (isAccepted == 1 && k != AnswerArray[current_answer].player) {
                if (response[k] == 2) {
                    score[k] -= 1;
                }
            }

            // if the word is accepted then add the corresponding points
            if (isAccepted == 1 && k == AnswerArray[current_answer].player) {

                if (usedByOtherPlayer == 1) {
                    score[AnswerArray[current_answer].player] += 1;
                }
                if(usedByOtherPlayer == 0) {
                    score[AnswerArray[current_answer].player] += 2;
                }
            }
        }

    }
    else {
        // the word already been processed just give the point
        score[AnswerArray[current_answer].player] += 1;
    }


}

