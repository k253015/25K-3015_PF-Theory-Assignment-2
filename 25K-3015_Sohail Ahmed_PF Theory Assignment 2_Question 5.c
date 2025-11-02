#include <stdio.h>
#include <stdlib.h>

const int MAX_MSG_LENGTH = 256;
const int TOGGLE_MASK = 18;

void encodeMessage(char message[]);
void decodeMessage(char message[]);
void reverseString(char str[]);
void toggleBits(char str[]);
void getString(char buffer[], int length);
void clearInputBuffer();
int length(char str[]);

int main() {
    char message[MAX_MSG_LENGTH];
    int choice = 0;

    while (1) {
        printf("\n--- Secure Message Terminal ---\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("-------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter message to ENCODE: ");
                clearInputBuffer();
                getString(message, MAX_MSG_LENGTH);
                encodeMessage(message);
                printf("Encoded Message: %s\n", message);
                break;
            case 2:
                printf("Enter message to DECODE: ");
                clearInputBuffer();
                getString(message, MAX_MSG_LENGTH);
                decodeMessage(message);
                printf("Decoded Message: %s\n", message);
                break;
            case 3:
                printf("\nTerminating program.\n");
                return 0;
            default:
                printf("\nError: Invalid choice. Please select from 1-3.\n");
        }
    }

    return 0;
}

void encodeMessage(char message[]) {
    reverseString(message);
    toggleBits(message);
}

void decodeMessage(char message[]) {
    toggleBits(message);
    reverseString(message);
}

int length(char str[]) {
    int i = 0;
    char n;
    if (str == NULL) {
        return 0;
    }
    do {
        n = str[i];
        i++;
    } while (n != '\0');
    return i - 1;
}

void reverseString(char str[]) {
    if (str == NULL) {
        return;
    }

    int size = length(str);
    if (size < 2) {
        return;
    }

    int start = 0;
    int end = size - 1;
    char temp;

    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void toggleBits(char str[]) {
    if (str == NULL) {
        return;
    }

    int size = length(str);
    for (int i = 0; i < size; i++) {
        str[i] = str[i] ^ TOGGLE_MASK;
    }
}

void getString(char buffer[], int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = length(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

void clearInputBuffer() {
    char c;
    while((c = getchar()) != '\n');
}