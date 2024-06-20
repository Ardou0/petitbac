#define MAX_CATEGORIES 8
#define MAX_LENGTH 150
#define DEFAULT_SIZE 1024
#define WORD_LENGTH 50

typedef struct {
    int id;
    char category[WORD_LENGTH];
    char word[WORD_LENGTH];

} Term;

/**
 * Get all the words from the file starting with the corresponding letter
 * @param the letter that the words will start with
 * @param The array of Term struct that will contain every word
 * @param the number of words corresponding
 */
void parseWordsFromFile(char, Term **, int *);

/**
 * Get all the categories for a corresponding difficulty
 * @param the difficulty
 * @param Table that will contain all the categories corresponding
 */
void gameMode(int , char [MAX_CATEGORIES][MAX_LENGTH]);

/**
 * Add a new occurence to the dictonnary
 * @param the word we want to add
 * @param the category associeted
 */
void addWordToFile(char [], char []);

/**
 * Allow the deleting of an occurence
 * @param the id of the word we want to delete
 */
void deleteWordFromFile(int);

/**
 * Allow the updating of an existing word
 * @param the id we want to update
 * @param the new word
 */
void updateWordFromFile(int, const char *);

/**
 * Clear all the spaces character in a string
 * @param the string we want to trim
 */
void trim(char *);