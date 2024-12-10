#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
typedef struct
{
    int userId;
    char name[50];
    int age;
} user;
bool checkId(char *file, int userid)
{
    FILE *fptr = fopen(file, "r");
    if (!fptr)
    {
        return true;
    }
    int uid, age;
    char n[50];
    while (fscanf(fptr, "%d,%49[^,],%d\n", &uid, n, &age) != EOF)
    {
        if (uid == userid)
        {
            fclose(fptr);
            return false;
        }
    }
    fclose(fptr);
    return true;
}
void create(char *file)
{
    FILE *fptr = fopen("users.txt", "a");
    if (!fptr)
    {
        printf("THE FILE IS NOT OPENED!!!\n");
        exit(1);
    }
    else
    {
        printf("SUCCESSFULLY CREATED AND OPENED !\n");
    }
    user u;
    int n;
    printf("Enter the number of user you want to enter:");
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        do
        {
            printf("Enter the User ID:");
            scanf("%d", &u.userId);
            getchar();
            if (!checkId(file, u.userId))
            {
                printf("Error: User Id %d already exists. Please enter a unique ID.\n", u.userId);
            }
            else
            {
                break;
            }
        } while (1);
    
       
        printf("Enter the name of user:");
        scanf("%[^\n]", u.name);
         getchar();
        printf("Enter the user age:");
        scanf("%d", &u.age);
        getchar();
        fprintf(fptr, "%d,%s,%d\n", u.userId, u.name, u.age);
    }
    printf("RECORD(s) ENTERED SUCCESSFULLY!\n");
    fclose(fptr);
}

void update(char *file)
{
    FILE *fptr = fopen(file, "r");
    if (!fptr)
    {
        printf("ERROR OPENING\n");
        exit(0);
    }
    FILE *ifptr = fopen("tempUsers.txt", "w");
    if (!ifptr)
    {
        printf("Error creating\n");
        exit(0);
    }
    int uid, age, c = 0;
    char name[50];
    user up_user;
    printf("Enter user ID to update:");
    scanf("%d", &up_user.userId);
    printf("Enter New Name:");
    scanf("%s", &up_user.name);
    printf("Enter new age:");
    scanf("%d", &up_user.age);
    while (fscanf(fptr, "%d,%99[^\n],%d\n", &uid, name, &age) != EOF)
    {
        if (uid == up_user.userId)
        {
            fprintf(ifptr, "%d,%s,%d\n", up_user.userId, up_user.name, up_user.age);
            c = 1;
        }
        else
        {
            fprintf(ifptr, "%d,%s,%d\n", uid, name, age);
        }
    }
    fclose(fptr);
    fclose(ifptr);
    if (c == 1)
    {
        remove(file);
        rename("tempUser.txt", file);
        printf("User Updated Succesfully\n");
    }
    else
    {
        remove("tempUsers.txt");
        printf("User Id Not Found\n");
    }
}
void delete(char *file)
{
    FILE *fptr = fopen(file, "r");
    if (!fptr)
    {
        printf("ERROR OPENING");
        exit(0);
    }
    FILE *ifptr = fopen("tempUsers.txt", "w");
    if (!ifptr)
    {
        printf("Error creating");
        exit(0);
    }
    int uid, age, c = 0;
    char name[50];
    printf("Enter user ID to update:");
    scanf("%d", &uid);
    while (fscanf(fptr, "%d,%99[^\n],%d\n", &uid, name, &age) != EOF)
    {
        if (uid != uid)
        {
            fprintf(ifptr, "%d,%s,%d\n", uid, name, age);
        }
        else
        {
            c = 1;
        }
    }
    fclose(fptr);
    fclose(ifptr);
    if (c == 1)
    {
        remove(file);
        rename("tempUser.txt", file);
        printf("User Deleted Succesfully.\n");
    }
    else
    {
        remove("tempUsers.txt");
        printf("User Id Not Found.\n");
    }
}
void read(char *file)
{
    FILE *fptr = fopen("users.txt", "r");
    if (!fptr)
    {
        printf("Failed to open ! Might not exist.\n");
        exit(0);
    }
    else
    {
        printf("File Opened Successfully.\n");
    }
    int uid, age;
    char name[50];
    printf("USER IN FILE\n");
    printf("ID\tName\t\t\tAge\n");
    while (fscanf(fptr, "%d,%49[^,],%d\n", &uid, name, &age) != EOF)
    {
        printf("%d\t%-15s\t\t%d\n", uid, name, age);
    }
    fclose(fptr);
}
int main()
{
    char *file = "users.txt";
    int choice;
    do
    {
        printf("Enter your choice: \n1. Add\n2. Update\n3. Delete\n4. Display\n0. Exit");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            create(file);
            break;
        case 2:
            update(file);
            break;
        case 3:
            delete (file);
            break;
        case 4:
            read(file);
            break;
        case 0:
            printf("Thanks !");
            exit(0);
        default:
            printf("Invalid Choice");
        }
    } while (choice != 0);
    return 0;
}