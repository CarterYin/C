#include <stdio.h>
#include <stdlib.h>

// 定义二叉排序树的节点结构
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// 创建新节点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 非递归插入节点
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }

    Node* current = root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

// 非递归查找节点
Node* search(Node* root, int data) {
    Node* current = root;

    while (current != NULL && current->data != data) {
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return current;
}

// 中序遍历（递归实现）
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("中序遍历: ");
    inorderTraversal(root);
    printf("\n");

    int key = 40;
    Node* result = search(root, key);
    if (result != NULL) {
        printf("找到节点: %d\n", result->data);
    } else {
        printf("未找到节点: %d\n", key);
    }

    return 0;
}