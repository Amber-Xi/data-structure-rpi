#include<iostream>
#define initial_size 100
class Node_year
{
	string title;
	int year;
	Node_year* next;
};
Node_year* yearBook[initial_size];
for(int i =0; i<initial_size; i++)
{
	yearBook[i] = NULL;
}

void add()