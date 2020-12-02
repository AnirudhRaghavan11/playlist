#include <stdio.h> 
#include <stdlib.h> 
  
typedef struct _number { 
    int num; 
    struct _number *next; 
} Number; 

void printList(Number *head) 
{ 
    while (head != NULL) { 
        printf("%d ", head->num); 
        head = head->next; 
    } 
} 

int main() 
{
    Number *f_number = (Number *)malloc(sizeof(Number));
    f_number->num = 1;
    f_number->next = NULL;

    Number s_number;
    s_number.num = 2;
    s_number.next = NULL;

    Number t_number;
    t_number.num = 3;
    t_number.next = NULL;

    f_number->next = &s_number;
    s_number.next = &t_number;

    printList(f_number); 
  
    return 0; 

}