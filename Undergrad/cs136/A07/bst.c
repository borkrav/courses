#include "pointerplay.h"
#include <stdio.h>
#include <stdlib.h>

/*
void postorder(struct node* tree) {
    if(tree != NULL) {
        postorder(tree->left);
        postorder(tree->right);
        printf("%d ", tree->data);
    }
}

void preorder(struct node* tree) {
    if(tree != NULL) {
        printf("%d ", tree->data);
        preorder(tree->left);
        preorder(tree->right);
    }
}


void inorder(struct node* tree) {
    if(tree != NULL) {
        inorder(tree->left);
        printf("%d ", tree->data);
        inorder(tree->right);
    }
}
*/

struct node* insertbst (int i, struct node *t){

   if (t == NULL){
      struct node* new = malloc(sizeof(struct node));
      new->data = i;
      new->left = NULL;
      new->right = NULL;
      return new;
   }
   
   else if (t->data > i){
      t->left = insertbst(i, t->left);
      return t;
   }
   
   else if (t->data < i){
      t->right = insertbst(i, t->right);
      return t;
   }
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

test = insertbst(10, test);
test = insertbst(15, test);
test = insertbst(1, test);
test = insertbst(2, test);
test = insertbst(0, NULL);

preorder(test);

free(left->right);
free(left);
free(right);
free(test);
}
*/



