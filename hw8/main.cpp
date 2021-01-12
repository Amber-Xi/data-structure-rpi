/*
A Node class is required (see the provided one in Rope.h), must have 
  weight, value, left, and right members.
  You can add other members.
The Rope class must have a constructor that takes a Node* 
  and uses that Node* as a root.
The Rope class must also have a function, expose_root() to return a pointer to the root Node.
  (This is poor class design, but will be necessary for us to autograde your data structure.)
*/

#include <cassert>
#include <string>
#include "Rope.h"

void StudentTests();
bool SAME(const Rope& r, const std::string& s);
void BasicTests();
Node* IndexTestRope();
Node* IndexTestRopestudent();
Node* ConcatTestRopeLeft();
Node* ConcatTestRopeRight();
Node* ConcatTestRopeLeftStu();
Node* ConcatTestRopeRightStu();

int main(){
	BasicTests();
	std::cout << "***Basic tests passed." << std::endl;
	StudentTests();
	std::cout << "***Student tests passed." << std::endl;
	return 0;
}

void StudentTests()
{
	Rope r1(IndexTestRopestudent());
	std::string s1 = "There is wifi to Amber";
	std::string rs1;

	r1.print(std::cout);
	r1.print_strings(std::cout);
	std::cout << "***Index test passed." << std::endl;
	std::cout << "***Basic report test passed." << std::endl;

	//Concat test
	Rope r2(ConcatTestRopeLeftStu());
	Rope r3(ConcatTestRopeRightStu());
	std::string s2 = "There is ";
	std::string s3 = "wifi t";

	std::cout << "***More index tests passed." << std::endl;

	r2.concat(r3);
	s2 += s3;
	std::cout << "***Concatenation test passed" << std::endl;

	//Split test
	Rope r4(IndexTestRopestudent()); //Wikipedia split @ 11
	std::string s4 = "There is wifi to Amber";
	Rope r5;
	std::string s5 = s4.substr(0,11);
	std::string s6 = s4.substr(11,11);
	r4.split(11,r5);
	r4.print(std::cout);
	r5.print(std::cout);
	r4.print_strings(std::cout);
	r5.print_strings(std::cout);
	std::cout << "***Split test passed" << std::endl;

	//Copy & Assignment tests
	Rope r9(IndexTestRopestudent());
	Rope r10(r9);
	std::string rs2;
	std::cout << "***Copy test passed" << std::endl;
	Rope r11;
	r11 = r9;
	std::cout << "***Assignment test passed" << std::endl;
}

//Used to compare a string and a rope that should be the same.
//You can uncomment the .report assert to test report on the whole string
bool SAME(const Rope& r, const std::string& s){
	/*std::cout << "Comparing string \"" << s << "\" to Rope:" << std::endl;
	r.print(std::cout);*/
	assert(r.size() == (int)s.length() && "ERROR: ROPE SIZE DOES NOT MATCH STRING SIZE");
	char c;
	for(unsigned int i=0; i<s.size(); i++){
		assert(r.index(i,c) && c == s[i] && "MISMATCH BETWEEN A CHARACTER IN ROPE AND STRING USING INDEX");
	}
	//assert(r.report(0,s.length()-1) == s && "MISMATCH BETWEEN ROPE.REPORT(0,length-1) AND STRING");
	return true;
}

void BasicTests(){
	Rope r1(IndexTestRope());
	std::string s1 = "Hello my name is Simon";
	std::string rs1;

	r1.print(std::cout);
	r1.print_strings(std::cout);
	assert(SAME(r1,s1));
	std::cout << "***Index test passed." << std::endl;
	assert(r1.report(0,s1.length()-1,rs1) && rs1 == s1);
	std::cout << "***Basic report test passed." << std::endl;

	//Concat test
	Rope r2(ConcatTestRopeLeft());
	Rope r3(ConcatTestRopeRight());
	std::string s2 = "Hello my ";
	std::string s3 = "name i";

	assert(SAME(r2,s2));
	assert(SAME(r3,s3));
	std::cout << "***More index tests passed." << std::endl;

	r2.concat(r3);
	s2 += s3;
	assert(SAME(r2, s2));
	std::cout << "***Concatenation test passed" << std::endl;

	//Split test
	Rope r4(IndexTestRope()); //Wikipedia split @ 11
	std::string s4 = "Hello my name is Simon";
	Rope r5;
	std::string s5 = s4.substr(0,11);
	std::string s6 = s4.substr(11,11);
	r4.split(11,r5);
	r4.print(std::cout);
	r5.print(std::cout);
	r4.print_strings(std::cout);
	r5.print_strings(std::cout);
	assert(SAME(r4,s5));
	assert(SAME(r5,s6));
	std::cout << "***Split test passed" << std::endl;

	//Copy & Assignment tests
	Rope r9(IndexTestRope());
	Rope r10(r9);
	std::string rs2;
	assert(r10.expose_root() != r9.expose_root());
 	assert(r10.size() == r9.size());
	assert(r10.report(0,r10.size()-1,rs1) && r9.report(0,r9.size()-1,rs2) && rs1 == rs2);
	std::cout << "***Copy test passed" << std::endl;
	Rope r11;
	r11 = r9;
	assert(r11.expose_root() != r9.expose_root());
 	assert(r11.size() == r9.size());
	assert(r11.report(0,r11.size()-1,rs1) && r9.report(0,r9.size()-1,rs2) && rs1 == rs2);
	std::cout << "***Assignment test passed" << std::endl;
}

