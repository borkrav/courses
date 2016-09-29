#include <stdio.h>
#include "ilist.h"


void printlist (ilist list){

ilist *printlist = &list;

if (iempty_huh(list) == 1)
{
printf("list is empty lol\n");

}

 while (iempty_huh(*printlist) != 1){
        
    printf("%d\n", ifirst(*printlist));
    ilist rest = irest(*printlist);
    printlist = &rest;
    }

}

int main(){
/*
ilist a = icons(1, icons(2, icons(3, icons(4, iempty()))));
ilist b = icons(5, icons(6, icons(7, icons(8, iempty()))));
ilist e = icons(9, iempty());
ilist f = icons(10, iempty());
ilist c = iempty();
ilist d = iempty();

ilist append = iappend(c,d);


int g = ifirst(append);
printf("%d\n",g);

idelete (append);
idelete(a);
idelete(b);
idelete(e);
idelete(f);
*/



ilist x = icons(10, iempty());
ilist y = iempty();
ilist z = icons(20,x);

printf("%d %d %d\n",ilength(x),ilength(y),ilength(z));

idelete(z);

}


