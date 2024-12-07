#include <stdio.h>

int main() {
    int num, digit1, digit2, digit3;
    
    printf("所有的水仙花数如下:\n");
    for (num = 100; num <= 999; num++) {
        digit1 = num / 100;          // 百位
        digit2 = (num / 10) % 10;    // 十位
        digit3 = num % 10;           // 个位
        
        if (digit1 * digit1 * digit1 + digit2 * digit2 * digit2 + digit3 * digit3 * digit3 == num) {
            printf("%d\n", num);
        }
    }
    
    return 0;
}