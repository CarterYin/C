#include <stdio.h>
#include <math.h>

int main() {
    double a, x_n, x_next;
    const double epsilon = 1e-5; // 精度要求

    // 读入一个正浮点数
    printf("请输入一个正浮点数 a: ");
    scanf("%lf", &a);

    // 检查输入的值是否有效
    if (a < 0) {
        printf("错误：输入的数必须为非负数！\n");
        return 1;
    }

    // 初始化 x_n（可以取 a 或 1.0）
    x_n = a > 1.0 ? a : 1.0;

    do {
        // 使用迭代公式计算下一个近似值
        x_next = 0.5 * (x_n + a / x_n);

        // 判断前后两次结果是否满足精度要求
        if (fabs(x_next - x_n) < epsilon) {
            break;
        }

        // 更新 x_n 为新的近似值
        x_n = x_next;
    } while (1);

    // 输出结果
    printf("平方根的近似值为: %.5f\n", x_next);

    return 0;
}
