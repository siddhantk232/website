#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
};

typedef struct Node Node;

Node *create(int data) {
  Node *node = malloc(sizeof(Node));
  node->next = NULL;
  node->prev = NULL;
  node->data = data;
}

void insert_end(Node **head, int data) {
  if (!(*head)) {
    *head = create(data);
    return;
  }

  Node *ptr = *head;

  while (ptr->next != NULL) {
    ptr = ptr->next;
  }

  Node *node = create(data);
  node->next = NULL;
  node->prev = ptr;
  ptr->next  = node;
}

void insert_start(Node **head, int data) {
  if (!(*head)) {
    *head = create(data);
    return;
  }

  Node *node = create(data);
  node->next = *head;
  node->prev = NULL;
  (*head)->prev = node;
  *head = node;
}

void insert_pos(Node *head, int pos, int data) {
  Node *ptr = head;

  for (int i = 1; i < pos - 1; ++i) {
    ptr = ptr->next;
  }

  Node *node = create(data);
  Node *temp = ptr->next;
  node->next = temp;
  node->prev = ptr;
  ptr->next = node;
  temp->prev = node;
}

void delete_end(Node *head) {
  if (!head) return;

  Node *ptr = head;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }

  ptr->prev->next = NULL;
  free(ptr);
}

void delete_start(Node **head) {
  if (!head) return;
  (*head)->next->prev = NULL;
  Node *temp = *head;
  *head = (*head)->next;
  free(temp);
}

void delete_pos(Node *head, int pos) {
  Node *ptr = head;

  for (int i = 1; i < pos - 1; ++i) {
    ptr = ptr->next;
  }

  Node *temp = ptr->next;
  ptr->next->next->prev = ptr;
  ptr->next = ptr->next->next;
  free(temp);
}

void display(Node *head) {
  while (head != NULL) {
    printf("%d -> ", head->data);
    head = head->next;
  }
  printf(" NULL\n");
}

int main() {
  Node *head = create(10);

  display(head);

  insert_end(&head, 20);
  insert_end(&head, 30);
  insert_end(&head, 40);

  insert_start(&head, 3);
  insert_start(&head, 2);
  insert_start(&head, 1);

  delete_end(head);
  delete_end(head);

  insert_pos(head, 2, 100);
  insert_pos(head, 3, 300);

  display(head);

  delete_start(&head);
  delete_start(&head);

  delete_pos(head, 3);

  display(head);
}
