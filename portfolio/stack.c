#include <stdio.h>
#include <stdlib.h>

#define MAX_CUSTOMERS 10
#define MAX_ITEMS 5

// Structure to represent a customer
typedef struct {
    int id;
    char name[50];
    int numItemsPurchased; // New field to represent the number of items purchased
} Customer;

// Structure to represent a grocery item
typedef struct {
    int itemCode;
    char itemName[50];
    float price;
} GroceryItem;

// Structure to represent a queue
typedef struct {
    Customer customers[MAX_CUSTOMERS];
    int front, rear;
} Queue;

// Function prototypes
void initializeQueue(Queue *q);
int isQueueEmpty(Queue *q);
int isQueueFull(Queue *q);
void enqueue(Queue *q, Customer c);
Customer dequeue(Queue *q);
void displayGroceryMenu(GroceryItem items[], int numItems);

int main() {
    Queue customerQueue;
    initializeQueue(&customerQueue);

    // Define grocery items
    GroceryItem groceryItems[MAX_ITEMS] = {
        {1, "Bread", 1.99},
        {2, "Milk", 2.49},
        {3, "Eggs", 1.79},
        {4, "Bananas", 0.49},
        {5, "Potatoes", 1.29}
    };

    int choice = 0;
    while (choice != 3) {
        printf("\nGrocery Store Management System\n");
        printf("1. Enter customer\n");
        printf("2. Serve customer\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                if (!isQueueFull(&customerQueue)) {
                    Customer newCustomer;
                    printf("Enter customer ID: ");
                    scanf("%d", &newCustomer.id);
                    printf("Enter customer name: ");
                    scanf("%s", newCustomer.name);
                    printf("Enter number of items purchased: ");
                    scanf("%d", &newCustomer.numItemsPurchased); // Get the number of items purchased
                    enqueue(&customerQueue, newCustomer);
                    printf("Customer entered into the queue.\n");
                } else {
                    printf("Queue is full. Cannot add more customers.\n");
                }
                break;
            }
            case 2: {
                if (!isQueueEmpty(&customerQueue)) {
                    Customer servingCustomer = dequeue(&customerQueue);
                    printf("Serving customer: ID %d, Name: %s\n", servingCustomer.id, servingCustomer.name);
                    displayGroceryMenu(groceryItems, MAX_ITEMS);
                } else {
                    printf("Queue is empty. No customers to serve.\n");
                }
                break;
            }
            case 3: {
                printf("Exiting the program.\n");
                break;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    }

    return 0;
}

// Function to initialize the queue
void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

// Function to check if the queue is full
int isQueueFull(Queue *q) {
    return (q->rear == MAX_CUSTOMERS - 1);
}

// Function to add a customer to the queue (enqueue operation)
void enqueue(Queue *q, Customer c) {
    if (isQueueFull(q)) {
        printf("Queue is full. Cannot add more customers.\n");
        return;
    }
    if (isQueueEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->customers[q->rear] = c;
}

// Function to remove a customer from the queue (dequeue operation)
Customer dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty. No customers to serve.\n");
        Customer nullCustomer = { .id = -1, .name = "NULL", .numItemsPurchased = 0 };
        return nullCustomer;
    }
    Customer servedCustomer = q->customers[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return servedCustomer;
}

// Function to display grocery menu
void displayGroceryMenu(GroceryItem items[], int numItems) {
    printf("\nGrocery Menu:\n");
    printf("Item Code\tItem Name\tPrice\n");
    for (int i = 0; i < numItems; i++) {
        printf("%d\t\t%s\t\t$%.2f\n", items[i].itemCode, items[i].itemName, items[i].price);
    }
}
