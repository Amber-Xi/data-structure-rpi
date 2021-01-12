#include <iostream>
#include <string>


// Note: It's ok that all the member variables are public for this
// tiny class.  We'll build up to a more robust and complete linked
// list implementation in lecture 11.
template <class T>
class Node {
public:
  T value;
  Node<T> *ptr;
};



template <class T>
void print(Node<T> *data, const std::string &label) {
  std::cout << label;
  Node<T> *tmp = data;
  while (tmp != NULL) {
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}



template <class T>
void reverse(Node<T>* &input) {
    if(input != NULL && input->ptr != NULL )
    {
        std::cerr << "" << std::end;
    }
  Node<T> *temp = input->ptr;
  Node<T> *temp2 = input->ptr->ptr;
  Node<T> *ori = input;
  while(temp2 != NULL){
    temp->ptr = input;
    input = temp;
    temp = temp2;
    temp2 = temp2->ptr;
  }
  temp->ptr = input;
  input = temp;
  ori->ptr = temp2;
}




int main() {

  // manually create a linked list of notes with 4 elements
  Node<int>* my_list = new Node<int>; 
  my_list->value = 1; 
  my_list->ptr = new Node<int>;
  my_list->ptr->value = 2;
  my_list->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->value = 3;
  my_list->ptr->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->ptr->value = 4;
  my_list->ptr->ptr->ptr->ptr = NULL;

  
  print(my_list,"my_list before");
  reverse(my_list);
  print(my_list,"my_list after ");

    Node<int>* my_list1 = new Node<int>;
    my_list1->value = 1;
    my_list1->ptr = new Node<int>;
    my_list1->ptr->value = 2;
    my_list1->ptr->ptr = NULL;
    print(my_list1,"my_list before");
    reverse(my_list1);
    print(my_list1,"my_list after ");
    
  Node<std::string>* my_list2 = new Node<std::string>; 
  my_list2->value = "apple"; 
  my_list2->ptr = new Node<std::string>;
  my_list2->ptr->value = "banana";
  my_list2->ptr->ptr = new Node<std::string>;
  my_list2->ptr->ptr->value = "carrot";
  my_list2->ptr->ptr->ptr = new Node<std::string>;
  my_list2->ptr->ptr->ptr->value = "date";
  my_list2->ptr->ptr->ptr->ptr = NULL;

  
  print(my_list2,"my_list before");
  reverse(my_list2);
  print(my_list2,"my_list after ");
    

  // Note: We are not deleting any of the Nodes we created...  so this
  // program has memory leaks!  More on this in lecture 11.

}

// ===========================================================================
