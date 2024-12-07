#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1000      // 每行的最大长度
#define MAXLINES 5000    // 最大行数
#define ALLOCSIZE 10000  // 可分配的存储空间大小

char *lineptr[MAXLINES]; // 指向文本行的指针数组

// 函数声明
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void shellsort(char *lineptr[], int nlines);

int main() {
    int nlines;
    // 读取输入行并排序
    if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
        shellsort(lineptr, nlines);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int mygetline(char*, int);
char *alloc(int);

// 读取输入行
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];
    
    // 读取第一行，表示接下来输入的行数
    if ((len = mygetline(line, MAXLEN)) <= 0) {
        return -1;
    }
    nlines = atoi(line); // 将第一行转换为整数，表示行数

    for (int i = 0; i < nlines; i++) {
        if ((len = mygetline(line, MAXLEN)) > 0) {
            if (i >= maxlines || (p = alloc(len)) == NULL) {
                return -1;
            } else {
                line[len - 1] = '\0'; // 删除换行符
                strcpy(p, line);
                lineptr[i] = p;
            }
        } else {
            return -1;
        }
    }
    return nlines;
}

// 输出排序后的行
void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

// 使用希尔排序算法对行进行排序
void shellsort(char *v[], int n) {
    int gap, i, j;
    char *temp;

    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            for (j = i - gap; j >= 0 && strcmp(v[j], v[j + gap]) > 0; j -= gap) {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
        }
    }
}

// 读取一行输入
int mygetline(char s[], int lim) {
    int i, c;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

// 分配内存
char *alloc(int n) {
    return (char *)malloc(n * sizeof(char));
}