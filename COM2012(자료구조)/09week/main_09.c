#include <stdio.h>
#include "bst.h"

int main() {
    node my_bst;
    node *root = &my_bst;

    while (1) {
        char command;
        int data;
        int data1, data2;

        printf("BST: ");
        printf("(");
        print(&my_bst);
        printf(")");
        printf("\n");
        printf("Enter command: ");
        scanf(" %c", &command);
        

        switch (command) {
            case '+':
                scanf(" %d", &data); //루트노드가 존재하지 않으면 create 함수, 존재하면 insert 함수
                if (my_bst.data == 0) {
                    my_bst = *create(data);
                } else {
                    insert_node(&my_bst, data);
                }
                break;
            case 'P':
                break;
            case 'I':
                inorder_traversal(&my_bst);
                printf("\n");
                break;
            case 'R':
                right_root_left_traversal(&my_bst);
                printf("\n");
                break;
            case 'N':
                printf("%d\n", get_min(&my_bst)->data);
                break;
            case 'X':
                printf("%d\n", get_max(&my_bst)->data);
                break;
            case 'F':
                scanf(" %d", &data);
                char path[100] = ""; // 경로를 저장할 버퍼
                node *found_node = find_node(root, data, path);
                break;
            case '-':
                scanf("%d", &data);
                delete_node(&my_bst, data);
                break;
            case 'H':
                printf("%d\n", height(&my_bst)-1);
                break;
            case 'G':
                scanf("(%d)", &data);
                {
                    node *right_child = get_right_child(&my_bst, data);
                    if (right_child != NULL) {
                        printf("%d\n", right_child->data);
                    } else {
                        printf("NULL\n");
                    }
                }
                break;
            case 'L':
                scanf("(%d)", &data);
                {
                    node *left_child = get_left_child(&my_bst, data);
                    if (left_child != NULL) {
                        printf("%d\n", left_child->data);
                    } else {
                        printf("NULL\n");
                    }
                }
                break;
            case '#':
                printf("%d\n", count_node(&my_bst));
                break;
            case 'C':
                clear(&my_bst);
                break;
            case '^':
                scanf("%d", &data);
                printf("%d\n", find_parent(&my_bst, data)->data);
                break;
            case 'A':
                printf("Enter two numbers: ");
                scanf("%d %d", &data1, &data2);
                printf("%d\n", find_lca(&my_bst, data1, data2)->data);
                break;
            case 'D':
                printf("Enter two numbers: ");
                scanf("%d %d", &data1, &data2);
                printf("%d\n", find_distance(&my_bst, data1, data2));
                break;
            case 'Q':
                return 0;
        }

    }
}