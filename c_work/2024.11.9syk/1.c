#include <stdio.h>

#define MAX_DEPTH 1000

int main() {
    int n;
    scanf("%d", &n); 

    int triangle[MAX_DEPTH][MAX_DEPTH] = {0};

    for (int i = 0; i < n; ++i) {
        triangle[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if(triangle[i][j]!=0)
            printf("%d ", triangle[i][j]);
        }
        printf("\n");
    }

    return 0;
}