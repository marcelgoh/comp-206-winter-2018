#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* prints a single separator line */
void dottedLine(int DAYSIZE) {
    int charsInLine = (DAYSIZE + 3)*7 - 1;
    printf("|");
    for (int i=0; i<charsInLine; i++) {
        printf("-");
    }
    printf("|\n");
}

void printMonth(int DAYSIZE, int month) {
    int charsInLine = (DAYSIZE + 3)*7 - 1;
    int charsInMonth;
    int count = 0;
    char monthName[10];

    /* for centering purposes, determines how many letters are in the month's name */
    switch (month) {
        case 5:                   charsInMonth = 3;
                                  break;
        case 6: case 7:           charsInMonth = 4;
                                  break;
        case 3: case 4:           charsInMonth = 5;
                                  break;
        case 8:                   charsInMonth = 6;
                                  break;
        case 1: case 10:          charsInMonth = 7;
                                  break;
        case 2: case 11: case 12: charsInMonth = 8;
                                  break;
        case 9:                   charsInMonth = 9;
                                  break;
        default:                  return;
    }

    /* sets monthName */
    switch (month) {
        case 1:  strcpy(monthName, "January");
                 break;
        case 2:  strcpy(monthName, "February");
                 break;
        case 3:  strcpy(monthName, "March");
                 break;
        case 4:  strcpy(monthName, "April");
                 break;
        case 5:  strcpy(monthName, "May");
                 break;
        case 6:  strcpy(monthName, "June");
                 break;
        case 7:  strcpy(monthName, "July");
                 break;
        case 8:  strcpy(monthName, "August");
                 break;
        case 9:  strcpy(monthName, "September");
                 break;
        case 10: strcpy(monthName, "October");
                 break;
        case 11: strcpy(monthName, "November");
                 break;
        case 12: strcpy(monthName, "December");
                 break;
        default: return;
    }

    charsInLine -= charsInMonth;
    printf("|");
    for (int i=0; i<charsInLine/2; i++) {
        printf(" ");
        count++;
    }
    charsInLine -= count;
    printf("%s", monthName);
    for (int i=0; i<charsInLine; i++) {
        printf(" ");
    }
    printf("|\n");
}

void printDaysOfTheWeek(int DAYSIZE) {
    char dayName[10];
    
    /* prints days of the week to specified format */
    printf("| ");
    strcpy(dayName, "Sunday");
    for (int i=0; i<DAYSIZE && dayName[i] != '\0'; i++) {
        printf("%c", dayName[i]);
    }
    if (DAYSIZE > 6) {
        for (int i=0; i<DAYSIZE-6; i++) {
            printf(" ");
        }
    }
    dayName[0] = '\0';
    printf(" | ");
    strcpy(dayName, "Monday");
    for (int i=0; i<DAYSIZE && dayName[i] != '\0'; i++) {
        printf("%c", dayName[i]);
    }
    if (DAYSIZE > 6) {
        for (int i=0; i<DAYSIZE-6; i++) {
            printf(" ");
        }
    }
    dayName[0] = '\0';
    printf(" | ");
    strcpy(dayName, "Tuesday");
    for (int i=0; i<DAYSIZE && dayName[i] != '\0'; i++) {
        printf("%c", dayName[i]);
    }
    if (DAYSIZE > 7) {
        for (int i=0; i<DAYSIZE-7; i++) {
            printf(" ");
        }
    }
    dayName[0] = '\0';
    printf(" | ");
    strcpy(dayName, "Wednesday");
    for (int i=0; i<DAYSIZE && dayName[i] != '\0'; i++) {
        printf("%c", dayName[i]);
    }
    if (DAYSIZE > 9) {
        for (int i=0; i<DAYSIZE-9; i++) {
            printf(" ");
        }
    }
    dayName[0] = '\0';
    printf(" | ");
    strcpy(dayName, "Thursday");
    for (int i=0; i<DAYSIZE && dayName[i] != '\0'; i++) {
        printf("%c", dayName[i]);
    }
    if (DAYSIZE > 8) {
        for (int i=0; i<DAYSIZE-8; i++) {
            printf(" ");
        }
    }
    dayName[0] = '\0';
    printf(" | ");
    strcpy(dayName, "Friday");
    for (int i=0; i<DAYSIZE && dayName[i] != '\0'; i++) {
        printf("%c", dayName[i]);
    }
    if (DAYSIZE > 6) {
        for (int i=0; i<DAYSIZE-6; i++) {
            printf(" ");
        }
    }
    dayName[0] = '\0';
    printf(" | ");
    strcpy(dayName, "Saturday");
    for (int i=0; i<DAYSIZE && dayName[i] != '\0'; i++) {
        printf("%c", dayName[i]);
    }
    if (DAYSIZE > 8) {
        for (int i=0; i<DAYSIZE-8; i++) {
            printf(" ");
        }
    }
    printf(" |\n");
}

