#include <stdio.h>
#include "array.h"

int main() {
    char command;
    char data;
    int new_position;
    // create 함수 호출
    create(my_array);

    while (1) {
        print();
        scanf(" %c", &command);
        switch (command) {
            case '+': // insert(array, data)
                scanf(" %c", &data);
                insert(data);
                break;
            case '<': // traverse_front(array, count)
                traverse_front(data);
                break;
            case '>': // traverse_rear(array, count)
                traverse_rear(data);
                break;
            case 'N':
                next();
                break;
            case 'P':
                previous();
                break;
            case '-': // delete(array)
                delete();
                break;
            case '@': // get_data(array)
                printf("현재 데이터 반환: %c\n", get_data());
                break;
            case '=': //replace(array, new_data)
                scanf(" %c", &data);
                replace(data);
                break;
            case 'E': // empty(array)
                empty();
                break;
            case 'M': // move(new_position)
                scanf(" %c", &data);
                if (data == 'n') {
                    move(count-1);
                } else if (data == 'N') {
                    move(cursor_position);
                } else if (data == 'P') {
                    move(cursor_position - 2);
                } else {
                    // Check if data is a number
                    if (data >= '0' && data <= '9') {
                        new_position = data - '0';
                        move(new_position);
                    } else {
                        printf("잘못된 명령어입니다.\n");
                    }
                }
                break;
            case 'n': // data_coount(array)
                data_count();
                break;
            case 'L': // print(array)
                break;
            case 'Q': // 종료
                printf("프로그램을 종료합니다.\n");
                return 0;
            case 'S': //sort(array)
                sort();
                break;
            case 'R': //reverse(array)
                reverse();
                break;
            case 'D': //remove_duplicates(array)
                remove_duplicates();
                break;
            default:
                printf("잘못된 명령어입니다.\n");
        }
    }

    return 0;
}
