#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {
    int data;
    struct Node *next;
};

typedef struct Node Node;

// Doubly Linked List Node
struct DNode {
    int data;
    struct DNode* next;
    struct DNode* prev;
};

typedef struct DNode DNode;

void ll();
Node *ll_create_node(int val);
Node *ll_insert_before_start(Node *head, int el);
void ll_insert_at_end(Node *head, int el);
int ll_insert_at_pos(Node *head, unsigned int pos, int el);
Node *ll_delete_start(Node *head);
void ll_delete_end(Node *head);
int ll_delete_pos(Node *head, int pos);
void ll_display(Node *head);
void ll_copy(Node *head, Node **head2);

void dll();
DNode *dll_insert_front(DNode* head, int data);
void dll_insert_after(DNode* prev_node, int data);
DNode *dll_insert_end(DNode* head, int data);
DNode *dll_delete_node(DNode* head, DNode* del_node);
void dll_display(DNode* node);
void dll_copy(DNode *head, Node **head2);

void cll();
void cll_insert_end(Node *head, int data);
void cll_insert_start(Node **head, int data);
void cll_insert_pos(Node *head, int pos, int data);
void cll_delete_end(Node *head);
void cll_delete_start(Node **head);
void cll_delete_pos(Node *head, int pos);
void cll_copy(Node *head, Node **head2);
void cll_display(Node *head);

void cdll();
DNode *cdll_create_node(int val);
void cdll_insert_end(DNode *head, int data);
void cdll_insert_start(DNode **head, int data);
void cdll_insert_pos(DNode *head, int pos, int data);
DNode *cdll_delete_node(DNode* head, DNode* del_node);
void cdll_delete_end(DNode *head);
void cdll_delete_start(DNode **head);
void cdll_copy(DNode *head, Node **head2);
void cdll_display(DNode *head);

int main() {
    while(true) {
	int ll_type;
	printf("1. Singly Linear Linked List\n");
	printf("2. Singly Circular Linked List\n");
	printf("3. Doubly Linear Linked List\n");
	printf("4. Doubly Circular Linked List\n");
	printf("5. Exit\n");
	printf("Enter the number corresponding to the type of Linked List you want to use: ");
	scanf("%d", &ll_type);

	switch(ll_type) {
	case 1:
	    printf("Using Singly Linear Linked List for further operations\n");
	    ll();
	    break;
	case 2:
	    printf("Using Singly Circular Linked List for further operations\n");
	    cll();
	    break;
	case 3:
	    printf("Using Doubly Linear Linked List for further operations\n");
	    dll();
	    break;
	case 4:
	    printf("Using Doubly Circular Linked List for further operations\n");
	    cdll();
	    break;
	case 5:
	    printf("Exiting...\n");
	    exit(0);
	default:
	    printf("Invalid choice, try again\n");
	}
    }
}

