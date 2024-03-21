/*
   CCPROG2 MP2 SOURCE CODE

    Do not forget to encode your name, section and date of submission.

    LASTNAME1, FIRSTNAME1: GANITUEN, ZHEAN ROBBY L.      SECTION1: S11B

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
#include "GANITUEN.h"

/* Do NOT include other header files. */

/*
   HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or CAUSE POINT DEDUCTIONS!

   1. You must apply struct data type in MP Part 2 (MP2).
       / a. Declare a typedef in your header file (LASTNAME1_LASTNAME2.h) for a user-defined struct data type
          whose members will be used to store ONE row of SoGA data values.  This struct data type should NOT
          have any array member except for the territory name (in other words, you have to specify
          each risk factor as a structure member explicitly).
       / b. Use the typedef alias (that you declared in your header file) for a 1D array of struct to
          represent and store ALL rows of the SoGA data values read from the SoGA_DATASET.txt file.
       c. Use the typedef alias as well to specify all struct or struct pointer
          variables/pointers/parameters/function return type that you need in your function definitions.
       d. At least one function definition should use a dereference operator (denoted by an asterisk
          symbol *) together with a structure member access operator (denoted by a dot symbol . )
          to access a structure member indirectly via a structure pointer variable.
       e. At least one other function definition should use a structure pointer operator ([i].) to
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

/* binSearch
   - does a binary search in the list of countries in the SOGA dataset

   @params:
   - countries [data *] : SOGA dataset
   - size [int] : number of countries
   - name [String (char[32])] : name to find, "target"

   @returns:
   - mid, if [name] is found
   - -1, if not found
*/
int binSearch(String countries[], int size, String name)
{
   int low = 0;
   int mid;
   int high = size - 1;

   while (low <= high)
   {
      mid = low + (high - low) / 2;

      if (!strcmp(name, countries[mid]))
         return mid;
      else if (strcmp(name, countries[mid]) < 0)
         high = mid + 1;
      else
         low = mid - 1;

      printf("\nDEBUG: %s\n", countries[mid]);
   }

   return -1; // not found
}

/* selSortString
   - Selection sort on a given String array

   @params:
   - arr [String (char[32])] : array of strings to be sorted
   - size [int] : size of arr

   @returns: none
*/
void selSortString(String arr[], int size)
{
   for (int i = 0; i < size - 1; i++)
   {
      int min = i;
      for (int j = i + 1; j < size; j++)
      {
         if (strcmp(arr[j], arr[min]) < 0)
         {
            min = j;
         }
      }
      if (min != i)
      {
         String temp;
         strcpy(temp, arr[i]);
         strcpy(arr[i], arr[min]);
         strcpy(arr[min], temp);
      }
   }
}

/* selSortDouble
   - Selection sort on a given Double array

   @params:
   - arr [String (char[32])] : array of strings to be sorted
   - size [int] : size of arr

   @returns: none
*/
void selSortDouble(double arr[], int size)
{
   for (int i = 0; i < size - 1; i++)
   {
      int min = i;
      for (int j = i + 1; j < size; j++)
      {
         if (arr[j] < arr[min])
         {
            min = j;
         }
      }
      if (min != i)
      {
         double temp = arr[i];
         arr[i] = arr[min];
         arr[min] = temp;
      }
   }
}

/* questionOne
   - function that answers question one. Question: "Which risk factor reduces the baseline life expectancy the
   most for <parameter_territory_name>? What is its value?"

   @params
   - countries[] [struct data] : an array of the SOGA data variables.
   - countryName [String (char[32])] : the country name that the user chose
   - output [double *] : pointer that will store the result
*/
void questionOne(data countries[], String countryName, double *output, String category)
{
   /*
      THIS SECTION USES LINEAR SEARCH!

      Algorithm for this question
      1. check if the country name exists (linear search)
      2. determine the max value of the data values of the categories of the country selected
   */
   int index;
   // PART 1. check if countryName exists in the list
   for (index = 0; index < COUNTRIES_COUNT; index++)
   {
      if (!strcmp(countryName, countries[index].name))
      {
         *output = 1; // change value to one, meaning "found"
         break;       // break the loop
      }
   }

   // PART 2.
   // only run thsi section if the country is found
   if (*output)
   {
      // assume AIR is the max
      *output = countries[index].AIR;
      strcpy(category, "Air Pollution");

      // compare max to each category
      // if the value at that category is larger
      // let that be the max
      // at the end of this, *output should have the maximum value
      if (*output < countries[index].APM)
      {
         *output = countries[index].APM;
         strcpy(category, "Ambient PM");
      }
      if (*output < countries[index].OZN)
      {
         *output = countries[index].OZN;
         strcpy(category, "Ozone");
      }
      if (*output < countries[index].HAP)
      {
         *output = countries[index].HAP;
         strcpy(category, "Household AP");
      }
      if (*output < countries[index].EOH)
      {
         *output = countries[index].EOH;
         strcpy(category, "Environmental Occupational Hazards");
      }
      if (*output < countries[index].OCC)
      {
         *output = countries[index].OCC;
         strcpy(category, "Occupational Hazard");
      }
      if (*output < countries[index].UHW)
      {
         *output = countries[index].UHW;
         strcpy(category, "Unsafe Handwashing");
      }
      if (*output < countries[index].MTB)
      {
         *output = countries[index].MTB;
         strcpy(category, "Metabolic Syndrome");
      }
      if (*output < countries[index].DTY)
      {
         *output = countries[index].DTY;
         strcpy(category, "Dietary");
      }
      if (*output < countries[index].HFP)
      {
         *output = countries[index].HFP;
         strcpy(category, "High Fasting Plasma Glucose");
      }
      if (*output < countries[index].TBC)
      {
         *output = countries[index].TBC;
         strcpy(category, "Tobacco");
      }
      if (*output < countries[index].SMK)
      {
         *output = countries[index].SMK;
         strcpy(category, "Smoking");
      }
      if (*output < countries[index].SSK)
      {
         *output = countries[index].SSK;
         strcpy(category, "Secondhand Smoke");
      }
      if (*output < countries[index].SEX)
      {
         *output = countries[index].SEX;
         strcpy(category, "Unsafe Sex");
      }
   }
}

