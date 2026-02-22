#include <stdio.h>

char my_array[30];
int array_size = 30; 
int cursor_position = 0; // 커서 위치를 나타내는 변수
int count = 0; // 배열에 저장된 데이터 개수를 나타내는 변수

// create 함수 정의
void create(char array[]) {
}

// 데이터 삽입 함수
void insert(char data) {
    if (count < 30) {
        // 커서 위치에서부터의 데이터를 한 칸씩 뒤로 이동
        for (int i = count; i > cursor_position; i--) {
            my_array[i] = my_array[i - 1];
        }
        my_array[cursor_position++] = data; // 커서 위치에 데이터 삽입
        count++; // 데이터 개수 증가
    } else {
        printf("배열이 꽉 찼습니다. 더 이상 데이터를 입력받을 수 없습니다.\n");
    }
}

void traverse_front() {
    cursor_position = 1; // 맨 왼쪽으로 커서를 이동합니다.
}

void traverse_rear() {
    cursor_position = count; // 맨 오른쪽으로 커서를 이동합니다.
}

void next() {
    if (cursor_position < array_size - 1) {
        cursor_position++; // 커서를 오른쪽으로 한 칸 이동합니다.
    } else {
        printf("더 이상 오른쪽으로 이동할 수 없습니다.\n");
    }
}

void previous() {
    
    if (cursor_position > 0) {
        cursor_position--; // 커서를 왼쪽으로 한 칸 이동합니다.
    } else {
        printf("더 이상 왼쪽으로 이동할 수 없습니다.\n");
    }
}

// 데이터 삭제 함수
void delete() {
    if (count > 0) {
        // 커서 위치에 있는 데이터를 삭제
        for (int i = cursor_position-1; i < count - 1; i++) {
            my_array[i] = my_array[i + 1]; // 뒤의 데이터를 앞으로 한 칸씩 이동
        }
        count--; // 데이터 개수 감소

        if (cursor_position > count) {
            cursor_position = 1;
        } else {
            cursor_position = cursor_position;
        }

    } else {
        printf("아무런 데이터가 남아있지 않습니다. 데이터를 삭제할 수 없습니다.\n");
    }
}

// 데이터 반환 함수
char get_data() {
    if (count > 0) {
        return my_array[cursor_position - 1];
    } else {
        printf("배열 내에 데이터가 존재하지 않습니다.\n");
        return '\0'; // 빈 값을 반환
    }
}

// 배열 대체 함수
void replace(char data) {
    if (count > 0) {
        my_array[cursor_position - 1] = data;
        printf("데이터가 %c로 대체되었습니다.\n", data);
    } else {
        printf("대체할 데이터가 존재하지 않습니다.\n");
    }
}

// 배열 비우기 함수
void empty() {
    count = 0;
    cursor_position = 0;
    printf("배열을 모두 비웠습니다.\n");
}

// 이동 함수: 숫자를 입력받아 이동
void move(int new_position) {
    if (new_position >= 0 && new_position < count) {
        char temp = my_array[cursor_position - 1]; // 현재 커서 위치의 데이터 저장
        if (new_position < cursor_position - 1) {
            // 왼쪽으로 이동
            for (int i = cursor_position - 1; i > new_position; i--) {
                my_array[i] = my_array[i - 1];
            }
        } else if (new_position > cursor_position - 1) {
            // 오른쪽으로 이동
            for (int i = cursor_position - 1; i < new_position; i++) {
                my_array[i] = my_array[i + 1];
            }
        }
        my_array[new_position] = temp; // 저장한 데이터를 새 위치에 넣음
        cursor_position = new_position + 1; // 커서 위치 업데이트
        printf("커서의 위치와 데이터의 위치가 %d로 이동하였습니다.\n", cursor_position - 1);
    } else {
        printf("올바르지 않은 위치입니다. 커서의 위치와 데이터의 위치를 변경하지 않습니다.\n");
    }
}

// 데이터 개수 반환 함수
int data_count() {
    printf("마지막 데이터의 인덱스 번호는 %d입니다.\n", count-1);
}

// 배열 출력 함수
void print() {
    printf("배열 출력: ");
    for (int i = 0; i < count; i++) {
        if (i == cursor_position-1) {
            printf("[%c] ", my_array[i]); // 커서 위치에는 대괄호로 표시
        } else {
            printf("%c ", my_array[i]);
        }
    }
    printf("\n");
}

//오름 차순 정렬 함수
void sort() {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (my_array[i] > my_array[j]) {
                char temp = my_array[i];
                my_array[i] = my_array[j];
                my_array[j] = temp;
            }
        }
    }
    printf("배열이 오름차순으로 정렬되었습니다.\n");
}

//내림 차순 정렬 함수
void reverse() {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (my_array[i] < my_array[j]) {
                char temp = my_array[i];
                my_array[i] = my_array[j];
                my_array[j] = temp;
            }
        }
    }
    printf("배열이 내림차순으로 정렬되었습니다.\n");
}

// 중복 제거 함수
void remove_duplicates() {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (my_array[i] == my_array[j]) {
                for (int k = j; k < count; k++) {
                    my_array[k] = my_array[k + 1];
                }
                count--;
                j--;
            }
        }
    }
    if (cursor_position > count) {
        cursor_position = count;
    } else {
        cursor_position = cursor_position;
    }
    printf("중복된 데이터가 제거되었습니다.\n");
}