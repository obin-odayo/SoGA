/*
	CCPROG2 MP2 header file (.h source code)
    
    Do not forget to encode your name, section and date of submission.
    
    LASTNAME1, FIRSTNAME1:                               SECTION1:
    LASTNAME2, FIRSTNAME2:                               SECTION2:
    
    DATE SUBMITTED     :
		
	Rename this file using your last names in alphabetical order, for example CRUZ_TAN.h
		
	Make sure to include your header file in your C source code for MP Part 2.  
*/

/*
    Encode below this comment the following:
    
    1. #define directives
    2. typedef alias(es)for your string(s)
    3. declaration of your user-defined struct data type(s)
    4. typedef alias(es) for your struct data type(s)

    You may have as many typedef as you deem necessary.

    This header should NOT include the codes for any function definitions.  Function definitions
    should be encoded in your C source file only.
*/

/* You have to put an inline comment for each struct member as part of the documentation. */

#ifndef GANITUEN
#define GANITUEN

#define COUNTRIES_COUNT 203
#define SOGA_COUNT 3045

typedef char String[32];
typedef char LongString[64]; // used in questionFor

/* data [structure]
    - stores the data values of a country

    @fields
    // REMARK, these are in the same order as it is in the SOGA dataset
    - name [String (char[32])], country name
    - BLE [double], Baseline Life Expectancy
    - AIR [double], Air Pollution
    - APM [double], Ambient PM
    - OZN [double], Ozone
    - HAP [double], Household AP
    - EOH [double], Environmental Occupational Hazard
    - OCC [double], Occupational Hazard
    - UHW [double], Unsafe Handwashing
    - MTB [double], Metabolic Syndrome
    - DTY [double], Dietary
    - HFP [double], High Fasting Plasma Glucose / Sugar 
    - TBC [double], Tobaccco
    - SMK [double], Smoking 
    - SSK [double], Secondhand Smoke
    - SEX [double], Unsafe Sex
*/
typedef struct data
{
    String name; // country name
    double BLE; // Baseline Life Expectancy
    double AIR; // Air Pollution
    double APM; // Ambient PM
    double OZN; // Ozone
    double HAP; // Household AP
    double EOH; // Environmental Occupational Hazard
    double OCC; // Occupational Hazard
    double UHW; // Unsafe Handwashing
    double MTB; // Metabolic Syndrome
    double DTY; // Dietary
    double HFP; // High Fasting Plasma Glucose / Sugar 
    double TBC; // Tobaccco
    double SMK; // Smoking 
    double SSK; // Secondhand Smoke
    double SEX; // Unsafe Sex
} data;

#endif
