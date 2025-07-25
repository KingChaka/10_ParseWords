#ifdef _WIN32
#include <conio.h>
#endif

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define WRD_SIZE_LIMIT 20									// here so word[] can be initialized w/ a variable with gcc compiler

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
 * Purpose:         This program prompts for a number of students to be organized into groups.
 *                  These students, numbered  1 to n, will be randomly assigned into groups of 3,
 *                  with no group have having more than 3 or fewer than 2 students.
 *
 *                  The groups and each member will then be display at the terminal.
 *
 * Program name:    BCAssignGroups.c
 *
 * Invocation:      ./a.out on Unix/Linux/MacOS
 *                    a.exe on Windows
 *
 * Variables:       const short int MAX_GRPS    - CONSTANT; the max number of groups allowed
 *                  const short int GRP_SIZE    - CONSTANT; the max number of group members allowed
 *                  const short int LOOP_MIN    - CONSTANT; used to control the number of loops
 *                  const short int GRP_COL     - CONSTANT; 2D array's column index for group number
 *                  const short int ATMPTS      - CONSTANT; used to limit user imputs attempts
 *                  const short int NOERR       - CONSTANT; main() return value; 0 is no errors
 *
 *                  short int Groups[][]        - 2D array for holding group and student numbers
 *                  short int RandomNum         - A number generated psuedo-randomly
 *                  short int baseLoop          - Corresponds to number of groups not needing special arrangement
 *                  short int grpType           - Determines display arrangement for the last two groups
 *                  short int Snum              - The number of students being grouped
 *                  short int Oops              - The current number of failed user inputs
 *
 *                  bool UsedNum[]              - Tracks which student numbers are used to avoid repeats
 *                  bool debug                  - Used to add more prints to console for debugging
 *
 * Functions:   GenUniqRanNum(min, max, arr[])  - used to generate random numbers w/o repeats
 *
 * Written by:      Doc G.  3/20/23
 *
 * Modifications:   Added print of current time                                 8/5/23  Doc
 *                  Cleaned up some messy code                                  5/20/25  Doc
 *                  Deleted print of current time and many other comments       Brandon Crenshaw  7/24/2025
 *                  Turned existing prints into debug statements                Brandon Crenshaw  7/24/2025
 *                  Added display code for the randomly generated data          Brandon Crenshaw  7/24/2025
 *
 * Special notes:   None
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

    /* CONSTANTS*/
    const char FILENAME[] = "FinalExamTextToParse.txt";
	const char END_OF_STR = '\0';
	const char NBSP = 160;									// "non-breaking space"; whitespace not recognized by isspace().
	
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


    /* LOAD FILE TO MEMORY * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
			printf("%c-",lowerChar);
			if(isDelimiter)
			{
				printf("\n");
			}
		}
		
		if(isValid)
        {
            word[index++] = lowerChar;
        }
        
        if(isSkippable)
        {
            goto NEXT;
        }
        
        if(isDelimiter)
		{
			word[index] = '\0';
			printf("%s\n",word);
			
			if(debug)
			{
				printf("\n");

			}
			
			index = 0;
			for(short int i = 0; i < (WRD_SIZE_LIMIT + 1); i++)
			{
				word[i]='\0';
			}
		}
        
        if(isEnd)
		{
			word[index++] = '\0';
			printf("%s\n",word);
		}
        
    }                                              			// End of file-to-array
    while(isEnd == false);
    
    fclose(sourceFile);

EOP:
    return (rtnCode);
}                                     						// End of main()


