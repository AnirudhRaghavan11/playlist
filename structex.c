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
        if (cur->degree == 0) {
            printf("%.2lf", cur->coef);
        }
        else if (cur->degree == 1) {
            printf("%.2lfx", cur->coef);
        }
        else {
            printf("%.2lfx^%d", cur->coef, cur->degree);
        }

        if (cur->next != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

int countTerms(Term *head) {
    int count = 0;
    for (Term *cur = head; cur != NULL; cur = cur->next) {
        count++;
    }

    return count;
}

Term *searchTerm(Term *head, int degree) {
    for (Term *cur = head; cur != NULL; cur = cur->next) {
        if (cur->degree == degree) {
            return cur;
        }
    }
    return NULL;
}

double evalPoly(Term *head, int x) {
    double sum = 0;
    for (Term *cur = head; cur != NULL; cur = cur->next) {
        sum += cur->coef * pow(x, cur->degree);
    }

    return sum;
}

Term *addFront(Term *head, double coef, int degree) {
    return createTerm(coef, degree, head);
}

Term *addBack(Term *head, double coef, int degree) {
    Term *term = createTerm(coef, degree, NULL);
    if (head == NULL) {
        return term;
    }
    else {
        Term *cur = head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = term;
        return head;
    }
}

int compareTerms(Term *left, Term *right) {
    if (left->degree < right->degree) {
        return -1;
    }
    else if (left->degree > right->degree) {
        return 1;
    }
    else { // if (left->degree == right->degree) {
        if (left->coef < right->coef)
            return -1;
        else if (left->coef > right->coef)
            return 1;
        else
            return 0;
    }
}

Term *addOrdered(Term *head, double coef, int degree) {
    Term *newNode = createTerm(coef, degree, NULL);
    if (head == NULL) { // empty list
        return newNode; // return the head
    }
    else if (compareTerms(newNode, head) > 0) { // insert front
        newNode->next = head;
        return newNode;
    }
    else { // insert back and middle
        // find location
        Term *prev = head;
        Term *cur = head->next;
        while (cur != NULL) {
            if (compareTerms(newNode, cur) > 0) {
                break;
            }
            prev = cur;
            cur = cur->next;
        }
        // assign the pointers
        newNode->next = cur;
        prev->next = newNode;
        return head;
    }
}

Term *deleteTerm(Term *head, int degree) {
    Term *search = searchTerm(head, degree);
    if (search == NULL) {
        printf("Could node find node with degree %d\n", degree);
        return head;
    }
    else if (head->degree == degree) { // front & last node
        Term *next = head->next;
        free(head);
        return next;
    }
    else { // middle & back
        Term *prev = head;
        Term *cur = head->next;
        while (cur->degree != degree) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur->next;
        free(cur);
        return head;
    }
}

Term *freePoly(Term *head) {
    while (head != NULL) {
        // printf("FREEING %d\n", head->degree);
        Term *next = head->next;
        free(head);
        head = next;
    }

    return NULL;
}

void printTerm(Term *cur) {
    if (cur->degree == 0) {
        printf("%.2lf", cur->coef);
    }
    else if (cur->degree == 1) {
        printf("%.2lfx", cur->coef);
    }
    else {
        printf("%.2lfx^%d", cur->coef, cur->degree);
    }

    if (cur->next != NULL) {
        printf(" + ");
    }
}

void printPolyRecur(Term *head) {
    if (head == NULL) {
        return;
    }
    else {
        printTerm(head);
        printPolyRecur(head->next);
    }
}

int countTermsRecur(Term *head) {
    if (head == NULL) {
        return 0;
    }
    else {
        return 1 + countTermsRecur(head->next);
    }
}

Term *searchTermRecur(Term *head, int degree) {
    if (head == NULL)
        return NULL;
    else if (head->degree == degree)
        return head;
    else
        return searchTermRecur(head->next, degree);
}

Term *addBack(Term *head, double coef, int degree) {
    Term *term = createTerm(coef, degree, NULL);
    if (head == NULL) {
        return term;
    }
    else {
        Term *cur = head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = term;
        return head;
    }
}

Term *addBackRecur(Term *head, double coef, int degree) {
    if (head == NULL) {
        return createTerm(coef, degree, NULL);
    }
    else if (head->next == NULL) {
        head->next = createTerm(coef, degree, NULL);
        return head;
    }
    else {
        head->next = addBackRecur(head->next, coef, degree);
        return head;
    }
}

int main() {
    Term *head = NULL;
    head = addBackRecur(head, 1, 6);
    head = addBackRecur(head, 1, 4);
    head = addBackRecur(head, 1, 7);
    head = addBackRecur(head, 1, 5);
    printPolyRecur(head);

    return 0;
}