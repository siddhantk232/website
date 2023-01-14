#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void circular_queue();
void dequeue();
void queue();

int main() {
  while(true) {
    int queue_type;
    printf("1. Simple Queue\n");
    printf("2. Circular Queue\n");
    printf("3. Doubly Ended Queue (Dequeue)\n");
    printf("4. Exit\n");
    printf("Enter the number corresponding to the queue you want to use: ");
    scanf("%d", &queue_type);

    switch(queue_type) {
    case 1:
      printf("Using simple queue for further operations\n");
      queue();
      break;
    case 2:
      printf("Using circular queue for further operations\n");
      circular_queue();
      break;
    case 3:
      printf("Using doubly ended queue for further operations\n");
      dequeue();
      break;
    case 4:
      printf("Exiting program\n");
      exit(0);
    default:
      printf("Invalid choice, try again\n");
    }
  }
}

int q_enqueue(int *arr, int *rear, int *front, int n, int el) {
  if (*rear == (n - 1)) {
    return -1;
  }
  if (*front == -1) {
    *front = 0;
  }
  arr[++(*rear)] = el;
  return 0;
}

int q_dequeue(int *rear, int *front) {
  if (*front == -1 || *front > *rear) {
    return -1;
  }

  *front = *front + 1;
  return 0;
}

void q_display(int *arr, int rear, int front) {
  if (front == -1) {
    printf("empty queue\n");
    return;
  }
  printf("Queue: ");
  while (rear >= front) {
    printf("%d ", arr[rear]);
    rear--;
  }
  printf("\n");
}

void queue() {
  int n = 100;
  int queue[n];
  int front = -1;
  int rear = -1;

  while(true) {
    printf("Enter choice: \n");
    printf("1. Insert element in queue\n");
    printf("2. Delete element in queue\n");
    printf("3. Display queue\n");
    printf("4. Back to queue choice\n");

    int option;
    scanf("%d", &option);

    if (option == 4) {
      break;
    }

    switch(option) {
    case 1: {
      int el;
      printf("Enter element to insert: ");
      scanf("%d", &el);
      int st = q_enqueue(queue, &rear, &front, n, el);

      if (st == -1) {
	printf("failed to insert element in queue (overflow)\n");
      }
      break;
    }

    case 2: {
      int st = q_dequeue(&rear, &front);
      if (st == -1) {
	printf("failed to delete element from queue (underflow)\n");
      }
      break;
    }

    case 3:
      q_display(queue, rear, front);
      break;

    default:
      printf("Invalid choice, try again\n");
    }
  }
}

int c_is_empty(int front) {
  return front == -1;
}

int c_is_full(int rear, int front, int size) {
  if ((front == rear + 1) || (front == 0 && rear == size - 1)) {
    return 1;
  }
  return 0;
}

int c_enqueue(int *arr, int *rear, int *front, int n, int el) {
  if (c_is_full(*rear, *front, n)) {
    // overflow
    return -1;
  }

  if (*front == -1) {
    *front = 0;
  }

  *rear = (*rear + 1) % n;
  arr[*rear] = el;
  return 0;
}

int c_dequeue(int* queue, int *rear, int *front, int n) {
  if (c_is_empty(*front)) {
    // underflow
    return -1;
  }

  int el = queue[*front];

  if (*front == *rear) {
    *front = -1;
    *rear = -1;
  } else {
    *front = (*front + 1) % n;
  }

  return el;
}

void c_display(int *arr, int rear, int front, int n) {
  if (c_is_empty(front)) {
    printf("empty queue\n");
    return;
  }

  int i;
  for (i = front; i != rear; i = (i + 1) % n) {
    printf("%d ", arr[i]);
  }
  printf("%d ", arr[i]);
  printf("\n");
}

void circular_queue() {
  int n = 5;
  int queue[n];
  int front = -1;
  int rear = -1;

  while(true) {
    printf("Enter choice: \n");
    printf("1. Insert element in circular queue\n");
    printf("2. Delete element in circular queue\n");
    printf("3. Display circular queue\n");
    printf("4. Back to queue choice\n");

    int option;
    scanf("%d", &option);

    if (option == 4) {
      break;
    }

    switch(option) {
    case 1: {
      int el;
      printf("Enter element to insert: ");
      scanf("%d", &el);
      int st = c_enqueue(queue, &rear, &front, n, el);

      if (st == -1) {
	printf("failed to insert element in queue (overflow)\n");
      }
      break;
    }

    case 2: {
      int st = c_dequeue(queue, &rear, &front, n);
      if (st == -1) {
	printf("failed to delete element from queue (underflow)\n");
      } else {
	printf("deleted %d from queue\n", st);
      }
      break;
    }

    case 3:
      c_display(queue, rear, front, n);
      break;

    default:
      printf("Invalid choice, try again\n");
      break;
    }
  }
}

