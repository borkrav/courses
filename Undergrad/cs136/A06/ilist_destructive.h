struct ilist_node;
typedef struct ilist_node *ilist;

ilist icons_destroy(char, ilist);
char ifirst(ilist);
ilist irest_destroy(ilist);
ilist iempty();
ilist icopy();
int iempty_huh(ilist);
void idelete(ilist);
int ilength(ilist);
ilist iappend_destroy(ilist il1, ilist il2);
//ilist reverselist(ilist list);
ilist reverselist(ilist);
ilist irest(ilist);
ilist findtail(ilist);
