#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int height;
    int value;
	struct Node *left;
	struct Node *right;
    struct Node *parent;
} node;

typedef struct avl_tree {
	node *root;
} avl;


node* create(int value) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->value = value;
    new_node->height = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// 높이(height)를 업데이트하는 함수
int update_height(node* root) {
    if (root == NULL) {
        return -1; // 공백 트리의 높이는 -1로 정의합니다.
    }
    int left_height = update_height(root->left); // 왼쪽 서브트리의 높이 계산
    int right_height = update_height(root->right); // 오른쪽 서브트리의 높이 계산
    root->height = (left_height > right_height ? left_height : right_height) + 1; // 노드의 높이는 자식 노드 중 더 높은 값에 1을 더합니다.
    return root->height; // 노드의 높이를 반환합니다.
}

// 균형을 확인하는 함수
int balance_factor(node* root) {
    if (root == NULL) {
        return 0; // 공백 트리의 균형 요인은 0입니다.
    }
    int left_height = (root->left != NULL) ? root->left->height : -1; // 왼쪽 서브트리의 높이
    int right_height = (root->right != NULL) ? root->right->height : -1; // 오른쪽 서브트리의 높이
    return left_height - right_height; // 왼쪽 서브트리의 높이에서 오른쪽 서브트리의 높이를 빼서 균형 요인을 계산합니다.
}

// 우회전 함수
node* rotate_right(node* root) {
    node* new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    root->height = (root->left != NULL ? root->left->height : -1) + 1;
    new_root->height = (new_root->right != NULL ? new_root->right->height : -1) + 1;
    return new_root;
}

// 좌회전 함수
node* rotate_left(node* root) {
    node* new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    root->height = (root->right != NULL ? root->right->height : -1) + 1;
    new_root->height = (new_root->left != NULL ? new_root->left->height : -1) + 1;
    return new_root;
}

// 노드 삽입 함수 (재귀적으로 노드를 삽입하고 균형을 유지하기 위해 회전 연산을 수행합니다.)
node* insert_node(node* root, int value) {
    if (root == NULL) {
        root = create(value); // 새로운 노드 생성
    } else if (value < root->value) {
        root->left = insert_node(root->left, value); // 왼쪽 서브트리에 삽입
    } else if (value > root->value) {
        root->right = insert_node(root->right, value); // 오른쪽 서브트리에 삽입
    }

    // 노드 삽입 후, 높이를 업데이트하고 균형을 확인하여 회전 연산을 수행합니다.
    update_height(root);
    int bf = balance_factor(root);

    // 균형이 깨진 경우 회전 연산을 수행합니다.
    if (bf > 1) {
        if (value < root->left->value) { // LL 형태
            root = rotate_right(root);
        } else { // LR 형태
            root->left = rotate_left(root->left);
            root = rotate_right(root);
        }
    } else if (bf < -1) {
        if (value > root->right->value) { // RR 형태
            root = rotate_left(root);
        } else { // RL 형태
            root->right = rotate_right(root->right);
            root = rotate_left(root);
        }
    }
    return root;
}

//function to print the tree
//ex) (5(3(2,4),7(6,8)))
void print(node* root) {
    if (root == NULL) return;
    printf("%d", root->value);
    if (root->left != NULL || root->right != NULL) {
        printf("(");
        print(root->left);
        printf(",");
        print(root->right);
        printf(")");
    }
}

//function to print nodes in inorder_traversal
void inorder_traversal(node* root) {
    if (root == NULL) {
        return;
    }
    inorder_traversal(root->left);
    printf("%d ", root->value);
    inorder_traversal(root->right);
}

// function to print nodes in right_root_left_traversal
void right_root_left_traversal(node* root) {
    if (root == NULL) {
        return;
    }
    right_root_left_traversal(root->right); 
    printf("%d ", root->value);
    right_root_left_traversal(root->left); 
}

//function to get the minimum node
node* get_min(node* root) {
    if (root->left == NULL) {
        return root;
    }
    return get_min(root->left);
}

//function to get the maximum node
node* get_max(node* root) {
    if (root->right == NULL) {
        return root;
    }
    return get_max(root->right);
}

//function to find the node with the value
//print the path to the node
//ex) Root-Right-Left
//If there isn't the node, print "Error"
node *find_node(node *root, int value, char *path) {
    if (root == NULL) {
        return NULL;
    }
    if (root->value == value) {
        printf("Root%s\n", path);
        return root;
    }
    if (value < root->value) {
        char newPath[100]; // 새로운 경로를 저장할 변수
        strcpy(newPath, path); // 이전 경로를 복사
        strcat(newPath, "-Left"); // 새로운 경로 추가
        return find_node(root->left, value, newPath); // 새로운 경로로 재귀 호출
    }
    if (value > root->value) {
        char newPath[100]; // 새로운 경로를 저장할 변수
        strcpy(newPath, path); // 이전 경로를 복사
        strcat(newPath, "-Right"); // 새로운 경로 추가
        return find_node(root->right, value, newPath); // 새로운 경로로 재귀 호출
    }
}