void ll() {
    Node *head = NULL;
    while(true) {
	printf("Enter choice: \n");
	printf("1. Create a linked list\n");
	printf("2. Insert a node at the beginning of the list\n");
	printf("3. Insert a node at the end\n");
	printf("4. Insert a node at a given position\n");
	printf("5. Delete a node from beginning\n");
	printf("6. Delete a node from end\n");
	printf("7. Delete a node from a given position\n");
	printf("8. Copy a given list\n");
	printf("9. Display the list\n");
	printf("10. Back to Linked List choice\n");


	int option;
	scanf("%d", &option);

	if (option == 10) {
	    break;
	}


	switch(option) {
	case 1: {
	    int val;
	    printf("Enter the value for the head node: ");
	    scanf("%d", &val);

	    head = ll_create_node(val);

	    printf("Linked List created!\n");
	    break;
	}

	case 2: {
	    int val;
	    printf("Enter the value to insert at the beginning: ");
	    scanf("%d", &val);
	    head = ll_insert_before_start(head, val);
	    printf("Linked List updated!");
	    break;
	}

	case 3: {
	    int val;
	    printf("Enter the value to insert at the end: ");
	    scanf("%d", &val);
	    ll_insert_at_end(head, val);
	    printf("Linked List updated!");
	    break;
	}

	case 4: {
	    int val;
	    unsigned int pos;

	    printf("Enter the position where you want to insert the node: ");
	    scanf("%d", &pos);

	    printf("Enter the value to insert at position %d: ", pos);
	    scanf("%d", &val);

	    ll_insert_at_pos(head, pos, val);

	    printf("Linked List updated!");
	    break;
	}

	case 5: {
	    printf("Deleting Node %d\n", head->data);
	    head = ll_delete_start(head);
	    break;
	}

	case 6: {
	    printf("Deleting the last node\n");
	    ll_delete_end(head);
	    break;
	}

	case 7: {
	    unsigned int pos;
	    printf("Enter the position where you want to delete the node: ");
	    scanf("%d", &pos);

	    if (pos == 1) {
		head = ll_delete_start(head);
	    } else {
		ll_delete_pos(head, pos);
	    }
	    break;
	}

	case 8: {
	    Node *head2 = NULL;
	    ll_copy(head, &head2);
	    printf("Copied linked list: \n");
	    ll_display(head2);
	    break;
	}

	case 9: {
	    ll_display(head);
	    break;
	}

	default:
	    printf("Invalid choice, try again\n");
	}
    }
}

void dll() {
    DNode *head = NULL;
    while(true) {
	printf("Enter choice: \n");
	printf("1. Create a doubly linked list\n");
	printf("2. Insert a node at the beginning of the list\n");
	printf("3. Insert a node at the end\n");
	printf("4. Insert a node at a given position\n");
	printf("5. Delete a node from beginning\n");
	printf("6. Delete a node from end\n");
	printf("7. Delete a node from a given position\n");
	printf("8. Copy a given list\n");
	printf("9. Display the list\n");
	printf("10. Back to Linked List choice\n");


	int option;
	scanf("%d", &option);

	if (option == 10) {
	    break;
	}


	switch(option) {
	case 1: {
	    if (head) {
		printf("You can't perform this operation as the linked list already exists!\n");
		break;
	    }

	    int val;
	    printf("Enter the value for the head node: ");
	    scanf("%d", &val);
	    head = dll_insert_front(head, val);

	    printf("Linked List created!\n");
	    break;
	}

	case 2: {
	    int val;
	    printf("Enter the value to insert at the beginning: ");
	    scanf("%d", &val);
	    head = dll_insert_front(head, val);
	    printf("Linked List updated!");
	    break;
	}

	case 3: {
	    int val;
	    printf("Enter the value to insert at the end: ");
	    scanf("%d", &val);

	    head = dll_insert_end(head, val);

	    printf("Linked List updated!");
	    break;
	}

	case 4: {
	    int val;
	    unsigned int pos;
	    printf("Enter the position where you want to insert the node: ");
	    scanf("%d", &pos);
	    printf("Enter the value to insert at position %d: ", pos);
	    scanf("%d", &val);

	    if (pos == 1) {
		head = dll_insert_front(head, val);
	    } else {
		DNode *temp = head;
		for (int i = 1; i < pos - 1 && temp != NULL; ++i) {
		    temp = temp->next;
		}

		if (temp == NULL) {
		    printf("invalid position");
		    break;
		} else {
		    dll_insert_after(temp, val);
		}
	    }
	
	    printf("Linked List updated!");
	    break;
	}

	case 5: {
	    printf("Deleting Node %d\n", head->data);
	    head = dll_delete_node(head, head);
	    break;
	}

	case 6: {
	    printf("Deleting Node %d\n", head->data);

	    DNode *last = head;
	    while(last->next != NULL) {
		last = last->next;
	    }

	    head = dll_delete_node(head, last);
	    break;
	}

	case 7: {
	    unsigned int pos;
	    printf("Enter the position where you want to delete the node: ");
	    scanf("%d", &pos);

	    if (pos == 1) {
		head = dll_delete_node(head, head);
	    } else {
		DNode *temp = head;
		for (int i = 1; i < pos && temp != NULL; ++i) {
		    temp = temp->next;
		}

		if (temp == NULL) {
		    printf("invalid position");
		    break;
		} else {
		    printf("deleting %d\n", temp->data);
		    head = dll_delete_node(head, temp);
		}
	    }
	
	    printf("Linked List updated!");
	    break;
	}

	case 8: {
	    Node *head2 = NULL;
	    dll_copy(head, &head2);
	    printf("Copied linked list: \n");
	    ll_display(head2);
	    break;
	}

	case 9: {
	    dll_display(head);
	    break;
	}

	default:
	    printf("Invalid choice, try again\n");
	}
    }
}

