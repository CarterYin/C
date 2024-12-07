#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

double my_atof(const char *str) {
    double result = 0.0;
    double fraction = 0.0;
    int exponent = 0;
    int sign = 1;
    int frac_sign = 1;
    int exp_sign = 1;
    int i = 0;

    // 跳过前导空格
    while (isspace(str[i])) {
        i++;
    }

    // 处理前导符号
    if (str[i] == '+' || str[i] == '-') {
        sign = (str[i] == '-') ? -1 : 1;
        i++;
    }

    // 解析整数部分
    while (isdigit(str[i])) {
        result = result * 10.0 + (str[i] - '0');
        i++;
    }

    // 解析小数部分
    if (str[i] == '.') {
        i++;
        double divisor = 10.0;
        while (isdigit(str[i])) {
            fraction += (str[i] - '0') / divisor;
            divisor *= 10.0;
            i++;
        }
    }

    // 解析指数部分
    if (str[i] == 'e' || str[i] == 'E') {
        i++;
        if (str[i] == '+' || str[i] == '-') {
            exp_sign = (str[i] == '-') ? -1 : 1;
            i++;
        }
        while (isdigit(str[i])) {
            exponent = exponent * 10 + (str[i] - '0');
            i++;
        }
    }

    // 计算最终结果
    result = sign * (result + fraction) * pow(10, exp_sign * exponent);

    return result;
}

int main() {
    char input[100];
    fgets(input, sizeof(input), stdin);

    double value = my_atof(input);
    printf("%.6f\n", round(value * 1000000) / 1000000);

    return 0;
}