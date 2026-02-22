//2022313366_윤주환
//추가 기능 3가지: 노드의 부모 노드 찾기, 두 노드의 최소 공통 조상 찾기, 두 노드 사이의 거리 찾기
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *left, *right;
} node;

// Function to create a root node
node* create (int data) {
    node *root = (node*)malloc(sizeof(node));
    root->data = data;
    root->left = root->right = NULL;
    return root;
}

// Function to insert a node
node* insert_node (node *root, int data) {
    if (root == NULL) return create(data);
    if (data < root->data) root->left = insert_node(root->left, data);
    else if (data > root->data) root->right = insert_node(root->right, data);
    return root;
}

// Function to print the tree
void print(node* root) {
    if (root == NULL) return;
    printf("%d", root->data);
    if (root->left != NULL || root->right != NULL) {
        printf("(");
        print(root->left);
        printf(",");
        print(root->right);
        printf(")");
    }
}

// Function to inorder traversal
void inorder_traversal(node* root) {
    if (root == NULL) return;
    inorder_traversal(root->left);
    printf("%d ", root->data);
    inorder_traversal(root->right);
}

// Function to postorder traversal
void right_root_left_traversal(node* root) {
    if (root == NULL) return;
    right_root_left_traversal(root->right);
    printf("%d ", root->data);
    right_root_left_traversal(root->left);
}

// Function to minimum value node
node* get_min(node *root) {
    node *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to maximum value node
node* get_max(node *root) {
    node *current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

// Function to find a node
node *find_node(node *root, int data, char *path) {
    if (root == NULL) {
        printf("Error\n");
        return NULL;
    }
    if (root->data == data) {
        printf("Root");
        printf("%s\n", path);
        return root;
    }
    if (data < root->data) {
        char newPath[100]; // 새로운 경로를 저장할 변수
        strcpy(newPath, path); // 이전 경로를 복사
        strcat(newPath, " > Left"); // 새로운 경로 추가
        return find_node(root->left, data, newPath); // 새로운 경로로 재귀 호출
    }
    if (data > root->data) {
        char newPath[100]; // 새로운 경로를 저장할 변수
        strcpy(newPath, path); // 이전 경로를 복사
        strcat(newPath, " > Right"); // 새로운 경로 추가
        return find_node(root->right, data, newPath); // 새로운 경로로 재귀 호출
    }
}

// Function to delete a node
node* delete_node(node *root, int data) {
    if (root == NULL) return root;

    // 데이터가 현재 노드보다 작은 경우 왼쪽 서브트리에서 삭제를 수행합니다.
    if (data < root->data) {
        root->left = delete_node(root->left, data);
    }
    // 데이터가 현재 노드보다 큰 경우 오른쪽 서브트리에서 삭제를 수행합니다.
    else if (data > root->data) {
        root->right = delete_node(root->right, data);
    }
    // 삭제할 노드를 찾은 경우입니다.
    else {
        // 자식이 하나 이거나 없는 경우
        if (root->left == NULL) {
            node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            node *temp = root->left;
            free(root);
            return temp;
        }

        // 두 개의 자식이 있는 경우
        // 왼쪽 서브트리에서 가장 큰 값을 가진 노드를 찾습니다.
        node *temp = get_max(root->left);

        // 찾은 노드의 값을 현재 노드로 복사합니다.
        root->data = temp->data;

        // 왼쪽 서브트리에서 찾은 노드를 삭제합니다.
        root->left = delete_node(root->left, temp->data);
    }
    return root;
}

// Function to print height of the tree
int height(node *root) {
    if (root == NULL) return 0;
    int left_height = height(root->left);
    int right_height = height(root->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

// Function to get the right child of a node
node* get_right_child(node *root, int data) {
    node *current = root;
    while (current != NULL) {
        if (current->data == data) {
            return (current->right != NULL) ? current->right : NULL;
        } else if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

// Function to get the left child of a node
node* get_left_child(node *root, int data) {
    node *current = root;
    while (current != NULL) {
        if (current->data == data) {
            return (current->left != NULL) ? current->left : NULL;
        } else if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}


// Function to count the number of nodes
int count_node(node *root) {
    if (root == NULL) return 0;
    return count_node(root->left) + count_node(root->right) + 1;
}

// Function to delete the tree
void clear(node *root) {
    root = NULL;
    root->left = root->right = NULL;    
}

//Function to find the parent of a node
node* find_parent(node *root, int data) {
    if (root == NULL) return NULL;
    if (root->left != NULL && root->left->data == data) return root;
    if (root->right != NULL && root->right->data == data) return root;
    if (data < root->data) return find_parent(root->left, data);
    if (data > root->data) return find_parent(root->right, data);
    return NULL;
}

//Function to find the lowest common ancestor(LCA) of two nodes
node* find_lca(node *root, int data1, int data2) {
    if (root == NULL) return NULL;
    if (data1 < root->data && data2 < root->data) return find_lca(root->left, data1, data2);
    if (data1 > root->data && data2 > root->data) return find_lca(root->right, data1, data2);
    return root;
}

//Function to find the distance between two nodes
int find_distance(node *root, int data1, int data2) {
    node *lca = find_lca(root, data1, data2);
    node *current = lca;
    int distance = 0;
    while (current->data != data1) {
        if (data1 < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
        distance++;
    }
    current = lca;
    while (current->data != data2) {
        if (data2 < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
        distance++;
    }
    return distance;
}