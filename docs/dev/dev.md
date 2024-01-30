# CCPROG2 Machine Project

**SoGA** Data Analysis.

## Activity 3: Instructions

Make 5 questions that use the following algorithms:

1. min or max
2. `count` or `sum` or `average`
3. linear search
    > Finding the target by comparing all the elements if it is equal to the target element. [Visual](https://www.mathwarehouse.com/programming/gifs/binary-vs-linear-search.php#binary-vs-linear-search-gif)
4. binary search (at least one)
    > Finding the target value from a sorted array through comparison (comparing the target element with the middle element). [Visual](https://www.mathwarehouse.com/programming/gifs/binary-vs-linear-search.php#binary-vs-linear-search-gif)
5. selection sort (at least one)
   > Setting a minimum value and comparing it with the rest of the elements. If none of the elements are smaller it goes to the end. [Visual](https://commons.wikimedia.org/wiki/File:Selection-Sort-Animation.gif)

   * At least three of the questions must have more than one parameter.
   * At least one of the questions should produce an array of strings,

## Activity 3: Output

Note. Parameters are enclosed by backtick, that is, `parameter`.
These questions will be given an example parameter and the expected answer will be
for that parameter *only*.

Question 1. What are the names and values of the top `num` countries with the highest `category`?

    * Algorithms: selection sort, maximum
    * Expected Answer: j
        (let: num = 5, category = Ozone)
        1. Nepal: 0.333468983
        2. India: 0.206115793
        3. Bhutan: 0.165264277
        4. North Korea: 0.16457043
        5. Bangladesh: 0.133546667

Question 2. What are the numbers of countries, minimum, maximum, and average values for
*Ozone*?

    * Algorithms: count, minimum, maximum, and average
    * Expected Answer:
        Count: 203
        Minimum: 0.000002689
        Maximum: 0.333468983
        Average: 0.023906429

Question 3. Given the last `num` countries below the average for `category`.
What country is the median in that set?

    * Algorithms: selection sort, average, count
    * Expected Answer:
        (let: num = 5, category = Dietary)
        Median: 0.86999776

Question 4. Is the Philippine's `category` above the average?

    * Algorithms: average
    * Expected Answer:
        (let: country = Philippines, category = Air Pollution)
        Yes

Question 5. Does the mode of the data in Ambient PM ever repeat?

    * Algorithms: Binary Search
    * Expected Answer:
        No

### Requirements

#### Algorithms Used

> Note. Algorithms 4 and 5 are required to be used at least once. No specific instructions for algorithms
1 to 3.

1. Minimum or maximum           Q1 and Q2.
2. Count or sum or average      Q2 to Q4.
3. Linear search                Not used
4. Binary search                Q5
5. Selection sort               Q3

#### Parameters

Questions 1,2, and 4 use more than 1 parameter.

#### Output

Question 1 and 2 produce an array of strings as its output.
