#include "linkedList.h"
#include <stdio.h>
#include <ctype.h>

int main() {
    LinkedList list;
    list.head = NULL;
    list.current = NULL;
    char command;
    char data;

    while (1) {
        printf("\n");
        scanf(" %c", &command);

        if (isdigit(command)) {
            int pos = command - '0';
            move_to(&list, pos-1); 

        } else {
            switch (command) {
                case '+':
                    scanf(" %c", &data);
                    if (list.current == NULL) {
                        addTail(&list, data);
                    } else {
                        add(&list, data);
                    }
                    print(&list);
                    break;
                case 'L':
                    print(&list);
                    break;
                case 'G':
                    get_data(&list);
                    break;
                case '<':
                    traverse_front(&list);
                    print(&list);
                    break;
                case '>':
                    traverse_rear(&list);
                    print(&list);
                    break;
                case 'N':
                    next(&list);
                    print(&list);
                    break;
                case 'P':
                    prev(&list);
                    print(&list);
                    break;
                case '-':
                    delete_data(&list);
                    print(&list);
                    break;
                case '=': 
                    scanf(" %c", &data);
                    replace(&list, data);
                    print(&list);
                    break;
                case '#':
                    data_count(&list);
                    print(&list);
                    break;
                case '?':
                    scanf(" %c", &data);
                    is_member(&list, data);
                    print(&list);
                    break;
                case 'C':
                    clear_list(&list);
                    print(&list);
                    break;
                case 'E':
                    is_empty(&list);
                    print(&list);
                    break;
                case 'r':
                    reverse_list(&list);
                    print(&list);
                    break;
                case 's':
                    sort_list(&list);
                    print(&list);
                    break;
                case 't':
                    int pos;
                    scanf(" %d", &pos);
                    truncate_list(&list, pos);
                    print(&list);
                    break;
                case 'Q':
                    return 0;
                default:
                    printf("잘못된 명령어입니다.\n");
            }
        }
    }

    return 0;
}