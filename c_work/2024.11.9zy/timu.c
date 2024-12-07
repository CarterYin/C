#include <stdio.h>
#include <string.h>

void shuffle(char *s, int m) {
    int len = strlen(s);
    char temp[len + 1];
    char *p = temp;
    
    // 将s的第m个字符后的部分复制到temp的开头
    for (int i = m; i < len; i++) {
        *p++ = s[i];
    }
    
    // 将s的前m个字符复制到temp的末尾
    for (int i = 0; i < m; i++) {
        *p++ = s[i];
    }
    
    *p = '\0'; // 添加字符串结束符
    
    // 将temp的内容复制回原字符串s
    p = temp;
    while (*p) {
        *s++ = *p++;
    }
    *s = '\0'; // 添加字符串结束符
}

int main() {
    char s[100];
    int m;
    
    //printf("请输入一个字符串: ");
    gets(s);
    
    //printf("请输入平移的值m: ");
    scanf("%d", &m);
    
    shuffle(s, m);

    //printf("平移后的字符串: %s\n", s);
    printf("%s\n", s);
    
    return 0;
}