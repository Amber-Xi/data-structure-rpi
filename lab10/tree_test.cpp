#include <iostream>
#include "Node.h"

bool shape_match(Node* a, Node*b) {
  if(a->left && b->left) {
    if(!shape_match(a->left,b->left)) return false;
  } else if (a->left || b->left) return false;

  if(a->right && b->right) {
    if(!shape_match(a->right,b->right)) return false;
  } else if (a->right || b->right) return false;

  return true;
}

Node* find_subtree_match(Node* t, Node* p) {
  if(!t) return new Node();
  if(shape_match(t,p)) return t;
  Node* l = find_subtree_match(t->left, p);
  if(l->value) return l;
  Node* r = find_subtree_match(t->right, p);
  if(r->value) return r;
  return new Node();
}

int main() {
  Node* a = new Node();
  a->value = 5;
  Node* lit = a;
  Node* rit = a;
  a->left = new Node();
  a->left->value = 7;
  lit = a->left;
  lit->left = new Node();
  lit->left->value = 6;
  lit->right = new Node();
  lit->right->value = 11;
  a->right = new Node();
  a->right->value = 13;
  rit = a->right;
  rit->right = new Node();
  rit->right->value = 21;

  Node* b = new Node();
  b->value = 17;
  lit = b;
  rit = b;
  b->left = new Node();
  b->left->value = 9;
  lit = b->left;
  lit->left = new Node();
  lit->left->value = 10;
  lit->right = new Node();
  lit->right->value = 1;
  b->right = new Node();
  b->right->value = 22;
  rit = b->right;
  rit->right = new Node();
  rit->right->value = 8;

  Node* c = new Node();
  c->value = 15;
  lit = c;
  rit = c;
  c->left = new Node();
  c->left->value = 20;
  lit = c->left;
  lit->left = new Node();
  lit->left->value = 4;
  lit->right = new Node();
  lit->right->value = 12;

  c->right = new Node();
  c->right->value = 14;
  rit = c->right;
  rit->left = new Node();
  rit->left->value = 16;
  lit = rit->left;
  rit->right = new Node();
  rit->right->value = 2;
  rit = rit->right;
  lit->left = new Node();
  lit->left->value = 3;
  lit->right = new Node();
  lit->right->value = 18;
  rit->right = new Node();
  rit->right->value = 19;

  if(shape_match(a,b)) {
    std::cout << "YAAYYYY!!" << std::endl;
  } else {
    std::cout << "Nope" << std::endl;
  }

  if(find_subtree_match(c,a)->value) {
    std::cout << "YAAYYYY!!" << std::endl;
  } else {
    std::cout << "Nope" << std::endl;
  }
}
