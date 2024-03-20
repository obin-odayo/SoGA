/*
	CCPROG2 MP2 SOURCE CODE

    Do not forget to encode your name, section and date of submission.
    
    LASTNAME1, FIRSTNAME1:                               SECTION1:
    LASTNAME2, FIRSTNAME2:                               SECTION2:
    
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

// include your own header file
#include "LASTNAME1_LASTNAME2.h"   

/* Do NOT include other header files. */ 

/* 
	HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or CAUSE POINT DEDUCTIONS!
	
	1. You must apply struct data type in MP Part 2 (MP2).
       a. Declare a typedef in your header file (LASTNAME1_LASTNAME2.h) for a user-defined struct data type
          whose members will be used to store ONE row of SoGA data values.  This struct data type should NOT  
          have any array member except for the territory name (in other words, you have to specify 
          each risk factor as a structure member explicitly).      
       b. Use the typedef alias (that you declared in your header file) for a 1D array of struct to 
          represent and store ALL rows of the SoGA data values read from the SoGA_DATASET.txt file.
       c. Use the typedef alias as well to specify all struct or struct pointer 
          variables/pointers/parameters/function return type that you need in your function definitions.
       d. At least one function definition should use a dereference operator (denoted by an asterisk 
          symbol *) together with a structure member access operator (denoted by a dot symbol . ) 
          to access a structure member indirectly via a structure pointer variable.
       e. At least one other function definition should use a structure pointer operator (->) to 
          access a structure member indirectly via a structure pointer variable.
    2. Document your codes with SENSIBLE comments.
    3. Use double data type (not float) for all floating point values/variables/functions/return type.
    4. Do NOT use any global variables.
    5. Do NOT call printf() except inside the main() function.
    6. Do NOT use file processing functions such as fopen(), fclose(), etc.
	7. Do NOT use library functions that were NOT discussed in our class.
*/



/*
    ALL typedef declarations must be encoded in your header file.  
    All #define must be encoded in your header file.
    Do NOT place them in this file.
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

  


int
main()
{
    /* Declare your own local variables. Describe the purpose of your local variables. */
    
    
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