#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->data[++(s->top)] = value;
    }
}

int pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return 0;
}

const char* evaluate_rpn(const char* expression) {
    static char result_str[20];
    Stack stack;
    initStack(&stack);

    char* expr_copy = (char*)malloc(strlen(expression) + 1);
    if (expr_copy == NULL) {
        return "ERROR";
    }
    strcpy(expr_copy, expression);

    char* token = strtok(expr_copy, " ");

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&stack, atoi(token));
        } else {
            if (stack.top < 1) {
                free(expr_copy);
                return "ERROR";
            }
            int b = pop(&stack);
            int a = pop(&stack);
            int result;

            switch (token[0]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b == 0) {
                        free(expr_copy);
                        return "ERROR";
                    }
                    result = a / b;
                    break;
                case '%':
                    result = a % b;
                    break;
                case '&':
                    result = a & b;
                    break;
                case '|':
                    result = a | b;
                    break;
                case '<':
                    if (strcmp(token, "<<") == 0) {
                        result = a << b;
                    } else {
                        free(expr_copy);
                        return "ERROR";
                    }
                    break;
                case '>':
                    if (strcmp(token, ">>") == 0) {
                        result = a >> b;
                    } else {
                        free(expr_copy);
                        return "ERROR";
                    }
                    break;
                default:
                    free(expr_copy);
                    return "ERROR";
            }
            push(&stack, result);
        }
        token = strtok(NULL, " ");
    }
    
    free(expr_copy);
    
    if (stack.top != 0) {
        return "ERROR";
    }
    
    sprintf(result_str, "%d", pop(&stack));
    return result_str;
}

int main() {
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) {
        char expression[256];
        fgets(expression, sizeof(expression), stdin);
        expression[strcspn(expression, "\n")] = 0;

        const char* result = evaluate_rpn(expression);
        printf("%s\n", result);
    }
    return 0;
}