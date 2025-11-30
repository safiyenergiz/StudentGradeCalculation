#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define NUM_EXAMS 3

typedef struct {
    char name[NAME_LEN];
    int grades[NUM_EXAMS];
    double avg;
} Student;

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {                }
}


double computeAverage(const int g[NUM_EXAMS]) {
    int sum = 0;
    for (int i = 0; i < NUM_EXAMS; i++) sum += g[i];
    return (double)sum / NUM_EXAMS; 
}

void printHeader(void) {
    printf("\n%-3s %-20s | %3s %3s %3s | %5s\n", 
    "#", "Name", "E1", "E2", "E3", "Average");
    printf("-----------------------------------------------\n");
}

void printStudent(int idx, const Student *s) {
    printf("%-3d %-20s | %3d %3d %3d | %5.2f\n",
    idx + 1, s->name, s->grades[0], s->grades[1], s->grades[2], s->avg);
}

void addStudent(Student arr[], int *pCount) {
    if (*pCount >= MAX_STUDENTS) {
        printf("Limit full! (%d)\n", MAX_STUDENTS);
        return;
    }
    Student s;
    printf("Student name: ");

    if(fgets(s.name, NAME_LEN, stdin) == NULL) {
        printf("ENTRY ERROR!\n");
        return;
    }
    size_t len = strlen(s.name);
    if (len > 0 && s.name[len - 1] == '\n') s.name[len - 1] = '\0';

    
    for (int i = 0 ; i < NUM_EXAMS; i++) {
        int ok = 0;
        while (!ok) {
            printf("%d. exam grade (0-100): ", i + 1);
            int val;
            if (scanf("%d",  &val) != 1) {
                printf("Enter a numerical value!\n");
                clearInputBuffer();
                continue;
            }
            if (val < 0 || val > 100) {
                printf("Should be between 0-100.\n");
                clearInputBuffer();
                continue;
            }
            s.grades[i] = val;
            ok = 1;
            clearInputBuffer();
        }
    }
    s.avg = computeAverage(s.grades);
    arr[*pCount] = s;
    (*pCount)++;
    printf("Added: %s (Average: %.2f)\n",s.name, s.avg);
}

void listStudents(const Student arr[], int count) {
    if (count == 0) {
        printf("No record.\n");
        return;
    }
    printHeader();
    for(int i = 0; i < count; i++) printStudent(i, &arr[i]);
}

void searchByname(const Student arr[], int count) {
    if (count == 0) {
        printf("No record.\n");
        return;
    }
    char key[NAME_LEN];
    printf("Search (title or part): ");
    if (fgets(key, NAME_LEN, stdin) == NULL) {
        printf("ENTRY ERROR!\n");
        return;
    }
    size_t len = strlen(key);
    if (len > 0 && key[len - 1] == '\n') key[len - 1] = '\0';

    int found = 0;
    for (int i = 0; i < count; i++) {
        

        if (strstr(arr[i].name, key) != NULL) {
            if (!found) printHeader();
            printStudent(i, &arr[i]);
            found = 1;
        }
    }
    if (!found) printf("No matches found!\n");
}

void bestAverage(const Student arr[], int count) {
    if (count == 0) {
        printf("No record.\n");
        return;
    }
    int bestIdx = 0;
    for ( int i = 1; i < count; i++) {
        if (arr[i].avg > arr[bestIdx].avg) bestIdx = i;
    }
    
    printf("Highest average: \n"); 
    printHeader();
    printStudent(bestIdx, &arr[bestIdx]);
}

void sortByAverage(Student arr[], int count) {
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j].avg < arr[j + 1].avg) {
                Student tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
    printf("Sorted by average (high to low).\n");
}

int menu(void) {
    printf("\n=== STUDENT NOTEBOOK ===\n");
    printf("1- Add Student\n");
    printf("2- List\n");
    printf("3- Search by Name\n");
    printf("4- Highest Average\n");
    printf("5- Sort by Average\n");
    printf("0- Exit\n");
    printf("Your Selection: ");

    int choice;
    
    if (scanf("%d", &choice) != 1) {
        clearInputBuffer();
        return -1;
    }
    clearInputBuffer(); 
    return choice;
}

int main (void) {
    Student students[MAX_STUDENTS];
    int count = 0;

    while (1) {
        int ch = menu();
        if (ch == -1) {
            printf("Invalid entry!\n");
            continue;
        }
        switch (ch) {
            case 1: addStudent(students, &count); break;
            case 2: listStudents(students, count); break;
            case 3: searchByname(students, count); break;
            case 4: bestAverage(students, count); break;
            case 5: sortByAverage(students, count); break;
            case 0: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }
}