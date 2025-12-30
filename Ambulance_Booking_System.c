#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct AmbulanceBooking {
    int tokenNumber;
    char firstName[50];
    char lastName[50];
    char mobileNumber[15];
    char disease[100];
    char ambulanceStatus[20];
};

#define MAX_BOOKINGS 100

int tokenCounter = 1;
struct AmbulanceBooking bookings[MAX_BOOKINGS];
int totalBookings = 0;

void displayMenu();
void bookAmbulance();
void checkBookingStatus();
void displayBookingDetails(struct AmbulanceBooking booking);
int validateMobileNumber(char mobile[]);
int validateName(char name[]);
void clearInputBuffer();
char* getRandomStatus();

int main() {
    int choice;
    srand(time(NULL));
    
    printf("\n");
    printf("===========================================================\n");
    printf("   AHMEDABAD ONLINE AMBULANCE BOOKING SERVICING SYSTEM\n");
    printf("===========================================================\n");
    printf("\n");
    
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                bookAmbulance();
                break;
            case 2:
                checkBookingStatus();
                break;
            case 3:
                printf("\nThank you for using Ahmedabad Online Ambulance Booking Service!\n");
                printf("Stay Safe! Stay Healthy!\n\n");
                break;
            default:
                printf("\nInvalid choice! Please enter 1, 2, or 3.\n\n");
        }
    } while(choice != 3);
    
    return 0;
}

void displayMenu() {
    printf("-----------------------------------------------------------\n");
    printf("                        MAIN MENU\n");
    printf("-----------------------------------------------------------\n");
    printf("1. Book Ambulance\n");
    printf("2. Check Your Ambulance Booking Status\n");
    printf("3. Exit\n");
    printf("-----------------------------------------------------------\n");
}

char* getRandomStatus() {
    int statusRandom = (rand() % 3) + 1;
    switch(statusRandom) {
        case 1:
            return "Available";
        case 2:
            return "On the Way";
        case 3:
            return "Busy";
        default:
            return "Available";
    }
}

void bookAmbulance() {
    struct AmbulanceBooking booking;
    int validInput = 0;
    char tempMobile[20];
    
    if(totalBookings >= MAX_BOOKINGS) {
        printf("\nSorry! Maximum booking limit reached. Cannot accept more bookings.\n\n");
        return;
    }
    
    printf("\n");
    printf("===========================================================\n");
    printf("              AMBULANCE BOOKING FORM\n");
    printf("===========================================================\n");
    printf("\n");
    
    booking.tokenNumber = tokenCounter++;
    
    // First Name
    do {
        printf("Enter First Name: ");
        fgets(booking.firstName, sizeof(booking.firstName), stdin);
        booking.firstName[strcspn(booking.firstName, "\n")] = 0;
        if(!validateName(booking.firstName)) {
            printf("Error: First name cannot be empty! Please try again.\n");
        } else {
            validInput = 1;
        }
    } while(!validInput);
    
    // Last Name
    validInput = 0;
    do {
        printf("Enter Last Name: ");
        fgets(booking.lastName, sizeof(booking.lastName), stdin);
        booking.lastName[strcspn(booking.lastName, "\n")] = 0;
        if(!validateName(booking.lastName)) {
            printf("Error: Last name cannot be empty! Please try again.\n");
        } else {
            validInput = 1;
        }
    } while(!validInput);
    
    // Mobile Number
    validInput = 0;
    do {
        printf("Enter Mobile Number (10 digits): ");
        fgets(tempMobile, sizeof(tempMobile), stdin);
        tempMobile[strcspn(tempMobile, "\n")] = 0;
        if(!validateMobileNumber(tempMobile)) {
            printf("Error: Mobile number must be exactly 10 digits! Please try again.\n");
        } else {
            strcpy(booking.mobileNumber, tempMobile);
            validInput = 1;
        }
    } while(!validInput);
    
    // Disease
    validInput = 0;
    do {
        printf("Enter Disease/Medical Condition: ");
        fgets(booking.disease, sizeof(booking.disease), stdin);
        booking.disease[strcspn(booking.disease, "\n")] = 0;
        if(strlen(booking.disease) == 0) {
            printf("Error: Disease/Medical Condition cannot be empty! Please try again.\n");
        } else {
            validInput = 1;
        }
    } while(!validInput);
    
    // Auto assign random status
    strcpy(booking.ambulanceStatus, getRandomStatus());
    
    // Store booking
    bookings[totalBookings] = booking;
    totalBookings++;
    
    // Display confirmation
    displayBookingDetails(booking);
    printf("\n");
}

void checkBookingStatus() {
    char searchMobile[20];
    int found = 0;
    int i;
    
    printf("\n");
    printf("===========================================================\n");
    printf("          CHECK AMBULANCE BOOKING STATUS\n");
    printf("===========================================================\n");
    
    if(totalBookings == 0) {
        printf("\nNo booking available.\n");
        printf("You have not made any ambulance bookings yet.\n");
        printf("===========================================================\n\n");
        return;
    }
    
    printf("Enter your Mobile Number: ");
    fgets(searchMobile, sizeof(searchMobile), stdin);
    searchMobile[strcspn(searchMobile, "\n")] = 0;
    
    for(i = 0; i < totalBookings; i++) {
        if(strcmp(bookings[i].mobileNumber, searchMobile) == 0) {
            printf("\n");
            printf("===========================================================\n");
            printf("              BOOKING STATUS FOUND\n");
            printf("===========================================================\n");
            printf("Token Number        : %d\n", bookings[i].tokenNumber);
            printf("First Name          : %s\n", bookings[i].firstName);
            printf("Last Name           : %s\n", bookings[i].lastName);
            printf("Mobile Number       : %s\n", bookings[i].mobileNumber);
            printf("Disease/Condition   : %s\n", bookings[i].disease);
            printf("Ambulance Status    : %s\n", bookings[i].ambulanceStatus);
            printf("===========================================================\n\n");
            found = 1;
            break;
        }
    }
    
    if(!found) {
        printf("\nNo booking found with this mobile number.\n");
        printf("===========================================================\n\n");
    }
}

void displayBookingDetails(struct AmbulanceBooking booking) {
    printf("\n");
    printf("===========================================================\n");
    printf("              BOOKING CONFIRMATION\n");
    printf("===========================================================\n");
    printf("Token Number        : %d\n", booking.tokenNumber);
    printf("First Name          : %s\n", booking.firstName);
    printf("Last Name           : %s\n", booking.lastName);
    printf("Mobile Number       : %s\n", booking.mobileNumber);
    printf("Disease/Condition   : %s\n", booking.disease);
    printf("Current Status      : %s\n", booking.ambulanceStatus);
    printf("===========================================================\n");
    printf("Your booking has been confirmed!\n");
    printf("Please note your Token Number: %d\n", booking.tokenNumber);
    printf("You can check status using option 2.\n");
    printf("===========================================================\n");
}

int validateMobileNumber(char mobile[]) {
    int i;
    int len = strlen(mobile);
    
    if(len != 10) {
        return 0;
    }
    
    for(i = 0; i < 10; i++) {
        if(!isdigit(mobile[i])) {
            return 0;
        }
    }
    
    return 1;
}

int validateName(char name[]) {
    int i;
    int hasNonSpace = 0;
    
    for(i = 0; name[i] != '\0'; i++) {
        if(!isspace(name[i])) {
            hasNonSpace = 1;
            break;
        }
    }
    
    return hasNonSpace;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Empty body - discards characters
    }
}
