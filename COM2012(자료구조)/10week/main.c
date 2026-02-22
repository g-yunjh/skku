#include "avl.h"
#include <stdio.h>

int main() {
    avl* my_avl = (avl*)malloc(sizeof(avl));
    my_avl->root = NULL;

    while (1) {
        char command;
        int data;

        printf("AVL: ");
        printf("(");
        print(my_avl->root);
        printf(")");
        printf("\n");
        printf("Enter command: ");
        scanf(" %c", &command);

        switch(command) 
        {
            case '+':
                scanf(" %d", &data);
                if (my_avl->root == NULL) {
                    my_avl->root = create(data);
                } else {
                    my_avl->root = insert_node(my_avl->root, data);
                }
                break;
            case 'P':
                break;
            case 'B':
                scanf(" %d", &data);
                printf("%d\n", get_balance_factor(my_avl->root, data));
                break;
            case 'I':
                inorder_traversal(my_avl->root);
                printf("\n");
                break;
            case 'R':
                right_root_left_traversal(my_avl->root);
                printf("\n");
                break;
            case 'N':
                printf("%d\n", get_min(my_avl->root)->value);
                break;
            case 'X':
                printf("%d\n", get_max(my_avl->root)->value);
                break;
            case 'F':
                scanf(" %d", &data);
                char path[100] = ""; // 경로를 저장할 버퍼
                node *found_node = find_node(my_avl->root, data, path);
                if (found_node == NULL) {
                    printf("Error\n"); // 노드를 찾지 못했을 경우 에러 출력
                }
                break;
            case 'T':
                height_tree(my_avl->root);
                break;
            case 'H':
                scanf(" %d", &data);
                height_node(my_avl->root, data);
                break;
            case 'G':
                scanf(" %d", &data);
                get_right_child(my_avl->root, data);
                break;
            case 'L':
                scanf(" %d", &data);
                get_left_child(my_avl->root, data);
                break;
            case '#':
                printf("%d\n", count_nodes(my_avl->root));
                break;
            case '-':
                scanf(" %d", &data);
                my_avl->root = delete_node(my_avl->root, data);
                break;
            case 'C':
                clear(my_avl->root);
                my_avl->root = NULL;
                break;
            case 'Q':
                return 0;
        }
    }
    
}