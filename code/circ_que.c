#include <stdio.h>
#define MAX 10
int queue[MAX];
int front, rear; /* = -1 */
void insert(void);
int delete_element(void);
int peek(void);
void display(void);
void menu(void);

int main() {
  front = -1;
  rear = -1;
  printf("\n");
  int option, val;
  menu();
  do {
    printf("Enter your option : ");
    scanf("%d\n", &option);
    switch (option) {
      case 1:
        insert();
        break;
      case 2:
        val = delete_element();
        if (val != -1)
          printf("The number deleted is : %d\n", val);
        break;
      case 3:
        val = peek();
        if (val != -1)
          printf("The first value in queue is : %d\n", val);
        break;
      case 4:
        display();
        break;
      case 5:
        break;
      default:
        menu();
        break;
    }
  } while (option != 5);
  fgetc(stdin);
  return 0;
}

void insert() {
  int num;
  printf("Enter the number to be inserted in the queue : ");
  scanf("%d\n", &num);
  if ((front == 0) && (rear == MAX - 1))
    printf("OVERFLOW\n");
  else {
    if ((front == -1) && (rear == -1))
      front = rear = 0;
    else if ((rear == MAX - 1) && (front != 0))
      rear = 0;
    else
      rear++;
    queue[rear] = num;
  }
}

int delete_element() {
  int val;
  if (front == -1 && rear == -1) {
    printf("UNDERFLOW\n");
    return -1;
  }
  val = queue[front];
  if (front == rear) {
    front = -1;
    rear = -1;
  } else {
    if (front == MAX - 1)
      front = 0;
    else
      front++;
  }
  return val;
}

int peek() {
  if ((front == -1) && (rear == -1)) {
    printf("QUEUE IS EMPTY\n");
    return -1;
  } else {
    return queue[front];
  }
}

void display() {
  int i;
  if ((front == -1) && (rear == -1))
    printf("QUEUE IS EMPTY\n");
  else {
    if (front < rear) {
      for (i = front; i <= rear; i++)
        printf("%d  ", queue[i]);
    } else {
      for (i = front; i < MAX; i++)
        printf("%d  ", queue[i]);
      for (i = 0; i <= rear; i++)
        printf("%d  ", queue[i]);
    }
    printf("\n");
  }
}

void menu() {
  printf("***** MAIN MENU *****");
  printf("1. Insert an element");
  printf("2. Delete an element");
  printf("3. Peek");
  printf("4. Display the queue");
  printf("5. EXIT");
}
