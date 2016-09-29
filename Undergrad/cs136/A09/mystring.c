//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

int mystrlen(char *a){
   int i = 0;
   for (i; a[i] > 0; i++);
   return i;
}

int mystrcmp (char *a, char *b){
   int i = 0;
   int n = mystrlen(a);
   int m = mystrlen(b);
   
   if (a[0] < b[0]) return -1;
   else if (a[0] > b[0]) return 1;
    
    
   for (i=1; i<n && i<m; i++){
      if (a[i] > b[i]) return 1;
      if (a[i] < b[i]) return -1;
   }
   
   if (m == n) return 0;
   if (n > m) return 1;
   else return -1;
}

char * mystrcpy (char *a, char *b){
   
   int len = mystrlen(b);
   
   for(int i=0; i<=len;i++) a[i]=b[i];
   return a;
      
} 

char * mystrcat (char *a, char *b){
   
   int lena = mystrlen(a);
   int lenb = mystrlen(b);
   
   for (int i = 0; i<= lenb; i++) a[i+lena]=b[i];
   return a;
}

char * mystrstr (char *haystack, char *needle){
   int lenh = mystrlen(haystack);
   int lenn = mystrlen(needle);
   
   if (lenn == 0) return haystack;
   
   
   for (int i = 0; i<lenh; i++){
      
      if (haystack[i] == needle[0]) {
         int j=1;
         
         for (int k =1; k<lenn; k++){
            if (haystack[i+k] == needle[k]) j+=1;
            else break;
         }
         
         if (j == lenn) return haystack+i;
      }
   }
   return 0;
}
      
/*
int main(){

  char a[1000000];
  char b[500000];
  char *c = "lol";

  for(int i = 0; i<999999; i++){
     a[i] = 'a';
   }
   
   a[999999] = 0;
   
   b[0] = 'a';
   
   for (int i = 1; i<499999; i++){
       b[i] = 'b';  
   }
   b[499999] = 0;

  char *x = mystrstr(c,"o");
  printf("%p %p \n", c, x);
  
 
}
*/
