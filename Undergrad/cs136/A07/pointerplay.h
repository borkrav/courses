// node structure for a binary search tree
struct node {
   int data;
   struct node *left;
   struct node *right;
};

// prints all nodes reachable from p
// that have not been printed since last preset
// labels the node corresponding to p
void pprint(char *label, struct node *p);

// resets pprint, and frees storage
// to prevent memory leaks, you must preset after using pprint
void preset();