/* questionTwo
   - function that answers question two. Question: What are the territories that have a risk factor value higher than <parameter_number_years> for Air Pollution in alphabetical order?

   @params
   - countries[] [struct data] : an array of the SOGA data variables.
   - name [String (char[32])] : the country name that the user chose.
   - output[] [String (char[32])] : the list of countries that will be used for the output
   - index [int] : the position of the selected country in output[]
*/
// void questionTwo(data countries[], String name, String output[], int *index, int *num){
//    /*
//    THIS QUESTION WILL USE:
//       SEARCH
//       SELECTION SORT

//    Algorithm for implementation
//    1. Search if the user selected country exists in the list (bin search)
//    2. Get the countries that have a Air Pollution than selected
//       2.1 Add these to output[]
//    3. Sort the elements of output[] (sel sort)
//    4. Determine the index of selected country in output[]
//    */

//    int found = -1;

//    // PART 1. find selected inthe list of countries
//    for (int index = 0; index < COUNTRIES_COUNT; index++)
//    {
//       if (!strcmp(name, countries[index].name))
//       {
//          found = 1;
//          break;
//       }
//    }

//    // do this so we wont waste time running the code if it isn't found
//    // in the first place
//    if (found == -1){
//       *index = -1; // index not found!
//    }
//    else {
//       // PART 2.
//       // get the Air Pollution value for country selected
//       int AP = countries[found].AIR;
//       *num = 0; // counts how many elements are in the array, initialize as 0

//       // set the first element of output be the selected country
//       // then increment num
//       strcpy(output[*num], countries[found].name);
//       (*num)++;

//       // iterate through the countries in the SOGA
//       // compare if the value of the country for AP is >country selected
//       for (int i = 0; i < COUNTRIES_COUNT; i++){
//          if(AP < countries[i].AIR){
//             strcpy(output[*num], countries[i].name);
//             (*num)++;
//          }
//       }

//       // PART 3. SELECTION SORT
//       selSort(output, *num);

//       // PART 4.
//       // find what the index of country selected is in output
//       for (int i = 0; i < *num; i++){
//          if(!strcmp(output[i], name)) *index = i;
//          break;
//       }
//    }
// }

/* questionFor

   @params:
   - countries [struct data] : SOGA dataset
   - category [String (char[32])] : category in SOGA dataset

   @returns
   - average of data values for the category
*/
questionFor(data *countries, String category)
{
   /*
   1. Verify if the category in SOGA dataset
   */

   // recall there are 14 categories
   for (int i = 0; i < 14; i++)
   {
   }
}