//Also used for split() test
Node* IndexTestRope(){
	Node* ret = new Node;
	ret->weight = 22;
	ret->left = new Node;
	ret->left->parent = ret;
	ret->left->weight = 9;
	ret->left->left = new Node;
	ret->left->left->parent = ret->left;
	ret->left->left->weight = 6;
	ret->left->right = new Node;
	ret->left->right->parent =	ret->left;
	ret->left->right->weight = 6;
	ret->left->left->left = new Node;
	ret->left->left->left->parent = ret->left->left;
	ret->left->left->left->weight = 6;
	ret->left->left->left->value = "Hello ";
	ret->left->left->right = new Node;
	ret->left->left->right->parent = ret->left->left;
	ret->left->left->right->weight = 3;
	ret->left->left->right->value = "my ";
	ret->left->right->left = new Node;
	ret->left->right->left->parent = ret->left->right;
	ret->left->right->left->weight = 2;
	ret->left->right->right = new Node;
	ret->left->right->right->parent = ret->left->right;
	ret->left->right->right->weight = 1;
	ret->left->right->left->left = new Node;
	ret->left->right->left->right = new Node;
	ret->left->right->left->left->parent = ret->left->right->left;
	ret->left->right->left->left->weight = 2;
	ret->left->right->left->left->value = "na";
	ret->left->right->left->right->parent = ret->left->right->left;
	ret->left->right->left->right->weight = 4;
	ret->left->right->left->right->value = "me i";
	ret->left->right->right->left = new Node;
	ret->left->right->right->left->parent = ret->left->right->right;
	ret->left->right->right->left->weight = 1;
	ret->left->right->right->left->value = "s";
	ret->left->right->right->right = new Node;
	ret->left->right->right->right->parent = ret->left->right->right;
	ret->left->right->right->right->weight = 6;
	ret->left->right->right->right->value = " Simon";
	return ret;
}
Node* IndexTestRopestudent()
{
	Node* ret = new Node;
	ret->weight = 22;
	ret->left = new Node;
	ret->left->parent = ret;
	ret->left->weight = 9;
	ret->left->left = new Node;
	ret->left->left->parent = ret->left;
	ret->left->left->weight = 6;
	ret->left->right = new Node;
	ret->left->right->parent =	ret->left;
	ret->left->right->weight = 6;
	ret->left->left->left = new Node;
	ret->left->left->left->parent = ret->left->left;
	ret->left->left->left->weight = 6;
	ret->left->left->left->value = "There ";
	ret->left->left->right = new Node;
	ret->left->left->right->parent = ret->left->left;
	ret->left->left->right->weight = 3;
	ret->left->left->right->value = "is ";
	ret->left->right->left = new Node;
	ret->left->right->left->parent = ret->left->right;
	ret->left->right->left->weight = 2;
	ret->left->right->right = new Node;
	ret->left->right->right->parent = ret->left->right;
	ret->left->right->right->weight = 1;
	ret->left->right->left->left = new Node;
	ret->left->right->left->right = new Node;
	ret->left->right->left->left->parent = ret->left->right->left;
	ret->left->right->left->left->weight = 2;
	ret->left->right->left->left->value = "wi";
	ret->left->right->left->right->parent = ret->left->right->left;
	ret->left->right->left->right->weight = 4;
	ret->left->right->left->right->value = "fi t";
	ret->left->right->right->left = new Node;
	ret->left->right->right->left->parent = ret->left->right->right;
	ret->left->right->right->left->weight = 1;
	ret->left->right->right->left->value = "o";
	ret->left->right->right->right = new Node;
	ret->left->right->right->right->parent = ret->left->right->right;
	ret->left->right->right->right->weight = 6;
	ret->left->right->right->right->value = " Amber";
	return ret;

}
Node* ConcatTestRopeLeft(){
	Node* ret = new Node;
	ret->weight = 6;
	ret->left = new Node;
	ret->right = new Node;
	ret->left->parent = ret;
	ret->left->weight = 6;
	ret->left->value = "Hello ";
	ret->right->parent = ret;
	ret->right->weight = 3;
	ret->right->value = "my ";
	return ret;
}

Node* ConcatTestRopeRight(){
	Node* ret = new Node;
	ret->weight = 2;
	ret->left = new Node;
	ret->right = new Node;
	ret->left->parent = ret;
	ret->left->weight = 2;
	ret->left->value = "na";
	ret->right->parent = ret;
	ret->right->weight = 4;
	ret->right->value = "me i";
	return ret;
}


Node* ConcatTestRopeLeftStu(){
	Node* ret = new Node;
	ret->weight = 6;
	ret->left = new Node;
	ret->right = new Node;
	ret->left->parent = ret;
	ret->left->weight = 6;
	ret->left->value = "There ";
	ret->right->parent = ret;
	ret->right->weight = 3;
	ret->right->value = "is ";
	return ret;
}

Node* ConcatTestRopeRightStu(){
	Node* ret = new Node;
	ret->weight = 2;
	ret->left = new Node;
	ret->right = new Node;
	ret->left->parent = ret;
	ret->left->weight = 2;
	ret->left->value = "wi";
	ret->right->parent = ret;
	ret->right->weight = 4;
	ret->right->value = "fi t";
	return ret;
}
