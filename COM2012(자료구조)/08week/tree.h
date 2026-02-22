#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode {
    char data;
    int degree;
    struct tagNode *child;
}Node;

typedef struct tagTree {
    Node *root;
    int binary;
}Tree; 

Node* newNode(char data) {
    Node* returnNode = (Node*)malloc(sizeof(Node));
    returnNode->data = data;
    returnNode->degree = 0;
    returnNode->child = NULL;
    return returnNode;

}

Tree* create() {
    Tree* returnTree = (Tree*)malloc(sizeof(Tree));
    returnTree->root = NULL;

    char type;
    printf("트리의 타입을 선택하세요 (B: 이진 트리, G: 일반 트리): ");
    scanf(" %c", &type);

    if (type == 'B') {
        // 이진 트리일 경우 자식 노드의 개수를 2개로 제한
        returnTree->binary = 1;
    } else if (type == 'G') {
        // 일반 트리일 경우 자식 노드의 개수를 제한하지 않음
        returnTree->binary = 0;
    } else {
        printf("올바른 입력이 아닙니다. 일반 트리로 생성합니다.\n");
        returnTree->binary = 0;
    }

    return returnTree;
}

void print(Node *p) {
    if (p == NULL) {
        return;
    }

    printf("%c", p->data);

    if (p->degree > 0) {
        printf("(");
        for (int i = 0; i < p->degree; i++) {
            print(&(p->child[i]));
            if (i < p->degree - 1) {
                printf(",");
            }
        }
        printf(")");
    }
}

Node* findNode(Node *root, char data) {
    if (root == NULL) {
        return NULL;
    }

    if (root->data == data) {
        return root;
    }

    Node *found = NULL;
    for (int i = 0; i < root->degree; i++) {
        found = findNode(&(root->child[i]), data);
        if (found != NULL) {
            break;
        }
    }
    return found;
}

void insertNode(Node *p, char data, int binary) {
    if (binary && p->degree >= 2) {
        printf("이진 트리에서는 더 이상 자식 노드를 추가할 수 없습니다.\n");
        return;
    }

    p->child = (Node*)realloc(p->child, sizeof(Node) * (p->degree + 1));
    p->child[p->degree].data = data;
    p->child[p->degree].degree = 0;
    p->child[p->degree].child = NULL;
    p->degree++;
}

Node* getSibling(Node* root, char data) {
    if (root == NULL) {
        return NULL;
    }

    for (int i = 0; i < root->degree; i++) {
        if (root->child[i].data == data) {
            if (root->degree <= 1) {
                printf("형제 노드가 존재하지 않습니다.\n");
                return NULL;
            } else {
                printf("{");
                for (int j = 0; j < root->degree; j++) {
                    if (j != i) {
                        printf("%c", root->child[j].data);
                        if (j < root->degree - 1) {
                            printf(",");
                        }
                    }
                }
                printf("}\n");
                return &(root->child[(i + 1) % root->degree]);
            }
        }
    }

    Node* sibling = NULL;
    for (int i = 0; i < root->degree; i++) {
        sibling = getSibling(&(root->child[i]), data);
        if (sibling != NULL) {
            break;
        }
    }
    return sibling;
}


Node* getParent(Node* root, char data) {
    if (root == NULL) {
        return NULL;
    }

    Node* parent = NULL;
    for (int i = 0; i < root->degree; i++) {
        if (root->child[i].data == data) {
            parent = root;
            break;
        } else {
            parent = getParent(&(root->child[i]), data);
            if (parent != NULL) {
                break;
            }
        }
    }
    return parent;
}

//print the children of the node
//ex) {b,c,d,e}
void getChild(Node* root, char data) {
    if (root == NULL) {
        return;
    }

    if (root->data == data) {
        if (root->degree == 0) {
            printf("자식 노드가 존재하지 않습니다.\n");
        } else {
            printf("{");
            for (int i = 0; i < root->degree; i++) {
                printf("%c", root->child[i].data);
                if (i < root->degree - 1) {
                    printf(",");
                }
            }
            printf("}\n");
        }
    } else {
        for (int i = 0; i < root->degree; i++) {
            getChild(&(root->child[i]), data);
        }
    }
}

