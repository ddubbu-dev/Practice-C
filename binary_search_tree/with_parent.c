#include <stdio.h>
#include <stdlib.h>

/**
 * BST
 * - Binary Tree
 * - Left < Root < Right
 */

typedef struct Node {
  int data;
  struct Node *left, *right, *parent;
} Node;

// fyi. 우선, parent 포인터변수가 추가되면 어떤 작업이 추가되는지만 체크하기
// parent; BST 에서는 안쓰이는데 RB Tree에서는 어떻게 사용될지 (c -> p -> g)
Node* insert(Node* root, int value);
void inorder_print(Node* root);
// TODO: skip
// Node* search(Node* root, int value);
// Node* find_max_node(Node* root);
// Node* delete(Node* root, int value);

int main() {
  Node* root = NULL;

  root = insert(root, 5);
  inorder_print(root);
  printf("\n");

  root = insert(root, 3);
  inorder_print(root);
  printf("\n");

  root = insert(root, 7);
  inorder_print(root);
  printf("\n");

  return 0;
}

Node* insert(Node* root, int value) {
  if (root == NULL) {
    root = (Node*)malloc(sizeof(Node));
    root->data = value;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    return root;
  }

  int cur_value = root->data;
  if (cur_value > value) {
    root->left = insert(root->left, value);
    root->left->parent = root;
  } else {
    root->right = insert(root->right, value);
    root->right->parent = root;
  }

  return root;
}

void inorder_print(Node* root) {
  if (root == NULL) {
    return;
  }

  inorder_print(root->left);
  printf("%d > ", root->data);
  inorder_print(root->right);
}
