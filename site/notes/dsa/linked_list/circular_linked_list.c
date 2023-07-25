#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

typedef struct Node Node;

Node* create(int data) {
    Node *t = malloc(sizeof(Node));
    t->data = data;
    t->next = NULL;

    return t;
}

/*
  1. create a new node with data.
  2. set the "next" of this new node to point to the head node.
  3. Go to the last node of the circular linked list:
    1. set temp to point to head.
    2. loop while head->next not equal to temp.
  4. change the "next" of the last node to point to this newly created node.
 */
void insert_end(Node *head, int data) {
    // create new node
    Node *node = create(data);

    // last node in a circular linked list points to the head
    node->next = head;

    // go to the last node and point its next to this "node"
    Node *temp = head;
    while (head->next != temp) {
	head = head->next;
    }
    head->next = node;
}

/*
  1. create a new node with data.
  2. set the "next" of this new node to point to the head node.
  3. Go to the last node of the circular linked list:
    1. set temp to point to head.
    2. loop while head->next not equal to temp.
  4. change the "next" of the last node to point to this newly created node.
  5. change the head to point to this newly created node.
 */
void insert_start(Node **head, int data) {
    // create new node
    Node *node = create(data);
    node->next = *head;

    // go to the last node, store it in temp
    Node *temp = *head;
    while (temp->next != *head) {
	temp = temp->next;
    }

    // make last node point to the new head node
    temp->next = node;

    // overwrite the head to point to the new head node
    *head = node;
}

/*
  1. move ptr to point to the node before the desired position.
     1. loop from 1 to (pos - 1) and set ptr = ptr->next
  2. create a new node.
  3. create a temp node that is set to point to ptr->next
  4. set ptr->next to point to this newly created node
  5. set the next pointer of this newly created node to point to the temp node created in step 3.
 */
void insert_pos(Node *head, int pos, int data) {
    for (int i = 1; i < pos - 1; ++i) {
	head = head->next;
    }

    Node *node = create(data);
    Node *temp = head->next;
    head->next = node;
    node->next = temp;
}

/*
  1. Go to the second last node of the circular linked list:
    1. set temp to point to head.
    2. loop while head->next->next not equal to temp.
  2. store the reference to the last node for deletion (free()).
  3. point the "next" of the second last node to point to head.
  4. free(the last node).
 */
void delete_end(Node *head) {
    Node *temp = head;
    // go to the second last node
    while (head->next->next != temp) {
	head = head->next;
    }

    // store ref to last node for deletion (free)
    Node *tb_free = head->next;

    // point second last node's next to head
    head->next = temp;

    free(tb_free);
}

/*
  1. Go to the last node of the circular linked list:
    1. set temp to point to head.
    2. loop while head->next not equal to temp.
  2. point last node's next to point to the second node from head.
  3. set ptr to point to the head node.
  4. move the head by one node:
    1. head = ptr->next.
  5. free(ptr).
 */
void delete_start(Node **head) {
    // go to the last node
    Node *temp = *head;
    Node *last = *head;
    while (last->next != temp) {
	last = last->next;
    }

    // point last node's next to second node from head
    last->next = temp->next;
    *head = temp->next;
    free(temp);
}

/*
  1. set up a temp node that points to the head node of the circular linked list.

  2. iterate until we're at the last node:
    1. loop while head->next not equal to temp.
    2. print head->data
    3. move head by one node (head = head->next)

  3. write an additional print statemen to print the last node (whose ->next was head)
 */
void display(Node *head) {
    Node *temp = head;

    while(head->next != temp) {
	printf("%d -> ", head->data);
	head = head->next;
    }
    printf("%d -> NULL\n", head->data);
}

int main() {
    Node *head = create(10); // 10 -> NULL
    head->next = head;

    insert_end(head, 20); // 10 -> 20 -> 10
    insert_end(head, 30); // 10 -> 20 -> 30 -> 10
    insert_end(head, 40); // 10 -> 20 -> 30 -> 40 -> 10
    insert_end(head, 50); // 10 -> 20 -> 30 -> 40 -> 50 -> 10
    insert_end(head, 60); // 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 10
    insert_end(head, 70); // 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70 -> 10

    insert_start(&head, 1); // 1 -> 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70 -> 1
    insert_start(&head, 2); // 2 -> 1 -> 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70 -> 2
    insert_start(&head, 3); // 3 -> 2 -> 1 -> 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70 -> 3

    insert_pos(head, 3, 5); // 3 -> 2 -> 5 -> 1 -> 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70 -> 3
    insert_pos(head, 4, 7); // 3 -> 2 -> 5 -> 7 -> 1 -> 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70 -> 3

    delete_end(head); // 3 -> 2 -> 5 -> 7 -> 1 -> 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 3
    delete_end(head); // 3 -> 2 -> 5 -> 7 -> 1 -> 10 -> 20 -> 30 -> 40 -> 50 -> 3
    delete_end(head); // 3 -> 2 -> 5 -> 7 -> 1 -> 10 -> 20 -> 30 -> 40 -> 3

    delete_start(&head); // 2 -> 5 -> 7 -> 1 -> 10 -> 20 -> 30 -> 40 -> 2
    delete_start(&head); // 5 -> 7 -> 1 -> 10 -> 20 -> 30 -> 40 -> 5

    display(head);
}
