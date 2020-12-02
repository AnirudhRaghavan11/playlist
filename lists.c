#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _student {
    char *name;
    double gpa;
    struct _student *next;
} Student;

Student *createStudent(char name[], double gpa, Student *next) {
    Student *pNew = malloc(sizeof(Student));
    pNew->name = malloc(strlen(name) + 1);
    strcpy(pNew->name, name);
    pNew->gpa = gpa;
    pNew->next = next;
    return pNew;
}
//returns -1 if the new node GPA is greater than the pre existing node
//returns 1 if the new node GPA is less than the pre existing node
// returns 0 if both GPA's are equal
int compareStudentsOnGPA(Student *pNew, Student *pExisting) {
    if (pNew->gpa > pExisting->gpa)
        return -1;
    else if (pNew->gpa < pExisting->gpa)
        return 1;
    else if (pNew->gpa == pExisting->gpa)
        return 0;
}

/***************************************************************************************************
 * Name: compareStudentsOnName
 * Parameters: Student* pNew --> new student node , Student * pExist ---> pre existing student node
 * Description: Compare names based on alphabetical order.
 * Return type: int. The function returns 0 if both students have same name,
 *              returns -1 if new student name is alphabetically greater than existing student name
 *              returns 1 if new student name is alphabetically less than existing student name
*******************************************************************************************************/
int compareStudentsOnName(Student *pNew, Student *pExist ){
    if(strcmp(pNew->name, pExist->name)==0)
        return 0;
    int iterations = strlen(pNew->name) > strlen(pExist->name) ? strlen(pExist->name) : strlen(pNew->name);
    for (int i = 0; i < iterations; i++){
        if (pNew->name[i] < pExist->name[i]){
            return 1;
        }
        else if (pNew->name[i] > pExist->name[i]){
            return -1;
        }
    }
}
//returns 1 if the student name already exist
//return 0 if student name does not exist
int isStudentExist( Student *pNew, Student *head) {
    while(head!=NULL) {
        if(compareStudentsOnName(pNew, head) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}
// we are already inserting the new students into the list regardless of alphabetical order when GPA is equal.
// This function is sorting the students based on the alphabetical order only when students have equal GPA.
int arrangeStudentsByName( Student *head){
    Student *current = head, *index = NULL;
    if(head == NULL)
        return 0;
    char temp[100];
    while(current != NULL) {  
    //Node index will point to node next to current  
    index = current->next;  
        
        while(index != NULL) {  
            //If current node's data is greater than index's node data, swap the data between them  
            if (compareStudentsOnGPA(index, current) == 0){
                if(compareStudentsOnName( index, current) ==1 ) {  
                    strcpy(temp,current->name);  
                    strcpy(current->name,index->name);  
                    strcpy(index->name,temp);  
                } 
            } 
            index = index->next;  
        }  
    current = current->next;    
    }   
    return 1;
}

void print(char prefix[], Student *head) {
    printf("%s", prefix);
    for (Student *ptr = head; ptr != NULL; ptr = ptr->next)
        printf("[%s-%g] ", ptr->name, ptr->gpa);
    printf("\n");
}


Student *add(Student *head, char name[], double gpa) {
    int hasEqualGPA = 0;
    int valFromCompareNames;
    Student *pNew = createStudent( name, gpa, NULL );
    if (head == NULL){
        return pNew;
    }
    /*else if (compareStudentsOnGPA(pNew, cur) == 0){
     if (valFromCompareNames < 0){
         break;
        }
    }*/
    
    else if (compareStudentsOnGPA(pNew, head) < 0){
        valFromCompareNames = isStudentExist( pNew, head );
        //printf("%d\n", valFromCompareNames);
        if( valFromCompareNames == 1){
            printf("Student named %s exists.\n",pNew->name);
            return head;
        }
        pNew->next = head;
        return pNew;
    }
    else {
        valFromCompareNames = isStudentExist( pNew, head );
        //printf("%d\n", valFromCompareNames);
        if( valFromCompareNames == 1){
            printf("Student named %s exists.\n",pNew->name);
            return head;
        }
        Student *prev = head;
        Student *cur = head;
        while (cur != NULL){
            if (compareStudentsOnGPA(pNew, cur) < 0){
                break;
            }
            if(compareStudentsOnGPA(pNew, cur)== 0){
                hasEqualGPA =1;
            }

            prev = cur;
            cur = cur->next;
            
        }
        pNew->next = cur;
        prev->next = pNew;
    }
    //print("\n\tFrom Add function, Now the list is: ", head);
    if(hasEqualGPA ==1 )
    arrangeStudentsByName( head );
    return head; 
}

double getGPA(Student *head, char name[]) {
    while (head != NULL){
        if (strcmp(head->name, name) == 0){
            return head->gpa;
        }
        head = head->next;
    }
    return -1.0;
}

int main(void) {
    char name[100];
    double gpa;
    Student *head = NULL;
    while (1) { // build the list
        printf("\nEnter a name (one word) and gpa, or xxx and 0 to exit: ");
        scanf("%s%lf", name, &gpa);
        if (strcmp(name, "xxx") == 0) break;
        head = add(head, name, gpa);
        print("\n\tNow the list is: ", head);
    }
    while (1) { // perform search
        printf("\nEnter a name to look up the gpa or xxx to exit: ");
        scanf("%s", name);
        if (strcmp(name, "xxx") == 0) break;
        gpa = getGPA(head, name);
        if (gpa < 0)
            printf("\n\t%s does not exist\n", name);
        else
            printf("\n\t%s has a GPA of %g\n", name, gpa);
    }
    return 0;
}
