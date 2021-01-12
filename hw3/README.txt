HOMEWORK 3: RESIZABLE TABLE


NAME:  < Heqiong Xi >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Zixiang Zhou, Zhaoxi Sun, Yiming Zhang, Qizhi Lu >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 18h >



ORDER NOTATION:

Write each answer in terms of n = the number of rows and m = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get
O(1)
set
O(1)
numRows
O(n)
numColumns
O(n)
push_back_row
O(n^2)
push_back_column
O(n^2)
pop_back_row
O(n^2)
pop_back_column
O(n^2)
print
O(n)

TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Table class design & implementation?
I use print to debug my code for some loops and function. I test the corner case by using "print" to print all the possible outputs.

EXTRA CREDIT: 
Indicate here if you implemented push_back for multiple rows or
multiple columns and/or rewrote your code using pointers instead of
subscripts for extra credit.  Also document the order notation for
your multi-row and multi-column push_back functions.
I implemented the extra credits and the both orders of extra credits functions are O(n^2).

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