/* questionFiv

   @params:
   - countries [struct data] : SOGA dataset

   @returns:
   - min value of the sum of the categories in the SOGA dataset
*/
double questionFiv(data *countries, String category)
{
   /*
   ALGORITHM for question 5
   1. Calculate the sum per category
   2. Put these in an array
   3. Determine the min of the array
   */

   // These are the sum of the categories in the SOGA dataset
   double sums[14] = {0}; // init as 0
   // index = 0 is for BLE
   // .. = 1 is for AIR
   // and so on...

   // Recall that the number of columns is the number of countries
   for (int i = 0; i < COUNTRIES_COUNT; i++)
   {
      sums[0] += countries[i].BLE;
      sums[1] += countries[i].AIR;
      sums[2] += countries[i].OZN;
      sums[3] += countries[i].HAP;
      sums[4] += countries[i].EOH;
      sums[5] += countries[i].OCC;
      sums[6] += countries[i].UHW;
      sums[7] += countries[i].MTB;
      sums[8] += countries[i].DTY;
      sums[9] += countries[i].HFP;
      sums[10] += countries[i].TBC;
      sums[11] += countries[i].SMK;
      sums[12] += countries[i].SSK;
      sums[13] += countries[i].SEX;
   }

   double min = sums[0];
   strcpy(category, "Baseline Life Expectancy");

   if (min > sums[1])
   {
      min = sums[1];
      strcpy(category, "Air Pollution");
   }
   if (min > sums[2])
   {
      min = sums[2];
      strcpy(category, "Ambient PM");
   }
   if (min > sums[3])
   {
      min = sums[3];
      strcpy(category, "Ozone");
   }
   if (min > sums[4])
   {
      min = sums[4];
      strcpy(category, "Household AP");
   }
   if (min > sums[5])
   {
      min = sums[5];
      strcpy(category, "Environmental Occupational Hazards");
   }
   if (min > sums[6])
   {
      min = sums[6];
      strcpy(category, "Occupational Hazard");
   }
   if (min > sums[7])
   {
      min = sums[7];
      strcpy(category, "Unsafe Handwashing");
   }
   if (min > sums[8])
   {
      min = sums[8];
      strcpy(category, "Metabolic Syndrome");
   }
   if (min > sums[9])
   {
      min = sums[9];
      strcpy(category, "Dietary");
   }
   if (min > sums[10])
   {
      min = sums[10];
      strcpy(category, "High Fasting Plasma Glucose");
   }
   if (min > sums[11])
   {
      min = sums[11];
      strcpy(category, "Tobacco");
   }
   if (min > sums[12])
   {
      min = sums[12];
      strcpy(category, "Smoking");
   }
   if (min > sums[13])
   {
      min = sums[13];
      strcpy(category, "Secondhand Smoke");
   }
   if (min > sums[14])
   {
      min = sums[14];
      strcpy(category, "Unsafe Sex");
   }

   return min;
}

int main()
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

   data SOGA[COUNTRIES_COUNT];
   
   // read SOGA SOGA.txt
   for (int i = 0; i < COUNTRIES_COUNT; i++)
   {
      scanf("%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf ", SOGA[i].name, SOGA[i].AIR, SOGA[i].APM, SOGA[i].OZN, SOGA[i].HAP, SOGA[i].EOH, SOGA[i].OCC, SOGA[i].UHW, SOGA[i].MTB, SOGA[i].DTY, SOGA[i].HFP, SOGA[i].TBC, SOGA[i].SMK, SOGA[i].SSK, SOGA[i].SEX);
   }
   
   printf("%s %lf", SOGA[0].name, SOGA[0].AIR);

   // check if it's working
   // printf("DEBUG .. %s -- %lf\n", countries[0].name, countries[0].BLE);

   // =================== QUESTION ONE
   /*String Q1_name;
   double Q1_out1 = 0; // initialize as 0, assume that countryName is not found
   String Q1_out2;      // category name output

   printf("==========QUESTION 1==========\n");

   printf("Which risk factor reduces the baseline life expectancy the most for <parameter_territory_name>? What is its value?\n\n\n");

   printf("What territory/country name do you want to use?\n>. (string) ");
   scanf(" %s", Q1_name); // remember no & for strings!

   // call the function
   questionOne(countries, Q1_name, &Q1_out1, Q1_out2);

   // if it is found, then run normal output
   if (Q1_out1)
   {
      // format A1: <countryName> - categoryName (value)
      printf("\nA1: <%s> - %s (%lf)", Q1_name, Q1_out2, Q1_out1);
   }
   // if Q1_out1 is still 0, then country name is not found
   else{
      printf("\nERROR: country name [%s] not found in SOGA dataset!\n", Q1_name);
   }*/

   // =================== QUESTION TWO
   /*String Q2_name;
   String Q2_out[COUNTRIES_COUNT];
   int Q2_num, Q2_idx;


   printf("\n\n==========QUESTION 2==========\n");

   printf("What are the territories that have a risk factor value higher than <parameter_number_years> for Air Pollution in alphabetical order? Identify the index of <parameter_territory_name> if it is in the list; otherwise, return an invalid statement.\n\n\n");*/

   // printf("What territory/country name do you want to use?\n>. (string) ");
   // scanf(" %s", Q2_name); // remember no & for strings!

   // questionTwo(countries,Q2_name, Q2_out, &Q2_num, &Q2_idx);

   // if (Q2_idx == -1){
   //    printf("\nERROR: country name [%s] not found in SOGA dataset!\n", Q2_name);
   // } else{
   //    printf("\nA2: <%d>\n", Q2_idx);
   //    // print the list of countries
   //    for (int i = 0; i < Q2_num; i++){
   //       printf("%s\n", Q2_out[i]);
   //    }
   //    printf("\n");
   // }

   // =================== QUESTION TWO
   // printf("\n\n==========QUESTION 5==========\n");
   // String Q5_cat;
   // printf("Which risk factor has the lowest total sum value? What is its value?\n\n\n");

   // double Q5_out = questionFiv(countries, Q5_cat);

   // printf("\nA5: %s (%lf)", Q5_cat, Q5_out);
   // return 0;
}