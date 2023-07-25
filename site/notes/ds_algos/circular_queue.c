#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int is_empty(int front) {
  return front == -1;
}

int is_full(int rear, int front, int size) {
  if ((front == rear + 1) || (front == 0 && rear == size - 1)) {
    return 1;
  }
  return 0;
}

int enqueue(int *arr, int *rear, int *front, int n, int el) {
  if (is_full(*rear, *front, n)) {
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

int dequeue(int* queue, int *rear, int *front, int n) {
  if (is_empty(*front)) {
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

void display(int *arr, int rear, int front, int n) {
  if (is_empty(front)) {
    printf("empty queue\n");
    return;
  }

  printf("arr: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  int i;
  for (i = front; i != rear; i = (i + 1) % n) {
      printf("%d ", arr[i]);
  }
  printf("%d ", arr[i]);

  printf("\n");

  printf("front = %d\nrear = %d\n", front, rear);
}

int main() {
  int n = 5;
  int queue[n];
  int front = -1;
  int rear = -1;

  while(true) {
    printf("Enter choice: \n");
    printf("1. Insert element in queue\n");
    printf("2. Delete element in queue\n");
    printf("3. Display queue\n");
    printf("4. Exit\n");

    int option;
    scanf("%d", &option);

    switch(option) {
      case 1: {
        int el;
        printf("Enter element to insert: ");
        scanf("%d", &el);
        int st = enqueue(queue, &rear, &front, n, el);

        if (st == -1) {
          printf("failed to insert element in queue (overflow)\n");
        }
        break;
      }

      case 2: {
        int st = dequeue(queue, &rear, &front, n);
        if (st == -1) {
          printf("failed to delete element from queue (underflow)\n");
        } else {
          printf("deleted %d from queue\n", st);
        }
        break;
      }

      case 3:
        display(queue, rear, front, n);
        break;

      case 4:
        exit(0);
        break;

      default:
        exit(0);
        break;
    }
  }
}
