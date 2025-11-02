#include<stdio.h>

const int MAX_SIZE = 5;

void push(int stack[], int* top) {
    if (*top >= MAX_SIZE - 1) {
        printf("\nError: STACK OVERFLOW. Cannot push new element.\n");
        return;
    }
    int value;
    printf("Enter value to PUSH: ");
    scanf("%d", &value);
    (*top)++;
    stack[*top] = value;
    printf("Success: %d has been pushed onto the stack.\n", value);
}

void pop(int stack[], int* top) {
    if (*top == -1) {
        printf("\nError: STACK UNDERFLOW. Cannot pop from an empty stack.\n");
        return;
    }
    printf("\nSuccess: %d has been popped from the stack.\n", stack[*top]);
    (*top)--;
    return;
}

void peek(int stack[], int top) {
    if (top == -1) {
        printf("\nPEEK: The stack is empty. Nothing to peek.\n");
        return;
    }
    printf("\nPEEK: The top element is %d.\n", stack[top]);
}

void display(int stack[], int top) {
    if (top == -1) {
        printf("\nDISPLAY: The stack is empty.\n");
        return;
    }
    printf("\n--- Stack Elements (Top to Bottom) ---\n");
    for (int i = top; i >= 0; i--) {
        printf("  %d\n", stack[i]);
    }
    printf("---------------------------------------\n");
}

int main ()  {
    int top = -1;
    int choice = 0;
    int stack[MAX_SIZE];

    while (1) {
        printf("\n--- Stack Operations Menu ---\n");
        printf("Stack Size: %d / %d\n", top + 1, MAX_SIZE);
        printf("------------------------------\n");
        printf("1. PUSH (Insert an element)\n");
        printf("2. POP (Remove an element)\n");
        printf("3. PEEK (View top element)\n");
        printf("4. DISPLAY (Show all elements)\n");
        printf("5. EXIT\n");
        printf("------------------------------\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                push(stack, &top);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("\nTerminating program. Goodbye.\n");
                return 0;
            default:
                printf("\nError: Invalid choice. Please select from 1-5.\n");
        }
    }

    return 0;
}