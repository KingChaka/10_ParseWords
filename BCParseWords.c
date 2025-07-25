#ifdef _WIN32
#include <conio.h>
#endif

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define WRD_SIZE_LIMIT 20                                   // here so word[] can be initialized w/ a variable when using gcc compiler

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Purpose:  Clear the screen in either Windows or Unix
 * Function Name:  clearScreen
 * Invocation:  clearScreen()
 * Variables: None
 * Functions called:  None
 * Written by Doc G.
 * Date: 2/19/23
 * Modifications:   Added flower box 2/17/25
 *                  Added "smart" include 5/28/25
 *                  stdlib is need for the WIN32 clear screen too
 *                      so preprocessor IF cmd changed to accomodate.
 *                      -- Brandon Crenshaw 06/27/25
 *
 * Special Notes:  This code will include the correct library
 *                 for either Windows or Unix.  See #ifdef
 *                 above the flower box.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void clearScreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}



/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

int main()
{
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Purpose:         This program takes an ascii text file and prints each word to its own line,
 *                  less any punctuation or numbers.
 *
 * Program name:    BCParseWords.c
 *
 * Invocation:      ./a.out on Unix/Linux/MacOS
 *                    a.exe on Windows
 *
 * Variables:       const char FILENAME[]       - CONSTANT; the file to be parse
 *                  const char END_OF_STR       - CONSTANT; null character signifying the end of a string
 *                  const char NBSP             - CONSTANT; "non-breaking space" character; not recognized by isspace().
 *                  const short int READERR     - CONSTANT; main() error code for failure to open file.
 *                  const short int NOERR       - CONSTANT; main() error code for no errors.
 *
 *                  char word[ ]                - cString to hold parsed word
 *                  char lowerChar              - case corrected character read from the file
 *                  char readChar               - character read from the file
 *
 *                  short int rtnCode           - variable holding the
 *                  short int index             - used to index the 'word' string (character array)
 *
 *                  bool isDelimiter            - indicates if the current character is whitespace
 *                  bool isSkippable            - indicates if the current character is punctuation
 *                  bool isValid                - indicates if the current character is a letter
 *                  bool isEnd                  - indicates if at the end of the file stream
 *                  bool debug
 *
 *                  FILE *sourceFile            - pointer to the file being read
 *
 *                  bool debug                  - Used to add more prints to console for debugging
 *
 * Functions:       clearScreen(void)           - used to clear the prompt; cross-platform
 *
 * Written by:      Brandon Crenshaw  25-Jul-2025
 *
 * Modifications:   None
 *
 * Special notes:   word size is limited to 20 characters. Numbers are ignored.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

    /* CONSTANTS*/
    const char FILENAME[] = "FinalExamTextToParse.txt";
    const char END_OF_STR = '\0';
    const char NBSP = 160;                                  // "non-breaking space"; whitespace not recognized by isspace().

    const short int READERR  = 1;
    const short int NOERR    = 0;


    /* VARIABLES */
    char word[WRD_SIZE_LIMIT + 1] = { };
    char lowerChar = END_OF_STR;
    char readChar = END_OF_STR;

    short int rtnCode = NOERR;
    short int index = 0;

    bool isDelimiter = false;
    bool isSkippable = false;
    bool isValid = false;
    bool isEnd = false;
    bool debug = false;
        // bool debug = true;

    FILE *sourceFile;



    clearScreen();
    sourceFile = fopen(FILENAME, "r");

    if(sourceFile == NULL)
    {
        printf("\tERROR: '%s' failed to open.\n",FILENAME);
        rtnCode = READERR;
        goto EOP;
    }                                                       // End of Read File Error

    index = 0;

    do
    {

NEXT:
        readChar = fgetc(sourceFile);
        lowerChar = tolower(readChar);

        isEnd = (lowerChar == EOF);
        isDelimiter = isspace(lowerChar) || (lowerChar == NBSP);
        isValid = isalpha(lowerChar);
        isSkippable = ispunct(lowerChar);

        if(debug)
        {
            printf("[%c]",lowerChar);
            if(isDelimiter)
            {
                printf("\n");
            }                                               // close if in debug: newline for new word
        }                                                   // close debug statement

        if(isValid)
        {
            word[index++] = lowerChar;
        }                                                   // close isValid condition

        if(isSkippable)
        {
            goto NEXT;
        }                                                   // close isSkippable (punctuation) condition

        if(isDelimiter)
        {
            if(index == 0)
            {
                goto NEXT;
            }                                               // closes repeated delimiters condition

            word[index] = END_OF_STR;
            printf("%s\n",word);

            if(debug)
            {
                printf("\n");

            }                                               // close debug statement

            index = 0;
            for(short int i = 0; i < (WRD_SIZE_LIMIT + 1); i++)
            {
                word[i] = END_OF_STR;
            }                                               // close add end of string char code
        }                                                   // close isDelimitter condition

        if(isEnd)
        {
            word[index] = END_OF_STR;
            printf("%s\n",word);
        }                                                   // End of isEnd condition
    }                                                       // End of do-while block
    while(isEnd == false);                                  // do while conditional

    fclose(sourceFile);

EOP:
    return (rtnCode);
}                                                           // End of main()


