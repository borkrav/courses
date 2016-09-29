// arraystuff.h -- some operations on arrays

//   all operations have running time O(n)

int sumarray(int a[], int n);

// a is an array of n elements
// sumarray must return the sum of the elements
// you may assume the result is in the range
//    [-2^-31, 2^31-1]

int maxarraypos(int a[], int n);

// a is an array of n elements
// maxarraypos must return the position of
//   the first occurrence of the maximum
//   value in a
// if there is no such value, must return 0

int lexlt(int a[], int n, int b[], int m);

// lexicographic "less than" between an array
//   a of length n and an array b of length m
// returns 1 if a comes before b in
//   lexicographic order; 0 otherwise

