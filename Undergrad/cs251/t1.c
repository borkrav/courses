#include <stdio.h>
#include <stdlib.h>

main () {
  int i,j;
  static int x[4000][4000];
  for (i=0; i<4000; i++) {
    for (j=0; j<4000; j++) {
      x[i][j]=i+j; }
  }
}
