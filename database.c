#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "database.h"

void gameMode(int difficulty, char categories[MAX_CATEGORIES][MAX_LENGTH]) {
    FILE *file = fopen("gameMode.csv", "r");
    if (!file) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }
    int gameMode = 1;
    char line[DEFAULT_SIZE];
    fgets(line, sizeof(line), file); // Skip header

    // Read each subsequent line in the CSV file
    while (fgets(line, sizeof(line), file)) {
        // Tokenize the line to get the difficulty level
        char *token = strtok(line, ",");

        // If the current game mode matches the desired difficulty level
        if (gameMode == difficulty) {
            int i = 0;
            while ((token = strtok(NULL, ",")) && i < MAX_CATEGORIES) {
                // Remove leading and trailing whitespace from the token
                trim(token);

                // Copy the category name into the categories array
                strncpy(categories[i], token, MAX_LENGTH - 1);

                // Ensure the string is null-terminated
                categories[i][MAX_LENGTH - 1] = '\0';

                trim(categories[i]);
                // Move to the next category
                i++;
            }
            gameMode++;
        }
        else {
            gameMode++;
        }
    }

    fclose(file);
}

void parseWordsFromFile(char letter, Term **words, int *wordCount) {

    FILE *file = fopen("words.csv", "r");
    if (!file) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    char line[DEFAULT_SIZE];
    int lines = 0;

    // Count the number of lines (excluding the header)
    fgets(line, sizeof(line), file); // Skip the header
    while (fgets(line, sizeof(line), file)) {
        lines++;
    }

    // Allocate memory for the words
    *words = malloc(sizeof(Term) * lines);
    if (*words == NULL) {
        perror("Cannot allocate memory");
        exit(EXIT_FAILURE);
    }

    // Reset the file pointer to the beginning and skip the header again
    rewind(file);
    fgets(line, sizeof(line), file); // Skip the header

    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        // Temporary variable to hold the current word
        Term currentWord;

        // Tokenize the line to extract the ID
        char *token = strtok(line, ",");
        currentWord.id = atoi(token);

        // Pass to the first letter
        token = strtok(NULL, ",");

        // Check if the word starts with the specified letter
        if(letter == *token) {

            // Tokenize to get the category
            token = strtok(NULL, ",");
            token[strcspn(token, "\n")] = 0;
            strcpy(currentWord.category, token);

            // Tokenize to get the actual word
            token = strtok(NULL, ",");
            token[strcspn(token, "\n")] = 0;
            strcpy(currentWord.word, token);

            // Store the current word in the words array
            (*words)[count++] = currentWord;

        }
    }

    *wordCount = count;
    fclose(file);
}

void addWordToFile(char word[], char category[]) {
    int category_exist = 0;
    trim(category);

    // Check if the category exists
    for (int i = 1; i <= 3; i++) {
        // Get the list of categories for the given difficulty level
        char categories[MAX_CATEGORIES][MAX_LENGTH];
        gameMode(i, categories);
        for (int j = 0; j < MAX_CATEGORIES; ++j) {
            // Remove leading and trailing whitespace from each category
            trim(categories[j]);
            if (strcmp(categories[j], category) == 0) {
                // Set flag if the category matches
                category_exist = 1;
            }
        }
    }

    if (category_exist) {
        // Open the file in append mode
        FILE *file = fopen("words.csv", "a+");
        if (!file) {
            perror("Cannot open file");
            exit(EXIT_FAILURE);
        }

        // Move the file pointer to the beginning of the file to read lines
        fseek(file, 0, SEEK_SET);

        char line[DEFAULT_SIZE];
        int lastId = 0;

        // Find the last ID in the file
        while (fgets(line, sizeof(line), file)) {
            char *token = strtok(line, ",");
            if (token != NULL) {
                // Convert the token to an integer
                lastId = atoi(token);
            }
        }

        int newId = lastId + 1;

        // Add the new word to the file
        fprintf(file, "\n%d,%c,%s,%s", newId, word[0], category, word);

        fclose(file);
    } else {
        printf("La categorie entree est fausse !\n");
    }
}


void deleteWordFromFile(int id) {
    FILE *file = fopen("words.csv", "r");
    if (!file) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    // Open a temporary file in write mode
    FILE *tempFile = fopen("temp.csv", "w");
    if (!tempFile) {
        perror("Cannot open temporary file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char line[DEFAULT_SIZE];
    // Read the header
    char *header = fgets(line, sizeof(line), file);

    if (header != NULL) {
        // Write the header to the temp file
        fprintf(tempFile, "%s", header);
    }

    // Read each line from the original file
    while (fgets(line, sizeof(line), file)) {
        // Create a copy of the line for tokenization
        char *lineCopy = strdup(line);
        char *token = strtok(line, ",");

        if (token != NULL) {
            int currentId = atoi(token);
            if (currentId != id) {
                // Write the line to the temp file if the ID does not match
                fprintf(tempFile, "%s", lineCopy);
            }
        }
        // Free the memory allocated by strdup
        free(lineCopy);
    }

    // Free the memory allocated by strdup
    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    // Delete the original file
    if (remove("words.csv") != 0) {
        perror("Error deleting the original file");
        exit(EXIT_FAILURE);
    }
    // Rename the temporary file to the original file's name
    if (rename("temp.csv", "words.csv") != 0) {
        perror("Error renaming the temporary file");
        exit(EXIT_FAILURE);
    }
}

void updateWordFromFile(int id, const char *word) {

    FILE *file = fopen("words.csv", "r");
    if (!file) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    // Open a temporary file in write mode
    FILE *tempFile = fopen("temp.csv", "w");
    if (!tempFile) {
        perror("Cannot open temporary file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char line[DEFAULT_SIZE];
    // Read the header line from the original file
    char *header = fgets(line, sizeof(line), file);

    if (header != NULL) {
        fprintf(tempFile, "%s", header);  // Write the header to the temp file
    }

    // Read each line from the original file
    while (fgets(line, sizeof(line), file)) {
        // Create a copy of the line for tokenization
        char *lineCopy = strdup(line);
        char *token = strtok(line, ",");

        if (token != NULL) {
            int currentId = atoi(token);
            // If the current ID does not match the ID to be updated, write the line to the temporary file
            if (currentId != id) {
                fprintf(tempFile, "%s", lineCopy);
            } else {
                // Write the updated line with new values
                token = strtok(NULL, ",");

                token = strtok(NULL, ",");

                // Write the new word details to the temporary file
                fprintf(tempFile, "%d,%c,%s,%s\n", id, word[0], token, word);
            }
        }
        free(lineCopy);  // Free the memory allocated by strdup
    }

    // Close both the original and temporary files
    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    // Delete the original file
    if (remove("words.csv") != 0) {
        perror("Error deleting the original file");
        exit(EXIT_FAILURE);
    }
    // Rename the temporary file to the original file's name
    if (rename("temp.csv", "words.csv") != 0) {
        perror("Error renaming the temporary file");
        exit(EXIT_FAILURE);
    }
}

void trim(char *str) {
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    // All spaces?
    if(*str == 0) {
        return;
    }

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = 0;
}