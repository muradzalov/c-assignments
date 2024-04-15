#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
    char data;
    struct node *left, *right;
} node;

node* newNode(char item) {
    node *temp = (node *)malloc(sizeof(node));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

node* insert(node* node, char data) {
    if (node == NULL) return newNode(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    return node;
}

void inOrder(node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%c", root->data);
        inOrder(root->right);
    }
}

void main() {
    node *root = NULL;
    char str[100];

    printf("Enter a string: ");
    scanf("%99s", str);

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            root = insert(root, tolower(str[i]));
        }
    }

    printf("Letters in alphabetical order: ");
    inOrder(root);
}