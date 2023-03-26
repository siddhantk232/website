#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

typedef struct Node Node;

Node *create(int val);
void insert_at_end(Node *head, int el);
void insert_before_start(Node **head, int el);
void insert_after(Node *ll, int el);
int insert_at_pos(Node *head, unsigned int pos, int el);
void delete_start(Node **head);
void delete_end(Node *head);
int delete_pos(Node *head, int pos);
void print_ll(Node *head);

int main() {
  Node *head = create(1);
  Node *head2 = create(100);

  // insert
  insert_at_end(head, 2);
  insert_at_end(head, 3);

  insert_before_start(&head, -2);
  insert_before_start(&head, -3);

  // -3 -2 1 2 3
  insert_after(head->next->next->next->next, 5);

  insert_at_pos(head, 6, 4);

  print_ll(head);

  insert_at_end(head2, 200);
  insert_at_end(head2, 300);
  insert_at_end(head2, 400);
  insert_at_end(head2, 500);

  print_ll(head);

  delete_start(&head);
  delete_end(head);
  delete_pos(head, 3);

  print_ll(head);
}

void delete_start(Node **head) {
  Node *temp = *head;
  *head = (*head)->next;

  free(temp);
}

void delete_end(Node *head) {
  while (head->next->next != NULL) {
    head = head->next;
  }

  Node *temp = head->next;
  head->next = NULL;
  free(temp);
}

int delete_pos(Node *head, int pos) {
  assert(pos > 1);
  for (int i = 1; i < pos - 1 && head != NULL; ++i) {
    head = head->next;
  }

  if (head == NULL) {
    return -1;
  }

  Node *temp = head->next;
  head->next = head->next->next;
  free(temp);
  return 0;
}

// O(n)
void insert_at_end(Node *head, int el) {
  assert(head != NULL);

  // go to the end
  while (head->next != NULL) {
    head = head->next;
  }

  // create new Node
  Node *n = create(el);
  head->next = n;
}

// O(1)
void insert_before_start(Node **head, int el) {
  Node *n = create(el);
  n->next = *head;
  *head = n;
}

// O(1)
void insert_after(Node *ll, int el) {
  assert(ll != NULL);
  Node *n = create(el);
  n->next = ll->next;
  ll->next = n;
}

int insert_at_pos(Node *head, unsigned int pos, int el) {
  assert(head != NULL);
  assert(pos > 1);

  for (int i = 1; i < pos - 1 && head != NULL; ++i) {
    head = head->next;
  }

  if (head == NULL) {
    return -1;
  }

  insert_after(head, el);
  return 0;
}

void print_ll(Node *head) {
  while (head != NULL) {
    printf("%d ", head->data);
    head = head->next;
  }
  printf("\n");
}

Node *create(int val) {
  Node *head = malloc(sizeof(Node));
  head->data = val;
  head->next = NULL;
  return head;
}
