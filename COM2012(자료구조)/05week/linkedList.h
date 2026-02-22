#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* next;
    struct Node* pre;
} Node;

typedef struct LinkedList{
	struct Node* head;
	struct Node* current;
}LinkedList;

Node* create(char data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->pre = NULL;
	newNode->data = data;
	return newNode;
}

//끝부분에 노드를 추가하는 함수
void addTail(LinkedList* list, char data) {
    Node* newNode = create(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->current = newNode;
    } else {
        list->current->next = newNode;
        newNode->pre = list->current;
        list->current = newNode;
    }
}

void print(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        if (current == list->current) {
            printf("[%c] -> ", current->data);
        } else {
            printf("%c -> ", current->data);
        }
        current = current->next;
    }
}

void get_data(LinkedList* list) {
    printf("%c", list->current->data);
    printf(" (");
    print(list);
    printf(")");
}

void traverse_front(LinkedList* list) {
    list->current = list->head;
}

void traverse_rear(LinkedList* list) {
    while (list->current->next != NULL) {
        list->current = list->current->next;
    }
}

void next(LinkedList* list) { 
    if (list->current->next != NULL) {
        list->current = list->current->next;
    }
}

void prev(LinkedList* list) {
    if (list->current->pre != NULL) {
        list->current = list->current->pre;
    }
}

void delete_data(LinkedList* list) {
    Node* temp = list->current;

    if (list->current->next != NULL) {
        list->current->next->pre = list->current->pre;
    }
    if (list->current->pre != NULL) {
        list->current->pre->next = list->current->next;
        list->current = list->current->next;
    } else {
        list->head = list->head->next;
        list->current = list->head;
    }

    if (list->current == NULL) {
        list->current = list->head;
    }
    
    free(temp);
}

//중간에 노드를 추가하는 함수
void add(LinkedList* list, char data) {
    Node* newNode = create(data);
    newNode->next = list->current->next;
    newNode->pre = list->current;
    list->current->next = newNode;
    list->current = newNode;
}

void replace(LinkedList* list, char data) {
    list->current->data = data;
}

void data_count(LinkedList* list) {
    int count = 0;
    Node* current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("%d\n", count);
}

void is_member(LinkedList* list, char data) {
    Node* current = list->head;
    int position = 1;
    while (current != NULL) {
        if (current->data == data) {
            printf("%d: ", position);
            return;
        }
        current = current->next;
        position++;
    }
    printf("Data '%c' not found in the list\n", data);
    print(list);
}

void clear_list(LinkedList* list) {
    Node* current = list->head;
    Node* temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->current = NULL;
}

void is_empty(LinkedList* list) {
    if (list->head == NULL) {
        printf("True\n");
    } else {
        printf("False\n");
    }
}

void move_to(LinkedList *list, int pos) {
    if (pos < 0) {
        printf("음수 위치는 지원하지 않습니다.\n");
        return;
    }

    int count = 0;
    Node *current = list->head;

    while (current != NULL && count < pos) {
        current = current->next;
        count++;
    }

    if (count < pos) {
        printf("리스트의 크기를 넘어서는 위치입니다.\n");
        return;
    }

    list->current = current;
}

void reverse_list(LinkedList* list) {
    Node* current = list->head;
    Node* prev = NULL;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        current->pre = next;
        prev = current;
        current = next;
    }
    list->head = prev;
}

void truncate_list(LinkedList* list, int pos) {
    if (list->head == NULL || pos <= 0) {
        clear_list(list); 
        return;
    }

    int count = 1;
    Node* current = list->head;

    while (current->next != NULL && count < pos) {
        current = current->next;
        count++;
    }

    current->next = NULL;

    list->current = current;
}

void sort_list(LinkedList* list) {
    Node* current = list->head;
    Node* index = NULL;
    char temp;

    if (list->head == NULL) {
        return;
    } else {
        while (current != NULL) {
            index = current->next;
            while (index != NULL) {
                if (current->data < index->data) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}