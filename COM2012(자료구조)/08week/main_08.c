#include "tree.h"
#include <stdio.h>

int main ()
{
    Tree* t = create();

    while (1) {
        char command;
        char data;
        char parentData;
        printf("Tree: ");
        print(t->root);
        printf("\n");

        printf("Enter command: ");
        scanf(" %c", &command);

        switch (command){
            case '+':
                scanf(" %c", &parentData);
                if (parentData == '^') {
                    scanf(" %c", &data);
                if (t->root == NULL) {
                    t->root = newNode(data);
                } else {
                    printf("이미 루트 노드가 존재합니다.\n");
                }
                break;
                }

                char childData[100]; // 최대 입력 문자열 길이
                scanf("(%[^)])", childData); // 괄호 안에 있는 문자열을 읽음

                // 부모 노드 찾기
                Node *parent = findNode(t->root, parentData);
                if (parent == NULL) {
                    printf("부모 노드를 찾을 수 없습니다.\n");
                } else {
                    // 자식 노드 추가
                    int i = 0;
                    while (childData[i] != '\0') {
                        if (childData[i] != ',') {
                            insertNode(parent, childData[i], t->binary);
                        }
                        i++;
                    }
                }
                break;
            case 'T':
                break;
            case 'S':
                scanf("(%c)", &data);
                getSibling(t->root, data);
                break;
            case 'P':
                scanf("(%c)", &data);
                printf("%c\n", getParent(t->root, data)->data);
                break;
            case 'C':
                scanf("(%c)", &data);
                getChild( t-> root, data);
                break;
            case 'L':
                scanf("%c", &data);
                if (data == '\n') // 개행 문자가 입력된 경우 전체 트리의 레벨을 출력
                {
                    int treeLevel = levelOfTree(t->root);
                    printf("트리의 레벨: %d\n", treeLevel);
                }
                else // 개행 문자가 아닌 다른 문자가 입력된 경우 해당 노드의 레벨을 출력
                {
                    int nodeLevel = levelOfNode(t->root, data);
                    if (nodeLevel == -1) {
                        printf("%c 노드를 찾을 수 없습니다.\n", data);
                    } else {
                        printf("%c 노드의 레벨: %d\n", data, nodeLevel);
                    }
                }
                break;
            case '-':
                scanf("%c", &data);
                deleteNode(t->root, data);
                break;
            case 'A':
                scanf("(%c)", &data);
                getAncestors(t->root, data);
                printf("\n");
                break;
            case 'D':
                scanf("(%c)", &data);
                getDescendants(t->root, data);
                printf("\n");
                break;
            case 'G':
                scanf("%c", &data);
                if (data == '\n') {
                    printf("%d\n", degreeOfTree(t->root));
                } else {
                    printf("%d\n", degreeOfNode(t->root, data));
                }
                break;
            case '#':
                printf("%d", countNode(t->root));
                printf("\n");
                break;
            case '=':
                scanf(" +%c(%[^)])", &parentData, childData);
                for (int i = 0; childData[i] != '\0'; i++) {
                    if (childData[i] != ',') {
                        insertSibling(t->root, parentData, childData[i]);
                    }
                }
                break;
            case 'J':
                char tree1_name, tree2_name;
                scanf(" (%c, %c, %c)", &data, &tree1_name, &tree2_name);

                // tree1과 tree2의 루트 노드를 찾음
                Node* tree1_root = findNode(t->root, tree1_name);
                Node* tree2_root = findNode(t->root, tree2_name);

                if (tree1_root == NULL || tree2_root == NULL) {
                    printf("해당 트리를 찾을 수 없습니다.\n");
                    break;
                }

                // 새로운 루트 노드 생성
                Node* newRoot = newNode(data);

                // 두 트리를 병합하여 새로운 루트 노드에 추가
                joinTrees(newRoot, tree1_root, tree2_root);
                break;

            case 'K':
                if (t->root != NULL) {
                    clear(t->root);
                    t->root = NULL; // 루트 노드를 NULL로 설정하여 중복 해제를 방지
                } else {
                    printf("트리가 이미 비어 있습니다.\n");
                }
                break;
            case 'Q':
                return 0;
               
        }
    }
    return 0;
}

