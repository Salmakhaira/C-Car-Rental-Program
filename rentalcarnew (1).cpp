#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CARS 10
#define MAX_NAME 50

typedef struct {
    char name[MAX_NAME];
    char status[10]; 
} Car;

struct Rental {
    char cust[50];
    char id[10];
    char car[50];
    int rent, all;
    int dr, mr, yr;
    int dturn, mturn, yturn;
};

void car(void);
void display(void);
void addCar(void);
void displayCar(void);
int is_valid_date(int d, int m, int y);
int calculate_days(int d1, int m1, int y1, int d2, int m2, int y2);
void clear_input_buffer(void);

int rentph[MAX_CARS] = {0}; 
Car fleet[MAX_CARS];
int numberofCars = 0;

int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // jmlh tgl dlm satu thn

int is_valid_date(int d, int m, int y) {
    // memastikan nilai yang diterima benar
    printf("Debug: Tanggal yang diinput: %d-%d-%d\n", d, m, y);

    if (m < 1 || m > 12) return 0;

    // kabisat
    if (m == 2) {
        int leap_year = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
        if (d < 1 || d > (leap_year ? 29 : 28)) return 0;
    } else if (d < 1 || d > month_days[m - 1]) {
        return 0;
    }

    return 1;
}

// hitung jumlah hari antara dua tanggal
int calculate_days(int d1, int m1, int y1, int d2, int m2, int y2) {
    int days = 0;

    if (y1 == y2 && m1 == m2) {
        return d2 - d1;
    }

    // hari dari tanggal awal ke akhir bulan tersebut
    days += month_days[m1 - 1] - d1;

    // hari dari awal bulan akhir ke tanggal akhir
    days += d2;

    // hari untuk bulan-bulan di antaranya
    for (int i = m1; i < m2 - 1; i++) {
        days += month_days[i];
    }

    // hari untuk tahun-tahun di antaranya
    for (int y = y1 + 1; y < y2; y++) {
        days += (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) ? 366 : 365;
    }

    return days;
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != EOF && c != '\n');
}

void addCar() {
    if (numberofCars >= MAX_CARS) {
        printf("The car fleet is full.\n");
        return;
    }
    printf("Enter car name: ");
    scanf(" %[^\n]", fleet[numberofCars].name);
    printf("Enter the rental price per day: ");
    scanf("%d", &rentph[numberofCars]);
    strcpy(fleet[numberofCars].status, "available");
    numberofCars++;
    printf("Car added successfully.\n");
}

void displayCar() {
    if (numberofCars == 0) {
        printf("No cars available.\n");
        return;
    }
    for (int i = 0; i < numberofCars; i++) {
        printf("Car %d: %s - %s\n", i + 1, fleet[i].name, fleet[i].status);
    }
}

void car(void) {
    struct Rental rental;
    FILE *ptr;
    int available = 0, days_rented;

    printf("Welcome to Queen Car Rent!\n");
    printf("Enter the Name of the Car You Want to Rent: ");
    scanf("%s", rental.car);

    // Clear the input buffer before reading dates
    clear_input_buffer();

    printf("Enter the Date You Will Rent the Car (dd mm yyyy): ");
    if (scanf("%d %d %d", &rental.dr, &rental.mr, &rental.yr) != 3) {
        printf("Error reading rental date.\n");
        clear_input_buffer();
        return;
    }

    if (!is_valid_date(rental.dr, rental.mr, rental.yr)) {
        printf("Invalid rental date.\n");
        return;
    }

    printf("Enter the Date You Will Return the Car (dd mm yyyy): ");
    if (scanf("%d %d %d", &rental.dturn, &rental.mturn, &rental.yturn) != 3) {
        printf("Error reading return date.\n");
        clear_input_buffer();
        return;
    }

    if (!is_valid_date(rental.dturn, rental.mturn, rental.yturn)) {
        printf("Invalid return date.\n");
        return;
    }

    // The car is available or no
    int found = 0;
    for (int i = 0; i < numberofCars; i++) {
        if (strcmp(fleet[i].name, rental.car) == 0) {
            found = 1;
            if (strcmp(fleet[i].status, "available") == 0) {
                strcpy(fleet[i].status, "rented");
                available = 1;
                break;
            } else {
                printf("Car is already rented.\n");
                return;
            }
        }
    }

    if (!found) {
        printf("Car not found.\n");
        return;
    }

    printf("Car is available!\n");

    printf("Enter Your Name: ");
    scanf("%s", rental.cust);

    printf("Enter Your ID Number: ");
    scanf("%s", rental.id);

    printf("Enter Rental Package (1 for 1 day, 3 for 3 days, 7 for 7 days): ");
    scanf("%d", &days_rented);

    if (days_rented != 1 && days_rented != 3 && days_rented != 7) {
        printf("Invalid rental package.\n");
        return;
    }

    rental.all = calculate_days(rental.dr, rental.mr, rental.yr, rental.dturn, rental.mturn, rental.yturn);

    rental.rent = rental.all * rentph[found - 1];
    int total_amount;
    if (days_rented == 1) {
        total_amount = 500000;
    } else if (days_rented == 3) {
        total_amount = 1450000;
    } else {
        total_amount = 3400000;
    }

    printf("Summary:\n");
    printf("NAME: %s\n", rental.cust);
    printf("ID: %s\n", rental.id);
    printf("RENTED CAR: %s\n", rental.car);
    printf("NUMBER OF DAYS: %d\n", days_rented);
    printf("Amount: %d\n", total_amount);
    printf("RENTAL: %d\n", rental.rent);

    ptr = fopen("Car_rent.txt", "a+");
    if (!ptr) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fwrite(&rental, sizeof(struct Rental), 1, ptr);
    fclose(ptr);
}

int main() {
    int option;
    
    while (1) {
        printf("Menu:\n");
        printf("1. Add Car\n");
        printf("2. Display Cars\n");
        printf("3. Rent a Car\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        clear_input_buffer(); 
        switch (option) {
            case 1:
                addCar();
                break;
            case 2:
                displayCar();
                break;
            case 3:
                car();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}