void printNumbers(int DAYSIZE, int FIRSTDAY) {
    int dayToPrint = 1;
    int blankDays = FIRSTDAY - 1;
    
    printf("|");
    /* print the first row */
    if (blankDays != 0) {
        for (int i=0; i<blankDays; i++) {
            printf(" ");
            for (int j=0; j<DAYSIZE; j++) {
                printf(" ");
            }
            printf(" |");
        }
    }
    for (int i=0; i<(7-blankDays); i++) {
        printf(" %d", dayToPrint);
        for (int j=0; j<DAYSIZE-1; j++) {
            printf(" ");
        }
        printf(" |");
        dayToPrint++;
    }
    printf("\n");

    /* print the next 21 days */
    for (int i=0; i<3; i++) {
        printf("|");
        for (int j=0; j<7; j++) {
            printf(" %d", dayToPrint);
            if (dayToPrint < 10) {
                printf(" ");
            }
            for (int k=0; k<DAYSIZE-2; k++) {
                printf(" ");
            }
            printf(" |");
            dayToPrint++;
        }
        printf("\n");
    }
    
    /* print (what should be) the last row */
    blankDays = 5-blankDays;
    printf("|");
    int count = 0;
    while (dayToPrint <= 30 && count < 7) {
        printf(" %d", dayToPrint);
        if (dayToPrint < 10) {
            printf(" ");
        }
        for (int i=0; i<DAYSIZE-2; i++) {
            printf(" ");
        }
        printf(" |");
        dayToPrint++;
        count++;
    }
    for (int i=0; i<blankDays; i++) {
        printf(" ");
        for (int j=0; j<DAYSIZE; j++) {
            printf(" ");
        }
        printf(" |");
    }
    printf("\n");

    /* print the last day in a separate row, if needed */
    if (FIRSTDAY == 7) {
        printf("| 30");
        for (int i=0; i<DAYSIZE-2; i++) {
            printf(" ");
        }
        printf(" |"); 
        for (int i=0; i<6; i++) {
            printf(" ");
            for (int j=0; j<DAYSIZE; j++) {
                printf(" ");
            }
            printf(" |");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Error. Usage: %s DAYSIZE FIRSTDAY\n", argv[0]);
        return -1;
    }
    int DAYSIZE = 0;
    int FIRSTDAY = 0;
    (atoi(argv[1]) >= 2) ? DAYSIZE = atoi(argv[1]):
                          printf("Error. DAYSIZE must be 2 or greater.\n");
    (atoi(argv[2]) > 0 && atoi(argv[2]) < 8) ? FIRSTDAY = atoi(argv[2]):
                                               printf("Error. FIRSTDAY must be between 1 and 7.\n");
    if (DAYSIZE == 0 || FIRSTDAY == 0) {
        return -1;
    }
    
    /* main loop that prints out calendar */
    for (int i=1; i<=12; i++) {
        dottedLine(DAYSIZE);
        printMonth(DAYSIZE, i);
        dottedLine(DAYSIZE);
        printDaysOfTheWeek(DAYSIZE);
        dottedLine(DAYSIZE);
        printNumbers(DAYSIZE, FIRSTDAY);
        (((FIRSTDAY + 2) % 7) == 0) ? (FIRSTDAY = 7):
                                      (FIRSTDAY = ((FIRSTDAY + 2) % 7));
    }
    dottedLine(DAYSIZE);

    return 0;
}
