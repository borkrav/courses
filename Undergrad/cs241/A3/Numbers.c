#include <stdio.h>

int main() {
    int i;

    while(1) {
        if(1 != scanf("%d", &i)) break;
        printf("%d\n", i);
    }
}
