int sumarray(int a[], int n){
   int sum =0;
   
   for(int i = 0; i<n; i++){
      sum+=a[i];
   }
   
   return sum;
}

int maxarraypos(int a[], int n){
   
   int i=0, max = -2147483648 ,posn=0;
   
   if (n == 0) return 0;
   
   for(i =0; i<n; i++){
      if (a[i] > max) {max = a[i]; posn = i;}
   }
   
   return posn; 
}
         
int lexlt(int a[], int n, int b[], int m){
   
   int i = 0;

   if (n == 0 && m == 0) return 0;
   if (n == 0 && m != 0) return 1;
   if (n != 0 && m == 0) return 0;

   if (a[0] > b[0]) return 0;
   if (b[0] > a[0]) return 1;
   
   
   for (i=1; i<m && i<n;i++){
      if (a[i] > b[i]) return 0;
      if (b[i] > a[i]) return 1;
   }
   
   if (m == n) return 0;
   if (n < m) return 1;
   else return 0;
}
      
      
   
      
   
           
   
     
   
   
   

