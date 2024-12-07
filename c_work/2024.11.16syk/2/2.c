#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(int);
int pop(void);
void clear(void);
int stack_empty(void);  // 添加 stack_empty 函数的声明

int main()
{
    int type;
    int op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atoi(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0)
                push(pop() / op2);
            else
                printf("ERROR: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0)
                push(pop() % op2);
            else
                printf("ERROR: zero divisor\n");
            break;
        case '&':
            push(pop() & pop());
            break;
        case '|':
            push(pop() | pop());
            break;
        case '<':
            op2 = pop();
            push(pop() << op2);
            break;
        case '>':
            op2 = pop();
            push(pop() >> op2);
            break;
        case '\n':
            if (stack_empty()) {
                printf("ERROR\n");
                clear();
            } else {
                printf("\t%d\n", pop());
                if (!stack_empty()) {
                    printf("ERROR\n");
                    clear();
                }
            }
            break;
        default:
            printf("ERROR%s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL 100

int sp = 0;
int val[MAXVAL];

void push(int f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("ERROR%d\n", f);
}

int pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("ERROR\n");
        return 0;
    }
}

void clear(void)
{
    sp = 0;
}

int stack_empty(void)
{
    return sp == 0;
}

int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getchar()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '-')
        return c;
    i = 0;
    if (isdigit(c) || c == '-') {
        while (isdigit(s[++i] = c = getchar()))
            ;
    }
    s[i] = '\0';
    if (c != EOF)
        ungetc(c, stdin);
    return NUMBER;
}