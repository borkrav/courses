#include "pointerplay.h"
#include <stdio.h>
#include <stdlib.h>

int memberbst (int i, struct node *t){

struct node *current = t;

   while(current != NULL){
      if (current->data == i){
          return 1;
      }
          
      else if (current->data < i){      
         current = current->right;      
      }
      
      else {         
         current = current->left;
      }   
   }
   
   
   return 0;


}

/*
int main(){

struct node *test = malloc(sizeof(struct node));
struct node *left = malloc(sizeof(struct node));
struct node *right = malloc(sizeof(struct node));

test->data = 5;
test->left = left;
test->right = right;
left->data = 3;
left->left = NULL;
left->right = NULL;
right->data = 7;
right->left=NULL;
right->right=NULL;

printf("%d\n", memberbst(10, NULL));

free(left);
free(right);
free(test);

}
*/
