#include<iostream>

class Node
{
	public:
	int value;
	Node* left;
	Node* right;

	bool shape_match(Node* a, Node* b);
	Node* find_subtree_match(Node* c, Node* a);

};


bool Node::shape_match(Node* a, Node* b)
{
	if(a->left && b->left)
	{
		if(!shape_match(a->left, b->left))
		{
			return false;
		}
	}
	else if(a->left || b->left)
	{
		return false;
	}

	if(a->right && b->right)
	{
		if(!shape_match(a->right, b->right))
		{
			return false;
		}
	}
	else if(a->right || b->right)
	{
		return false;
	}

	return true;
}


Node* Node::find_subtree_match(Node* c, Node* a)
{
	if(!c) 
	{
		return new Node();
	}
	if(shape_match(c,a))
	{
		return c;
	}
	Node* l = find_subtree_match(l->left, a);
	if(l->value)
	{
		return l;
	}
	Node* r = find_subtree_match(r->right, a);
	if(r->value)
	{
		return r;
	}
	return new Node();
}


int main()
{
	Node* n= new Node();
	n->value = 5;
	n->left = new Node();
	n->left->value = 7;
	n->right = new Node();
	n->right->value = 13;

	n->left->left = new Node();
	n->left->left->value = 6;
	n->left->right = new Node();
	n->left->right->value = 11;

	n->right->right = new Node();
	n->right->right->value = 21;



	Node* b= new Node();
	b->value = 17;
	b->left = new Node();
	b->left->value = 9;
	b->right = new Node();
	b->right->value = 22;

	b->left->left = new Node();
	b->left->left->value = 10;
	b->left->right = new Node();
	b->left->right->value = 1;

	b->right->right = new Node();
	b->right->right->value = 8;


	if(shape_match(n,b))
	{
		std::cout << "coooool" << std::endl;
	}
}