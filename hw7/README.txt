HOMEWORK 7: SPATIALLY-EMBEDDED ADJACENCY MAPS


NAME:  < Heqiong Xi >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Qizhi Lu >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10h>



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity along with a short
justification for each of the functions below:

n: The total number of users
l: The total number of users with a location
d: The total number of users with degree >= 1
m: The total number of connections
p: The number of users that a function will print out

loadConnections():O(log(n))
I need to over all the list of users' id and because of the order notation of map is 0(log(the number of elements)), it is O(log(n)).

loadLocations():O(log(l))
I need to over all the list of users' locations and because of the order notation of map is 0(log(the number of elements)), it is O(log(l)).

printAllUsersWithinDistance():O(log(l+p))
I need to over all the list of users' locations to check the users within the given distance and then I need to print all satisfied users. Thus, the order notation is O(log(l+p)) by using map.

printDegreesHistogram(O(log(n+p))):
At first I need to go over the users' list, and add the degree of them, then print out. 

printDegreesOfAll()O(log(n+p)):
I just need to go over the list simply and print out.

printFriendsWithDegree():O(log(n+p))
I need to find the users' friends which in the number of connections and print out those friends' degrees which is the number of users can be printed out.

printFriendsWithinDistance():O(log(m+p))
I need to find the users' friends first which is the number of connections and check their distances with the given user and then print out those friends' degrees.

printUsersWithinIDRange():O(log(n+p))
Go over the whole users list is required, then checking the offset with the iterator and print out.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






