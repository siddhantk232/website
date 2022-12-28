#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

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
void merge(Node *head, Node *head2);
void reverse(Node **head);
void print_ll(Node *head);
int search(Node *head, int target);

int main() {
  Node *head = create(10);

  insert_at_end(head, 20);
  insert_at_end(head, 30);
  insert_at_end(head, 40);
  insert_at_end(head, 50);

  printf("linked list after insert_end operation:\n");
  print_ll(head);

  insert_before_start(&head, 3);
  insert_before_start(&head, 2);

  insert_before_start(&head, 1);

  printf("linked list after insert_beginning operation:\n");
  print_ll(head);

  insert_at_pos(head, 4, 4);

  printf("linked list after insert_at_pos operation:\n");
  print_ll(head);

  delete_end(head);
  delete_end(head);

  printf("linked list after delete_end operation:\n");
  print_ll(head);

  delete_start(&head);
  delete_start(&head);

  printf("linked list after delete_start operation:\n");
  print_ll(head);

  delete_pos(head, 3);

  printf("linked list after delete_pos operation:\n");
  print_ll(head);

  reverse(&head);
  printf("reversed linked list:\n");
  print_ll(head);

  int pos = search(head, 4);

  if (pos) {
    printf("Found 4 at position %d\n", pos);
  } else {
    printf("Couldn't find 4 int the given linked list\n");
  }
}

int search(Node *head, int target) {
  int pos = 0;
  while(head != NULL) {
    pos++;
    if (head->data == target) {
      break;
    }
    head = head->next;
  }

  return pos;
}

void delete_start(Node **head) {
  Node *temp = *head;
  *head = (*head)->next;

  free(temp);
}

void delete_end(Node *head) {
  while(head->next->next != NULL) {
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
}

void merge(Node *head, Node *head2) {
  while(head->next != NULL) {
    head = head->next;
  }

  head->next = head2;
}

// O(n)
void reverse(Node **head) {
  Node *curr = *head, *next = NULL,  *prev = NULL;

  while (curr != NULL) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  *head = prev;
}

// O(n)
void insert_at_end(Node *head, int el) {
  assert(head != NULL);

  // go to the end
  while(head->next != NULL) {
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
  // pos = index + 1
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
  while(head != NULL) {
    printf("%d -> ", head->data);
    head = head->next;
  }
  printf("NULL\n");
}

Node *create(int val) {
  Node *head = malloc(sizeof(Node));
  head->data = val;
  head->next = NULL;
  return head;
}
