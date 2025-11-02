#include<stdio.h>

void customer_information(char name[], int CNIC[]) {
    long long cnic_number;
    printf("Enter your Name: ");
    scanf(" %[^\n]", name);

    printf("Enter your 13-digit CNIC (without hyphens): ");
    scanf("%lld", &cnic_number);

    for (int i = 12; i >= 0; i--) {
        CNIC[i] = cnic_number % 10;
        cnic_number /= 10;
    }
}

void display_inventory(int product_code[], int quantity_in_stock[], int price_per_product[]) {
    printf("Product Code \t Quantity in Stock \t Price Per Product\n");
    for (int i = 0; i < 4; i++) {
        printf("%03d \t\t %d \t\t\t %d\n", product_code[i], quantity_in_stock[i], price_per_product[i]);
    }
}

void add_item_to_cart(int cart_product_codes[], int cart_quantities[], int *cart_count,
                      int product_code[], int quantity_in_stock[], int price_per_product[]) {
    int code_of_product, purchase_quantity;
    printf("Enter the Product Code (001, 002, 003, 004): ");
    scanf("%d", &code_of_product);
    printf("Enter Purchase Quantity: ");
    scanf("%d", &purchase_quantity);

    int found = 0;
    for (int i = 0; i < 4; i++) {
        if (code_of_product == product_code[i]) {
            found = 1;
            if (quantity_in_stock[i] >= purchase_quantity) {
                quantity_in_stock[i] -= purchase_quantity;
                cart_product_codes[*cart_count] = code_of_product;
                cart_quantities[*cart_count] = purchase_quantity;
                (*cart_count)++;
                printf("Item added to cart successfully!\n");
            } else {
                printf("Insufficient stock!\n");
            }
            break;
        }
    }

    if (!found)
        printf("Invalid Product Code! Please enter 001–004.\n");
}

int calculate_total_bill(int cart_product_codes[], int cart_quantities[], int cart_count,
                         int price_per_product[]) {
    int total = 0;
    for (int i = 0; i < cart_count; i++) {
        int index = (cart_product_codes[i] % 10) - 1;
        total += cart_quantities[i] * price_per_product[index];
    }
    return total;
}

int apply_promo_discount(int total, int *discount_applied, int *discount_value) {
    char promo_input[50];
    char promo_code[] = {'E','i','d','2','0','2','5','\0'};

    printf("\nEnter promo code if any: ");
    scanf("%s", promo_input);

    int same = 1;
    for (int i = 0; promo_code[i] != '\0' || promo_input[i] != '\0'; i++) {
        if (promo_code[i] != promo_input[i]) {
            same = 0;
            break;
        }
    }

    if (same) {
        printf("\nPromo code applied successfully! 25%% discount added.\n");
        *discount_value = (total * 25) / 100;
        total -= *discount_value;
        *discount_applied = 1;
    } else if (promo_input[0] != '\0') {
        printf("\nInvalid promo code! No discount applied.\n");
        *discount_applied = 0;
        *discount_value = 0;
    } else {
        *discount_applied = 0;
        *discount_value = 0;
    }

    return total;
}

void display_total_bill(int cart_product_codes[], int cart_quantities[], int cart_count,
                        int price_per_product[], int *final_total, int *discount_applied, int *discount_value) {
    int total = calculate_total_bill(cart_product_codes, cart_quantities, cart_count, price_per_product);
    *final_total = apply_promo_discount(total, discount_applied, discount_value);

    printf("\n============================================================\n");
    printf("Product Code\tQuantity\tPrice/Item\tTotal\n");
    printf("============================================================\n");

    for (int i = 0; i < cart_count; i++) {
        int index = (cart_product_codes[i] % 10) - 1;
        int item_total = cart_quantities[i] * price_per_product[index];
        printf("%03d\t\t%-8d\t%-10d\t%-10d\n", cart_product_codes[i], cart_quantities[i],
               price_per_product[index], item_total);
    }

    printf("============================================================\n");
    if (*discount_applied)
        printf("%50s %d\n", "TOTAL BILL (after 25% discount) =", *final_total);
    else
        printf("%50s %d\n", "TOTAL BILL =", *final_total);
    printf("============================================================\n");
}

void show_invoice(char name[], int CNIC[], int cart_product_codes[], int cart_quantities[],
                  int cart_count, int price_per_product[], int final_total, int discount_applied, int discount_value) {

    printf("\n====================== INVOICE ======================\n");
    printf("Customer Name: %s\n", name);
    printf("Customer CNIC: ");
    for (int i = 0; i < 13; i++)
        printf("%d", CNIC[i]);
    printf("\n-----------------------------------------------------\n");
    printf("Product Code\tQuantity\tPrice\tTotal\n");
    printf("-----------------------------------------------------\n");

    int total_without_discount = 0;
    for (int i = 0; i < cart_count; i++) {
        int index = (cart_product_codes[i] % 10) - 1;
        int item_total = cart_quantities[i] * price_per_product[index];
        printf("%03d\t\t%d\t\t%d\t%d\n", cart_product_codes[i],
               cart_quantities[i], price_per_product[index], item_total);
        total_without_discount += item_total;
    }

    printf("-----------------------------------------------------\n");
    printf("Total (without discount): %d\n", total_without_discount);
    if (discount_applied)
        printf("Discount Applied (25%%): %d\n", discount_value);
    printf("Final Total: %d\n", final_total);
    printf("=====================================================\n");
}

int main() {
    char name[50];
    int CNIC[13];
    int product_code[4] = {001,002,003,004};
    int quantity_in_stock[4] = {50,10,20,8};
    int price_per_product[4] = {100,200,300,150};

    int choice = 0;
    int cart_product_codes[50];
    int cart_quantities[50];
    int cart_count = 0;
    int final_total = 0;
    int discount_applied = 0;
    int discount_value = 0;

    do {
        printf("\n-----> MENU-DRIVEN APPLICATION <-----\n");
        printf("1. Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("\nEnter your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                customer_information(name, CNIC);
                break;
            case 2:
                display_inventory(product_code, quantity_in_stock, price_per_product);
                break;
            case 3:
                add_item_to_cart(cart_product_codes, cart_quantities, &cart_count,
                                 product_code, quantity_in_stock, price_per_product);
                break;
            case 4:
                display_total_bill(cart_product_codes, cart_quantities, cart_count,
                                   price_per_product, &final_total, &discount_applied, &discount_value);
                break;
            case 5:
                show_invoice(name, CNIC, cart_product_codes, cart_quantities,
                             cart_count, price_per_product, final_total, discount_applied, discount_value);
                break;
            case 6:
                return 0;
            default:
                printf("Invalid Choice! Please enter a number between 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}