void cll() {
    Node *head = NULL;
    while(true) {
	printf("Enter choice: \n");
	printf("1. Create a Singly Circular linked list\n");
	printf("2. Insert a node at the beginning of the list\n");
	printf("3. Insert a node at the end\n");
	printf("4. Insert a node at a given position\n");
	printf("5. Delete a node from beginning\n");
	printf("6. Delete a node from end\n");
	printf("7. Delete a node from a given position\n");
	printf("8. Copy a given list\n");
	printf("9. Display the list\n");
	printf("10. Back to Linked List choice\n");


	int option;
	scanf("%d", &option);

	if (option == 10) {
	    break;
	}

	switch(option) {
	case 1: {
	    if (head) {
		printf("You can't perform this operation as the linked list already exists!\n");
		break;
	    }

	    int val;
	    printf("Enter the value for the head node: ");
	    scanf("%d", &val);
	    head = ll_create_node(val);
	    head->next = head;

	    printf("Linked List created!\n");
	    break;
	}

	case 2: {
	    int val;
	    printf("Enter the value to insert at the beginning: ");
	    scanf("%d", &val);
	    cll_insert_start(&head, val);
	    printf("Linked List updated!");
	    break;
	}

	case 3: {
	    int val;
	    printf("Enter the value to insert at the end: ");
	    scanf("%d", &val);

	    cll_insert_end(head, val);

	    printf("Linked List updated!");
	    break;
	}

	case 4: {
	    int val;
	    unsigned int pos;
	    printf("Enter the position where you want to insert the node: ");
	    scanf("%d", &pos);
	    printf("Enter the value to insert at position %d: ", pos);
	    scanf("%d", &val);

	    if (pos == 1) {
		cll_insert_start(&head, val);
	    } else {
		cll_insert_pos(head, pos, val);
	    }
	
	    printf("Linked List updated!");
	    break;
	}

	case 5: {
	    printf("Deleting Node %d\n", head->data);
	    cll_delete_start(&head);
	    break;
	}

	case 6: {
	    cll_delete_end(head);
	    break;
	}

	case 7: {
	    unsigned int pos;
	    printf("Enter the position where you want to delete the node: ");
	    scanf("%d", &pos);

	    if (pos == 1) {
		cll_delete_start(&head);
	    } else {
		cll_delete_pos(head, pos);
	    }
	
	    printf("Linked List updated!");
	    break;
	}

	case 8: {
	    Node *head2 = NULL;
	    cll_copy(head, &head2);
	    printf("Copied linked list: \n");
	    ll_display(head2);
	    break;
	}

	case 9: {
	    cll_display(head);
	    break;
	}

	default:
	    printf("Invalid choice, try again\n");
	}
    }
}


