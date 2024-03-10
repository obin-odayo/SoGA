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

/*
    TODO:
    - [DONE] Bug Fixes 
    - [DONE] Output Validation
    - [DONE] Cleaning
    - [DONE] Documentation
    - NOT FOUND scenario for functions with searches.
        - Q4
        - Q5
*/

#include <stdio.h>
#include <string.h>
/* Do NOT include other header files. */

/* Declared Constants */
#define COUNTRIES_COUNT 203 // in using COUNTRIES_COUNT, always subtract it by one since this includes "Global"
#define SOGA_COUNT 3045     // SOGA_COUNT / COUNTRIES_COUNT should always be 15

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

typedef char String[32];

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

/* swap

    purpose: swap the positions of x and y.

    params:
    - double *x [double *]: pointer for double x
    - double *y [double *]: pointer for double y

    return:
    - none
*/
void swap(double *x, double *y)
{
    double sorted = *x;
    *x = *y;
    *y = sorted;
}

/* removeGbl

    purpose: remove global column in SOGA array.

    params:
    - SOGA [double *]: original SOGA array.
    - noGlobal [double *]: new array where the SOGA without a global will be stored.

    return:
    - none
*/
void removeGbl(double SOGA[][SOGA_COUNT / COUNTRIES_COUNT], double noGlobal[][SOGA_COUNT / COUNTRIES_COUNT])
{
    int i, j; // used for for loops

    // loop from 0 to COUNTRIES_COUNT - 1 (see comment [1] in this function as to why that is)
    for (i = 0; i < COUNTRIES_COUNT - 1; i++)
    {
        for (j = 0; j < SOGA_COUNT / COUNTRIES_COUNT; j++)
        {
            // [1] notice here that SOGA[i + 1] is used.
            // Recall that COUNTRIES_COUNT = 203.
            // Therefore, at 201 this will become SOGA[201+1] or SOGA[202].

            // By doing this we don't assign SOGA[0][j] in the new array.
            // Hence removing all the data for global.
            noGlobal[i][j] = SOGA[i + 1][j];
        }
    }
}

/* filterCat

    purpose: create an array that only contains the variables of one category.

    params:
    - SOGA [double *]: original SOGA array.
    - filter [doube *]: SOGA array that only contains a specific category.
    - category [int]: category number

    return:
    - none
*/
void filterCat(double SOGA[][SOGA_COUNT / COUNTRIES_COUNT], double filter[COUNTRIES_COUNT], int category)
{
    int i;

    for (i = 0; i < COUNTRIES_COUNT; i++)
    {
        // Since the column of the category is a constant.
        // We only need to check all the rows of that specific category.
        filter[i] = SOGA[i][category];
    }
}

