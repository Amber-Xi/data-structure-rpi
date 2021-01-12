HOMEWORK 8: ROPES


NAME:  < Heqiong Xi >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Yimin Zhang, Huancheng Sun, Tianjin Xu >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 25h >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor:
1)&2) O(m) because of the processing of constructing rope, it needs to go through all the nodes on that rope

Construct from Node*:
1£©O(log(m)) The construct take O(1) to "steal" the rope.It takes O(log(m)) by adding all the right's weight.
2) O(p) one left Node and a lot of right subtree, taking O(p) to add it all up

Index:
1) O(log(n)) because of binary tree, index function go over one of the subtrees, so  it will take log(n) to reach the leaf.
2) O(p) in the unbalanced tree, the index will go over every nodes to reach the leaf.


Report:
1)O(log(n)) to reach the leaf and O(1) to reach another Node
2)O(p+v) In the unbalanced, O(p) to reach the leaf, and it have to iterator going through all the leafs which a node only has one character.

iterator operator++:
1)O(log(n)) When going the rightest or the leftest of the subtree taking O(log(n)) to reach, but generally taking O(1)
2)O(p) when a lot of nodes on the tree, it will cost a lot to find the right subtree

Split:
1)O(log(n)) taking O(log(n)) to reach the objective node, and also taking O(log(n)) to reach the end of the rope
2)O(p) O(p) to reaching the end and O(p) to return

Concat:
1)&2)the concat operation depend on the copy constructor, thus the order of moving is just O(1)

TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?
I am checking all the test functions. I am doing the index functions and concatenation test functions, then go split to test my split functions and then test copy and assignment functions, which first in the general cases. Talking about the corner cases, I general go through my case. 


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

