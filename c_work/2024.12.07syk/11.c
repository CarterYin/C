#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // 检查是否提供了正确的命令行参数
    if (argc != 3) {
        printf(" %s <n> <k>\n", argv[0]);
        return 1;
    }

    // 获取 n 和 k 的值
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    if (n <= 0 || k <= 0) {
        printf("n 和 k 必须是正整数。\n");
        return 1;
    }

    // 初始化圈子
    int *people = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        people[i] = 1;  // 1 表示此人还在圈中
    }

    int count = 0;  // 当前报数的总人数
    int index = 0;  // 当前下标
    int remaining = n;  // 剩余人数

    printf("退出顺序: ");
    while (remaining > 0) {
        if (people[index] == 1) {
            count++;  // 报数
            if (count % k == 0) {
                // 当前编号的人退出
                printf("%d ", index + 1);
                people[index] = 0;  // 标记为退出
                remaining--;  // 剩余人数减一
            }
        }

        // 移动到下一个人
        index = (index + 1) % n;
    }
    printf("\n");

    // 释放分配的内存
    free(people);

    return 0;
}