/* binSearch

    purpose: binary search.

    params:
    - array[] [double]: a 1d double array that will be binary searched.
    - size [int]: size of array.
    - target [double]: target of binary search.

    returns:
    - mid [int]: index of target in array.
    - -1 [int]: if index not found.

*/
int binSearch(double array[COUNTRIES_COUNT - 1], int size, double target)
{
    int low = 0;
    int mid;
    int high = size - 1;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (array[mid] == target)
            return mid;
        else if (array[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

/* questionOne

    purpose: get the top num of category and return the output (which is a string) to a pointer sOutput.

    params:
    - num [int]: number of countries which have the highest value for the category.
    - category [int]: the category number.
    - double SOGA[][] [double]: 2d array of SOGA dataset.
    - countries [String]: array containing all countries.
    - double topData[][] [double]: 2d array that contains the result.

    return:
    - none

*/
void questionOne(int num, int category, double SOGA[][SOGA_COUNT / COUNTRIES_COUNT], String countries[], double topData[num][2])
{

    /*
        - This question uses selection sort and and maximum.

        Algorithm for implementation:
            Part 1. Sort the data values of all countries for the category selected.
            Part 2. Given the sorted array, include the country name and value in `topCountries` if it is in the top
            `num` of countries for that category.
    */

    /*
        Part 1.
        Sort the values of the array.
    */
    int row;                          // used in the for loops
    double sorted[COUNTRIES_COUNT];   // temporary array that will be sorted
    double unsorted[COUNTRIES_COUNT]; // temporary array that won't be sorted

    // using filterCat, create a 1d array with only the relevant data values of the selected category
    // create a sorted and unsorted for later use
    // ... the unsorted will be used to get the original position of the country in the SOGA dataset.
    filterCat(SOGA, sorted, category);
    filterCat(SOGA, unsorted, category);

    int min;  // minimum variable in the array
    int i, j; // for loop of selection sort and country

    for (row = 0; row < COUNTRIES_COUNT; row++)
    {
        min = row;

        for (i = row; i < COUNTRIES_COUNT; i++)
        {
            // sort in decreasing order so we use > not <
            if (sorted[i] > sorted[min])
            {
                min = i;
            }
        }
        // swap the positions
        swap(&sorted[min], &sorted[row]);
    }

    /*
        Part 2.
        Only put the top num data in the final array.
    */
    for (i = 0; i < num; i++)
    {
        // The second row of topData is for the variables of the country for the category.
        topData[i][1] = sorted[i];
    }

    // Determine what the country name is for the specific data.
    for (i = 0; i < num; i++)
    {
        for (j = 0; j < COUNTRIES_COUNT; j++)
        {
            if (topData[i][1] == unsorted[j])
            {
                // The first row of topData is for the country names that are selected.
                topData[i][0] = (double)(j);
            }
        }
    }
}

/* questionTwo

    purpose: Get the count, minimum, maximum, and average of countries for a specific category.

    params:
    - category [int]: the category number.
    - double SOGA[][] [double]: 2d array of SOGA dataset.
    - double results[] [double]: array that contains the result
    return:
    - none

*/
void questionTwo(int category, double SOGA[][SOGA_COUNT / COUNTRIES_COUNT], double results[4])
{
    /*
        - This question uses count, minimum, maximum, and average.

        Algorithm for implementation:
            Part 1. Filter category from the total data set and get size.
            Part 2. Get the min.
            Part 3. Get the max.
            Part 4. Get the average
    */

    /*
        Part 1.
        Filter category.
        Then, get size.
    */

    int i; // used in for loop
    double catData[COUNTRIES_COUNT - 1];
    double min, max;
    double avg = 0;

    // using filterCat, create a 1d array with only the relevant data values of the selected category
    filterCat(SOGA, catData, category);

    // determine count using sizeof operator
    // recall that we don't have global here, so we subtract 1.
    // put result in results array
    // count value will be stored in results[0]

    // count needs to be double because array is double
    // the data type of this will just be type casted later on
    results[0] = COUNTRIES_COUNT - 1;

    /*
        Part 2, 3.
        Get the min and max.

        The min and max can be solved simultaneously.
    */

    min = catData[0];
    max = catData[0];

    for (i = 1; i < (int)results[0]; i++)
    {
        if (min > catData[i])
        {
            min = catData[i];
        }

        if (max < catData[i])
        {
            max = catData[i];
        }
    }

    // put results in array
    // min value will be stored in results[1]
    // max value will be stored in results[2]
    results[1] = min;
    results[2] = max;

    /*
        Part 4.
        Get the average of the array
    */
    for (i = 0; i < (int)results[0]; i++)
    {
        avg += catData[i];
    }

    avg /= results[0];

    // put the results in array
    // avg value will be stored in results[1][3]
    results[3] = avg;
}

/* questionTri


    purpose: Print the country that is the median of the last num countries below the average of a category.

    params:
    - num [int]: number of countries which have the highest value for the category.
    - category [int]: the category number.
    - double SOGA[][] [double]: 2d array of SOGA dataset.
    - string countries [String]: the list of countries.
    - output [String]: output, name of country.
    return:
    - none

*/
void questionTri(int num, int category, double SOGA[][SOGA_COUNT / COUNTRIES_COUNT], String countries[COUNTRIES_COUNT], String output)
{

    /*
        - This question uses count, minimum, maximum, and average.

        Algorithm for implementation:
            Part 1. Get the average of the data set.
            Part 2. Create a new array with data values below the average.
            Part 3. Using selection sort, sort the new array.
            Part 4. Get the last num elements in the new array.
            Part 5. Get the median (middle position) in the new array.
    */

    int i, count = 0;                // initialize count as zero, this will be used in Part 2 in indexing for blwAvg.
    double catData[COUNTRIES_COUNT]; // SOGA data for a specific category
    double blwAvg[COUNTRIES_COUNT];  // array that only includes those below the avg.
    double top[num];                 // array that only includes the top num elements in blwAvg.
    double avg = 0;                  // initialize avg because we want to use += later in getting the average
    double med;                      // median of top[]
    int min, h, k;                   // variables used in selection sort

    // use filterCat again to only get the relevant data values.
    filterCat(SOGA, catData, category);

    /*
        Part 1.
        Get the average of catData.
    */
    for (i = 0; i < COUNTRIES_COUNT - 1; i++)
    {
        avg += catData[i];
    }
    avg /= COUNTRIES_COUNT - 1;

    /*
        Part 2.
        Add elements in catData to blwAvg if it is below the average
    */
    for (i = 0; i < COUNTRIES_COUNT; i++)
    {
        if (catData[i] < avg)
        {
            blwAvg[count] = catData[i]; // use count in indexing blwAvg, this is why it was initialized = 0.
            count++;                    // increment count.
        }
    }

    /*
        Part 3.
        Selection sort blwAvg.
    */
    for (h = 0; h < count; h++)
    {
        min = h;

        for (k = h; k < count; k++)
        {
            if (blwAvg[k] > blwAvg[min])
            {
                min = k;
            }
        }
        swap(&blwAvg[min], &blwAvg[h]);
    }

    /*
        Part 4
        Get the first num elements in blwAvg.
    */

    for (i = 0; i < num; i++)
    {
        top[i] = blwAvg[i];
    };

    /*
        Part 5
        Get the median of the data
    */
    if (num % 2)
        med = top[(num - 1) / 2];
    else
        med = top[(num / 2)]; // note that the median will be count/2 ONLY not count/2 and count/2 - 1.

    for (int i = 0; i < COUNTRIES_COUNT - 1; i++)
    {
        if (catData[i] == med)
            strcpy(output, countries[i]);
    }
}

/* questionFor

    purpose: sort the data of a category and find the data above and below a country.

    params:
    - country [String]: the country the user selected
    - num [int]: number of countries which have the highest value for the category.
    - category [int]: the category number.
    - double SOGA[][] [double]: 2d array of SOGA dataset.
    - double output[] [double]: array of the output, the value at the index, index + 1, and index - 1.

*/
void questionFor(String country, int category, double SOGA[][SOGA_COUNT / COUNTRIES_COUNT], String countries[COUNTRIES_COUNT], double output[3])
{

    /*
        - Linear search and selection sort.

        Algorithm for implementation:
            Part 1. Sort the data for the category.
            Part 2. Search for the key and the element above and below.
    */

    // use filterCat
    double dataCat[COUNTRIES_COUNT];
    double sorted[COUNTRIES_COUNT];
    double key;
    int i, j, min; // used for selection sort

    filterCat(SOGA, dataCat, category);
    filterCat(SOGA, sorted, category);

    /*
        Part 1
        Do selection sort
    */

    for (i = 0; i < COUNTRIES_COUNT - 1; i++)
    {
        min = i;

        for (j = i; j < COUNTRIES_COUNT - 1; j++)
        {
            if (sorted[j] > sorted[min])
            {
                min = j;
            }
        }
        swap(&sorted[min], &sorted[i]);
    }

    /*
        Part 2
        Find the data value of the country for the category and this will be key.
    */
    for (i = 0; i < COUNTRIES_COUNT - 1; i++)
    {
        // use strcmp, recall if strcmp is true it will return 0
        // otherwise
        if (!strcmp(country, countries[i]))
        {
            key = dataCat[i];
        }
    }

    // linear search
    for (i = 0; i < COUNTRIES_COUNT - 1; i++)
    {
        if (sorted[i] == key)
        {
            output[1] = key;

            // added some error handling here so that above and below
            // don't go out of bounds
            if (i != 0)
                output[2] = sorted[i + 1];
            else
                output[2] = sorted[0];

            if (i != COUNTRIES_COUNT - 1)
                output[0] = sorted[i - 1];
            else
                output[0] = sorted[COUNTRIES_COUNT - 1];
        }
    }
}

/* questionFiv

    purpose: determine the frequency of a value in the data set for a category.

    params:
    - category [int]: category selected by the user.
    - low [double]: lower bound of the range.
    - up [double]: upper bound of the range,
    - double[][] [double]: SOGA dataset.
    - output[] [double]: the output of the function that will contain the value and its frequency,

    return:
    - none
    */
void questionFiv(int category, String country, double SOGA[][SOGA_COUNT / COUNTRIES_COUNT], String countries[COUNTRIES_COUNT], int *position)
{
    /*
        - selection sort, binary search, count.

        Algorithm for implementation:
            Part 1. Sort the data for the category.
            Part 2. Search for the key and the element above and below.

    */

    double sorted[COUNTRIES_COUNT];
    double dataCat[COUNTRIES_COUNT];
    int i, j, min; // selection sort variables
    int index;
    double target;                  // binary search target

    filterCat(SOGA, sorted, category);
    filterCat(SOGA, dataCat, category);

    // find the value of user input Country for category
    for (i = 0; i < COUNTRIES_COUNT - 1; i++)
    {
        if (!strcmp(countries[i], country))
        {
            index = i;

            break;
        }
    }

    target = dataCat[index];

    /*
        Part 1.
        Selection Sort in INCREASING ORDER
    */

    for (i = 0; i < COUNTRIES_COUNT - 1; i++)
    {
        min = i;
        for (j = i; j < COUNTRIES_COUNT - 1; j++)
        {
            if (sorted[j] < sorted[min])
            {
                // notice less than sign because it's increasing order
                min = j;
            }
            swap(&sorted[min], &sorted[i]);
        }
    }

    /*
        Part 2.
        Binary Search
    */
    *position = binSearch(sorted, COUNTRIES_COUNT - 1, target);
}

int main()
{
    /* Declare your own local variables. Describe the purpose of your local variables. */

    /* SOGA dataset variables */

    /* Remark on Countries.
          For questions that get the min/max/average/etc. of all countries.
          EXCLUDE countries[0] because that is "Global".
    */
    String countries[COUNTRIES_COUNT] = {
        "China",
        "North_Korea",
        "Taiwan",
        "Cambodia",
        "Indonesia",
        "Laos",
        "Malaysia",
        "Maldives",
        "Myanmar",
        "Philippines",
        "Sri_Lanka",
        "Thailand",
        "Timor_Leste",
        "Vietnam",
        "Fiji",
        "Kiribati",
        "Marshall_Islands",
        "Micronesia",
        "Papua_New_Guinea",
        "Samoa",
        "Solomon_Islands",
        "Tonga",
        "Vanuatu",
        "Armenia",
        "Azerbaijan",
        "Georgia",
        "Kazakhstan",
        "Kyrgyzstan",
        "Mongolia",
        "Tajikistan",
        "Turkmenistan",
        "Uzbekistan",
        "Albania",
        "Bosnia_and_Herzegovina",
        "Bulgaria",
        "Croatia",
        "Czechia",
        "Hungary",
        "North_Macedonia",
        "Montenegro",
        "Poland",
        "Romania",
        "Serbia",
        "Slovakia",
        "Slovenia",
        "Belarus",
        "Estonia",
        "Latvia",
        "Lithuania",
        "Moldova",
        "Russia",
        "Ukraine",
        "Brunei",
        "Japan",
        "South_Korea",
        "Singapore",
        "Australia",
        "New_Zealand",
        "Andorra",
        "Austria",
        "Belgium",
        "Cyprus",
        "Denmark",
        "Finland",
        "France",
        "Germany",
        "Greece",
        "Iceland",
        "Ireland",
        "Israel",
        "Italy",
        "Luxembourg",
        "Malta",
        "Netherlands",
        "Norway",
        "Portugal",
        "Spain",
        "Sweden",
        "Switzerland",
        "UK",
        "Argentina",
        "Chile",
        "Uruguay",
        "Canada",
        "USA",
        "Antigua_and_Barbuda",
        "Bahamas",
        "Barbados",
        "Belize",
        "Cuba",
        "Dominica",
        "Dominican_Republic",
        "Grenada",
        "Guyana",
        "Haiti",
        "Jamaica",
        "Saint_Lucia",
        "Saint_Vincent_and_the_Grenadines",
        "Suriname",
        "Trinidad_and_Tobago",
        "Bolivia",
        "Ecuador",
        "Peru",
        "Colombia",
        "Costa_Rica",
        "El_Salvador",
        "Guatemala",
        "Honduras",
        "Mexico",
        "Nicaragua",
        "Panama",
        "Venezuela",
        "Brazil",
        "Paraguay",
        "Algeria",
        "Bahrain",
        "Egypt",
        "Iran",
        "Iraq",
        "Jordan",
        "Kuwait",
        "Lebanon",
        "Libya",
        "Morocco",
        "Palestine",
        "Oman",
        "Qatar",
        "Saudi_Arabia",
        "Syria",
        "Tunisia",
        "Turkey",
        "UAE",
        "Yemen",
        "Afghanistan",
        "Bangladesh",
        "Bhutan",
        "India",
        "Nepal",
        "Pakistan",
        "Angola",
        "Central_African_Republic",
        "Congo",
        "Congo_Kinshasa",
        "Equatorial_Guinea",
        "Gabon",
        "Burundi",
        "Comoros",
        "Djibouti",
        "Eritrea",
        "Ethiopia",
        "Kenya",
        "Madagascar",
        "Malawi",
        "Mauritius",
        "Mozambique",
        "Rwanda",
        "Seychelles",
        "Somalia",
        "Tanzania",
        "Uganda",
        "Zambia",
        "Botswana",
        "Lesotho",
        "Namibia",
        "South_Africa",
        "Eswatini",
        "Zimbabwe",
        "Benin",
        "Burkina_Faso",
        "Cameroon",
        "Cabo_Verde",
        "Chad",
        "Gambia",
        "Ghana",
        "Guinea",
        "Guinea_Bissau",
        "Liberia",
        "Mali",
        "Mauritania",
        "Niger",
        "Nigeria",
        "Sao_Tome_and_Principe",
        "Senegal",
        "Sierra_Leone",
        "Togo",
        "American_Samoa",
        "Bermuda",
        "Cook_Islands",
        "Greenland",
        "Guam",
        "Monaco",
        "Nauru",
        "Niue",
        "Northern_Mariana_Islands",
        "Palau",
        "Puerto_Rico",
        "Saint_Kitts_and_Nevis",
        "San_Marino",
        "Tokelau",
        "Tuvalu",
        "South_Sudan",
        "Sudan"};

    /* Remark on SOGA.
          Each country including "Global" has 15 categories.
          Therefore:   SOGA[0][0] to SOGA[0][15] are the data of "Global" ..
                       SOGA[1][0] to SOGA[1][15] are the data of "China" .. etc.
    */
    double SOGA[COUNTRIES_COUNT][SOGA_COUNT / COUNTRIES_COUNT] = {
        {73.4713904415403931, 1.7697473333512299, 1.0087602581961499, 0.0717502060555120, 0.6764523882545460, 3.1489502002003200, 0.2968589707770950, 0.5748086549943000, 5.1211119670784502, 1.8505786916959399, 1.4543965308567099, 2.0841082096233499, 1.8106261020059500, 0.3019698470526320, 0.3053048325757150},
        {77.5821751025047064, 1.8507312753740599, 1.3935180944526600, 0.0741871322081522, 0.3403652907877590, 2.8612756570639801, 0.3526318250844580, 0.0174277178320210, 4.7162098014074196, 2.0287275468521000, 0.9871771617261800, 2.7779200067099898, 2.4378633717131102, 0.3866165421873550, 0.0900161702555660},
        {73.0855127008440064, 3.1342872068321301, 1.1295251478998001, 0.1645704303942920, 1.6797115881136100, 4.2782639701601397, 0.4376740280075070, 0.0359061381980013, 4.9269264128266199, 2.2714160532025098, 1.1124651308429501, 2.8908820476335002, 2.4338114985391899, 0.4944100764872560, 0.1262347945514650},
        {80.1445412858693942, 0.7378775665629200, 0.6836612122116300, 0.0262445265757663, 0.0279932519681694, 1.1889442491738400, 0.2007426406904220, 0.0149155861252410, 3.9235755507543399, 1.1799271812634100, 1.5528740323413599, 1.9195305714220900, 1.6694376245661400, 0.2805282703356800, 0.0769296421341320},
        {69.8487469323495986, 2.3084538210292500, 0.4245574246962900, 0.0164196262902010, 1.8050943396972601, 3.3140121037765899, 0.3064998485458400, 0.3241190205207970, 4.0908798018164800, 1.6680543665489900, 1.6947293896495399, 2.4766093992756901, 2.0391757355861100, 0.4254349055469650, 0.2370534557185520},
        {71.3805439405161053, 1.3808307333803600, 0.7713929919591300, 0.0211633630637920, 0.5554723357200260, 2.4635020028427701, 0.3266787739510870, 0.4457314158036350, 6.4222249284414703, 2.0325360860130002, 1.8730797136168500, 2.1441845762170000, 1.7807039676453900, 0.3757242156769960, 0.0984708578327230},
        {68.8918544153846000, 2.7480454928558800, 0.4472147879277600, 0.0312918073952915, 2.1978757090800398, 3.8589783842807699, 0.3100384677265140, 0.4714484942990250, 5.9355166249628404, 1.9882896711481901, 2.2037081698396399, 2.4377526103864300, 1.9937493054789099, 0.4489684876587750, 0.1873364955404500},
        {75.0064769151444040, 0.7387631948560800, 0.7114121587119900, 0.0204225844621106, 0.0072429425380989, 1.1606709992776800, 0.1946851506995840, 0.0787509116185419, 5.3842044668608198, 1.9449275924466300, 1.6978052730192299, 2.0864344370618100, 1.7155944055847401, 0.3916913024986290, 0.1310603786393470},
        {78.9436246219063946, 0.6160720334627300, 0.3655253493726300, 0.0748887156499620, 0.1738330579870540, 1.1776675623302100, 0.2712212229271100, 0.0926865229358782, 5.8905475518431398, 2.0262340719870102, 2.0560425046568702, 1.9620881108625201, 1.6382484641840900, 0.3452052426493710, 0.0475100336659720},
        {69.3905023123834042, 2.6144655207527898, 0.7856182262564000, 0.0515286658092577, 1.6695737749779200, 3.5796872416543302, 0.2291578785259820, 0.3382010567951280, 5.7954078942142502, 1.8337726850809699, 2.1908392206405698, 2.2346438850343699, 1.9048282317399099, 0.3420218072978970, 0.2204295447973410},
        {71.7984234318080041, 1.6756805496935701, 0.6916344808788000, 0.0023702340124459, 0.9294844455570230, 2.3836161953223001, 0.2244568653901100, 0.2429261319374940, 6.1650077329156296, 2.1621674058242899, 1.8853433744537300, 2.5755561758801901, 2.1599348411876802, 0.4604475572412950, 0.1646481964707080},
        {77.2643173347700980, 1.1807356374837801, 0.5920425886289300, 0.0202427209589047, 0.5399936628835750, 1.6488770289431001, 0.1788181028234130, 0.0899623472440965, 6.8139879824028098, 1.7353991008018901, 2.8055064197736499, 1.1584794328332899, 0.8934047228817830, 0.2386576527656810, 0.0481682180389380},
        {78.2199602764748931, 1.0333131908672499, 0.8083335272585001, 0.0350270096517988, 0.1826095340894230, 1.7226516855750900, 0.2914785679819970, 0.1910439593451940, 4.3378533375470596, 1.2604306928416700, 1.6333996103247701, 1.7745760186524500, 1.5515736079584901, 0.2289614677142420, 0.5515999208915330},
        {70.5378553099645984, 2.2854057312019198, 0.3587332702640000, 0.0143270036532357, 1.8563815301390900, 3.2301877394607299, 0.2424663139424300, 0.4382605799104340, 5.2636171164371897, 2.0166238997408898, 1.7477651520810200, 2.0282873397510999, 1.6943816441650601, 0.3465454667943960, 0.4148279934074140},
        {74.4164751323593947, 1.4013225662849200, 0.7125842594815200, 0.0213182115241750, 0.6285457943600650, 2.0117079629473800, 0.2675993345317810, 0.0655160711624632, 6.2666118020874997, 1.9573428332964200, 2.0826286856723999, 2.2638381707549500, 1.9295676630779801, 0.3527244536539630, 0.1638557204127980},
        {68.3420572152875963, 1.1141543493309700, 0.5679619347006100, 0.0016640474083545, 0.5208575188814140, 1.5273523640180700, 0.1369936354381880, 0.1801307494252460, 11.6444654838042005, 2.9491646699276699, 5.5385468160669102, 2.1890657544663301, 1.6388617754392800, 0.5766049534184670, 0.1827209216715600},
        {60.7225499905653976, 2.0701908269325702, 0.2360163899195300, 0.0169171842376912, 1.7886745952633401, 2.9727452005179602, 0.1329431022519860, 0.5191365756353790, 7.7452489973464704, 2.2920819811270001, 4.0338852638460603, 4.1054119360078802, 3.5332487208118701, 0.6565658113996450, 0.4019138249206830},
        {65.4522631272684947, 1.2201226108762999, 0.3960947300458900, 0.0000373117302672, 0.8003614375256090, 1.7851561805905800, 0.1726846293977930, 0.1912822334654150, 8.1877246210190595, 2.6908112377034001, 3.8285240757809902, 2.2876164051995000, 1.7921677443347599, 0.5398193240076949, 0.2597336244114100},
        {64.1491319848459938, 1.1935863054286000, 0.4632078167118300, 0.0001205211612643, 0.7031166968639010, 1.7175357614753000, 0.1932815295111960, 0.1268077950703910, 8.5213177292877909, 2.5818804727465201, 3.9500700425768800, 3.0399599609256600, 2.5708183497426900, 0.5343900194242510, 0.8507436619911890},
        {64.5459850020405952, 3.2393049351194598, 0.2803275768538400, 0.0004757070134360, 2.8909430663056002, 4.7479361086513903, 0.3076639280926090, 0.8511782744984090, 5.3251123925535104, 1.9052879231872899, 2.8212151163688302, 2.4800958379049800, 1.9113831036118301, 0.6235353373273680, 0.8573168358793030},
        {70.5660127562711068, 1.8583237814113700, 0.3969365604954200, 0.0120599525951519, 1.4054687538331101, 2.1759261527925799, 0.1658171758504920, 0.0738271719151129, 8.4535076288979507, 2.3741325989423099, 3.6703542208658502, 3.0758702515568399, 2.5256570411799801, 0.6500471798176189, 0.2506699870112210},
        {59.1329046832727983, 3.4931864989914598, 0.2522902581757400, 0.0001744039592282, 3.1623040833387002, 4.6465214449803298, 0.2402153879791130, 0.5487103806810441, 7.1543653546625201, 2.8727985463720498, 3.1002422916352499, 3.2307337074199798, 2.6295676715966598, 0.6527731331975990, 0.2403054247764590},
        {72.9699813998887947, 1.0492505902696201, 0.4075022537504800, 0.0101752684995233, 0.6115830779007470, 1.3910013014246900, 0.1744776573526390, 0.0579751844136069, 7.2289272980347103, 1.9587695008398101, 3.4994101976535199, 2.6170205164483500, 2.1387184775005301, 0.5271179748478970, 0.2065947726740940},
        {65.4540194317413011, 2.9272507944978101, 0.3503826090155700, 0.0033268937724102, 2.5043097594364498, 3.9072776703078498, 0.3157824387863290, 0.4560977697789920, 8.2372708934212309, 2.8202983789755600, 2.9650408289595198, 2.0547555662010000, 1.6580814533506201, 0.4258673224634750, 0.2153242386083180},
        {75.6862792868842007, 1.3534181884504599, 1.2779727284978200, 0.0455677460425505, 0.0302542594966155, 2.1752456463125198, 0.2053411699671270, 0.0220151075779711, 6.8708294336071702, 2.7140484798379800, 2.1211244888927800, 2.5933018411190898, 2.2232185240951599, 0.4150658378729870, 0.0922454778334160},
        {70.8263998824180021, 1.3343126708672099, 1.2093347946607900, 0.0173002219471812, 0.0989624549117991, 2.1996009489223201, 0.1067406975134590, 0.0648466714031031, 7.2117845464022796, 2.9010412295814398, 2.0366003192408200, 2.3840684106468801, 1.8884173521010901, 0.5256205285736399, 0.0564051954667950},
        {73.3429221188854967, 1.2473701649821600, 0.8056627227488899, 0.0206598621433614, 0.3945368531444020, 2.1171461957351201, 0.1740765915557890, 0.0168086166386701, 9.8576938726280900, 3.0033540829109500, 2.4432156161884802, 2.6003284084043701, 2.2631613703678299, 0.4005689059984830, 0.0913731986877620},
        {71.9256332903781015, 1.0480809288786801, 0.8779029588319800, 0.0440657377838534, 0.1177947949136500, 1.8618924638058700, 0.2339913171820740, 0.0218498859315588, 8.0892750831686406, 2.6617860181197002, 1.9603495419973300, 2.1744832985227398, 1.9060820804583900, 0.3063875181467350, 0.0948678234428260},
        {73.4175721365603948, 1.6207267502347500, 0.9832652501551700, 0.0616646722368159, 0.5329816036175290, 2.5938623035405901, 0.1523313612697730, 0.0514935564076353, 6.9683577162904298, 3.6496603041269502, 0.9759148768341100, 2.4376516895387099, 2.0235971543363300, 0.4513955329604900, 0.1190050732060680},
        {68.0072893855055014, 1.8333960791609500, 1.2307605601635001, 0.0098909190978134, 0.5402524932638780, 2.4260936185154001, 0.1116261155838740, 0.0689514141318881, 6.0053303563742197, 3.3951408205416600, 0.5743343103698501, 2.3903405417298602, 2.1275732791810502, 0.2882075636817230, 0.0965985311199090},
        {69.5311128799696974, 2.0487848002396301, 1.2642041177216901, 0.0321752308748557, 0.6743026779294180, 3.4211764484686098, 0.1076462986095090, 0.2600334242636110, 8.1444464934890295, 3.2393643128399998, 2.2683042912500202, 1.5681723087142700, 1.2389137732262201, 0.3504475024439130, 0.0464997020264380},
        {70.7458138981648972, 1.5855264891307399, 1.5714731365704899, 0.0121554550423753, 0.0021749839896046, 2.7031836548008701, 0.0828624974361530, 0.0704070718680470, 11.6042391795020006, 4.7573582368359801, 2.0837319766272802, 2.3281336770773300, 1.7292483467937501, 0.6473871355405550, 0.0916941668052120},
        {68.4046736489056002, 1.7560217511107701, 1.5460995498068399, 0.0120477887982275, 0.1727980293754140, 2.7066290871273999, 0.1104290494705250, 0.0513230885872531, 8.7112046100140095, 3.6302098815988901, 2.3794917950390402, 1.5541002264012200, 1.2238020375829000, 0.3463704822403740, 0.0780726098822980},
        {78.3387247806502955, 1.0715537141802300, 0.7110452056285200, 0.0088838654817920, 0.3295681429804490, 1.9687186500701901, 0.1305581232905410, 0.0094242094900494, 6.6270296219994398, 2.8178992084768302, 0.9011611552203500, 2.4538552304788102, 2.1461830273349300, 0.3628951898340770, 0.0404235536212240},
        {76.9403651718024975, 1.3591156069631301, 1.0047577575284199, 0.0203236788830310, 0.3029840237294220, 2.1536932505790700, 0.1285984578788230, 0.0041970642455169, 7.5525378126585103, 2.3481656058003799, 2.5237041739744899, 3.0366050448163300, 2.7701405639121099, 0.3545977461852770, 0.0655932138899260},
        {73.3217907552006949, 1.0187223310421001, 0.8394062387669800, 0.0113731841203730, 0.1567662232049680, 1.8235246340608500, 0.1132290355234740, 0.0068615408772388, 8.6586632063651106, 3.2264348866657100, 1.6180140236269300, 2.8901853834746398, 2.6659067762961302, 0.3177243768328420, 0.0929421219531430},
        {78.6425878659436961, 0.6576646896691900, 0.5994780363135100, 0.0270389693369140, 0.0310731773479347, 1.3551150786430199, 0.2535196975469060, 0.0033104260642602, 6.5484414956380199, 2.2462135799512501, 1.6501394683139501, 2.4979474264692998, 2.2863980779609698, 0.3002550749618540, 0.0475331789859160},
        {79.4166371539984937, 0.5901041480440899, 0.5585162107069700, 0.0260382178800427, 0.0068285155752790, 1.2832575347453501, 0.2131122899854600, 0.0075479934916700, 6.5824491365553097, 2.4776330796622301, 2.1034898030504401, 2.3492159838437101, 2.1854356501371899, 0.2222072920251890, 0.0591549412503410},
        {76.5749404774457929, 0.7723517029293000, 0.6218489331462700, 0.0313697011009992, 0.1149947610874020, 1.4932772426339900, 0.1817928423820380, 0.0080408212617158, 7.0553619586517904, 2.8389350288222102, 1.8077899732857201, 2.9958021122906899, 2.7708721009404398, 0.3284012004979220, 0.0703165933515210},
        {74.3332682481000973, 1.3651090247444999, 1.1278270642905901, 0.0065037570931850, 0.2067124141237000, 2.0750039150914401, 0.0901188231566720, 0.0046393309916937, 7.5493458537655904, 2.2924498053912399, 2.2687754540556599, 2.8289099615444102, 2.5607674187298102, 0.3634382111133900, 0.0576068620317330},
        {75.8367078197164943, 1.1666807866033899, 0.8849783930330000, 0.0079762004705657, 0.2517149228490330, 1.7999556087554500, 0.1004399401988540, 0.0025347029043559, 7.7561969007978497, 2.5371954065087698, 2.2070918009156801, 3.5608823619061498, 3.2955991913311400, 0.3824744627242890, 0.0569004046189720},
        {78.0667012657982013, 0.8643624209305100, 0.7705083874274000, 0.0161910770117544, 0.0739685917416750, 1.5403173039441800, 0.2345639597936330, 0.0054349182112361, 5.8342245340847700, 2.2411608656109201, 1.6180525134843000, 2.6640707151172500, 2.5046672986905598, 0.2166824298094100, 0.0809264106907220},
        {75.4971192679848997, 0.7598648489552200, 0.6460238144464200, 0.0055425567466756, 0.1026459422629810, 1.5795208948798301, 0.1569515966788940, 0.0108517994063533, 7.8410336291508296, 2.8927946279926902, 1.0188015758879601, 2.4356206434391199, 2.1965814114340398, 0.3014623370558810, 0.1378214755944360},
        {75.6518007987157972, 1.0542866362764201, 0.8796334244164100, 0.0078870476365296, 0.1531523360436610, 1.7373490678815999, 0.1505448129148730, 0.0033958117484900, 7.0065770461300598, 2.1980560735393899, 1.9373956220699100, 2.8102346028458500, 2.6029708209697899, 0.2950046757189000, 0.0971824959867430},
        {77.5323291799354024, 0.7019586844827800, 0.6822725355782900, 0.0137161327143076, 0.0063873654841160, 1.3157660375573099, 0.1175493987083340, 0.0046813197719047, 7.2593452577100903, 3.0443910299368500, 1.3015813782853201, 2.0868554705089801, 1.8811280669001000, 0.2533866347780390, 0.0655819335513000},
        {81.3053289986426933, 0.4675946916402200, 0.4122111876384100, 0.0266976310519880, 0.0296840312534954, 1.0906113192763900, 0.2686199085953260, 0.0028175869841220, 4.6617679813698203, 1.6401514013058101, 0.9312080408056600, 1.9277209567126501, 1.8083184711083100, 0.1792716082086090, 0.0427319292140570},
        {73.9889095494228997, 0.8377781643552900, 0.8219609057661500, 0.0066174972196933, 0.0087297076503745, 1.4155392839506100, 0.1218988527198380, 0.0040435925125593, 8.7523224243628892, 3.8429318155650098, 0.9581021611379000, 2.6542753704719799, 2.4522175676711000, 0.2414772942611310, 0.1149316486406780},
        {78.0194070090123972, 0.1406409192720500, 0.1096566387007100, 0.0043449883571043, 0.0264597857570550, 0.6296200730283800, 0.1218349888783340, 0.0048957632216400, 8.0840532145375601, 1.9281378308694499, 0.8336812587238400, 2.0092185767954902, 1.9016399099012899, 0.1525102220276860, 0.1127850515158710},
        {75.8436919381559989, 0.5032136946227700, 0.4573974902064500, 0.0041462844476854, 0.0400489517262486, 1.0496008442260201, 0.1340991131728660, 0.0058013839149851, 8.0259197637498403, 2.7612449648272301, 1.0592536483276100, 2.1988233513531399, 2.0273455554098101, 0.2108774980442690, 0.1364576064172380},
        {76.2177412756987991, 0.3847751678750100, 0.3635905900034300, 0.0041216011379532, 0.0166091810700379, 0.8703721794495600, 0.1227478071098740, 0.0075021063150444, 7.6188648312542897, 2.8069639805872302, 0.7879158761260400, 2.0409515854028499, 1.8970562436993199, 0.1794916022041520, 0.0860720376813050},
        {74.2659063732677964, 0.7290541469118800, 0.6327273283369400, 0.0097406377104505, 0.0823199207813587, 1.5139904137060800, 0.0915281329137940, 0.0281010662770456, 9.0206085415363297, 3.0864223692614701, 1.1883077843224801, 2.2520094378039799, 2.0399570757662100, 0.2480077651948700, 0.1539378795811360},
        {72.9564898146524996, 0.5272146586572900, 0.5029791964939300, 0.0076035989252858, 0.0160925744746123, 1.1718112063585100, 0.1815422779753250, 0.0115277327348906, 8.1515707274758000, 3.0171757550162801, 1.2344034777286801, 2.5982391730807102, 2.3880889081818002, 0.2636754552756170, 0.2017573033460280},
        {70.1327443149915979, 0.8042134607969900, 0.7487527422080600, 0.0080654803513056, 0.0444701526357818, 1.4124199546140099, 0.1266577013114300, 0.0114770115469298, 9.0073697159739794, 3.5188989392626100, 1.0337488566472901, 2.7728140260753000, 2.5277597736527300, 0.2939776728232460, 0.2018958048267900},
        {74.2987651752525977, 0.2210994070621300, 0.2136204373924800, 0.0035281297066945, 0.0039065828270282, 0.5769244521064800, 0.2264537904347460, 0.0137289305479982, 5.0933630326326798, 1.6883057858608299, 2.5619358770323002, 1.7018061095778900, 1.5392269199030599, 0.1848412520639610, 0.1162100831391090},
        {84.5578506644436061, 0.2977848374067700, 0.2810960378403400, 0.0170335717056105, 0.0006375208364631, 0.8496743367434900, 0.2282017417911820, 0.0165865460516699, 2.5465997935923199, 0.9917247373833500, 0.6439600975476900, 1.7098827107082000, 1.6136749750938000, 0.1235385594396090, 0.0494821114101850},
        {82.8262503583496965, 0.6914682869075700, 0.6530732370972600, 0.0422119614657390, 0.0004344449449576, 1.2513010845703101, 0.1449047469784690, 0.0135573820959820, 3.1066382629367402, 1.1692836940950400, 1.2001363400292999, 1.7003756925189299, 1.5996407860872599, 0.1190959879219950, 0.0463987922605040},
        {84.5652999143781017, 0.5656494303521000, 0.5472818301532000, 0.0188058153963055, 0.0008760856814831, 0.9105764465002300, 0.1829966409788280, 0.0303448411347347, 3.2787150286877100, 1.2260884555113001, 0.9909740922721400, 1.2481220110277500, 1.1435746677642999, 0.1195455336262800, 0.0551197134522430},
        {82.7899548288581997, 0.1113238479809700, 0.1046831054067200, 0.0059728652829563, 0.0007802083971171, 0.8276187434519600, 0.3627274871449370, 0.0064986729540948, 3.7906776904507802, 1.2424880921672099, 0.9460235454910900, 1.3139771548438799, 1.2395712047728400, 0.0989627624440180, 0.0396962650547300},
        {81.6992297742213935, 0.1005196886564100, 0.0920216595539400, 0.0077901521342909, 0.0008181636852953, 0.8798127797875900, 0.3205365163748160, 0.0082691817684548, 4.0632277331345001, 1.4921426494659900, 0.9250674326475000, 1.6255884473151001, 1.5413370593487501, 0.1127297554199630, 0.0397536845030830},
        {82.0321823451503036, 0.2206411990143000, 0.1768209601306300, 0.0448147853307574, 0.0003859752111026, 0.9988955800413600, 0.4518062128231290, 0.0032768419480505, 3.6433047749047098, 1.0185784291572899, 0.8505094746763200, 2.0907831991890999, 2.0055914892034301, 0.1320919575858280, 0.1290492241128330},
        {82.1000381454632020, 0.3239627462669400, 0.2929893251506300, 0.0315047576043810, 0.0010443847684485, 0.9356883990894200, 0.2351131634188730, 0.0024433813465379, 5.3441809050457598, 1.4530604349979701, 1.2102942345440100, 1.9237414450501800, 1.8194401664395099, 0.1622829086824280, 0.0471755080900350},
        {81.3531791954299024, 0.3418017793953000, 0.3176560218501400, 0.0249227521972415, 0.0005072215765693, 1.2260637738405900, 0.3956249475553900, 0.0076964567703612, 3.2340002005164599, 1.1063147371399500, 0.8714890965275000, 2.1986880883109698, 2.1108461243536900, 0.1375280849834160, 0.0486733166214320},
        {80.7916729731151975, 0.4556603081198600, 0.4170898618640600, 0.0396901015092936, 0.0007841588681572, 0.9725386848258200, 0.2172943776203060, 0.0029356946908337, 4.5974876133871696, 1.3162684080886000, 1.5840574767179301, 1.8709452445722401, 1.7513146761659000, 0.1696862617886270, 0.0421154672099530},
        {81.0639076537872967, 0.2653665224792100, 0.2373280445560200, 0.0286198403784113, 0.0003650710865202, 1.1006183484203500, 0.3650916049683560, 0.0060719866742289, 3.2907965653545999, 1.1374306451290199, 0.9056860729024599, 2.6567122911553200, 2.5653258355615902, 0.1382374741553890, 0.0533903263636550},
        {81.7728091627578948, 0.0750435243175600, 0.0698128022367700, 0.0048787645638555, 0.0004114509056023, 0.6541854335963500, 0.2356178434624920, 0.0015390697345907, 5.5946234935811203, 1.8020703622527501, 1.5082183386738699, 1.4716783334804000, 1.4117895674017500, 0.0827930409536890, 0.0274313227840540},
        {82.7713582936120957, 0.2501753093492700, 0.2347354761060500, 0.0155397735020841, 0.0006275837008047, 1.0169497316937099, 0.4323770100352110, 0.0046298797539635, 2.9914620946894002, 1.0798286727148101, 0.6023482509951400, 1.7340448157584700, 1.6789015753894001, 0.0840853910668220, 0.0607141724402570},
        {81.1636643318509954, 0.3114787956569000, 0.2897633459886300, 0.0224906414667316, 0.0003062994659047, 0.9785426107323900, 0.2759418390170370, 0.0037883485874062, 5.1336959292308704, 1.4089937024383199, 1.4523624334810701, 1.9193739550136499, 1.8506668655240299, 0.1083150202908600, 0.0495471691914130},
        {80.8865147322061944, 0.5096903472326501, 0.4787737448276400, 0.0286438962638584, 0.0032655895223712, 1.2505312113042200, 0.1932362779861170, 0.0036641681394229, 4.6648376217073304, 1.5537366985996199, 1.1576892924778399, 2.8487311843169199, 2.6968034486723300, 0.2413638083850030, 0.0432371477552070},
        {83.8917219255797022, 0.0879759152209700, 0.0744750569835600, 0.0133235180732783, 0.0003301099608706, 0.8563043411547400, 0.2911972422332380, 0.0048086200833382, 3.9363586232974801, 1.5193157545180500, 1.0027307153236500, 1.8983131450980699, 1.7938726615492899, 0.1477831646540720, 0.0332735811307150},
        {81.9545200098864939, 0.1630509116428000, 0.1585292295399200, 0.0040340727149300, 0.0005677008536509, 0.9648120178990200, 0.2444365985548270, 0.0049655303951113, 3.6763328414981098, 1.2865666152071400, 1.0340490784555401, 2.1085162136602502, 2.0112121371300198, 0.1323037687522660, 0.0452371496981240},
        {82.9020467589883054, 0.5014223440505300, 0.4670463462716300, 0.0368814756588876, 0.0007557993475302, 0.9078697657770201, 0.1591785634132920, 0.0078998169606592, 4.1634900632856100, 0.9490498470676000, 1.5042266439606400, 1.4910058764975100, 1.4016048683279401, 0.1195160365761300, 0.0471963205719560},
        {83.0321327612239060, 0.4097948071190000, 0.3697967844473300, 0.0406656948011488, 0.0017625805108707, 1.1554898376412599, 0.3347980437747110, 0.0025644855069231, 4.3930215050361703, 1.2729886659577401, 1.3383520740138599, 1.7257214473788201, 1.6268551037543699, 0.1434319751311220, 0.0555471282493730},
        {82.7989527790003024, 0.2449403416241300, 0.2193710957480000, 0.0260296748884912, 0.0004833477291726, 0.9612182168821600, 0.2973501068796200, 0.0044945516816597, 4.1030143768355298, 1.2723857004956800, 1.3241200933581800, 1.9206228083413801, 1.8336445953590901, 0.1265542918459060, 0.0375795966402420},
        {82.4367243309812068, 0.4241285112150500, 0.3893895527083000, 0.0352405623469707, 0.0010354416331921, 1.2126275779663600, 0.2771777794681190, 0.0048106342247678, 5.2955904410769703, 1.7905170884919099, 1.8070667975814301, 1.7280331907926001, 1.6151449690248800, 0.1534377525485840, 0.0337983575583820},
        {81.6982742498877030, 0.3103999582065900, 0.2880672047099500, 0.0230635983270417, 0.0003485632062734, 1.1143930352968401, 0.4181455574676110, 0.0039262380327472, 3.0364948881876299, 1.0288797222270500, 0.8049729689122700, 2.2788651748330602, 2.1985817551337399, 0.1218882106289530, 0.0376293407076820},
        {82.8291798839163960, 0.1066044004224800, 0.0931077916491500, 0.0134742164628108, 0.0002483026779601, 0.7985011614091500, 0.2815474531833500, 0.0061029768517642, 3.4026080856891401, 1.1904308441905700, 1.0326548150888899, 1.4107951483386800, 1.3312690697879099, 0.1074018839974830, 0.0480872328294740},
        {81.6691837339334938, 0.1965480141223900, 0.1745570522596400, 0.0196199840751774, 0.0027300609083341, 0.9521460513161299, 0.1976996008890670, 0.0094607955942507, 3.8536905073828498, 1.1359366943606899, 1.4024905553582001, 1.4800868351261600, 1.3569144396486601, 0.1529414355704550, 0.1444120783692140},
        {83.0122773325250023, 0.2583719212409700, 0.2050413693776800, 0.0508626433676369, 0.0039754702692250, 0.9667161537043500, 0.2565874372987620, 0.0039901464221828, 3.6001471918136301, 0.9657782155411200, 1.1368831861614599, 2.0044057222147602, 1.9153711816978600, 0.1413450776065450, 0.0669104808140160},
        {82.7676689369120027, 0.0783144784690700, 0.0683764250761500, 0.0097753417855273, 0.0002838939492307, 0.6458728586081400, 0.2020186663163910, 0.0051340005195470, 4.2788189505312699, 1.4120655411834200, 1.1267875648606300, 1.6357905003390101, 1.5709936294295099, 0.0871029921158600, 0.0431843669497600},
        {83.8636222586253979, 0.2200108626663700, 0.1904880738563400, 0.0305029139437920, 0.0001846933170384, 0.9115206829261200, 0.3318378011904600, 0.0032420932356558, 4.0235862436435204, 1.2305311321650001, 0.9671801285357901, 1.6672458907318199, 1.5977344089732000, 0.1009510443185210, 0.0438731219739590},
        {81.0393178137811958, 0.2457976487085900, 0.2375096166044700, 0.0083793401399817, 0.0001892858469148, 1.1481306425533500, 0.3911913179122590, 0.0057718904401582, 3.3054343867403002, 1.2818978801918599, 1.1504191478185399, 2.3056684998625601, 2.2036661638475699, 0.1465353654903940, 0.0486370059933420},
        {76.5370204229263038, 0.4641210639392600, 0.4260507469289700, 0.0146166612792769, 0.0233352650722765, 1.3171703687436600, 0.3075784398628660, 0.0399017003910274, 4.1571718300027802, 1.5390459776819900, 1.2709157840006200, 2.1628155515378600, 1.9425873382872700, 0.2745202600024190, 0.2266889420439780},
        {80.0880792119810963, 0.5954759862041500, 0.5540160694913800, 0.0101783445832666, 0.0306042040692347, 1.1824815887209801, 0.2022446903529560, 0.0221759536251511, 4.4749456862988897, 1.3210731909766600, 1.4029551498588300, 1.3300116459390801, 1.1543108735228000, 0.2100961674097310, 0.1690927902975830},
        {77.4570963084575936, 0.2868827435940800, 0.2582601720322000, 0.0104998964757073, 0.0181088463968422, 1.0094022732153101, 0.3000408205307820, 0.0301018158342572, 3.8285444922492502, 1.5481342792198900, 1.0470426369407000, 2.2663441225487899, 2.0685453071410400, 0.2650586859401760, 0.1973760471014000},
        {82.0414512122682993, 0.1584942560323400, 0.1389945417005700, 0.0195603585953279, 0.0002990220650645, 0.9625640248538100, 0.4041158629719060, 0.0071658801646493, 3.7521733038258600, 1.2838585266447100, 1.0458976014119401, 2.0047894525155701, 1.9188439805768800, 0.1220115591749360, 0.0513650712870230},
        {78.8424419583499940, 0.2352511210684700, 0.1919640232179800, 0.0436054119820000, 0.0006037046266698, 1.0267773021373601, 0.3048784872393920, 0.0066575539184868, 4.9108717749880402, 1.6347835083700299, 1.6589876005483699, 2.3376154268572802, 2.2338112889517800, 0.1494391502086070, 0.0849771151615220},
        {76.2582063471889029, 0.5594746663308700, 0.5500444467533500, 0.0000144605206032, 0.0089590438064136, 0.8193768635148200, 0.0695009212062700, 0.0702238663189405, 6.1575809193191899, 1.4449932565377599, 2.4992951847053901, 0.8134435745583100, 0.6815271572039310, 0.1421763479919630, 0.2668378199226140},
        {73.3172664416166953, 0.5093840284822601, 0.4940074745115100, 0.0048838280113159, 0.0104056515015287, 0.7729592958460200, 0.0818215324960930, 0.0519673956906388, 6.5681611394571702, 1.5762414397551101, 2.0663061807058800, 0.8992704524339400, 0.7525214372288640, 0.1603684403079910, 0.6536446717370550},
        {76.1656222001990955, 0.6424109877236700, 0.6415923277877600, 0.0000357977077101, 0.0007423076309010, 0.8883600302560500, 0.0749622739679840, 0.0546938459093695, 5.3572306662802598, 1.2665987115816200, 2.2897746644091801, 0.6876353915689000, 0.5835284694391590, 0.1105907874321730, 0.3024364174768410},
        {74.3883277744536002, 0.9373977077080200, 0.6947938561930400, 0.0149154992594873, 0.2171877900679820, 1.5264402669651200, 0.2118963640141800, 0.1573103016565080, 6.2190760479857401, 1.1800844460897399, 2.3950000302544101, 1.2315693585009899, 1.0438911968311699, 0.2038568035322190, 0.6170569258709691},
        {78.5782374832099038, 0.6652906946905700, 0.6328038614102200, 0.0110419388379768, 0.0210430498990206, 1.3759834765405301, 0.3926102160477000, 0.0660431113519451, 5.1365009047801200, 1.3312849816154799, 1.6381283987943400, 2.5800052103757500, 2.4008799910318999, 0.2339724658252460, 0.1588091763743480},
        {72.3063605586621065, 0.6271012046383200, 0.5529935760834001, 0.0001831231481333, 0.0706952298020127, 0.9572781814758000, 0.1125643384172150, 0.0829031196679040, 5.8993820063882199, 1.0785509795578301, 2.2095501442511201, 0.8325341711194900, 0.7125518893048340, 0.1293104013693520, 0.2924396056547780},
        {73.1138721485439049, 0.9756843096109999, 0.7725542205207500, 0.0056817236133497, 0.1882443581901040, 1.7672537549606300, 0.1917734604395060, 0.1839186797261480, 6.9258121902107499, 1.8873929819170701, 1.8438826106820700, 1.8148955952318200, 1.6426466159365001, 0.1975297954914620, 0.3954350078856810},
        {73.2762205574448018, 0.8060740998502900, 0.7673696906969200, 0.0018799450608640, 0.0345218796489775, 1.2192637573876799, 0.1025027058331320, 0.0769543850435923, 6.5467643188217197, 1.4403639818728400, 2.7518232783260999, 0.9675481652666200, 0.8117324599194550, 0.1657354295500400, 0.2563024505775640},
        {67.2848454965185994, 1.0077628340522700, 0.8837183752979900, 0.0003579166702963, 0.1152213283885150, 1.6634909667170601, 0.1013957111522790, 0.2351321156257170, 8.2614656013876608, 1.8548082245154500, 3.2576103245196300, 1.1307429328884400, 0.9058985520910600, 0.2414662341876830, 0.5645021781071050},
        {63.7260839973562980, 2.5700127703867000, 0.3071801245915000, 0.0135543878794095, 2.1990550537069402, 4.0485953248725197, 0.1264508819617940, 0.9759461933246310, 6.2539408227646298, 1.6491761514697201, 2.3650693739387898, 0.6745024065188800, 0.5366552796788679, 0.1433178693407270, 1.0220280468973000},
        {76.1217408828170932, 0.7753446296149500, 0.6244985867370100, 0.0147142926884243, 0.1303754191387010, 1.2144864490811900, 0.1485143353041710, 0.0625422981941597, 7.4846876678502401, 1.4102155772254199, 3.3312442620958200, 1.3975991217191099, 1.2004944206560100, 0.2177920220695460, 0.4890523113944450},
        {75.1266546441619028, 0.7387408332938200, 0.6974142035348500, 0.0003573076463539, 0.0387688508539412, 1.1392606806653200, 0.1206647815808280, 0.0672748104990148, 5.9147294998225304, 1.3324374349020200, 2.5281435931005398, 1.0548618457673300, 0.9327084976420820, 0.1356030436347600, 0.2267405864889870},
        {72.9152317279114044, 0.7864230652014300, 0.7321754376187500, 0.0001999506218908, 0.0508312616018003, 1.2381132387488101, 0.0602996662683920, 0.0996169538575771, 6.7414572927985601, 1.4791735273876701, 2.8519672128755200, 0.9092548261490701, 0.7478366951764170, 0.1723797657222260, 0.5122039403208590},
        {72.5597920002074943, 1.0004216245508200, 0.8418369671543100, 0.0007306540289989, 0.1490350682119300, 1.5373050032758999, 0.1026556402548240, 0.1890870947148930, 6.8711227296252604, 1.7021414707277800, 2.7510238280823698, 1.6757286385802801, 1.4197676766945100, 0.2928690773263300, 0.5069680002285820},
        {74.7865098549337972, 0.9686447267810200, 0.9661610138636800, 0.0009830653971505, 0.0014519116823948, 1.1722705003952401, 0.0644371685563390, 0.0525461951743438, 9.0167816337043103, 2.0722351598144400, 4.0509301562340703, 1.3882559461049100, 1.1107126675180701, 0.2989740273669240, 0.3934513664812580},
        {71.9360520403847943, 1.0646423355235299, 0.6506899428899400, 0.0163369030339169, 0.3775877935935060, 1.8130872581299000, 0.1587966337844190, 0.1937135409506820, 4.2215207340520404, 1.2099517339715800, 1.5690666083668501, 0.6855412833333100, 0.5904835259805740, 0.0997501508585400, 0.3374478049576340},
        {76.3672764246288978, 0.6201681241096000, 0.5512991207275600, 0.0057355801552745, 0.0607427420594746, 1.1803161193857199, 0.1997429666004390, 0.0960170110717087, 4.8220266972753896, 1.3171137359138900, 1.7341706993903800, 0.7096174765577500, 0.6220769333319540, 0.0941813280828680, 0.3343080940732220},
        {80.0138876347993033, 0.9274194785621300, 0.7169036643995500, 0.0063789721720582, 0.1926470850019090, 1.6290393998950601, 0.1336102768252800, 0.1978807620634770, 3.5670461443008001, 1.0308011783342901, 1.0551066445377200, 0.4462860690353000, 0.3558377918336930, 0.0937280211627180, 0.3239586148631590},
        {79.8434970346910973, 0.7917149624976200, 0.6535246987535700, 0.0119777613871292, 0.1206940867706270, 1.4048540779412699, 0.1835247851595200, 0.0641187486484824, 4.9525926458841498, 1.6682548867686899, 1.7356130452255101, 1.0265985365349799, 0.8732043437906470, 0.1718274003572450, 0.2678800661294930},
        {79.8930141654523993, 0.5134231349204000, 0.4508408429660900, 0.0124298040118163, 0.0491474930509810, 1.0133874086162999, 0.1617576523291290, 0.0539488459843653, 5.0772406259187504, 1.4476355591727701, 1.5662650566890901, 1.1536819476972500, 1.0245160666807500, 0.1508710462530590, 0.1835552573024440},
        {75.5640478948693044, 0.8630954738933400, 0.6339682761392600, 0.0176177020143484, 0.2018532474605480, 1.6252801344618599, 0.1269013002338110, 0.1665001639612310, 6.5991666161989002, 1.5059443764246201, 2.5418366877052998, 0.7206515913142900, 0.6037961639627270, 0.1261284372917690, 0.4583891280590680},
        {72.5615829815551052, 1.3540447539908200, 0.5403693062304000, 0.0062821955466319, 0.7743069111418490, 2.5188608066023499, 0.2436070110886990, 0.4829182108427550, 4.7254637895624398, 1.1394399974608100, 2.2967860315122599, 0.7027086979660200, 0.5544702265537180, 0.1551851146819560, 0.2966165269655220},
        {72.0526766437016022, 1.4381237716516500, 0.4274167482190700, 0.0209610025082156, 0.9536741196584020, 2.4486982825441399, 0.2830873858564330, 0.2672140671749190, 5.4049463765169197, 1.5373168181278101, 1.9091420864808999, 1.2234568117649001, 1.0500304514842900, 0.1962521800454480, 0.1304439385649940},
        {75.6715997128357998, 0.8386506297887600, 0.6312521448828901, 0.0329403927094205, 0.1674252324627330, 1.6633094467093801, 0.2029038625600920, 0.0821101667760900, 6.9255153633212103, 1.4429809481097100, 2.9358523575220401, 0.9787273554455300, 0.8127280091415660, 0.1769897112783380, 0.2112597022451580},
        {75.3557665117416065, 1.1454457905532700, 0.4007549829962600, 0.0111924820505322, 0.7048471864093530, 1.7585552563149900, 0.1591379449358500, 0.1138568550429110, 7.3628878698312503, 1.6877817774840800, 2.6603816232444499, 0.8482573084603801, 0.6679371626929510, 0.1935389790818930, 0.3891202065141640},
        {79.8052727908696937, 0.5132025966620400, 0.4043451192249700, 0.0117510105424827, 0.0946008512006102, 1.0085043166483800, 0.1174203995513640, 0.1415545681591940, 5.6437181306606901, 1.5230730959933700, 2.2867966450948098, 0.8414855107233700, 0.7286579249285841, 0.1218161792180870, 0.5226075968018900},
        {74.8835368297312982, 0.9144455197727300, 0.8978241537597700, 0.0107573881275727, 0.0061663901943803, 1.8566293272136700, 0.3966677716221340, 0.1108424708414470, 7.3741814027197599, 2.1738418243346702, 2.6281338018583802, 1.4349046032788499, 1.1981857109166800, 0.2603910479726890, 0.3374687482994860},
        {75.7443781010499038, 0.5721354310248900, 0.4054598189043500, 0.0298658374628502, 0.1343046734143340, 1.2059740667776100, 0.2334776755624550, 0.1179628316170350, 4.9492715809786203, 1.3816389548868400, 1.5843500798259800, 1.7886355009749100, 1.5736416718274699, 0.2515372797374200, 0.2385908749913740},
        {76.4831993023956045, 0.8903678435453800, 0.4004244254237700, 0.0189666865201303, 0.4577228638948440, 1.6085971308977201, 0.2322449680164170, 0.1038643759442120, 6.5289672425100500, 1.7443349993329100, 2.3540613905414500, 1.9890806973814701, 1.7570495351634301, 0.2609742063162490, 0.3417073676268530},
        {76.1232787150366050, 1.1924710223230901, 1.1645939965602701, 0.0272653598118069, 0.0034310844913108, 1.9741832379937001, 0.1509218587014230, 0.0366202712396131, 7.3384461281772202, 1.8886431229111600, 2.0547772175513201, 1.5177026550911701, 1.1616043692854401, 0.3953825723710200, 0.0544799475195670},
        {77.0051650576633051, 1.4635171406414600, 1.4195388555236499, 0.0482900078247894, 0.0035864643528782, 2.1230647530588098, 0.1761858421743200, 0.0268594360788654, 7.1870531346900002, 1.3564886084638901, 3.4446549112170302, 1.4734162378105500, 1.1877880442774100, 0.3136594168429670, 0.0241946332895540},
        {70.9452086087815985, 2.1108969261807600, 2.0841119987480599, 0.0317227663938269, 0.0015514273119237, 3.1551342084079899, 0.0921638311829160, 0.1804796192252670, 8.5983468203985307, 2.0450561283367699, 2.2439512746498198, 2.0662669920400698, 1.6615296709251799, 0.4357854448607700, 0.0119406225981750},
        {77.7514368965001950, 1.2999574201979101, 1.2554126087714499, 0.0475554898727211, 0.0028657447357574, 2.3617491940474902, 0.1293001556115600, 0.0334753409737942, 7.5008982556323103, 1.9438232401443400, 2.1090452644611601, 1.4757137500819899, 1.2072338835027101, 0.3036952567628930, 0.0338679975311180},
        {73.2323096480400011, 2.0167431025241900, 1.9953188047482699, 0.0182999462272164, 0.0046129010272580, 3.0265863409134002, 0.1377641040021020, 0.0383622912779913, 11.5869620960256992, 2.6947403019254499, 3.2887546244012098, 2.4409484193678099, 2.0061584355068600, 0.4917250932614930, 0.0252628181648190},
        {78.2001289694598967, 1.1582965474432101, 1.1337847150025500, 0.0268018974558402, 0.0005335112135043, 1.9410197420806601, 0.1032830554244840, 0.0273645387333517, 9.0534023268899197, 1.8394691944407700, 2.6574387647419999, 2.0614276349772398, 1.7589151883425800, 0.3583755069491020, 0.0263385912873700},
        {81.2923094685820047, 1.7038663472513800, 1.6787643047478300, 0.0309184499317041, 0.0005973102946371, 2.5603473103453802, 0.1345599001350590, 0.0329561709117030, 7.3667411934905704, 1.8335001454946500, 2.3035829474729801, 1.9383085890526199, 1.6075975777874201, 0.3781793464339960, 0.0196916415912510},
        {76.5819869416697969, 1.1936282543721299, 1.1679437287984800, 0.0243877602709830, 0.0032214073998063, 2.0837763654439398, 0.1779637307271570, 0.0301776178480679, 8.3700187043775394, 2.1818962024028399, 2.4825414368914802, 3.3377559700870201, 2.9953771396668598, 0.4706321793958640, 0.0424688714111880},
        {75.8633960834569052, 1.4698978376601799, 1.4348655953285001, 0.0364005049321463, 0.0031645470157855, 2.1741605297112598, 0.1155440606560920, 0.0383565036898688, 8.8698619029386094, 2.2149720817998402, 2.6883189070692000, 1.9645002654095101, 1.5477930957067700, 0.4764434144798740, 0.0619973438621880},
        {73.2907152574059069, 1.5921019032265600, 1.4676067450485999, 0.0299417419647909, 0.0868255417044566, 2.6837122718791302, 0.1831694063457120, 0.1320050745688520, 9.6222222776663404, 2.1007307979760599, 2.6015016315673001, 1.4454920711981301, 1.1322141835420301, 0.3416021477014370, 0.0906537180319730},
        {74.7643466380792034, 1.3496688640148300, 1.3060964553821299, 0.0235580434745373, 0.0194034807163490, 2.1371312826569699, 0.1310217821227160, 0.0363311846015648, 8.6574636379609906, 2.3073260998783400, 3.2303572103976599, 2.0363406223744200, 1.6509843749094999, 0.4339648900681820, 0.0285206726330780},
        {73.9326267957857937, 1.5257595904458900, 1.4998327217857199, 0.0217010074537427, 0.0054709275029552, 2.4387568213038802, 0.1261116753754120, 0.0365312887673497, 8.1997237028636398, 2.1594914317201601, 2.6825518473696399, 1.0008214720850801, 0.7408420236095740, 0.2763039682747600, 0.0601600977434200},
        {76.2488139682883030, 1.2686221313912700, 1.2497939206309601, 0.0247953202842695, 0.0000774050650279, 1.8923388667930401, 0.1398287395325330, 0.0122238062502191, 6.2452158761445000, 1.1823154428398399, 2.5160947408925098, 1.0829106802874300, 0.8487978129929700, 0.2552727817980410, 0.0178976113707280},
        {74.4937190403456952, 1.9421385412534800, 1.9074277423521799, 0.0377658714860303, 0.0036902221834652, 2.7981130907923002, 0.1067218364528490, 0.0408438918923082, 8.4331881059743399, 2.1865120972938001, 2.4727366114228602, 1.5419518329168200, 1.1926700114317399, 0.3935845228682240, 0.0415976522944700},
        {73.8128571909577005, 1.4441067566834700, 1.4176915415224201, 0.0263156869201282, 0.0022706484810442, 2.4220004888065700, 0.1314719035056560, 0.0321452309112260, 7.9469200615057503, 2.6494244967042602, 2.4096155143691100, 2.1285229811910300, 1.7916241387504599, 0.4012001444270370, 0.0173800864525900},
        {77.6682106754364980, 1.2628617846458401, 1.2309095476658500, 0.0310847426445093, 0.0033846001959859, 2.1833282487518502, 0.1469581035897960, 0.0336653112013749, 8.5435558101462306, 1.8945404377228201, 2.5091618328275600, 2.1755910704115302, 1.8412932603851100, 0.3873036004027880, 0.0510503985617990},
        {78.3079716506127994, 1.1148584930709500, 1.0498917393084599, 0.0642413633910479, 0.0057224508402385, 2.1900199905344500, 0.3974129470315690, 0.0402290212029328, 6.5859974811063200, 1.1992272305821801, 1.7848912882607799, 2.5390573596128299, 2.2610383934186000, 0.3500530638233390, 0.0349636932599540},
        {73.8736490873504010, 1.4825085013985599, 1.4363539456592500, 0.0549344110648349, 0.0000579763554782, 2.4872607907498598, 0.1693890435574730, 0.0372293484290225, 8.1864445340688992, 1.4305638755230301, 2.5790410954869998, 1.8340426671357799, 1.4451895557424601, 0.4360429779055010, 0.0585794462948290},
        {67.6700666958937944, 2.1716123498141400, 1.1185911615869899, 0.0303357232472194, 0.9452242948825220, 3.9955983287994501, 0.2153874560918890, 0.5339611531507270, 7.2332734228870397, 2.8652909885251701, 1.5699811590167601, 2.3083131714601599, 1.9288784447587799, 0.4421869950770230, 0.0537183756149770},
        {63.2342969709320997, 2.6642821586646801, 0.5883149506766800, 0.0342444451174373, 1.9720503195936401, 4.2164996943438604, 0.2668780627308460, 0.3354468832668330, 6.6942545558313702, 2.5295467671294700, 2.1574300523269199, 1.2392929201485099, 0.8373922570673430, 0.4243345039394630, 0.0580286168484250},
        {74.5579395650413943, 2.9119563759732898, 1.1649937352680799, 0.1335466671492470, 1.5281857912704500, 4.5387277013276597, 0.2907662224593680, 0.5933617746012060, 5.0831964598618704, 2.1667644414271501, 1.5024951909505999, 2.0107688805625701, 1.6121424483727800, 0.3687849880525110, 0.0687675228358270},
        {73.0107576986280975, 2.0937607345393401, 0.8106302897309799, 0.1652642767882920, 1.0778972561169300, 3.5314837800303600, 0.4134353811057140, 0.3090845541226340, 4.5105432177159797, 1.5439289891278201, 1.3756697696551801, 1.1851017185119199, 0.9542200146371440, 0.1938896863204460, 0.1499122983598370},
        {70.7816560457501964, 2.6931530410089701, 1.5112807853752901, 0.2061157934070930, 0.9413770657048131, 4.8102572364898704, 0.3333492104343350, 0.9640701071300550, 4.4064925250700799, 1.7247861438873100, 1.5896086650724199, 1.7902444883090001, 1.4321727385044800, 0.3421186564422380, 0.1273706278835360},
        {71.0369595831105016, 3.0486123251336599, 1.1897445863205300, 0.3334689828806750, 1.4617374509420500, 4.7471297103653098, 0.6610893718730180, 0.4127117152260240, 3.1632696123842501, 1.2667152938989701, 0.9617917825613600, 2.5405198238978000, 2.2621290311982301, 0.2767556191290340, 0.1646525792231590},
        {65.8466114228780981, 2.8321347303003299, 1.3149762653464001, 0.1190419981500530, 1.3225208128515100, 4.8080761985003599, 0.2616661688509370, 0.8558359784654070, 5.6063880668791501, 2.2760009420119900, 1.8236560804196500, 2.0685204195039000, 1.6815937777265899, 0.3541729553396780, 0.0539422283067670},
        {65.0805006587196999, 1.4141694473454200, 0.5354010560586000, 0.0167157069580952, 0.8286770723913151, 3.2514980244189200, 0.2733508340107560, 1.2561568909079901, 4.0248798612303700, 1.0345303252153699, 1.2843712455746801, 1.0037006347098001, 0.8543261839069490, 0.1570836215147580, 1.6764116558950499},
        {52.2520987293263985, 2.3739088117261100, 0.2617636295563800, 0.0250111066668168, 2.0625175811523300, 5.8672865744616400, 0.2948537433775940, 2.8122415287173199, 2.8257286155124000, 0.8357819410007000, 0.9891496555221601, 0.7122255922380600, 0.6017266689013280, 0.1128455241273730, 1.9012895393390401},
        {65.3788187809299046, 1.5901685254279301, 0.7996771489890100, 0.0191850359687891, 0.7231198170051840, 2.9021435734538401, 0.1645137173015460, 0.9809516381901350, 4.6112455776556196, 1.2334025674415301, 1.4181127730360901, 0.7615864865489400, 0.6364712316503610, 0.1284278224687940, 1.8467895570715500},
        {65.0014088182618934, 2.2938871652067001, 0.3397786417178400, 0.0336061061988318, 1.8757372694497900, 4.1171339570015304, 0.3937877048187630, 1.1867429271713099, 3.9363926352934202, 1.0146686455325900, 1.1900265807707600, 0.6174893876380600, 0.5467982249610370, 0.0704654503800410, 0.4488952802154100},
        {65.9735163819205042, 1.1788034178950400, 0.9555780394525200, 0.0155201940439156, 0.1916260729284010, 1.8842128749306499, 0.1570810225933880, 0.3874711753808100, 4.1044434431566401, 0.8605141714017300, 1.3532478468269300, 0.6245002909503100, 0.5116887642762150, 0.1159367214818300, 4.2701498197612997},
        {67.7519084236303968, 1.1327542953379599, 1.0344523783038799, 0.0075163122181010, 0.0838439639143616, 1.8396747857153499, 0.1344101214477430, 0.4567157038050880, 5.1194525088259404, 1.1315170007886599, 1.8077203756012901, 0.8027370122575200, 0.6681267775466320, 0.1414635919479820, 1.5556302061922900},
        {63.8060287694512027, 2.4861917466576502, 0.2061771410359400, 0.0274510419370344, 2.2284574968792699, 5.0806775057576097, 0.3238023900781000, 1.9399178724625401, 3.2475508739236099, 0.9807844196774200, 0.9391560907185700, 0.8042538431592500, 0.7137239462937970, 0.0864155510296670, 0.5884073129039680},
        {68.6426794016761050, 2.0771625432433898, 0.2811679997371100, 0.0048823460678591, 1.7584538862827499, 3.6133892768095999, 0.2110548602668130, 1.1781953837437700, 4.0872632845438099, 1.2530179314471901, 1.0709870381716800, 0.9529497562716100, 0.7202829517723330, 0.2184704065235370, 0.2147287400662350},
        {66.6695552686660022, 1.5017914524479199, 1.0175769760270299, 0.0150845275276197, 0.4389019689591010, 3.0324154909090701, 0.1188838167701360, 0.9355893538782140, 3.9868593803668699, 1.4977500615043600, 1.1528011578145201, 1.3920681642475199, 1.1403575589947399, 0.2573283766753750, 1.8766161361107401},
        {63.7509167868844031, 2.1282093137522198, 0.5221425660562700, 0.0170111974278129, 1.5328281510903401, 4.6429702936953401, 0.2029595463175230, 1.8679360941059600, 3.3019104918506099, 1.1295492971062400, 0.9966430561168500, 0.7268330827719200, 0.5878375031172141, 0.1411743461584150, 0.6955349761623070},
        {68.7870148096966005, 2.2859116822066698, 0.2591709952853900, 0.0226500380327224, 1.9740869263507199, 4.5559437294149800, 0.2593988429261320, 1.5659321633848200, 2.9916289261081901, 1.1555469742477400, 0.8913901581271800, 0.3403351736450700, 0.2829674527050660, 0.0570590877143790, 0.8283814157892661},
        {66.5297655639513010, 1.6041479630216300, 0.3048120276782700, 0.0137743846118923, 1.2561283930541300, 3.2637024517682800, 0.1986760439278610, 1.2118262280308201, 3.0748780814411698, 0.8726974000228001, 0.8289406227040100, 0.7102966095162200, 0.6070563061516340, 0.1018471853526250, 2.5470779545250801},
        {65.4366637518740930, 2.6348985568959602, 0.2317106260321100, 0.0109884722325546, 2.3533057245730600, 5.1918256892709600, 0.2853190571109960, 1.8899074914997600, 4.5433749879741603, 1.6403917568875801, 0.9129733120383901, 0.7818692902417900, 0.6121599956564840, 0.1540118015264230, 0.4129857931455520},
        {64.7354476818022988, 2.1189018207645498, 0.1925653164605000, 0.0102439335947793, 1.8930445118856500, 3.9273976135201800, 0.2181384061916990, 1.3325570724082501, 3.5687221827012898, 0.9748637920321100, 1.1167634488553699, 0.9259313049807401, 0.8174606037551370, 0.1084869500807740, 2.2983352244727402},
        {75.4008119368681946, 0.7237452945006900, 0.7065832488597000, 0.0000464183523405, 0.0162067057103883, 0.9785679453041800, 0.0864953973146780, 0.0177375811427254, 10.4663572681819002, 2.2383358158652000, 4.6776639109712903, 1.6176535041696001, 1.1949016826130501, 0.4351498831728550, 0.1876100522447500},
        {58.3827783529704973, 1.9964241013653801, 0.1317857737951000, 0.0056404617707457, 1.8392817744195900, 3.1749241007453000, 0.1933520552158190, 0.7859377621639820, 3.3887723811903001, 0.9942837531510300, 0.9902954575825400, 0.7783881752438500, 0.6804006762329490, 0.0992196994774940, 4.9547520909197500},
        {68.6136683891606936, 2.2445022198023299, 0.3983062392165400, 0.0327762728144876, 1.7692399355276500, 3.8533314659132998, 0.2664854187506620, 1.0539525740541800, 3.5681578539484202, 0.8911313582910300, 1.1410936417084701, 1.3705033275954199, 1.2461988931581400, 0.1274166823624940, 0.8820702197604930},
        {73.5258606948006985, 0.5587074816539400, 0.5479347159037600, 0.0052563740811422, 0.0055270384141437, 0.9283918076159700, 0.1552787535810010, 0.1041841656440850, 5.6091246812165396, 1.5844264895952300, 1.8703185627132100, 1.9443671159961200, 1.6819629832051199, 0.2852868349768300, 0.2033434827436760},
        {58.4651634628330967, 3.0436089678257101, 0.0770284214978100, 0.0102842889678598, 2.9483979954010500, 5.8348647117524104, 0.4200680408591280, 1.9794109121524599, 2.9916048515817302, 1.1957006574327800, 0.9123965360660100, 0.8692130463188100, 0.7245281788833819, 0.1459212169564380, 0.5434232742345910},
        {67.0801105882212028, 2.2140111283117201, 0.2901741457801700, 0.0093694103363049, 1.8768268409045701, 3.7098723579877300, 0.2210530307594640, 1.0434872303242699, 4.1221868035922702, 1.1383287528051400, 1.0441885883615201, 1.2118814879564299, 1.0439508357446701, 0.1742897065495440, 1.5047787019963701},
        {66.1282085610217933, 2.0859409617594902, 0.3321023878367300, 0.0195580180833730, 1.6949477752666799, 3.4324721688541202, 0.2293970923909110, 0.9381763162197250, 3.5579788383434301, 0.8746937848194000, 1.1765415518141400, 0.6959792415999300, 0.5964614947313440, 0.0992242985561660, 1.6867116003742200},
        {63.1360145244764013, 1.7276920346342099, 0.4158980446475600, 0.0147732219444094, 1.2578800816351099, 3.1815323915587701, 0.1584761839628680, 1.0831022115899200, 3.5059178345384598, 1.1774153006096599, 1.0308006483634300, 0.8937896877522800, 0.7600253166535040, 0.1347494598772770, 3.0552619959960001},
        {62.2312498908622018, 1.3425860898392501, 0.7714702136416000, 0.0160962732031038, 0.5223707162809890, 2.4563767818548898, 0.1629541047690280, 0.6753774829085730, 4.5901768706880697, 1.2720198762073001, 1.7572528889874000, 1.5412559236758101, 1.2258019650030101, 0.3243101912661860, 4.7267510240219197},
        {51.7274359777468007, 1.3762892505531299, 0.4398933249353800, 0.0149210670572444, 0.8908532794498850, 3.1050965405832498, 0.1474435831135070, 1.1822977236573600, 2.6265963476739400, 0.6582715117258900, 1.0462689078372100, 1.2835094526819300, 1.0458677658689599, 0.2394937700971700, 7.3330157079253198},
        {65.1832129836368068, 1.3308989746258200, 0.6419617253231600, 0.0257662438342408, 0.6279830647943210, 2.5115973437845600, 0.1360597739544290, 0.7349230362168130, 4.1748331092570696, 1.1880865424821700, 1.4392484904659100, 1.0851991879442300, 0.9106910057614930, 0.1801383802803400, 3.5534626442569399},
        {65.1722066137321008, 0.9847936727648900, 0.8139665964980900, 0.0159661525161567, 0.1467902693133990, 2.1751282461166399, 0.2273683903673600, 0.5917311878104240, 4.4426540390806197, 1.0252492559681201, 1.6591343904425200, 1.2247518526622800, 1.0178858052798900, 0.2187445498100540, 5.2767008985836297},
        {58.1839996719411019, 1.2745991234381200, 0.5087291528420400, 0.0116620632696254, 0.7199703061647180, 2.6471651394396898, 0.1346438681909850, 0.9618052159853290, 4.4680375991302599, 0.9671686892907700, 1.7919425386781600, 0.6350144457537700, 0.5118820173576490, 0.1235847831953900, 5.6101386342351898},
        {60.9783226067194022, 1.7520613575133801, 0.3447334139656100, 0.0081850194324460, 1.3660861329872800, 3.0769134039666501, 0.1646808028139690, 0.9657969871655681, 3.5073776844789899, 1.0589578139407800, 1.3199497540770300, 1.4569379878102600, 1.2368810706077400, 0.2208300398545260, 3.0252585938289398},
        {64.4340416971975003, 2.5317241970753801, 0.4547479120743300, 0.0270499109130071, 1.9947700252126499, 4.2858619662678397, 0.1721593175430910, 1.2761001660409499, 3.7882251231709501, 1.0364036057846999, 1.2139150970483601, 0.6470439779865300, 0.5071168733302760, 0.1413479566378580, 0.5646288850421260},
        {61.6084643722957992, 2.7421206385695300, 0.3183223810078300, 0.0130908278273694, 2.3689824165243198, 5.0599234448245500, 0.1019772035757640, 1.7726567983601600, 3.2586794021328598, 1.0928267646962500, 1.0670930360176700, 0.5534008148374100, 0.3853693157018370, 0.1673430301912830, 0.4645622364689930},
        {63.3425894825026035, 2.0770610989045002, 0.9176320375136600, 0.0214327411031192, 1.0691808468240300, 4.0777124481922797, 0.1381398708415770, 1.6453059948447999, 3.8933826256107200, 0.8824923231717500, 1.1792141238934699, 0.6725034439948500, 0.5513326601246010, 0.1229048210088950, 2.2181996675429998},
        {73.6819371429031946, 1.5515073746097601, 1.1599483287058501, 0.0099367700361341, 0.3452717347950480, 2.1142295691936499, 0.0984790737582980, 0.3383341982869440, 4.9343061201580998, 1.3776838391961099, 1.6240158450896001, 0.7897498226408300, 0.6362362822680721, 0.1467262096545030, 0.3502248052577950},
        {60.3372657881363992, 2.8839565562974099, 0.3302567471520400, 0.0204025938227375, 2.4877661534328901, 7.2199505998081301, 0.1924610406508340, 3.5199076430244198, 3.0122203724251500, 1.1186122208275200, 0.9378532395666700, 0.7437201792729100, 0.5739947429777670, 0.1716410406609440, 0.9219729860509100},
        {66.6582552759964955, 2.3806811435282200, 0.5467385941192900, 0.0177994511149819, 1.7352977833776300, 3.6359421189229599, 0.1353855085313140, 0.8546822203467310, 4.2030935139670600, 1.2819585665854700, 1.1416479912474100, 1.0577851585332800, 0.8119624547681640, 0.2564518993440710, 1.4430608266703999},
        {66.2605700124145045, 1.9725036257577699, 1.0017797963452200, 0.0241520402829849, 0.8764837954475410, 3.1071204594514898, 0.1334991924316850, 0.7774896350616270, 4.6453674545764398, 1.1104177260333801, 1.4617096392183300, 0.5355598034023100, 0.4405329670292560, 0.0974022686979620, 1.2282506735336101},
        {61.2385429698021966, 2.7924780741455799, 0.3953878167382300, 0.0187788429490894, 2.3209182678221900, 4.6709304608049402, 0.2033139413462950, 1.4715307490769300, 3.3164885884003898, 0.9092703100111200, 0.9855392692877800, 1.0584404145814099, 0.8623202587446670, 0.2028654911263600, 1.0446488337108699},
        {60.9029865455340982, 2.6298980327403498, 0.4352531478154400, 0.0168853033067293, 2.1075250902918699, 4.8269626297758403, 0.1423297593269550, 1.6531277110819100, 3.9498459044449201, 1.2656060435560501, 1.1873439488389601, 0.5985550864208899, 0.4183036651365550, 0.1834338795019690, 1.3978079566834400},
        {66.0246634639938037, 2.1028954257736001, 0.3853821815158100, 0.0098759629294705, 1.6577577317100101, 3.9303063182853202, 0.1456888136313520, 1.5062944867545400, 3.8221228218569099, 1.1660086435990000, 1.2969390684240900, 0.5491597386683700, 0.4479769060371690, 0.1039281822680350, 1.0040790741908101},
        {61.7962989451465035, 2.6184003154161801, 0.3146839932446600, 0.0236797808019915, 2.2509577681936399, 5.1589831468619796, 0.2201894128400430, 1.6751744171809999, 3.2960739124748200, 1.0202245396993599, 1.0348806296893500, 0.6472538985319100, 0.5110074324040210, 0.1385081071653150, 0.6955705594362130},
        {70.7733337985313966, 1.9355920376868201, 1.0068960857383900, 0.0112760722009853, 0.8537632879019700, 3.8011816369540399, 0.0941923854635010, 1.2428767250743999, 4.0206514796902404, 1.3564679588100601, 1.0192359885657001, 0.6963219162077400, 0.5513644758002700, 0.1515269385995740, 0.1784449252600520},
        {62.4536192662873972, 3.0998475928517299, 0.2924988702890200, 0.0235237775681583, 2.7398153924969901, 6.7213942008627896, 0.2783504051569710, 2.6230579074800300, 3.1765035347916202, 0.9676741401201400, 0.9167390456143000, 0.4705207516255200, 0.3131477204929070, 0.1573829177213430, 0.3668989391030520},
        {64.2716452315813029, 2.3518588300805900, 0.8348737122263500, 0.0241313415858002, 1.4367591833897999, 4.8746304928667001, 0.1039815993860030, 2.2514784610491501, 3.3341048792097201, 0.8713738668375700, 0.9055328785259000, 0.3963446569272800, 0.2728479613021620, 0.1274838563363260, 0.9932975459328330},
        {70.9055774997285937, 1.9374316605097901, 0.6751881192557400, 0.0325894521194954, 1.1644314979700601, 2.5644073079677598, 0.1442742377093110, 0.3802667769090390, 4.7796318533654896, 1.2210156550015201, 1.2155999577775400, 0.6939558036658900, 0.6147818356183170, 0.0829039047949180, 0.2314081111139790},
        {68.4061620450204941, 2.2669723948629898, 0.5812336627215600, 0.0166111109177791, 1.6049092356008301, 4.1043760172260999, 0.1449547809226030, 1.2692077318198800, 4.3503305029135202, 1.1983432460484100, 1.5034446772509400, 0.8656109530631400, 0.6114215942870370, 0.2663488934018120, 0.4595493520983920},
        {61.7002932289103967, 2.7287730302458799, 0.4213175914525600, 0.0137546688174695, 2.2329256325477300, 4.4993147449647601, 0.1435783506910230, 1.4514002645370301, 3.4682220854777102, 1.1009001437186501, 0.7561706949387100, 0.9699139047081300, 0.7444463831763030, 0.2330934814531820, 0.9677673445800320},
        {64.9722884769331017, 2.3446453897091302, 0.5312886662355500, 0.0268681760716447, 1.7219158712271101, 4.8157606391788903, 0.1882546983490410, 2.0119573070438199, 3.8201424962846899, 1.2228931466104200, 0.8530188077009599, 0.9734855963840000, 0.8143835681040200, 0.1692291004498830, 1.1769186260041700},
        {72.1619460710113998, 0.4642308161260800, 0.2584777233206000, 0.0098147331181622, 0.1924395677759070, 0.8865277471774400, 0.1790146386911860, 0.0792387742775702, 8.3448039207207607, 1.9394502844089900, 3.7498953569121598, 2.3676860815358700, 1.9395423826302900, 0.5034644530518190, 0.1043185237729030},
        {81.2102174085253949, 0.1749453901054600, 0.1463754419327300, 0.0156157781800914, 0.0131164987062959, 0.5937176201648799, 0.1920349753307420, 0.0255367847864107, 4.8851722542965499, 1.5556468643742001, 1.5350995066152999, 1.2961140364732400, 1.1777708424372699, 0.1396390523162130, 0.2301286480789030},
        {75.4019924049743935, 0.2795374593217700, 0.2214744373467300, 0.0070158226490946, 0.0502623274324918, 0.5945110636138800, 0.1597241761922700, 0.0392887120358409, 9.1736332026364202, 1.9341563710211700, 3.7686029957060598, 2.1809408406607500, 1.6787834317732799, 0.5594294856513640, 0.2395858352242610},
        {73.3053335345063033, 0.1871396465247800, 0.1563855971779500, 0.0220865078475327, 0.0088478296412831, 0.9395900101427200, 0.4450229724022990, 0.0086811728087355, 3.6019239921148198, 1.3533771661395400, 1.0305999641280701, 3.6326216466308701, 3.4494489567811999, 0.2819760070412800, 0.1221097828292560},
        {76.2060432119561995, 0.4325503129700200, 0.3757596612606600, 0.0002220315326724, 0.0553529114938414, 0.7924945300079700, 0.1522007164330010, 0.0523663401304759, 8.3495362541725804, 2.6483331028879702, 2.5762130640465299, 2.3700499506910000, 1.9610148924473001, 0.4927960667372700, 0.1625629241174520},
        {80.0217072766331938, 0.3337723311486700, 0.3098280497151100, 0.0246138408107583, 0.0002776952974557, 1.1441087055605501, 0.4642336815711870, 0.0035396160224366, 3.4980869089741198, 1.0734508794663200, 0.8408576563849400, 2.5449492968115899, 2.4415313683188500, 0.1638719377658330, 0.0751183199373880},
        {63.3183025734807998, 0.3671281990061700, 0.2751010354584400, 0.0001053643228346, 0.0902183040791087, 0.9495686757056400, 0.1761687006208770, 0.0946168928935620, 9.9445405594863203, 2.9676234958540202, 4.0448492983779296, 3.2667625258930100, 2.7009042604726998, 0.6439393994536430, 0.2568239024633530},
        {70.5416132550230941, 0.3838608029506600, 0.3090645492153900, 0.0092499425722252, 0.0641693521523905, 0.7055939375248700, 0.1516556411335160, 0.0717505205327313, 9.5304978770209807, 2.5393676175495998, 4.2164957921169304, 2.3903911136180400, 1.7933598340879100, 0.6586848536302909, 0.2623596033186000},
        {72.8433110969580042, 0.5592764807417200, 0.3465551204275400, 0.0374652619439644, 0.1715691987535730, 0.9515969142527499, 0.1724327016236630, 0.0677102064024950, 7.1700036072630597, 2.0017994840093398, 2.9410183841570898, 2.3543057841353301, 2.0017199464244202, 0.4079180894265870, 0.1636792761193960},
        {67.4529203506776014, 0.2859549058284100, 0.2846629285645600, 0.0005442462671823, 0.0007355134396079, 0.7322097409956400, 0.2069230616405380, 0.0989305760949719, 7.5616587160385400, 2.2648591760383900, 3.6657259776976598, 2.5551175496298999, 1.8689600664014301, 0.6994177725471930, 0.3387616263389220},
        {80.2796391615915041, 0.1556402496024800, 0.1535930137165700, 0.0018176133591794, 0.0002560660810076, 0.3791364680584500, 0.0952557573220930, 0.0545877193596596, 6.0982278767667104, 1.3159523017995800, 2.5441181991002502, 1.1197627943978301, 0.9909372350524850, 0.1472570678974990, 0.1910430667522860},
        {72.0795956412119949, 0.2908290954234800, 0.2685753713136200, 0.0000026899511596, 0.0217502279604531, 0.6655325572891400, 0.1022156328343580, 0.1075642257569740, 6.1497688186769297, 1.5308909271775200, 2.3446614756158901, 0.7364007347224900, 0.5863295778086690, 0.1602622394908200, 0.9445048771474520},
        {82.0801306747739972, 0.2231221697330200, 0.1951723127928800, 0.0284297847664448, 0.0005410885171386, 0.8630316547631500, 0.3144303769882270, 0.0022356397096957, 3.4340986196408498, 1.0667308052252200, 0.9480658016442201, 1.7331152339208800, 1.6515661317245600, 0.1223313349181440, 0.0758291703312180},
        {72.1760237592667977, 0.2589646214871000, 0.2478656019825500, 0.0103850506177992, 0.0007578003586133, 0.7832195095554200, 0.1719888340065270, 0.1032562640881590, 8.4628549467001104, 2.4680919516675299, 3.7288860579824501, 2.3802939551575002, 1.8227037770059400, 0.6227580996971940, 0.3294665998468250},
        {67.9341806980634999, 0.4884903349182000, 0.2678947692933900, 0.0024575246545169, 0.2141303124958540, 1.0958044320052001, 0.2022733448018100, 0.1340318275195930, 8.5897707378330797, 2.7582388387979200, 3.7676487215068302, 2.7968235157881800, 2.2504985601289000, 0.6180263800486760, 0.2842691798073820},
        {63.5278538181136980, 2.3697724053613900, 0.3505533230177600, 0.0160080182451807, 1.9671221992380501, 5.1631482919346903, 0.2008851983811440, 2.1326623167247600, 3.0672916620334800, 0.8699977596752601, 0.9033228844716900, 0.7812965565127000, 0.6426488509419240, 0.1400485834646120, 1.4354375517728899},
        {70.3471930066096007, 2.3124308542231899, 1.3222038667006599, 0.0274897102094513, 0.8751909145918120, 4.0319969077351603, 0.1928756362361380, 0.4839385093342230, 8.9686245756862295, 2.6623935491122501, 2.3120372919889398, 1.7024465301272200, 1.3864187365309100, 0.3572448037041060, 0.2735533711621800}};

    // array where the SOGA data set without global will be stored.
    double noGlobal[COUNTRIES_COUNT][SOGA_COUNT / COUNTRIES_COUNT];

    // array with the categories represented by integers.
    char sShowCategories[480] = "0: Baseline Life Expectancy\n1: Air Pollution\n2: Ambient PM\n3: Ozone\n4: Household AP\n5: Environmental Occupational Hazard\n6: Occupational Hazard\n7: Unsafe Hand Washing\n8: Metabolic Syndrome\n9: Deitary\n10: High Fasting Plasma Glucose/Sugar\n11: Tobacco\n12: Smoking\n13: Secondhand Smoke\n14: Unsafe Sex";

    // used for for loops for the entire source code.
    int i;
    // int k;

    int num;      // how many countries the question will print.
    int category; // the category the user will choose.

    /* Variables for question 1 */
    String countryName;
    /*  the following variable/s should be here but are reliant on the user input so it's defined later on:

        double oneOutput[num][2]; // output of question one.
    */

    /* Variables for question 2*/
    double twoOutput[4];

    /* Variables for question 3*/
    String triOutput;

    /* Variables for Question 4*/
    String countrySelected, above, below;
    double forOutput[3]; // note that forOutput[0] is the value before the countrySelected
                         // and forOutput[2] is the value after.
                         // forOutput[1] is the value at the index

    /* Variables for Question 5*/
    int fivOutput;

    // call removeGBL function to make an array without the global data values
    removeGbl(SOGA, noGlobal);

    // ================
    // ===== QUESTION 1
    // ================

    printf("=====\nQUESTION 1.\n=====\033[1;33m\nWhat are the names and values of the top `num` countries with the highest `category`?\n\n\033[0m");

    // get the user inputs for the parameters of questionOne();
    printf("How many countries do you want to print?\n>. (int) ");
    scanf("%d", &num);
    double oneOutput[num][2]; // output of question one.

    // print out the categories for the user.
    printf("\n=====\n%s\n=====\n\n", sShowCategories);
    printf("What category do you want to use?\n>. (int) ");
    scanf("%d", &category);

    // execute the function.
    questionOne(num, category, noGlobal, countries, oneOutput);
    // print result of the function.
    // type cast oneOutput[i][0] because we want that to be a whole number
    printf("\n=====\nOutput of QUESTION 1.\n=====\n\033[1;33m");
    for (i = 0; i < num; i++) {
        int index = (int) oneOutput[i][0];
        strcpy(countryName, countries[index]);
        printf("%d. %s: %.5lf\n", (i + 1), countryName, oneOutput[i][1]);
    }

    printf("\033[0m");

    // ================
    // ===== QUESTION 2
    // ================

    printf("\n=====\nQUESTION 2.\n=====\033[1;33m\nWhat are the number of countries, minimum, maximum, and average values for `category`\n\033[0m\n");
    // // print out the categories for the user.
    printf("=====\n%s\n=====\n\n", sShowCategories);
    printf("What category do you want to use?\n>. (int) ");
    scanf("%d", &category);

    // execute the function
    questionTwo(category, noGlobal, twoOutput);

    // print result of the function
    printf("\n=====\nOutput of QUESTION 2.\n=====\n\033[1;33m");
    printf("Count: %d\n", (int) twoOutput[0]);
    printf("Min: %.8lf\n", twoOutput[1]);
    printf("Max: %.8lf\n", twoOutput[2]);
    printf("Avg: %.8lf\n", twoOutput[3]);
    printf("\033[0m");

    // ================
    // ===== QUESTION 3
    // ================

    printf("\n=====\nQUESTION 3.\n=====\033[1;33m\nGiven the last `num` countries below the average for `category`. What country is the median in that set?\n\033[0m\n");
    printf("How many countries?\n>. (int) ");
    scanf("%d", &num);

    // print out the categories for the user.
    printf("\n=====\n%s\n=====\n\n", sShowCategories);
    printf("What category do you want to use?\n>. (int) ");
    scanf("%d", &category);

    // execute the function
    questionTri(num, category, noGlobal, countries, triOutput);
    // print the result of the function
    printf("\n=====\nOutput of QUSESTION 3.\n=====\n\033[1;33m");
    printf("%s", triOutput);
    printf("\033[0m");

    // ================
    // ===== QUESTION 4
    // ================

    printf("\n\n=====\nQUESTION 4.\n=====\033[1;33m\nGiven the data sorted in descending order for `category` what are the countries above and below the data of `country`.\n\033[0m\n\n");
    // get what countries they want
    printf("What country do you want?\nInstructions, case sensitive and replace spaces and underscores\n>. (string) ");
    scanf("%s", countrySelected);

    // print out the categories for the user.
    printf("\n=====\n%s\n=====\n\n", sShowCategories);
    printf("What category do you want to use?\n>. (int) ");
    scanf("%d", &category);

    // execute the function
    questionFor(countrySelected, category, noGlobal, countries, forOutput);

    // determine the country names above and below the country
    for (i = 0; i< COUNTRIES_COUNT; i++)
        if (noGlobal[i][category] == forOutput[0])
            strcpy(above, countries[i]);

    for (i = 0; i< COUNTRIES_COUNT; i++)
        if (noGlobal[i][category] == forOutput[2])
            strcpy(below, countries[i]);

    // print the result of the function
    printf("\n=====\nOutput of QUESTION 4.\n=====\n\033[1;33m");
    printf("\nAbove: %s, %.5lf", above, forOutput[0]);
    printf("\n%s: %.5lf", countrySelected, forOutput[1]);
    printf("\nBelow: %s, %.5lf", below, forOutput[2]);
    printf("\033[0m");

    // ================
    // ===== QUESTION 5
    // ================

    printf("\n\n=====\nQUESTION 5.\n=====\033[1;33m\nIn `category`, what is the position of `country`'s data value if is sorted in increasing order?\n\033[0m\n\n");
    printf("What country do you want?\nInstructions, case sensitive and replace spaces and underscores\n>. (string) ");
    scanf("%s", countrySelected);

    // print out the categories for the user.
    printf("\n=====\n%s\n=====\n\n", sShowCategories);
    printf("What category do you want to use?\n>. (int) ");
    scanf("%d", &category);

    // execute the function
    questionFiv(category, countrySelected, noGlobal, countries, &fivOutput);

    // print the result of the function
    printf("\n=====\nOutput of QUESTION 5.\n=====\n\033[1;33m");
    printf("\nPosition: %d", fivOutput);
    printf("\033[0m");
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
