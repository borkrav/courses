#include <stdlib.h>
#include "pointerplay.h"


struct node *x, *y, *y1, *z, *z1, *z2;

int main(){

x = malloc(sizeof(struct node));
y = malloc(sizeof(struct node));
y1 = malloc(sizeof(struct node));
z = malloc(sizeof(struct node));
z1 = malloc(sizeof(struct node));
z2 = malloc(sizeof(struct node));

x->data = 123;
x->left = y;
x->right = y1;

y->data = 456;
y->left = NULL;
y->right = y1;

y1->data = 789;
y1->left = x;
y1->right = z2;

z->data = 456;
z->left = NULL;
z->right = z1;

z1->data = 789;
z1->left = y1;
z1->right = z2;

z2->data = 987;
z2->left = NULL;
z2->right = NULL;

pprint("x",x);
pprint("y",y);
pprint("z",z);

free(x);
free(y);
free(z);
free(y1);
free(z1);
free(z2);

preset();


return 0;
}
