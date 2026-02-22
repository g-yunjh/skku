#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int revenue;
    char storename[50];
    struct Node* left;
    struct Node* right;
} Node;

// Helper function to create a new node
Node* createNode(int revenue, char* storename) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->revenue = revenue;
    strcpy(newNode->storename, storename);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert a new node into the BST
Node* insertNode(Node* root, int revenue, char* storename) {
    if (root == NULL) {
        return createNode(revenue, storename);
    }
    if (revenue < root->revenue) {
        root->left = insertNode(root->left, revenue, storename);
    } else if (revenue > root->revenue) {
        root->right = insertNode(root->right, revenue, storename);
    }
    return root;
}

// Find the minimum value node in the BST
Node* findMinNode(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

// Delete a node from the BST
Node* deleteNode(Node* root, char* storename) {
    if (root == NULL) return root;

    int cmp = strcmp(storename, root->storename);
    if (cmp < 0) {
        root->left = deleteNode(root->left, storename);
    } else if (cmp > 0) {
        root->right = deleteNode(root->right, storename);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = findMinNode(root->right);
        root->revenue = temp->revenue;
        strcpy(root->storename, temp->storename);
        root->right = deleteNode(root->right, temp->storename);
    }
    return root;
}

// Function to print the BST
void show(Node* root) {
    if (root == NULL) return;
    printf("%s: %d", root->storename, root->revenue);
    if (root->left != NULL || root->right != NULL) {
        printf("(");
        show(root->left);
        printf(",");
        show(root->right);
        printf(")");
    }
}

// Find node by storename
Node* findNode(Node* root, char* storename) {
    if (root == NULL) return NULL;
    int cmp = strcmp(storename, root->storename);
    if (cmp < 0) return findNode(root->left, storename);
    if (cmp > 0) return findNode(root->right, storename);
    return root;
}

// Get maximum revenue node
Node* getMax(Node* root) {
    while (root->right != NULL) root = root->right;
    return root;
}

// Get minimum revenue node
Node* getMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

// Range search
void rangeNode(Node* root, int min, int max) {
    if (root == NULL) return;
    if (min < root->revenue) rangeNode(root->left, min, max);
    if (min <= root->revenue && max >= root->revenue)
        printf("%s: %d\n", root->storename, root->revenue);
    if (max > root->revenue) rangeNode(root->right, min, max);
}

// Count total nodes
int countNode(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNode(root->left) + countNode(root->right);
}

// Helper function to round a floating point number to the nearest integer
int roundRevenue(double revenue) {
    return (int)(revenue + 0.5);
}

int main() {
    Node* root = NULL;

    while (1) {
        char command;
        char storename[50];
        double revenue_double;
        int revenue, min, max;

        printf("\nEnter command: ");
        scanf(" %c", &command);

        switch (command) {
            case '+':  // Insert node
                scanf("%s %lf", storename, &revenue_double);
                revenue = roundRevenue(revenue_double);
                root = insertNode(root, revenue, storename);
                show(root);
                printf("\n");
                break;
            case '-':  // Delete node
                scanf("%s", storename);
                root = deleteNode(root, storename);
                show(root);
                printf("\n");
                break;
            case 'P':  // Show tree
                printf("Tree structure:\n");
                show(root);
                printf("\n");
                break;
            case 'X':  // Get max revenue store
                {
                    Node* maxNode = getMax(root);
                    if (maxNode != NULL) printf("Max revenue store: %s: %d\n", maxNode->storename, maxNode->revenue);
                }
                break;
            case 'N':  // Get min revenue store
                {
                    Node* minNode = getMin(root);
                    if (minNode != NULL) printf("Min revenue store: %s: %d\n", minNode->storename, minNode->revenue);
                }
                break;
            case 'F':  // Find node
                scanf("%s", storename);
                {
                    Node* foundNode = findNode(root, storename);
                    if (foundNode != NULL) printf("%s: %d\n", foundNode->storename, foundNode->revenue);
                    else printf("Store not found.\n");
                }
                break;
            case '~':  // Range search
                scanf("%d %d", &min, &max);
                printf("Stores with Revenue between %d and %d:\n", min, max);
                rangeNode(root, min, max);
                break;
            case '#':  // Count nodes
                printf("Total Stores: %d\n", countNode(root));
                break;
            case 'Q':  // Quit
                return 0;
            default:
                printf("Invalid command.\n");
        }
    }

    return 0;
}