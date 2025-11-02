#include <stdio.h>

const int GRID_ROWS = 5;
const int  GRID_COLS = 5;
const int FLAG_POWER_ON = (1 << 0);
const int FLAG_OVERLOAD = (1 << 1);
const int FLAG_MAINTENANCE = (1 << 2);

void initializeGrid(int grid[GRID_ROWS][GRID_COLS]);
void displayMenu();
void waitForEnter();
void clearInputBuffer();
void updateSectorStatus(int grid[GRID_ROWS][GRID_COLS]);
void querySectorStatus(int grid[GRID_ROWS][GRID_COLS]);
void runSystemDiagnostic(int grid[GRID_ROWS][GRID_COLS]);

int main() {
    int grid[GRID_ROWS][GRID_COLS];
    int choice = 0;
    initializeGrid(grid);

    while (1) {
        displayMenu();
        printf("IESCO Operator, enter your choice (1-4): ");

        if (scanf("%d", &choice) != 1) {
            printf("Error: Please enter a number.\n");
            clearInputBuffer();
            waitForEnter();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                updateSectorStatus(grid);
                break;
            case 2:
                querySectorStatus(grid);
                break;
            case 3:
                runSystemDiagnostic(grid);
                break;
            case 4:
                printf("\nShutting down monitoring system.\n");
                return 0;
            default:
                printf("\nError: Invalid choice. Please select from 1-4.\n");
        }

        if (choice != 4) {
            waitForEnter();
        }
    }

    return 0;
}

void initializeGrid(int grid[GRID_ROWS][GRID_COLS]) {
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            grid[i][j] = FLAG_POWER_ON;
        }
    }
}

void displayMenu() {
    printf("=========================================\n");
    printf("  IESCO Power Grid Monitor\n");
    printf("=========================================\n");
    printf("  Grid Size: %d x %d Sectors\n", GRID_ROWS, GRID_COLS);
    printf("-----------------------------------------\n");
    printf("1. Update Sector Status\n");
    printf("2. Query Sector Status\n");
    printf("3. Run System-Wide Diagnostic\n");
    printf("4. Exit System\n");
    printf("=========================================\n");
}

void updateSectorStatus(int grid[GRID_ROWS][GRID_COLS]) {
    int row, col, flagChoice, action;
    int flagToUpdate = 0;

    printf("\n--- Update Sector Status ---\n");
    printf("Enter sector row (0-%d): ", GRID_ROWS - 1);
    scanf("%d", &row);
    printf("Enter sector col (0-%d): ", GRID_COLS - 1);
    scanf("%d", &col);

    if (row < 0 || row >= GRID_ROWS || col < 0 || col >= GRID_COLS) {
        printf("Error: Invalid sector coordinates. Aborting.\n");
        clearInputBuffer();
        return;
    }

    printf("\nWhich status to update?\n");
    printf("  1. Power Status\n");
    printf("  2. Overload Warning\n");
    printf("  3. Maintenance Required\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &flagChoice);

    switch (flagChoice) {
        case 1: flagToUpdate = FLAG_POWER_ON; break;
        case 2: flagToUpdate = FLAG_OVERLOAD; break;
        case 3: flagToUpdate = FLAG_MAINTENANCE; break;
        default:
            printf("Error: Invalid flag choice.\n");
            clearInputBuffer();
            return;
    }

    printf("\nWhat action?\n");
    printf("  1. Set (Turn ON / Report Issue)\n");
    printf("  0. Clear (Turn OFF / Resolve Issue)\n");
    printf("Enter action (1 or 0): ");
    scanf("%d", &action);

    if (action == 1) {

        grid[row][col] |= flagToUpdate;
        printf("\nSuccess: Flag has been SET for sector (%d, %d).\n", row, col);
    } else if (action == 0) {

        grid[row][col] &= ~flagToUpdate;
        printf("\nSuccess: Flag has been CLEARED for sector (%d, %d).\n", row, col);
    } else {
        printf("Error: Invalid action. Must be 1 or 0.\n");
    }
}

void querySectorStatus(int grid[GRID_ROWS][GRID_COLS]) {
    int row, col;
    printf("\n--- Query Sector Status ---\n");
    printf("Enter sector row (0-%d): ", GRID_ROWS - 1);
    scanf("%d", &row);
    printf("Enter sector col (0-%d): ", GRID_COLS - 1);
    scanf("%d", &col);


    if (row < 0 || row >= GRID_ROWS || col < 0 || col >= GRID_COLS) {
        printf("Error: Invalid sector coordinates.\n");
        clearInputBuffer();
        return;
    }

    int status = grid[row][col];

    printf("\n--- Status Report for Sector (%d, %d) ---\n", row, col);
    printf("  Raw Status Value: %d\n", status);
    printf("----------------------------------------\n");

    if (status & FLAG_POWER_ON) {
        printf("  [1] Power Status:         ON\n");
    } else {
        printf("  [1] Power Status:         OFF\n");
    }

    if (status & FLAG_OVERLOAD) {
        printf("  [2] Overload Warning:     YES (Overloaded)\n");
    } else {
        printf("  [2] Overload Warning:     NO (Normal)\n");
    }

    if (status & FLAG_MAINTENANCE) {
        printf("  [3] Maintenance Required: YES\n");
    } else {
        printf("  [3] Maintenance Required: NO\n");
    }
    printf("========================================\n");
}

void runSystemDiagnostic(int grid[GRID_ROWS][GRID_COLS]) {
    int totalSectors = GRID_ROWS * GRID_COLS;
    int overloadCount = 0;
    int maintenanceCount = 0;

    printf("\nRunning system-wide diagnostic...\n");

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            int status = grid[i][j];


            if (status & FLAG_OVERLOAD) {
                overloadCount++;
            }


            if (status & FLAG_MAINTENANCE) {
                maintenanceCount++;
            }
        }
    }
    printf("\n--- System Diagnostic Report ---\n");
    printf("  Total Sectors Scanned:  %d\n", totalSectors);
    printf("  Sectors Overloaded:     %d\n", overloadCount);
    printf("  Sectors Req. Maintenance: %d\n", maintenanceCount);
    printf("==================================\n");
}

void waitForEnter() {
    printf("\nPress Enter to return to the main menu...");
    while (getchar() != '\n');
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}