//function to print the height of the tree
void height_tree(node* root) {
    if (root == NULL) {
        printf("0\n");
        return;
    }
    printf("%d\n", root->height);
}

//function to print the height of the node
void height_node(node* root, int value) {
    if (root == NULL) {
        printf("Error\n");
        return;
    }
    if (root->value == value) {
        printf("%d\n", root->height);
        return;
    }
    if (value < root->value) {
        height_node(root->left, value);
    } else if (value > root->value) {
        height_node(root->right, value);
    }
}

//function to get right child of the selected node
//If there isn't the child node, print "NULL"
void get_right_child(node* root, int value) {
    if (root == NULL) {
        printf("NULL\n");
        return;
    }
    if (root->value == value) {
        if (root->right == NULL) {
            printf("NULL\n");
            return;
        }
        printf("%d\n", root->right->value);
        return;
    }
    if (value < root->value) {
        get_right_child(root->left, value);
    } else if (value > root->value) {
        get_right_child
        (root->right, value);
    }
}

//function to get left child of the selected node
void get_left_child(node* root, int value) {
    if (root == NULL) {
        printf("NULL\n");
        return;
    }
    if (root->value == value) {
        if (root->left == NULL) {
            printf("NULL\n");
            return;
        }
        printf("%d\n", root->left->value);
        return;
    }
    if (value < root->value) {
        get_left_child(root->left, value);
    } else if (value > root->value) {
        get_left_child(root->right, value);
    }
}

//function to count the number of nodes in the tree
int count_nodes(node* root) {
    if (root == NULL) {
        return 0; // 빈 트리이므로 0을 반환합니다.
    }
    
    // 현재 노드를 포함한 왼쪽 서브트리와 오른쪽 서브트리의 노드 수를 재귀적으로 구합니다.
    int left_count = count_nodes(root->left);
    int right_count = count_nodes(root->right);

    // 현재 노드와 왼쪽 서브트리, 오른쪽 서브트리의 노드 수를 합하여 반환합니다.
    return 1 + left_count + right_count;
}


// 노드 삭제 함수 (재귀적으로 노드를 삭제하고 균형을 유지하기 위해 회전 연산을 수행합니다.)
node* delete_node(node* root, int value) {
    if (root == NULL) {
        return root;
    }
    if (value < root->value) {
        root->left = delete_node(root->left, value);
    } else if (value > root->value) {
        root->right = delete_node(root->right, value);
    } else {
        if (root->left == NULL) {
            node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            node* temp = root->left;
            free(root);
            return temp;
        }
        node* temp = get_min(root->right);
        root->value = temp->value;
        root->right = delete_node(root->right, temp->value);
    }

    // 노드 삭제 후, 높이를 업데이트하고 균형을 확인하여 회전 연산을 수행합니다.
    update_height(root);
    int bf = balance_factor(root);

    // 균형이 깨진 경우 회전 연산을 수행합니다.
    if (bf > 1) {
        if (balance_factor(root->left) >= 0) { // LL 형태
            root = rotate_right(root);
        } else { // LR 형태
            root->left = rotate_left(root->left);
            root = rotate_right(root);
        }
    } else if (bf < -1) {
        if (balance_factor(root->right) <= 0) { // RR 형태
            root = rotate_left(root);
        } else { // RL 형태
            root->right = rotate_right(root->right);
            root = rotate_left(root);
        }
    }
    return root;
}

//function to clear the tree
void clear(node* root) {
    if (root == NULL) {
        return;
    }
    clear(root->left);
    clear(root->right);
    free(root);
}

int get_balance_factor(node* root, int value) {
    // 노드를 찾기 위해 탐색합니다.
    node* current = root;
    while (current != NULL) {
        if (current->value == value) {
            break; // 노드를 찾으면 루프를 종료합니다.
        } else if (value < current->value) {
            current = current->left; // 왼쪽 자식으로 이동합니다.
        } else {
            current = current->right; // 오른쪽 자식으로 이동합니다.
        }
    }

    // 노드를 찾지 못한 경우
    if (current == NULL) {
        printf("Error\n");
        return 0;
    }

    // 왼쪽 서브트리와 오른쪽 서브트리의 높이를 계산합니다.
    int left_height = (current->left != NULL) ? current->left->height : -1;
    int right_height = (current->right != NULL) ? current->right->height : -1;

    // 균형 요인을 반환합니다.
    return left_height - right_height;
}