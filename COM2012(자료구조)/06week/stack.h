#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void create(Stack *my_stack) {
    my_stack->top = -1;
}

bool isEmpty(Stack *my_stack) {
    return my_stack->top == -1;
}

bool is_full(Stack *my_stack) {
    return my_stack->top == MAX_SIZE - 1;
}

void push(Stack *my_stack, char element) {
    if (is_full(my_stack)) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    my_stack->data[++(my_stack->top)] = element;
    print(my_stack);
}

char pop(Stack *my_stack) {
    if (isEmpty(my_stack)) {
        printf("Error (nothing to pop)\n");
        return ' ';
    }
    return my_stack->data[(my_stack->top)--];
}

char peek(Stack *my_stack) {
    return my_stack->data[my_stack->top];
}

void print(Stack *my_stack) {
    printf("Stack: ");
    for (int i = 0; i <= my_stack->top; i++) {
        if (i == my_stack->top) {
            printf("[%c] ", my_stack->data[i]);
        } else {
            printf("%c ", my_stack->data[i]);
        }
    }
    printf("\n");
}

void element_count(Stack *my_stack) {
    printf("%d\n", my_stack->top + 1);
}

void top(Stack *my_stack) {
    if (isEmpty(my_stack)) {
        printf("Stack is empty\n");
        return;
    }
    printf("(%d, %c)\n", my_stack->top + 1, my_stack->data[my_stack->top]);
}

void is_member(Stack *my_stack, char element) {
    for (int i = 0; i <= my_stack->top; i++) {
        if (my_stack->data[i] == element) {
            printf("True\n");
            return;
        }
    }
    printf("False\n");
}

void replace(Stack *my_stack, char new_element) {
    char old_element = peek(my_stack); 
    if (old_element == '\0') { 
        printf("Stack is empty\n");
        return;
    }

    for (int i = 0; i <= my_stack->top; i++) {
        if (my_stack->data[i] == old_element) {
            my_stack->data[i] = new_element;
            printf("%c replaced with %c\n", old_element, new_element);
            return;
        }
    }
    printf("%c not found in the stack\n", old_element);
}

void clear(Stack *my_stack) {
    my_stack->top = -1;
    printf("Stack cleared\n");
    print(my_stack);
}


int findElement(Stack *my_stack, char element) {
    int position = 1;
    for (int i = 0; i <= my_stack->top; i++) {
        if (my_stack->data[i] == element) {
            return position;
        }
        position++;
    }
    return -1; 
}


void reverse(Stack *my_stack) {
    char temp[MAX_SIZE];
    int index = 0;
    while (!isEmpty(my_stack)) {
        temp[index++] = pop(my_stack);
    }
    for (int i = 0; i < index; i++) {
        my_stack->data[i] = temp[i];
    }
    my_stack->top = index - 1;
}