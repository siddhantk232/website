#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct Node {
    int data;
    struct Node *next;
};

void insert_at_end(struct Node *head, int el);
struct Node* insert_before_start(struct Node *head, int el);
void insert_after(struct Node *ll, int el);
int  insert_at_pos(struct Node *head, unsigned int pos, int el);
void print_ll(struct Node *head);

int main() {
    struct Node *head = malloc(sizeof(struct Node));
    head->data = 1;

    insert_at_end(head, 2);
    insert_at_end(head, 3);

    head = insert_before_start(head, -2);
    head = insert_before_start(head, -3);

    // -3 -2 1 2 3
    insert_after(head->next->next->next->next, 5);

    insert_at_pos(head, 6, 4);

    print_ll(head);
}

// O(n)
void insert_at_end(struct Node *head, int el) {
    assert(head != NULL);

    // go to the end
    while(head->next != NULL) {
        head = head->next;
    }

    // create new struct Node
    struct Node *n = malloc(sizeof(struct Node));
    n->data = el;
    n->next = NULL;
    head->next = n;
}

// O(1)
struct Node* insert_before_start(struct Node *head, int el) {
    assert(head != NULL);
    struct Node *n = malloc(sizeof(struct Node));
    n->data = el;
    n->next = head;

    return n;
}

// O(1)
void insert_after(struct Node *ll, int el) {
    assert(ll != NULL);
    struct Node *n = malloc(sizeof(struct Node));
    n->data = el;
    n->next = ll->next;
    ll->next = n;
}

int insert_at_pos(struct Node *head, unsigned int pos, int el) {
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

void print_ll(struct Node *head) {
    while(head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