// Deque implementation in C

#define MAX 10

void de_addFront(int *arr, int item, int *pfront, int *prear);
void de_addRear(int *arr, int item, int *pfront, int *prear);
int de_delFront(int *arr, int *pfront, int *prear);
int de_delRear(int *arr, int *pfront, int *prear);
void de_display(int *arr);
int de_count(int *arr);

void dequeue() {
  int arr[MAX];
  int front, rear, n;

  front = rear = -1;
  for (int i = 0; i < MAX; i++)
    arr[i] = 0;

  while(true) {
    printf("Enter choice: \n");
    printf("1. Insert element in dequeue from rear\n");
    printf("2. Insert element in dequeue from front\n");
    printf("3. Delete element in dequeue from rear\n");
    printf("4. Delete element in dequeue from front\n");
    printf("5. Display dequeue\n");
    printf("6. Back to queue choice\n");

    int option;
    scanf("%d", &option);

    if (option == 6) {
      break;
    }

    switch(option) {
    case 1: {
      int el;
      printf("Enter element to insert: ");
      scanf("%d", &el);
      de_addRear(arr, el, &front, &rear);
      break;
    }

    case 2: {
      int el;
      printf("Enter element to insert: ");
      scanf("%d", &el);
      de_addFront(arr, el, &front, &rear);
      break;
    }

    case 3: {
      int i = de_delRear(arr, &front, &rear);
      printf("removed item: %d\n", i);
      break;
    }

    case 4: {
      int i = de_delFront(arr, &front, &rear);
      printf("removed item: %d\n", i);
      break;
    }

    case 5: {
      printf("Elements in a deque: ");
      de_display(arr);
      break;
    }
      

    default:
      printf("Invalid choice, try again\n");
      break;
    }
  }
}

void de_addFront(int *arr, int item, int *pfront, int *prear) {
  int i, k, c;

  if (*pfront == 0 && *prear == MAX - 1) {
    printf("\nDeque is full.\n");
    return;
  }

  if (*pfront == -1) {
    *pfront = *prear = 0;
    arr[*pfront] = item;
    return;
  }

  if (*prear != MAX - 1) {
    c = de_count(arr);
    k = *prear + 1;
    for (i = 1; i <= c; i++) {
      arr[k] = arr[k - 1];
      k--;
    }
    arr[k] = item;
    *pfront = k;
    (*prear)++;
  } else {
    (*pfront)--;
    arr[*pfront] = item;
  }
}

void de_addRear(int *arr, int item, int *pfront, int *prear) {
  int i, k;

  if (*pfront == 0 && *prear == MAX - 1) {
    printf("\nDeque is full.\n");
    return;
  }

  if (*pfront == -1) {
    *prear = *pfront = 0;
    arr[*prear] = item;
    return;
  }

  if (*prear == MAX - 1) {
    k = *pfront - 1;
    for (i = *pfront - 1; i < *prear; i++) {
      k = i;
      if (k == MAX - 1)
	arr[k] = 0;
      else
	arr[k] = arr[i + 1];
    }
    (*prear)--;
    (*pfront)--;
  }
  (*prear)++;
  arr[*prear] = item;
}

int de_delFront(int *arr, int *pfront, int *prear) {
  int item;

  if (*pfront == -1) {
    printf("\nDeque is empty.\n");
    return 0;
  }

  item = arr[*pfront];
  arr[*pfront] = 0;

  if (*pfront == *prear)
    *pfront = *prear = -1;
  else
    (*pfront)++;

  return item;
}

int de_delRear(int *arr, int *pfront, int *prear) {
  int item;

  if (*pfront == -1) {
    printf("\nDeque is empty.\n");
    return 0;
  }

  item = arr[*prear];
  arr[*prear] = 0;
  (*prear)--;
  if (*prear == -1)
    *pfront = -1;
  return item;
}

void de_display(int *arr) {
  int i;

  printf("\n front:  ");
  for (i = 0; i < MAX; i++)
    printf("  %d", arr[i]);
  printf("  :rear\n");
}

int de_count(int *arr) {
  int c = 0, i;

  for (i = 0; i < MAX; i++) {
    if (arr[i] != 0)
      c++;
  }
  return c;
}
