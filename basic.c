#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _student {
    char name[20];
    int age;
    int roll;
}Student;

int main() {
    Student st[5];
    for( int i = 0; i < 5; i++) {
        printf("Enter deatils for student %d :\n", i+1);
        printf("Enter name :");
        scanf("%s", st[i].name);
        printf("\n Enter age :");
        scanf("%d", &st[i].age);
        printf("\n Enter roll :");
        scanf("%d", &st[i].roll);

    }

    for( int i = 0; i < 5; i++){
        printf("Details for student %d :\n", i+1);
        printf("Name :");
        printf("%s", st[i].name);
        printf("\n Age :");
        printf("%d", st[i].age);
        printf("\n Roll :");
        printf("%d", st[i].roll);
        printf("\n**************************************\n");
    }


}
