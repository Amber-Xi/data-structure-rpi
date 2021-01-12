/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++()
{
	if (ptr_->right != NULL) 
	{ // find the leftmost child of the right node
      ptr_ = ptr_->right;
      while (ptr_->left != NULL) 
      	{ 
      		ptr_ = ptr_->left; 
      	}
    } 
    else 
    { // go upwards along right branches...  stop after the first left
      while (ptr_->parent != NULL && ptr_->parent->right == ptr_) 
      	{ 
      		ptr_ = ptr_->parent; 
      	}
      ptr_ = ptr_->parent;
    }
    return *this;	
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const
{
	if(!root)
	{
		return NULL;
	}
	Node* p = root;
	while(p->left)
	{
		p = p-> left;
	}
	return p;
}


Rope::Rope()
{
	root = NULL;
	size_ = 0;

}
//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p)
{
	root = p;
	size_ = p->Sum();
}

Rope::~Rope()
{
	destroy_tree(root);
}

Rope::Rope(const Rope& r)
{
	if(r.root == NULL)
	{
		root = NULL;
		size_ = 0;
		return;
	}
	else
	{
		this->root = copy_tree(r.root, r.root->parent);
		this->size_ = r.size_;
	}
	this->root->parent = NULL;

}


void Rope::destroy_tree(Node* p) 
{
    if (!p) return;
    destroy_tree(p->right);
    destroy_tree(p->left);
    delete p;
}

Rope& Rope::operator= (const Rope& r)
{
	if (&r != this)
	{
		this->destroy_tree(this->root);
      this->root = copy_tree(r.root, r.root->parent);
      size_ = r.size_;
    }
    return *this;
}

Node* Rope::copy_tree(Node* old_root, Node* the_parent) 
{
    if (old_root == NULL) 
      return NULL;
    Node *answer = new Node;
    answer->weight = old_root->weight;
    answer->value = old_root ->value;
    answer->left = copy_tree(old_root->left,answer);
    answer->right = copy_tree(old_root->right,answer);
    answer->parent = the_parent;
    return answer;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const
{
	if(i > size_ || i<0)
	{
		return false;
	}
	Node* tmp = root;
	while(!is_leaf(tmp))
	{
		if(tmp->weight <= i)
		{
			i = i - tmp->weight;
			tmp = tmp->right;
	
		}
		else if(tmp->weight > i)
		{
			tmp = tmp->left;
		}
	}
	c = tmp->value[i];
	return true;


}

int Node::Sum() const
{
	int sum = 0;
	const Node *temp = this;
	while(temp->right == NULL && temp->left != NULL){
		temp = temp->left;
	}
	while(temp->right != NULL){
		sum += temp->weight;
		temp = temp->right;
	}
	sum += temp->weight;
	return sum;
}

//Add the other rope (r)'ss string to the end of my string
void Rope::concat(const Rope& r)
{
	Rope* new_rope = new Rope(r);

	Node* n = new Node();
	n->parent = NULL;
	n->left = this->root;
	n->right = new_rope->root;
	n -> weight = root->Sum();

	this->root = n;

	if (this->root->left) 
	{
    	this->root->left->parent = this->root;
  	}
  	if (this->root->right) 
  	{
    	this->root->right->parent = this->root;
  	}
  	size_ += new_rope->size_;

  	new_rope->root = NULL;
  	delete new_rope;


}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const
{
	s = "";
	if(i > j || i< 0 || j<0)
	{
		return false;
	}

	char c;

	while(i <= j)
	{
		if(index(i, c))
		{
			s+=c;
		}
		++i;
	}

	return true;

}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs)
{	
	Node* tmp = root;
	while(!is_leaf(tmp))
	{
		if(tmp->weight <= i)
		{
			i = i - tmp->weight;
			tmp = tmp->right;
	
		}
		else if(tmp->weight > i)
		{
			tmp = tmp->left;
		}
	}

	//std::cout << tmp->weight<< std::endl;
	if(i != 0)
	{
		rhs.root = new Node;
		rhs.root -> weight = 0;
		rhs.size_ = 0;
		return *this;
	}


	while(tmp -> parent -> left == tmp)
	{
		tmp = tmp->parent;
	}

	rhs.root = tmp;
	tmp->parent->right = NULL;
	tmp = tmp->parent;
	rhs.root->parent = NULL;
	rhs.size_ = rhs.root->Sum();

	if(rhs.root->left || rhs.root->right)
	{
		rhs.root->weight = rhs.root->left->Sum();
	}

	while(tmp != this->root)
	{
		if(tmp->parent->right && tmp -> parent ->right != tmp)
		{
	
			tmp = tmp->parent;
			Rope r_new = Rope();
			r_new.root = tmp->right;
			tmp->right = NULL;
			r_new.root -> parent = NULL;
			tmp -> weight = tmp->left->Sum();
			r_new.size_  = r_new.root->Sum();
			rhs.concat(r_new);
		}
		tmp = tmp->parent;
	}

	this-> size_ = (this->root)->Sum();
	this-> root ->weight = this->root->left->Sum();

	return *this;
	

}
