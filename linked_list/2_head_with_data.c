#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free

/**
 * head : 데이터 포함, 곧 첫 번째 노드
 * 단점 : 이중 포인터로 head_ptr 관리 필요함
 */

typedef struct Node {
  struct Node* next;
  int data;
} Node;

// 순회
Node* create_node(int data);
void print_all_node(Node* head);
Node* find_last_node(Node* head);
int node_len(Node* head);

// 추가
void add_last_node(Node** head, int data);
void add_first_node(Node** head, int data);
void insert_node(Node* head, int nth, int data);

// 순회2
Node* find_node_nth(Node* head, int nth);
Node* find_node_data(Node* head, int data);

// 수정 및 삭제
void edit_node(Node* head, int nth, int modify_data);
void delete_first_node(Node** head);
void delete_node(Node** head, int nth);
void delete_all_node(Node** head);

int main() {
  Node* head = NULL;

  add_last_node(&head, 1);
  add_last_node(&head, 3);
  insert_node(head, 2, 2);
  print_all_node(head);
  printf("\n[len]: %d", node_len(head));
  printf("\n[(%d)th data]: %d", 2, find_node_nth(head, 2)->data);
  printf("\n[%d data exist]: %s", 3, find_node_data(head, 3) ? "yes" : "no");
  printf("\n[%d data exist]: %s", 50, find_node_data(head, 50) ? "yes" : "no");

  edit_node(head, 1, 100);
  printf("\n[after update!]");
  print_all_node(head);

  delete_first_node(&head);
  printf("\n[after delete!]");
  print_all_node(head);

  delete_node(&head, 2);
  printf("\n[after delete!]");
  print_all_node(head);

  delete_all_node(&head);
  printf("\n[all deleted!]");
  // print_all_node(head); // malloc-free 확인 불가

  printf("\n");

  return 0;
}

Node* create_node(int data) {
  Node* node = (Node*)malloc(sizeof(Node));
  node->next = NULL;
  node->data = data;

  return node;
}

void print_all_node(Node* cur) {
  printf("\n[print all] ");

  while (cur != NULL) {
    printf("%d > ", cur->data);
    cur = cur->next;
  }
}

Node* find_last_node(Node* cur) {
  while (cur->next != NULL) {
    cur = cur->next;
  }
  return cur;
}

int node_len(Node* cur) {
  int cnt = 0;

  while (cur != NULL) {
    cur = cur->next;
    cnt++;
  }

  return cnt;
}

void add_last_node(Node** head_ptr, int data) {
  /**
   * Q. 왜 main쪽에서
   * Node head = NULL; 로 할당하고, 포인터를 줄일 수 없나요?
   *
   * A. 구조체변수를 선언하고 그 자체를 NULL로 초기화할 수 없음.
   */

  Node* head = *head_ptr;  // 2중 포인터 익숙해지기

  Node* new_node = create_node(data);
  if (head == NULL) {
    *head_ptr = new_node;
  } else {
    Node* last_node = find_last_node(head);
    last_node->next = new_node;
  }
}

void add_first_node(Node** head_ptr, int data) {
  Node* head = *head_ptr;

  Node* new_node = create_node(data);
  // swap
  new_node->next = head;
  *head_ptr = new_node;
}

void insert_node(Node* head, int nth, int data) {
  Node* new_node = create_node(data);

  for (int i = 1; i < nth - 1 && head != NULL; i++) {
    head = head->next;
  }

  if (head != NULL) {
    // swap
    new_node->next = head->next;
    head->next = new_node;
  }
}

Node* find_node_nth(Node* head, int nth) {
  if (nth < 1 || nth > node_len(head)) {
    printf("\nwrong search! \n");
    return head;
  }

  for (int i = 1; i < nth && head != NULL; i++) {
    head = head->next;
  }

  return head;
}

Node* find_node_data(Node* head, int data) {
  Node* cur = head;

  while (cur != NULL) {
    if (cur->data == data) {
      return cur;
    }
    cur = cur->next;
  }

  return NULL;
}

void edit_node(Node* head, int nth, int modify_data) {
  Node* target_node = find_node_nth(head, nth);
  if (target_node != NULL) {
    target_node->data = modify_data;
  }
}

void delete_first_node(Node** head_ptr) {
  Node* cur = *head_ptr;

  if (cur != NULL) {
    Node* will_deleted = cur;
    *head_ptr = cur->next;
    free(will_deleted);
  }
}

void delete_node(Node** head_ptr, int nth) {
  Node* cur = *head_ptr;

  if (cur == NULL) return;

  if (nth == 1) {
    delete_first_node(head_ptr);
    return;
  }

  for (int i = 1; i < nth - 1 && cur->next != NULL; i++) {
    cur = cur->next;
  }

  if (cur->next != NULL) {
    Node* will_deleted = cur->next;
    cur->next = cur->next->next;
    free(will_deleted);
  }
}

void delete_all_node(Node** head_ptr) {
  Node* cur = *head_ptr;
  Node* next_node = NULL;

  while (cur != NULL) {
    next_node = cur->next;
    free(cur);
    cur = next_node;
  }

  *head_ptr = NULL;
}
