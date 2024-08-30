#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free

/**
 * head : Dummy Node, 단순 시작 주소 역할만
 */

typedef struct Node {
  struct Node* next;
  int data;
} Node;

// 순회
Node* init_list();
Node* create_node(int data);
void print_all_node(Node* head);
Node* find_last_node(Node* head);
int node_len(Node* head);

// 추가
void add_last_node(Node* head, int data);
void add_first_node(Node* head, int data);
void insert_node(Node* head, int nth, int data);

// 순회2
Node* find_node_nth(Node* head, int nth);
Node* find_node_data(Node* head, int data);

// 수정 및 삭제
void edit_node(Node* head, int nth, int modify_data);
void delete_first_node(Node* head);
void delete_node(Node* head, int nth);
void delete_all_node(Node* head);

int main() {
  Node* head = init_list();

  add_last_node(head, 1);
  add_last_node(head, 3);
  insert_node(head, 2, 2);
  print_all_node(head);
  printf("\n[len]: %d", node_len(head));
  printf("\n[(%d)th data]: %d", 2, find_node_nth(head, 2)->data);
  printf("\n[%d data exist]: %s", 3, find_node_data(head, 3) ? "yes" : "no");
  printf("\n[%d data exist]: %s", 50, find_node_data(head, 50) ? "yes" : "no");

  edit_node(head, 1, 100);
  printf("\n[after update!]");
  print_all_node(head);

  delete_first_node(head);
  printf("\n[after delete!]");
  print_all_node(head);

  delete_node(head, 2);
  printf("\n[after delete!]");
  print_all_node(head);

  delete_all_node(head);
  printf("\n[all deleted!]");
  // print_all_node(head); // malloc-free 확인 불가

  printf("\n");

  return 0;
}

Node* init_list() {
  Node* head = (Node*)malloc(sizeof(Node));
  head->next = NULL;

  return head;
}

Node* create_node(int data) {
  Node* node = (Node*)malloc(sizeof(Node));
  node->next = NULL;
  node->data = data;

  return node;
}

void print_all_node(Node* head) {
  printf("\n[print all] ");

  Node* cur = head->next;
  while (1) {
    if (cur) {
      printf("%d > ", cur->data);
    } else {
      break;
    }
    cur = cur->next;
  }
}

Node* find_last_node(Node* head) {
  // 힌트: last_node.next = NULL

  // ver1. cur pointer 할당 후 이동
  Node* cur = head;
  while (cur->next != NULL) {
    cur = cur->next;
  }
  return cur;

  // // ver2. cur pointer (=head) 재사용
  // while (head->next != NULL) {
  //   head = head->next;
  // }
  // return head;
}

int node_len(Node* head) {
  int cnt = 0;

  while (head->next != NULL) {
    head = head->next;
    cnt++;
  }

  return cnt;
}

void add_last_node(Node* head, int data) {
  Node* new_node = create_node(data);
  Node* last_node = find_last_node(head);
  last_node->next = new_node;
}

void add_first_node(Node* parent_node, int data) {
  Node* new_node = create_node(data);

  // swap
  new_node->next = parent_node->next;
  parent_node->next = new_node;
}

/*
[참고] insert 과정이 swap과 유사함
- tmp = new_node->next
- b = parent_node->next
- a = new_node;

void swap(int a, int b) {
  int tmp = b;
  b = a;
  a = tmp;
}
*/

void insert_node(Node* parent_node, int nth, int data) {
  // add 심화, 중간에 끼워넣기
  Node* new_node = create_node(data);

  for (int i = 1; i < nth; i++) {
    if (parent_node->next != NULL) {
      parent_node = parent_node->next;
    }
  }

  // swap
  new_node->next = parent_node->next;
  parent_node->next = new_node;
}

Node* find_node_nth(Node* head, int nth) {
  if (nth < 1 || nth > node_len(head)) {
    printf("\nwrong search! \n");
    return head;
  }

  Node* cur = head->next;

  for (int i = 1; i < nth; i++) {
    cur = cur->next;
  }

  return cur;
}

Node* find_node_data(Node* cur, int data) {
  Node* p = cur->next;

  while (p) {
    if (p->data == data) {
      return p;
    }

    p = p->next;
  }

  return NULL;
}

void edit_node(Node* head, int nth, int modify_data) {
  Node* target_node = find_node_nth(head, nth);
  target_node->data = modify_data;
}

void delete_first_node(Node* head) {
  Node* will_deleted = head->next;
  head->next = will_deleted->next;
  free(will_deleted);
}

void delete_node(Node* head, int nth) {
  Node* parent_node = head;

  for (int i = 1; i < nth; i++) {
    parent_node = parent_node->next;
  }

  Node* will_deleted = parent_node->next;
  parent_node->next = will_deleted->next;
  free(will_deleted);
}

void delete_all_node(Node* head) {
  Node* will_deleted = head;
  Node* next_node = NULL;

  while (will_deleted != NULL) {
    next_node = will_deleted->next;
    free(will_deleted);
    will_deleted = next_node;
  }

  free(head);
  head = NULL;
}