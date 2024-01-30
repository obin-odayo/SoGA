/*
	CCPROG2 MP1 SOURCE CODE

    Do not forget to encode your name, section and date of submission.
    
    LASTNAME1, FIRSTNAME1: GANITUEN, ZHEAN ROBBY             SECTION1: S11A
    
    DATE SUBMITTED     :
		
	Rename this file using your last names in alphabetical order, for example CRUZ_TAN.c
		
	Make sure to compile your C source code with a -Wall directive.  
	   Example: CCPROG2> gcc -Wall LASTNAME1_LASTNAME2.c
	   
	Fix all warnings.  Do NOT run the program if you still have a warning.  You must have
	0 error, 0 warning before running the program.
	   
	Run the resulting a.exe file in the command line with input and output (I/O) redirection.
	   Example: a < SoGA_DATASET.TXT > OUTPUT_LASTNAME1_LASTNAME2.TXT

*/

#include <stdio.h>
#include <string.h>
/* Do NOT include other header files. */

#include "SoGA.h"

/* 
	HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or CAUSE POINT DEDUCTIONS!
	
	1. You must apply arrays and strings in MP Part 1 (MP1).
    2. Document your codes with SENSIBLE comments.
    3. Use double data type (not float) for all floating point 
       values/variables/functions/return type
    4. Do NOT use any global variables.
    5. Do NOT call printf() except inside the main() function.
    6. Do NOT use the following yet this MP.
        a. struct data type
	    b. file processing functions such as fopen(), fclose(), etc.
	7. Do NOT use library functions that were NOT discussed in our class.
*/


/*
    You may declare any typedef that you need below this comment.
*/



/*
    Define any function that you need below this comment.  

    The following should be included as comments and appear BEFORE EACH function definition:
       a. Purpose: describe succintly what the function is supposed to accomplish.
       b. Parameters: describe succintly the nature/purpose of each parameter.
       c. Return type: if the function is not void, describe succintly what it will return as a result.          

    For functions that serve as answers to the questions, include the following as comments
    BEFORE the function definition itself:
       a. Question number, and the actual question.
       b. Thereafter, type the answer number, and the corresponding expected answer.
    
    For example: 
      Q1:  Which country has the lowest baseline life expectancy?
      A1:  Lesotho

    Document the body of the function by including comments alongside codes that you think
    may not be easy to understand to the person reading the codes. 
*/

/*
questionOne
    purpose: get the top nNumCountries of nCategory and return the output (which is a string) to a pointer sOutput.

    params:
    - nNumCountries [int]: number of countries which have the highest value for the category.
    - nCategory [int]: the category number.
    - *sOutput [ptr, string]: the output of the function.

*/
char *questionOne(int nNumCountries, int nCategory, char *sOutput){

    /* Personal Notes:
        - Always exclude GLOBAL from countrues!
    */

    

    strcpy(sOutput, "Hello World");
    return sOutput;
}  

int
main()
{
    /* Declare your own local variables. Describe the purpose of your local variables. */
    
    /* Miscelaneous variables*/

    /* this long variable is for showing the categories to the user
    to make it easier for them to pick one */
    char sShowCategories[480] = "1: Baseline Life Expectancy\n2: Air Pollution\n3: Ambient PM\n4: Ozone\n5: Household AP\n6: Environmental Occupational Hazard\n7: Occupational Hazard\n8: Unsafe Hand Washing\n9: Metabolic Syndrome\n10: Deitary\n11: High Fasting Plasma Glucose/Sugar\n12: Tobacco\n13: Smoking\n14: Secondhand Smoke\n15: Unsafe Sex";
    
    /* Variables for question 1 */
    int nNumCountries; // how many countries the question will print.
    int nCategory; // the category the user chose for question 1.
    char sOneOutput[640]; // the output of question one.

    printf("Question 1. What are the names and values of the top `num` countries with the highest `category`?\n");


    // get the user inputs for the parameters of questionOne();

    printf("How many countries do you want to print?\n>. (int) ");
    scanf("%d", &nNumCountries);

    // print out the categories for the user.
    printf("\n=====\n%s\n=====\n", sShowCategories); 
    printf("What category do you want to use?\n>. (int) ");
    scanf("%d", &nCategory);

    // execute the function and print the result out.    
    questionOne(nNumCountries, nCategory, sOneOutput);
    
    printf("%s", sOneOutput);

    /* 
       Call the function that answers a question. Thereafter, use printf() to print the question 
       and the corresponding answer.  For example:

       expectancy = Q1_Answer(territory, param_x, param_y); // where expectancy, territory, param_x and param_y are local variables.

       printf("Q1: Which territory has the lowest baseline life expectancy?\n");
       printf("A1: %s %lf\n", territory, expectancy);       

       TEST CASES HARD REQUIREMENTS:
       You should have multiple test cases, i.e., functions calls to answer those 
       Questions that involve parameter(s).  There should be function calls with
       different actual paramete values.  For questions that require searching
       (linear or binary search), there should be a test case, i.e., a  function 
       call with a search key parameter that does not exist, i.e., NOT FOUND scenario.
    */

	return 0;
}
