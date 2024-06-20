//
// Created by cjournet on 22/05/2024.
//
#include "database.h"
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


void addword(){
    char word[WORD_LENGTH], category[WORD_LENGTH], i=0;
    printf("Quel mot voulez-vous ajouter :");
    scanf(" %s",&word);

    //Parsing the word in lowercase letter
    while (word[i]!='\0'){
        word[i]= tolower(word[i]);
        i=i+1;
    }
    printf("Dans quelle categorie %s est :", word);
    scanf(" %s",&category);

    // Finaly adding the word to the words.csv file
    addWordToFile(word, category);
}

void modification(){
    int id,i=0;
    char newword[WORD_LENGTH];
    printf("Quel est le numero de votre mot? ");
    scanf("%d",&id);
    printf("Veuillez reecrire le mot: ");
    scanf(" %s",&newword);

    //Parsing the word in lowercase letter
    while (newword[i]!='\0'){
        newword[i]= tolower(newword[i]);
        i=i+1;
    }

    // Update the processed word
    updateWordFromFile(id, newword);
}

void delete(){
    int id;
    printf("Quel est le numero du mot que vous voulez supprimer?");
    scanf("%d",&id);
    deleteWordFromFile(id);
}