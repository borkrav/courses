#include <iostream>
using namespace	std;

int match(char T[], char P[], int n, int m) {
	
	int F[m+1]; F[0]=0; F[1]=0;
	int k=0;
	
	for (int q=2; q<=m; q++) {
		while (k>0 && P[k] != P[q-1]) {
			k=F[k];
		}
		if (P[k] == P[q-1]) {
			k++;
		}
		F[q] = k;
	}
	
	k=0;
	
	for (int q = 1; q<=n; q++) {
		while (k>0 && T[q-1] != P[k]) {
			k = F[k];
		}
		if (P[k] == T[q-1]) {
			k++;
			if (k==m) {
				return q-m+1;
			}
			
		}
	}
		
	return -1;
		
}


/*
int main (int argc, char * const argv[]) {
	
	char T [100] = {'a','b','a','b','a','b','a','b','a','b'};
	char P [100] = {'a','a','b','a','a','a','a','b'};
	char A [100] = {'a','b','a'};
	char B [100] = {'a','b','a','b','a','b'};
	
	
	int a = match(T, P, 10, 8);
	
	cout << a << endl;
		
	return 0;
}

*/
