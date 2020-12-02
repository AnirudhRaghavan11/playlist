#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _term {
    double coef;
    int degree;
    struct _term *next;
} Term;

Term *createTerm(double coef, int degree, Term *next) {
    Term *term = (Term *)malloc(sizeof(Term));
    term->coef = coef;
    term->degree = degree;
    term->next = next;

    return term;
}

void printPoly(Term *head) {
    for (Term *cur = head; cur != NULL; cur = cur->next) {
        printf("%.2lf", cur->coef);

        if (cur->degree != 0) {
            printf("x^%d", cur->degree);
        }

        if (cur->next != NULL) {
            printf(" + ");
        }
    }
}

int countTerms(Term *head) {
    int count = 0;
    for (Term *cur = head; cur != NULL; cur = cur->next) {
        count++;
    }
    return count;
}

Term *searchTerm(Term *head, int degree) {
  int cur;
    while (head != NULL) {
        if (head->degree == degree) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

double evalPoly(Term *head, double x) {
    double count = 0;
    while(head != NULL) {
        count += head->coef * pow(x, head->degree);
        head = head->next;//this is basically head++ to move the pointer to the next node
    }

    return count;
}

int main() {
    Term *x0 = createTerm(25, 0, NULL);
    Term *x1 = createTerm(2, 1, x0);
    Term *x2 = createTerm(5, 2, x1);
    Term *x3 = createTerm(10, 3, x2); 
    Term *head = x3;

    printPoly(head);
    printf("\n");

    printf("There are %d terms in the poly\n", countTerms(head));

    int degree;
    printf("What degree are you searching for?\n");
    scanf("%d", &degree);

    Term *searchResult = searchTerm(head, degree);
    if (searchResult == NULL) { // if (!searchResult) {
        printf("Term with degree %d NOT FOUND\n", degree);
    }
    else {
        printf("Term with degree %d FOUND\n", degree);
    }

    double x;
    printf("What is the value of x in the poly?\n");
    scanf("%lf", &x);
    printf("The poly evaluates to %lf\n", evalPoly(head, x));

    return 0;
}