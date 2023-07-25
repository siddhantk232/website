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

Node *head;

void insert_end(int data) {
  if (!(head)) {
    head = create(data);
    return;
  }

  Node *ptr = head;

  while (ptr->next != NULL) {
    ptr = ptr->next;
  }

  Node *node = create(data);
  node->next = NULL;
  node->prev = ptr;
  ptr->next  = node;
}

void display() {
  Node *ptr = head;
  while (ptr != NULL) {
    printf("%d -> ", ptr->data);
    ptr = ptr->next;
  }
  printf(" NULL\n");
}

int main() {
  insert_end(10);
  insert_end(20);
  insert_end(30);
  insert_end(40);

  display(head);
}