//print the level of the node(루트 노드에서 해당 노드까지의 간선 수)
// Return the level of the node (the number of edges from the root node to the specified node)
int levelOfNode(Node* root, char data) {
    if (root == NULL) {
        return -1; // 노드를 찾을 수 없을 경우 -1 반환
    }

    if (root->data == data) {
        return 0; // 루트 노드일 경우 레벨 0 반환
    }

    for (int i = 0; i < root->degree; i++) {
        int level = levelOfNode(&(root->child[i]), data);
        if (level != -1) {
            return level + 1; // 자식 노드에서 찾은 경우 현재 레벨에 1을 더하여 반환
        }
    }

    return -1; // 자식 노드에서도 발견하지 못한 경우 -1 반환
}

//print the level of the tree(트리 전체에서 가장 깊은 노드의 레벨)
int levelOfTree(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int maxLevel = 0;
    for (int i = 0; i < root->degree; i++) {
        int level = levelOfTree(&(root->child[i])) + 1;
        if (level > maxLevel) {
            maxLevel = level;
        }
    }
    return maxLevel;
}



//delete node if there isn't any child node
void deleteNode(Node* root, char data) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < root->degree; i++) {
        if (root->child[i].data == data) {
            if (root->child[i].degree == 0) {
                for (int j = i; j < root->degree - 1; j++) {
                    root->child[j] = root->child[j + 1];
                }
                root->degree--;
                root->child = (Node*)realloc(root->child, sizeof(Node) * root->degree);
                return;
            } else {
                printf("자식 노드가 존재하여 삭제할 수 없습니다.\n");
                return;
            }
        } else {
            deleteNode(&(root->child[i]), data);
        }
    }
}

//print the ancestors of the node
//출력은 해당노드에서 거슬러 올라가며
//부모노드를 출력하고 루트노드까지 출력 ex) F B A
void getAncestors(Node* root, char data) {
    if (root == NULL) {
        return;
    }

    if (root->data == data) {
        return;
    }

    for (int i = 0; i < root->degree; i++) {
        if (findNode(&(root->child[i]), data) != NULL) {
            getAncestors(&(root->child[i]), data); // 해당 노드를 찾은 경우 해당 노드의 조상 노드 출력
            break;
        }
    }

    printf("%c ", root->data); // 현재 노드 출력
}

//print the descendants of the node
//출력은 바로 아래 자식노드에서 시작하여 모든 자손노드를 출력 ex) D E
void getDescendants(Node* root, char data) {
    if (root == NULL) {
        return;
    }

    if (root->data == data) {
        // 해당 노드의 자손 노드 출력
        for (int i = 0; i < root->degree; i++) {
            printf("%c ", root->child[i].data);
            getDescendants(&(root->child[i]), root->child[i].data);
        }
    } else {
        // 입력된 노드가 아닌 경우, 모든 자식 노드로 재귀 호출
        for (int i = 0; i < root->degree; i++) {
            getDescendants(&(root->child[i]), data);
        }
    }
}

//선택한 노드의 자식 노드의 개수를 반환
int degreeOfNode(Node* root, char data) {
    if (root == NULL) {
        return 0;
    }

    if (root->data == data) {
        return root->degree;
    }

    for (int i = 0; i < root->degree; i++) {
        int count = degreeOfNode(&(root->child[i]), data);
        if (count != 0) {
            return count;
        }
    }
    return 0;
}

//자식이 가장 많은 노드의 자식노드 개수
int degreeOfTree(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int max = root->degree;
    for (int i = 0; i < root->degree; i++) {
        int degree = degreeOfTree(&(root->child[i]));
        if (degree > max) {
            max = degree;
        }
    }
    return max;
}

//count the number of nodes in the tree
int countNode(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int count = 1; // 현재 노드 카운트
    for (int i = 0; i < root->degree; i++) {
        count += countNode(&(root->child[i])); // 모든 자식 노드의 카운트 누적
    }
    return count;
}

//insert sibling nodes
void insertSibling(Node* root, char parentData, char siblingData) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < root->degree; i++) {
        if (root->child[i].data == parentData) {
            root->child = (Node*)realloc(root->child, sizeof(Node) * (root->degree + 1));
            root->child[root->degree].data = siblingData;
            root->child[root->degree].degree = 0;
            root->child[root->degree].child = NULL;
            root->degree++;
            return;
        } else {
            insertSibling(&(root->child[i]), parentData, siblingData);
        }
    }
}

//join the trees
//joinTrees(newRoot, tree1, tree2)
void joinTrees(Node* newRoot, Node* tree1, Node* tree2) {
    newRoot->degree = 2;
    newRoot->child = (Node*)malloc(sizeof(Node) * 2);
    newRoot->child[0] = *tree1;
    newRoot->child[1] = *tree2;
}

//delete the tree
void clear(Node* root) {root = NULL;}
