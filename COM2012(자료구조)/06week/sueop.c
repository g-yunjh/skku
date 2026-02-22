#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 스택 구조체 정의
#define MAX_SIZE 100

typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

// 스택 함수 정의
void init(Stack *stack) {
    stack->top = -1;
}

bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

bool isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack *stack, char item) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++(stack->top)] = item;
}

char pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[(stack->top)--];
}

char peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top];
}

// 괄호 검사 함수
bool checkParentheses(char *expression) {
    Stack stack;
    init(&stack);

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        if (ch == '(') {
            push(&stack, '(');
        } else if (ch == ')') {
            if (isEmpty(&stack) || pop(&stack) != '(') {
                return false; // 괄호 짝이 맞지 않음
            }
        }
    }

    return isEmpty(&stack); // 스택이 비어있어야 괄호 짝이 맞음
}

// 우선순위 반환 함수
int precedence(char op);

// 후위 표기식 변환 함수
void infixToPostfix(char *infix, char *postfix) {
    Stack stack;
    init(&stack);

    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];
        if (ch >= '0' && ch <= '9') {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            pop(&stack); // '(' 제거
        } else { // 연산자인 경우
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(ch)) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }

    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }
    postfix[j] = '\0';
}

// 후위 표기식 계산 함수
int evaluatePostfix(char *postfix) {
    Stack stack;
    init(&stack);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
        if (ch >= '0' && ch <= '9') {
            push(&stack, ch - '0'); // ASCII 코드를 숫자로 변환
        } else {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            switch (ch) {
                case '+':
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    push(&stack, operand1 / operand2);
                    break;
                default:
                    printf("Invalid operator: %c\n", ch);
                    exit(EXIT_FAILURE);
            }
        }
    }

    return pop(&stack);
}

// 우선순위 반환 함수 구현
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0; // 괄호 또는 다른 문자인 경우
    }
}


int main() {
    char infix[MAX_SIZE];
    bool validExpression = false;

    while (!validExpression) {
        printf("괄호를 포함한 중위 표현식을 입력하세요: ");
        scanf("%s", infix);

        // 괄호 검사
        if (checkParentheses(infix)) {
            validExpression = true;
        } else {
            printf("괄호가 올바르게 닫히지 않았습니다. 다시 입력하세요.\n");
        }
    }

    char postfix[MAX_SIZE];
    infixToPostfix(infix, postfix);
    printf("후위 표기식: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("결과: %d\n", result);

    return EXIT_SUCCESS;
}