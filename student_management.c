#include<stdio.h>
#include<stdlib.h>

void addstudent();
void studentrecord();
void searchstudent();
void delete();

struct student {
    char first_name[20];
    char last_name[20];
    int rollno;
    char Class[10];
    char vill[50];
    float per;
};

void main() {
    int choice = 0;
    while (choice != 5) {
        printf("\n\t\t\t\t========= STUDENT DATABASE =========\n");
        printf("\n\t\t\t\t 1. ADD STUDENT RECORD\n");
        printf("\t\t\t\t 2. DISPLAY RECORDS\n");
        printf("\t\t\t\t 3. SEARCH RECORD\n");
        printf("\t\t\t\t 4. DELETE RECORD\n");
        printf("\t\t\t\t 5. EXIT\n");
        printf("\n\t\t\t\t ___________________________\n");
        printf("\t\t\t\t Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addstudent();
                break;
            case 2:
               studentrecord();
               printf("\n\t\t\tPress any key to continue");
               getchar(); getchar(); // Fix for key press pause
               break;
            case 3:
               searchstudent();
               printf("\n\t\t\tPress any key to continue");
               getchar(); getchar(); // Fix for key press pause
               break;
            case 4:
                delete();
                printf("\n\t\t\tPress any key to continue");
                getchar(); getchar(); // Fix for key press pause
                break;
        }
    }
}

void addstudent() {
    char another;
    FILE *fp;
    struct student info;
    do {
        printf("\n\t\t\t\t ====== ADD STUDENT INFO ======\n");
        fp = fopen("student_info", "a");

        if (fp == NULL) {
            fprintf(stderr, "\n\t\t\t\t Can't Open File\n");
            return;
        }

        printf("\n\t\t\t\t Enter first name: ");
        scanf("%s", info.first_name);

        printf("\n\t\t\t\t Enter last name: ");
        scanf("%s", info.last_name);

        printf("\n\t\t\t\t Enter Roll no: ");
        scanf("%d", &info.rollno);

        printf("\n\t\t\t\t Enter Class: ");
        scanf("%s", info.Class);

        printf("\n\t\t\t\t Enter address: ");
        scanf("%s", info.vill);

        printf("\n\t\t\t\t Enter percentage: ");
        scanf("%f", &info.per);

        printf("\n\t\t\t\t ________________________________\n");

        fwrite(&info, sizeof(struct student), 1, fp);
        fclose(fp);

        printf("\n\t\t\t\t Record stored successfully\n");

        printf("\n\t\t\t\t Do you want to enter another record? (y/n): ");
        scanf(" %c", &another); // Space before %c to skip newline

    } while (another == 'y' || another == 'Y');
}

void studentrecord() {
    FILE *fp;
    struct student info;
    fp = fopen("student_info", "r");
    printf("\n\t\t\t\t ====== STUDENT RECORDS ======\n");
    if (fp == NULL) {
        fprintf(stderr, "\n\t\t\t\t Can't Open File\n");
        return;
    }
    else {
        printf("\t%-20s%-20s%-10s%-10s%-10s%-10s\n", "First Name", "Last Name", "Roll No", "Class", "Address", "Percentage");
        printf("\t%-20s%-20s%-10s%-10s%-10s%-10s\n", "__________", "_________", "________", "_____", "_______", "__________");
    }

    while (fread(&info, sizeof(struct student), 1, fp)) {
        printf("\t%-20s%-20s%-10d%-10s%-10s%-10.2f\n", info.first_name, info.last_name, info.rollno, info.Class, info.vill, info.per);
    };
    fclose(fp);
    getchar();
}

void searchstudent() {
    FILE *fp;
    struct student info;
    int roll_no, found = 0;
    fp = fopen("student_info", "r");
    printf("\n\t\t\t\t ====== SEARCH STUDENT ======\n");
    if (fp == NULL) {
        fprintf(stderr, "\n\t\t\t\t Can't Open File\n");
        return;
    }
    printf("\n\t\t\t\t Enter Roll Number to search: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(struct student), 1, fp)) {
        if (info.rollno == roll_no) {
            found = 1;
            printf("\n\t\t\t\t Student name: %s %s", info.first_name, info.last_name);
            printf("\n\t\t\t\t Roll_No: %d", info.rollno);
            printf("\n\t\t\t\t Class: %s", info.Class);
            printf("\n\t\t\t\t Address: %s", info.vill);
            printf("\n\t\t\t\t Percentage: %.2f", info.per);
            printf("\n\t\t\t\t __________________________\n");
        }
    }
    if (!found) {
        printf("\t\t\t\t Record not found\n");
    }

    fclose(fp);
    getchar();
}

void delete() {
    FILE *fp, *fp1;
    struct student info;
    int roll_no, found = 0;

    printf("\n\t\t\t\t ====== DELETE STUDENT ======\n");
    fp = fopen("student_info", "r");
    fp1 = fopen("temp.txt", "w");
    if (fp == NULL || fp1 == NULL) {
        fprintf(stderr, "\n\t\t\t\t Can't Open File\n");
        return;
    }

    printf("\n\t\t\t\t Enter Roll Number to delete: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(struct student), 1, fp)) {
        if (info.rollno == roll_no) {
            found = 1;
        } else {
            fwrite(&info, sizeof(struct student), 1, fp1);
        }
    }

    fclose(fp);
    fclose(fp1);

    if (found) {
        remove("student_info");
        rename("temp.txt", "student_info");
        printf("\n\t\t\t\t Record Deleted Successfully\n");
    } else {
        printf("\n\t\t\t\t Record Not Found\n");
    }
}
