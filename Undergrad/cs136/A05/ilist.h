// Abstract data type ilist

// ilist is defined as follows

// ilist iempty()   
//    returns an empty ilist

// int iempty_huh(ilist il) 
//    returns 1 (true) if il is empty
//    returns 0 (false) if il is not empty

// ilist icons(int in, ilist il)
//    adds the new first element in to il

// int ifirst(ilist il)
//    returns the first element in il
//    il must not be empty

// ilist irest(ilist il)
//    returns il except for the first element
//    il must not be empty

// void idelete(ilist il)
//    frees the storage for ilist
//    all further references to il become invalid
//    NOTE: every ilist created by icons must eventually
//          be freed (exactly once) by being a member of 
//          an ilist that is consumed by delete

// *****************************************************************
//   Do not look past this line, unless you are implementing ilist.c
//   If you use any of the information below, you'll be sorry
//       YOU HAVE BEEN WARNED
// *****************************************************************

struct ilist_node;
typedef struct ilist_node *ilist;

ilist icons(int, ilist);
int ifirst(ilist);
ilist irest(ilist);
ilist iempty();
int iempty_huh(ilist);
void idelete(ilist);
int ilength(ilist);
ilist iappend(ilist il1, ilist il2);
ilist reverselist(ilist list);
  

