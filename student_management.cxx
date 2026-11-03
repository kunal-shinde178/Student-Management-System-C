#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int roll;
    char name[50];
    int age;
    float marks;
};

struct Student s[100];
int count = 0;

// Load Data From File
void loadData()
{
    FILE *fp = fopen("students.dat", "rb");

    if(fp == NULL)
        return;

    count = fread(s, sizeof(struct Student), 100, fp);

    fclose(fp);
}

// Save Data To File
void saveData()
{
    FILE *fp = fopen("students.dat", "wb");

    if(fp == NULL)
    {
        printf("\nFile Error!");
        return;
    }

    fwrite(s, sizeof(struct Student), count, fp);
    fclose(fp);
}

// Find Student
int findStudent(int roll)
{
    int i;

    for(i = 0; i < count; i++)
    {
        if(s[i].roll == roll)
            return i;
    }

    return -1;
}

// Add Student
void addStudent()
{
    int roll;

    if(count >= 100)
    {
        printf("\nStudent Limit Reached!");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &roll);

    if(findStudent(roll) != -1)
    {
        printf("\nRoll Number Already Exists!");
        return;
    }

    s[count].roll = roll;

    printf("Enter Name: ");
    scanf(" %49[^\n]", s[count].name);

    printf("Enter Age: ");
    scanf("%d", &s[count].age);

    printf("Enter Marks (Out of 100): ");
    scanf("%f", &s[count].marks);

    if(s[count].marks < 0 || s[count].marks > 100 ||
       s[count].age <= 0)
    {
        printf("\nInvalid Details!");
        return;
    }

    count++;

    saveData();

    printf("\nStudent Added Successfully!");
}

// Display Students
void displayStudents()
{
    int i;

    if(count == 0)
    {
        printf("\nNo Records Found!");
        return;
    }

    for(i = 0; i < count; i++)
    {
        printf("\n----- STUDENT %d -----\n", i + 1);

        printf("Roll Number: %d\n", s[i].roll);
        printf("Name: %s\n", s[i].name);
        printf("Age: %d\n", s[i].age);
        printf("Marks: %.2f\n", s[i].marks);
    }
}

// Search Student
void searchStudent()
{
    int roll, pos;

    printf("\nEnter Roll Number: ");
    scanf("%d", &roll);

    pos = findStudent(roll);

    if(pos == -1)
    {
        printf("\nStudent Not Found!");
        return;
    }

    printf("\nStudent Found!\n");
    printf("Roll Number: %d\n", s[pos].roll);
    printf("Name: %s\n", s[pos].name);
    printf("Age: %d\n", s[pos].age);
    printf("Marks: %.2f\n", s[pos].marks);
}

// Update Student
void updateStudent()
{
    int roll, pos;

    printf("\nEnter Roll Number: ");
    scanf("%d", &roll);

    pos = findStudent(roll);

    if(pos == -1)
    {
        printf("\nStudent Not Found!");
        return;
    }

    printf("Enter New Name: ");
    scanf(" %49[^\n]", s[pos].name);

    printf("Enter New Age: ");
    scanf("%d", &s[pos].age);

    printf("Enter New Marks: ");
    scanf("%f", &s[pos].marks);

    if(s[pos].age <= 0 ||
       s[pos].marks < 0 || s[pos].marks > 100)
    {
        printf("\nInvalid Details!");
        return;
    }

    saveData();

    printf("\nStudent Updated Successfully!");
}

// Delete Student
void deleteStudent()
{
    int roll, pos, i;

    printf("\nEnter Roll Number: ");
    scanf("%d", &roll);

    pos = findStudent(roll);

    if(pos == -1)
    {
        printf("\nStudent Not Found!");
        return;
    }

    for(i = pos; i < count - 1; i++)
    {
        s[i] = s[i + 1];
    }

    count--;

    saveData();

    printf("\nStudent Deleted Successfully!");
}

// Calculate Result
void calculateResult()
{
    int roll, pos;
    float percentage;

    printf("\nEnter Roll Number: ");
    scanf("%d", &roll);

    pos = findStudent(roll);

    if(pos == -1)
    {
        printf("\nStudent Not Found!");
        return;
    }

    percentage = s[pos].marks;

    printf("\nName: %s\n", s[pos].name);
    printf("Percentage: %.2f%%\n", percentage);

    if(percentage >= 90)
        printf("Grade: A+");
    else if(percentage >= 80)
        printf("Grade: A");
    else if(percentage >= 70)
        printf("Grade: B");
    else if(percentage >= 60)
        printf("Grade: C");
    else if(percentage >= 40)
        printf("Grade: D");
    else
        printf("Grade: Fail");
}

// Main Function
int main()
{
    int choice;

    loadData();

    do
    {
        printf("\n\n================================");
        printf("\n   STUDENT MANAGEMENT SYSTEM");
        printf("\n================================");

        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Calculate Result");
        printf("\n7. Exit");

        printf("\n\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                calculateResult();
                break;

            case 7:
                saveData();
                printf("\nThank You!");
                break;

            default:
                printf("\nInvalid Choice!");
        }

    } while(choice != 7);

    return 0;
}