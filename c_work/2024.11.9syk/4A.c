#define _crt_secure_no_warnings 1
#include <stdio.h>

void order(int n, int* nums, int* current, int* used,  int start) {
        if (start == n) {
            for (int i = 0; i < n; i++) {
                printf("%d ", current[i]);
            }
            printf("\n");
            return;
        }

        for (int i = 0; i < n; i++) {
            if (!used[i]) {  
                current[start] = nums[i];  
                used[i] = 1;  
                order(n, nums, current, used,  start + 1);
                used[i] = 0;
            }
        }
}

int main() {
    int n;
    scanf("%d", &n);
    int nums[n];
    int used[n];
    int current[n];

        for (int i = 0; i < n; i++) {
            nums[i] = i + 1;
            used[i] = 0;  
        }
    order(n, nums, current, used, 0);

    return 0;
}