HOMEWORK 6: CROSSWORD BLACKOUT


NAME:  < Heqiong Xi >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Qizhi Lu, Tianjian Xu >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 60h >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h)?

The order notation of creating and filling the dimension of the board is O(w*h), because of two "for loops".
The order notation of number of words in the dictionary is O(d.size()), because I need to go over the whole list.
The order notation of number of spaces within a letter is O(l.size()), because it is for me to cover the list one by one.
The order notation of number of constraints is 0(c.size()), because it is for me to create vector --- the index of the list is the value of constraints and the value of the list is the repeated times of constraints.
The order notation of getting the across word is 0(the row of grid times the column of grid), because I need to go over all the columns and rows and find the word.
The order notation of getting the across word is 0(the row of grid times the column of grid), same reason like above.
The small combination algorithm is 0(n) and the large one 'Combination' is O(n^3). I combined the specific length for the number of different constraints first, and then I combined the specific length combinations to the big vector.



DESCRIPTION OF YOUR ADDTIONAL PUZZLES/DICTIONARIES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).
My puzzle is very simple, just with some simple words. The interesting one is the third case with has my name on there.

SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES/DICTIONARIES:
# of solutions & approximate wall clock running time for different
puzzles / dictionaries for a single solution or all solutions. Be
specific about which puzzle/dictionary/parameters you were timing.

Dic                   Board             number of solutions(all solutions)
blackout_dic1         Blackout1              3          a few seconds
blackout_dic2         Blackout1              3          a few seconds
blackout_dic1         blackout2              1          a few seconds
blackout_dic2         blackout2              0          a few seconds
blackout_dic1         blackout3              4          a few seconds
blackout_dic2         blackout3              3          a few seconds
sporcle1_dict1        sporcle1_constraintsA  1 		a few seconds
sporcle1_dict3        sporcle1_constraintsA  1 		a few seconds
sporcle1_dict4        sporcle1_constraintsA  1		a few seconds
sporcle1_dict1        sporcle1_constraintsB  40		a few seconds
sporcle1_dict3        sporcle1_constraintsB  40		a few seconds
sporcle1_dict4        sporcle1_constraintsB  40		a few seconds
dic_case              case 1                 2		a few seconds
dic_case              case 2                 2		a few seconds
dic_case              case 3                 2		a few seconds


MISC. COMMENTS TO GRADER: 
(optional, please be concise!)


