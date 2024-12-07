#include <stdio.h>

void itoa_recursive(unsigned long long n, char s[], int *index) {
    if (n / 10) {
        itoa_recursive(n / 10, s, index);
    }
    s[(*index)++] = n % 10 + '0';
}

void itoa(unsigned long long n, char s[]) {
    int index = 0;
    if (n == 0) {
        s[index++] = '0';
    } else {
        itoa_recursive(n, s, &index);
    }
    s[index] = '\0';
}

int main() {
    unsigned long long n;
    char str[21]; // 最大支持20位数字+1位终止符
    scanf("%llu", &n);
    itoa(n, str);
    printf("%s\n", str);
    return 0;
}