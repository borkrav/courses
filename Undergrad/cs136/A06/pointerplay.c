#include <stdlib.h>
#include <stdio.h>
#include "pointerplay.h"

// association list structure used by pprint
struct assoc {
   struct node *n;
   int nodenum;
   int printed;
   struct assoc *next;
};

// association list labels nodes with unique ints
static struct assoc *assoc_list;

// traverses data structure, adds p to association list
static void pprint_assoc(struct node *p){
   if (p == NULL) return;
   struct assoc *a;
   struct assoc *lasta = NULL;
   int lastc = 0;
   for (a=assoc_list; a != NULL && a->n != p; a = a->next) {
      lastc = a->nodenum;
      lasta = a;
   }
   if (a == NULL) {
      a = malloc(sizeof(struct assoc));
      a->n = p;
      a->printed = 0;
      a->next = NULL;
      a->nodenum = lastc + 1;
      if (assoc_list == NULL) assoc_list = a;
      else lasta->next = a;
      pprint_assoc(p->left);
      pprint_assoc(p->right);
   }
}

// looks up p in association list
static int pprint_look(struct node *p){
   struct assoc *a;
   int lastc = 0;
   for (a=assoc_list; a != NULL && a->n != p; a = a->next) {}
   if (a == NULL) return 0;
   return a->nodenum;
}

// frees association list, resents to empty
void preset(){
   struct assoc *a = assoc_list;
   while (a != NULL){
      struct assoc *tmp = a->next;
      free(a);
      a = tmp;
   }
   assoc_list = NULL;
}

// prints all nodes reachable from p
// that have not been printed since last reset
// labels the node corresponding to p
void pprint(char *label, struct node *p){
   pprint_assoc(p);
   struct assoc *aa;
   for (aa=assoc_list;aa != NULL; aa=aa->next) {
      if (aa->printed) continue;
      printf("#%d:\t%d",aa->nodenum,aa->n->data);
      aa->printed = 1;
      int left = pprint_look(aa->n->left);
      int right = pprint_look(aa->n->right);
      if (left == 0) printf("\tNULL");
      else printf("\t#%d",left);
      if (right == 0) printf("\tNULL");
      else printf("\t#%d",right);
      printf("\n");
   }
   printf("%s:\t#%d\n",label,pprint_look(p));
}   