void cdll() {
    DNode *head = NULL;
    while(true) {
	printf("Enter choice: \n");
	printf("1. Create a Doubly Circular linked list\n");
	printf("2. Insert a node at the beginning of the list\n");
	printf("3. Insert a node at the end\n");
	printf("4. Insert a node at a given position\n");
	printf("5. Delete a node from beginning\n");
	printf("6. Delete a node from end\n");
	printf("7. Delete a node from a given position\n");
	printf("8. Copy a given list\n");
	printf("9. Display the list\n");
	printf("10. Back to Linked List choice\n");


	int option;
	scanf("%d", &option);

	if (option == 10) {
	    break;
	}

	switch(option) {
	case 1: {
	    if (head) {
		printf("You can't perform this operation as the linked list already exists!\n");
		break;
	    }

	    int val;
	    printf("Enter the value for the head node: ");
	    scanf("%d", &val);
	    head = (DNode*)malloc(sizeof(DNode));
	    head->data = val;
	    head->next = head;
	    head->prev = head;

	    printf("Linked List created!\n");
	    break;
	}

	case 2: {
	    int val;
	    printf("Enter the value to insert at the beginning: ");
	    scanf("%d", &val);
	    cdll_insert_start(&head, val);
	    printf("Linked List updated!");
	    break;
	}
	case 3: {
	    int val;
	    printf("Enter the value to insert at the end: ");
	    scanf("%d", &val);

	    cdll_insert_end(head, val);

	    printf("Linked List updated!");
	    break;
	}

	case 4: {
	    int val;
	    unsigned int pos;
	    printf("Enter the position where you want to insert the node: ");
	    scanf("%d", &pos);
	    printf("Enter the value to insert at position %d: ", pos);
	    scanf("%d", &val);

	    if (pos == 1) {
		cdll_insert_start(&head, val);
	    } else {
		cdll_insert_pos(head, pos, val);
	    }
	
	    printf("Linked List updated!");
	    break;
	}

	case 5: {
	    printf("Deleting Node %d\n", head->data);
	    cdll_delete_start(&head);
	    break;
	}

	case 6: {
	    cdll_delete_end(head);
	    break;
	}

	case 7: {
	    unsigned int pos;
	    printf("Enter the position where you want to delete the node: ");
	    scanf("%d", &pos);

	    if (pos == 1) {
		cdll_delete_start(&head);
	    } else {
		DNode *temp = head;
		for (int i = 1; i < pos && temp != NULL; ++i) {
		    temp = temp->next;
		}

		if (temp == NULL) {
		    printf("invalid position");
		    break;
		} else {
		    printf("deleting %d\n", temp->data);
		    head = cdll_delete_node(head, temp);
		}
	    }
	
	    printf("Linked List updated!");
	    break;
	}

	case 8: {
	    Node *head2 = NULL;
	    cdll_copy(head, &head2);
	    printf("Copied linked list: \n");
	    ll_display(head2);
	    break;
	}

	case 9: {
	    cdll_display(head);
	    break;
	}

	default:
	    printf("Invalid choice, try again\n");
	}
    }
}


void cdll_insert_end(DNode *head, int data) {
    // create new node
    DNode *node = cdll_create_node(data);

    // last node in a circular linked list points to the head
    node->next = head;

    // go to the last node and point its next to this "node"
    DNode *temp = head;
    while (temp->next != head) {
	temp = temp->next;
    }
    // temp is now the last node
    node->prev = temp;
    temp->next = node;

    node->prev = head;
}

void cdll_insert_start(DNode **head, int data) {
    // create new node
    DNode *node = cdll_create_node(data);
    node->next = *head;

    // go to the last node, store it in temp
    DNode *temp = *head;
    while (temp->next != *head) {
	temp = temp->next;
    }

    // make last node point to the new head node
    temp->next = node;
    node->prev = temp->next;

    (*head)->prev = node;
    // overwrite the head to point to the new head node
    *head = node;
}

void cdll_insert_pos(DNode *head, int pos, int data) {
    for (int i = 1; i < pos - 1; ++i) {
	head = head->next;
    }

    DNode *node = cdll_create_node(data);
    DNode *temp = head->next;
    head->next = node;
    node->prev = head;
    node->next = temp;
    temp->prev = node;
}

void cdll_delete_end(DNode *head) {
    DNode *temp = head;
    // go to the second last node
    while (head->next->next != temp) {
	head = head->next;
    }

    // store ref to last node for deletion (free)
    DNode *tb_free = head->next;

    // point second last node's next to head
    head->next = temp;
    temp->prev = head;

    free(tb_free);
}

