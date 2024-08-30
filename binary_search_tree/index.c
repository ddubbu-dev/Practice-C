#include <stdio.h>
#include <stdlib.h>

/**
 * BST
 * - Binary Tree
 * - Left < Root < Right
 */

typedef struct Node {
  int data;
  struct Node *left, *right;
} Node;

Node* insert(Node* root, int value);
void inorder_print(Node* root);
Node* search(Node* root, int value);

// hard
Node* find_max_node(Node* root);
Node* delete(Node* root, int value);

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

  root = insert(root, 1);
  inorder_print(root);
  printf("\n");

  root = insert(root, 9);
  inorder_print(root);
  printf("\n");

  root = insert(root, 6);
  inorder_print(root);
  printf("\n");

  root = delete (root, 7);
  inorder_print(root);
  printf("\n");

  return 0;
}

Node* insert(Node* root, int value) {
  if (root == NULL) {  // = leaf node
    root = (Node*)malloc(sizeof(Node));
    root->data = value;
    root->left = NULL;
    root->right = NULL;
    return root;
  }

  int cur_value = root->data;
  if (cur_value > value) {
    root->left = insert(root->left, value);
  } else {
    root->right = insert(root->right, value);
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

Node* search(Node* root, int target_value) {
  if (root == NULL) {
    return NULL;
  }

  int cur_value = root->data;
  if (cur_value == target_value) {
    return root;
  } else if (target_value < cur_value) {
    return search(root->left, target_value);
  } else {
    return search(root->right, target_value);
  }
}

Node* find_max_node(Node* root) {  // leaf = NULL
  if (root && root->right == NULL) {
    return root;
  }

  return find_max_node(root->right);
}

Node* delete(Node* root, int target_value) {
  if (root == NULL) {
    return NULL;
  }

  int cur_value = root->data;

  if (target_value < cur_value) {
    root->left = delete (root->left, target_value);
    return root;
  } else if (target_value > cur_value) {
    root->right = delete (root->right, target_value);
    return root;
  }

  // target_value == cur_value
  Node* deleted_node = root;
  // 1. 자식 노드 한개만 or 아예 없을 경우
  if (deleted_node->left == NULL || deleted_node->right == NULL) {
    Node* new_root = NULL;
    if (deleted_node->left == NULL) {
      new_root = deleted_node->right;
    } else {
      new_root = deleted_node->left;
    }

    free(deleted_node);

    return new_root;
  }

  // 2. 자식 노드 두개
  // deleted_node->left 중 가장 큰값이 새로운 root 로 갱신됨
  Node* new_root = find_max_node(deleted_node->left);
  deleted_node->data = new_root->data;
  deleted_node->left = delete (root->left, new_root->data);  // recursive

  return root;
}