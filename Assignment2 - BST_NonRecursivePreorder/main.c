#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *left;
    struct node *right;
};

struct binary_search_tree {
    struct node *root;
};

void non_recursive_preorder(int *myArray, int lengthOfArray) {
    // Create a binary search tree
    struct binary_search_tree *tree = (struct binary_search_tree *) malloc(sizeof(struct binary_search_tree));
    if (tree == NULL) {
        printf("Cannot allocate space in heap...Exiting...\n");
        exit(1);
    }
    tree->root = NULL;

    // Create root node and assign first element of myArray
    struct node *root = (struct node *) malloc(sizeof(struct node));
    root->value = myArray[0];
    root->left = root->right = NULL;

    // tree's root assigned to root node that we just created.
    tree->root = root;

    // The for loop to add myArray elements to tree
    // We initialized i=1 because first element of myArray is root
    for (int i = 1; i < lengthOfArray; i++) {
        struct node *newNode;
        struct node *temp;
        struct node *parent;

        temp = tree->root;
        while (temp != NULL) {
            parent = temp;
            if (myArray[i] < temp->value) temp = temp->left;
            else if (myArray[i] > temp->value) temp = temp->right;
            else return;
        }

        newNode = (struct node *) malloc(sizeof(struct node));
        newNode->value = myArray[i];
        newNode->left = newNode->right = NULL;

        if (tree->root == NULL) {
            tree->root = newNode;
            return;
        }
        if (myArray[i] < parent->value) parent->left = newNode;
        else parent->right = newNode;
    }

    // Iterative preorder
    struct node *save[100];
    int top = 0;

    save[top++] = root;
    while (top != 0) {
        root = save[--top];

        printf("%4d", root->value);

        if (root->right != NULL)
            save[top++] = root->right;
        if (root->left != NULL)
            save[top++] = root->left;
    }
}

int main() {
    int myArray[10] = {80, 8, 30, 90, 5, 3, 15, 7, 22, 6};
    non_recursive_preorder(myArray, 10);

    // result should be: 80   8   5   3   7   6  30  15  22  90
    return 0;
}