void cdll_delete_start(DNode **head) {
    // go to the last node
    DNode *temp = *head;
    DNode *last = *head;
    while (last->next != temp) {
	last = last->next;
    }

    // point last node's next to second node from head
    last->next = temp->next;
    *head = temp->next;
    (*head)->prev = last;
    free(temp);
}

DNode *cdll_delete_node(DNode* head, DNode* del_node) {
    if (head == NULL || del_node == NULL) {
	return head;
    }

    // if del_node is the head node, point the head pointer to the next of del_node
    if (head == del_node) {
	return del_node->next;
    }

    // if del_node is not at the last node, point the prev of node next to del_node to the previous of del_node
    if (del_node->next != NULL) {
	del_node->next->prev = del_node->prev;
    }

    // if del_node is not the first node, point the next of the previous node to the next node of del_node
    if (del_node->prev != NULL) {
	del_node->prev->next = del_node->next;
    }

    free(del_node);

    return head;
}

void cdll_copy(DNode *head, Node **head2) {
    if (!head) return;
    DNode *temp = head;
    *head2 = ll_create_node(0);
    (*head2)->data = head->data;
    (*head2)->next = NULL;

    Node *current = *head2;

    head = head->next;
    while (head != temp) {
	// Allocate new memory for a new 'node'.
        current->next = ll_create_node(head->data);
        current = current->next;
        current->next = NULL;
        head = head->next;
    }
}

void cdll_display(DNode *head) {
    DNode *temp = head;

    while(head->next != temp) {
	printf("%d -> ", head->data);
	head = head->next;
    }
    printf("%d -> NULL\n", head->data);
}

void cll_insert_end(Node *head, int data) {
    // create new node
    Node *node = ll_create_node(data);

    // last node in a circular linked list points to the head
    node->next = head;

    // go to the last node and point its next to this "node"
    Node *temp = head;
    while (head->next != temp) {
	head = head->next;
    }
    head->next = node;
}

void cll_insert_start(Node **head, int data) {
    // create new node
    Node *node = ll_create_node(data);
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

void cll_insert_pos(Node *head, int pos, int data) {
    for (int i = 1; i < pos - 1; ++i) {
	head = head->next;
    }

    Node *node = ll_create_node(data);
    Node *temp = head->next;
    head->next = node;
    node->next = temp;
}

void cll_delete_end(Node *head) {
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

void cll_delete_pos(Node *head, int pos) {
    for (int i = 1; i < pos - 1 && head != NULL; ++i) {
	head = head->next;
    }

    if (head == NULL) {
	return;
    }

    Node *temp = head->next;
    head->next = head->next->next;
    free(temp);
}

void cll_delete_start(Node **head) {
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

void cll_copy(Node *head, Node **head2) {
    if (!head) return;
    Node *temp = head;
    *head2 = ll_create_node(0);
    (*head2)->data = head->data;
    (*head2)->next = NULL;

    Node *current = *head2;

    head = head->next;
    while (head != temp) {
	// Allocate new memory for a new 'node'.
        current->next = ll_create_node(head->data);
        current = current->next;
        current->next = NULL;
        head = head->next;
    }
}

void cll_display(Node *head) {
    Node *temp = head;

    while(head->next != temp) {
	printf("%d -> ", head->data);
	head = head->next;
    }
    printf("%d -> NULL\n", head->data);
}


DNode *dll_insert_front(DNode* head, int data) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));

    newNode->data = data;

    newNode->next = (head);

    newNode->prev = NULL;

    if ((head) != NULL)
	(head)->prev = newNode;

    return newNode;
}

// insert a node after a specific node
void dll_insert_after(DNode* prev_node, int data) {
    // check if previous node is null
    if (prev_node == NULL) {
	printf("previous node cannot be null");
	return;
    }

    // allocate memory for newNode
    DNode* newNode = (DNode*)malloc(sizeof(DNode));

    // assign data to newNode
    newNode->data = data;

    // set next of newNode to next of prev node
    newNode->next = prev_node->next;

    // set next of prev node to newNode
    prev_node->next = newNode;

    // set prev of newNode to the previous node
    newNode->prev = prev_node;

    // set prev of newNode's next to newNode
    if (newNode->next != NULL)
	newNode->next->prev = newNode;
}

