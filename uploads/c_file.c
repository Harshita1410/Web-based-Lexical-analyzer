#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct for a basic linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
void insertNode(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (!(*head)) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to display the list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to free the memory of the list
void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Recursive function to find the factorial of a number
int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

// Main function
int main() {
    struct Node* head = NULL;

    // Insert nodes
    insertNode(&head, 10);
    insertNode(&head, 20);
    insertNode(&head, 30);

    // Display the linked list
    printf("Linked List: ");
    displayList(head);

    // Calculate factorial
    int number = 5;
    printf("Factorial of %d is %d\n", number, factorial(number));

    // Free the list
    freeList(head);

    return 0;
}
