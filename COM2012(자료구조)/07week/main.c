#include "queue.h"
#include <stdio.h>
#include <ctype.h>

int main()
{
    Queue my_queue;
    create(&my_queue);

    while (1){
        char command;
        char data;

        scanf(" %c", &command);

        if (isdigit(command)) {
            int num = command - '0';
            if (scanf(" %c", &command) == 1 && command == '-') {
                for (int i = 1; i < num; i++) {
                    if (!is_empty(&my_queue)) {
                        peek(&my_queue);
                        dequeue(&my_queue);
                    }
                }
            } else {
                printf("Invalid command\n");
            }
        }

        switch (command)
        {
        case '+':
            scanf(" %c", &data);
            enqueue(&my_queue, data);
            print(&my_queue);
            break;
        case 'L':
            print(&my_queue);
            break;
        case 'P':
            peek(&my_queue);
            break;
        case '-':
            peek(&my_queue);
            dequeue(&my_queue);
            print(&my_queue);
            break;
        case 'F':
            if (is_full(&my_queue))
            {
                printf("True\n");
            }
            else
            {
                printf("False\n");
            }
            print(&my_queue);
            break;
        case '#':
            data_count(&my_queue);
            break;
        case 'H':
            head(&my_queue);
            break;
        case 'T':
            tail(&my_queue);
            break;
        case 'E':
            if (is_empty(&my_queue))
            {
                printf("True\n");
            }
            else
            {
                printf("False\n");
            }
            break;
        case '?':
            scanf(" %c", &data);
            if (is_member(&my_queue, data))
            {
                printf("True\n");
            }
            else
            {
                printf("False\n");
            }
            break;
        case '=':
            scanf(" %c", &data);
            replace(&my_queue, data);
            print(&my_queue);
            break;
        case 'C':
            clear(&my_queue);
            print(&my_queue);
            break;
        case 'R':
            rotate(&my_queue);
            print(&my_queue);
            break;
        case 'M':
            scanf(" %c", &data);
            printf("%d\n", count(&my_queue, data));
            break;
        case 'B':
            peekBack(&my_queue);
            break;
        case 'Q':
            return 0;
        default:
            printf("Invalid command\n");
            break;
        }
    }
}