#include "stack.h"
#include <stdio.h>
#include <ctype.h>

//나만의 기능 3가지 추가: 요소 찾기, 스택 반전, 스택이 빈 함수인지 확인

int main() {
    Stack my_stack;
    create(&my_stack);

    while (1) {
        char command;
        char element;
        scanf(" %c", &command);

            if (isdigit(command)) {
                int num = command - '0';
                if (scanf(" %c", &command) == 1 && command == '-') {
                    for (int i = 1; i < num; i++) {
                        if (!isEmpty(&my_stack)) {
                            printf("%c\n", peek(&my_stack));
                            pop(&my_stack);
                        }
                    }
                } else {
                    printf("Invalid command\n");
                }
            }

        switch (command) {
            case '+':
                scanf(" %c", &element);
                push(&my_stack, element);
                break;
            case 'L':
                print(&my_stack);
                break;
            case 'P':
                printf("%c\n", peek(&my_stack));
                break;
            case '-':
                printf("%c\n", pop(&my_stack));
                print(&my_stack);
                break;
            case 'F':
                if (is_full(&my_stack)) {
                    printf("True\n");
                } else {
                    printf("False\n");
                }
                print(&my_stack);
                break;
            case '#': 
                element_count(&my_stack);
                break;
            case 'T':
                top(&my_stack);
                break;
            case '?':
                scanf(" %c", &element);
                is_member(&my_stack, element);
                break;
            case '=':
                scanf(" %c", &element);
                replace(&my_stack, element);
                print(&my_stack);
                break;
            case 'C':
                clear(&my_stack);
                break;
            case 'S':
                scanf(" %c", &element);
                printf("%d\n", findElement(&my_stack, element));
                break;
            case 'R':
                reverse(&my_stack);
                print(&my_stack);
                break;
            case 'E':
                if (isEmpty(&my_stack)) {
                    printf("True\n");
                } else {
                    printf("False\n");
                }
                break;
            case 'Q':
                return 0;
        }
    }
}