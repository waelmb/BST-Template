#include <iostream>
#include <stdlib.h> 
#include "bst.h"


int main(){
    int x;
    int h;

    bst<int> *t = new bst<int>();

    while( (std::cin >> x)) 
        t->insert(x);

    if(t->size() <= 20) {
      t->inorder();
      t->preorder();
    }
	
	 h = t->height();
     std::cout << "\n#### Reported height of tree:   " << h << "\n";
     
     //
     printf("Testing delete with balancing\n");
     
	/*
     std::vector<int>* v = t->to_vector();
	for(int i = 0; i < v->size(); i++) {
		x = v->at(i);
	     printf("Deleting %d\n", x);
	     if(t->remove(x)) {
	     	printf("success\n");
	     	t->inorder();
		 }
		 else {
		 	printf("failed\n");
		 }
	}
	printf("\n");
	 */
	 x = 51;
     printf("Deleting %d\n", x);
     if(t->remove(x)) {
     	printf("success\n");
     	t->inorder();
	 }
	 else {
	 	printf("failed\n");
	 }
	 
	 x = 55;
     printf("Deleting %d\n", x);
     if(t->remove(x)) {
     	printf("success\n");
     	t->inorder();
	 }
	 else {
	 	printf("failed\n");
	 }
	 
	  x = 60;
     printf("Deleting %d\n", x);
     if(t->remove(x)) {
     	printf("success\n");
     	t->inorder();
	 }
	 else {
	 	printf("failed\n");
	 }
	 
	 x = 69;
     printf("Deleting %d\n", x);
     if(t->remove(x)) {
     	printf("success\n");
     	t->inorder();
	 }
	 else {
	 	printf("failed\n");
	 }
	 
	 x = 75;
     printf("Deleting %d\n", x);
     if(t->remove(x)) {
     	printf("success\n");
     	t->inorder();
	 }
	 else {
	 	printf("failed\n");
	 }
	 
	  x = 81;
     printf("Deleting %d\n", x);
     if(t->remove(x)) {
     	printf("success\n");
     	t->inorder();
	 }
	 else {
	 	printf("failed\n");
	 }
	 
	 x = 90;
     printf("Deleting %d\n", x);
     if(t->remove(x)) {
     	printf("success\n");
     	t->inorder();
	 }
	 else {
	 	printf("failed\n");
	 }
	 
	 x = 94;
     printf("Deleting %d\n", x);
     if(t->remove(x)) {
     	printf("success\n");
     	t->inorder();
	 }
	 else {
	 	printf("failed\n");
	 }

    t->preorder();
    
    delete t;
    
    return 0;
}
