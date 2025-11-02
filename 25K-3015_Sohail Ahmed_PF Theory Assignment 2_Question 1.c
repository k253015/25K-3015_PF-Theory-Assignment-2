#include <stdio.h>

void AddBook(int isbns[], char titles[][50], int quantities[] ,float prices[]) {
    int bookNumber,quantity;
    char bookName[100];
    float price;

    printf("Enter Name of Book:");
    scanf(" %[^\n]",bookName);
    printf("Enter Price of Book:");
    scanf("%f",&price);
    printf("Enter Quantity of Book:");
    scanf("%d",&quantity);
    printf("Enter ISBN Number of Book:");
    scanf("%d",&bookNumber);

    for ( int i = 0; i < 100; i++) {
        if (isbns[i] == 0) {
            isbns[i] = bookNumber;
            int j;
            for (j = 0; bookName[j] != '\0' && j < 49; j++) {
                titles[i][j] = bookName[j];
            }
            titles[i][j] = '\0';
            prices[i] = price;
            quantities[i] = quantity;
            break;
        }
        if ((i == 99) && (isbns[i] !=0)) {
            printf("Book Store is Full!\n");
            break;
        }
    }

    printf("Successfully added a new book!\n");
}

void ProcessSale(int isbns[], int quantities[]) {
    int isbn, quantity;

    printf("Enter Book Number:");
    scanf("%d",&isbn);
    printf("Enter Quantity sold:");
    scanf("%d",&quantity);

    for ( int i = 0; i < 100; i++) {
        if (isbn == isbns[i]) {
            quantities[i] -= quantity;

            if (quantities[i] <= 0) {
                printf("Warning, out of stock for ISBN:%d\n",isbn);
            }
            printf("Sale Processed!\n");
            break;
        }
    }
}

void GenerateLowStockReport(int quantities[], int isbns[],char titles[][50], float prices[] ) {
    printf("----------------> Low Stock Report <---------------\n");

    for ( int i = 0; i < 100; i++) {
        if ((quantities[i] < 5) && (isbns[i] != 0)) {
            printf("ISBN:         %d\n", isbns[i]);
            printf("Book Title:   %s\n", titles[i]);
            printf("Quantity:     %d\n", quantities[i]);
            printf("Price:        %.2f\n", prices[i]);

        }
    }
}

int main() {
    int isbns[100] ={0};
    char titles[100][50] = {""};
    float prices[100] ={0};
    int quantities[100] ={0};
    int choice;
        printf("---------------> LIBERTY BOOKS <---------------\n");
    do {
        printf("---------------> Main Menu <---------------\n");
        printf("1. Add a New Book\n");
        printf("2. Process Sale\n");
        printf("3. Generate Low Stock Report\n");
        printf("4. Exit\n");
        scanf("%d",&choice);

        switch (choice) {
            case 1:
                AddBook(isbns, titles, quantities, prices);
                break;
            case 2:
                ProcessSale(isbns, quantities);
                break;
            case 3:
                GenerateLowStockReport(quantities, isbns, titles, prices);
                break;
            case 4:
                printf("Program Closed!\n");
                return 0;
        }
    }while (choice != 4);

    return 0;
}