// insert a newNode at the end of the list
DNode *dll_insert_end(DNode* head, int data) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));

    newNode->data = data;

    newNode->next = NULL;


    if (head == NULL) {
	newNode->prev = NULL;
	return newNode;
    }

    DNode* temp = head;

    while (temp->next != NULL)
	temp = temp->next;

    temp->next = newNode;

    newNode->prev = temp;

    return head;
}

DNode *dll_delete_node(DNode* head, DNode* del_node) {
    if (head == NULL || del_node == NULL) {
	return head;
    }

    // if del_node is the head node, point the head pointer to the next of del_node
    if (head == del_node) {
	return del_node->next;
    }

    // if del_node is not at the last node, point the prev of node next to del_node to the previous of del_node
    if (del_node->next != NULL) {
	del_node->next->prev = del_node->prev;
    }

    // if del_node is not the first node, point the next of the previous node to the next node of del_node
    if (del_node->prev != NULL) {
	del_node->prev->next = del_node->next;
    }

    free(del_node);

    return head;
}

void dll_copy(DNode *head, Node **head2) {
    if (!head) return;
    *head2 = ll_create_node(0);
    (*head2)->data = head->data;
    (*head2)->next = NULL;

    Node *current = *head2;

    head = head->next;
    while (head != NULL) {
	// Allocate new memory for a new 'node'.
        current->next = ll_create_node(head->data);
        current = current->next;
        current->next = NULL;
        head = head->next;
    }
}

// print the doubly linked list
void dll_display(DNode* node) {
    if (node == NULL) {
	printf("Empty list\n");
	return;
    }
    while (node != NULL) {
	printf("%d -> ", node->data);
	node = node->next;
    }
    printf("NULL\n");
}

Node *ll_delete_start(Node *head) {
    Node *next = head->next;;
    free(head);
    return next;
}

void ll_delete_end(Node *head) {
    while(head->next->next != NULL) {
	head = head->next;
    }

    Node *temp = head->next;
    head->next = NULL;
    free(temp);
}

int ll_delete_pos(Node *head, int pos) {
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

// O(n)
void ll_insert_at_end(Node *head, int el) {
    // go to the end
    while(head->next != NULL) {
	head = head->next;
    }

    // create new Node
    Node *n = ll_create_node(el);
    head->next = n;
}

// O(1)
Node *ll_insert_before_start(Node *head, int el) {
    Node *n = ll_create_node(el);
    n->next = head;
    return n;
}

// O(1)
void ll_insert_after(Node *ll, int el) {
    Node *n = ll_create_node(el);
    n->next = ll->next;
    ll->next = n;
}

int ll_insert_at_pos(Node *head, unsigned int pos, int el) {
    for (int i = 1; i < pos - 1 && head != NULL; ++i) {
	head = head->next;
    }

    if (head == NULL) {
	return -1;
    }

    ll_insert_after(head, el);
    return 0;
}

void ll_display(Node *head) {
    while(head != NULL) {
	printf("%d -> ", head->data);
	head = head->next;
    }
    printf("NULL\n");
}

Node *ll_create_node(int val) {
    Node *head = malloc(sizeof(Node));
    head->data = val;
    head->next = NULL;
    return head;
}

void ll_copy(Node *head, Node **head2) {
    if (!head) return;
    *head2 = ll_create_node(0);
    (*head2)->data = head->data;
    (*head2)->next = NULL;

    Node *current = *head2;

    head = head->next;
    while (head != NULL) {
	// Allocate new memory for a new 'node'.
        current->next = ll_create_node(head->data);
        current = current->next;
        current->next = NULL;
        head = head->next;
    }
}

DNode *cdll_create_node(int val) {
    DNode *head = malloc(sizeof(DNode));
    head->data = val;
    head->next = NULL;
    head->prev = NULL;
    return head;
}
