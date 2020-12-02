#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _term {
    double coef;
    int degree;
    struct _term* next;
} Term;

Term *createTerm(double coef_in, int degree_in) {
    Term* tempTerm = (Term*) malloc(sizeof(Term));
    tempTerm->coef = coef_in;
    (*tempTerm).degree = degree_in;
    tempTerm->next = NULL;
    return tempTerm;
}

void printTerm(Term* term) {
    if (term == NULL) {
        printf("That Term Doesn't Exist!\n");
    }
    else {
        if (term->degree == 0) {
            printf("%.1lf", term->coef);
        }
        else if (term->degree == 1) {
            printf("%.1lfx", term->coef);
        }
        else {
            printf("%.1lfx^%d", term->coef, term->degree);
        }
    }
}

void printPoly(Term* head) {
    for (Term* current = head; current != NULL; current = current->next) {
        printTerm(current);

        if (current->next != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

int countTerms(Term* head) {
    int counter = 0;
    for (Term* current = head; current != NULL; current = current->next) {
        counter++;
    }
    return counter;
}

Term* searchTerm(Term* head, int degree) {
    for (Term* current = head; current != NULL; current = current->next) {
        if (current->degree == degree) {
            return current;
        }
    }
    printf("Couldn't find a term with degree %d\n", degree);
    return NULL;
}

double evalTerm(Term* term, double x) {
    return term->coef * (pow(x, term->degree));
}

double evalPoly(Term* head, double x) {
    double result = 0.0;
    for (Term* current = head; current != NULL; current = current->next) {
        result += evalTerm(current, x);
    }
    return result;
}

Term* addAtFront(Term* head, double coef_new, int degree_new) {
    Term* newTerm = createTerm(coef_new, degree_new);
    newTerm->next = head;
    return newTerm;
}

Term* addAtFrontWithTerm(Term* head, Term* newTerm) {
    newTerm->next = head;
    return newTerm;
}

void addAtFrontModify(Term** link_list, Term* newTerm) {
    newTerm->next = *link_list;
    *link_list = newTerm;
}

void addAtBack(Term* head, double coef_new, int degree_new) {
    for (Term* current = head; current != NULL; current = current->next) {
        if (current->next == NULL) {
            current->next = createTerm(coef_new, degree_new);
            break;
        }
    }

    // Term* current;
    // for (current = head; current->next != NULL; current = current->next);
    // current->next = createTerm(coef_new, degree_new);
}

void addAtBackWithTerm(Term* head, Term* newTerm) {
    for (Term* current = head; current != NULL; current = current->next) {
        if (current->next == NULL) {
            current->next = newTerm;
            break;
        }
    }
}

// 0 if equal
// -1 if left is less than
// 1 if left is greater than
int compareTerms(Term* left, Term* right) {
    if (left->degree < right->degree) {
        return -1;
    }
    else if (left->degree > right->degree) {
        return 1;
    }
    else {
        if (left->coef < right->coef) {
            return -1;
        }
        else if (left->coef > right->coef) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

// inserting the new node and returning the head of linked list
Term* addOrderedWithTerm(Term* head, Term* newNode) {
    if (head == NULL) { //since the head is Null, the newNode becomes the head. The condition becomes false the second time as head 
    //is already initialised and is pointing to newNode
        return newNode;
    }
    else if (compareTerms(newNode, head) > 0) {
        newNode->next = head;
        return newNode;
    }
    else {
        Term* prev = head;

        while (prev->next != NULL) {
            if (compareTerms(newNode, prev->next) > 0) {
                break;
            }
            prev = prev->next;
        }

        newNode->next = prev->next;//inserts in middle
        prev->next = newNode;

        return head;
    }
}

/*
Empty List
    Create Node
    Update Head
List is not empty (compare nodes)
    Insert front (new node is bigger)
        Set new node->next to head of the list
        Update head
    Insert middle and back (need prev & cur)
        Iterate through the list, find where node goes
        Update new nodes next to cur
        Update prev next to new node
*/
Term* addOrdered(Term* head, double coef_new, int degree_new) {
    Term* newNode = createTerm(coef_new, degree_new);
    return addOrderedWithTerm(head, newNode);
}

void addOrderedModify(Term** link_list, Term* newTerm) {
    Term* head = addOrderedWithTerm(*link_list, newTerm);//Here, the newNode returned from addOrderedWithTerm becomes the head
    *link_list = head;
}

/*
Delete function
    Delete front & last item
        Free node
        Head points to the next node
    Delete middle & back
        Move prev->next to the next node
        Free node
*/
Term* deleteTerm(Term* head, int degree) {

    Term* search = searchTerm(head, degree);
    if (search == NULL) {
        printf("Could not delete degree %d from the list\n", degree);
        return head;
    }
    else if (head->degree == degree) {
        Term* newHead = head->next;
        free(head);
        return newHead;
    }
    else {
        Term* prev = head;

        while (prev->next != NULL) {
            if (prev->next->degree == degree) {
                break;
            }
            prev = prev->next;
        }
        
        Term* toBeDeleted = prev->next;
        prev->next = toBeDeleted->next;
        free(toBeDeleted);

        return head;
    }
}

void freeTerms(Term* head) {
    while (head != NULL) {
        printf("Freeing degree %d\n", head->degree);
        Term* next = head->next;
        free(head);
        head = next;
    }
}

int main() {
    Term* link_list = NULL;

    addOrderedModify(&link_list, createTerm(5.6, 6));
    addOrderedModify(&link_list, createTerm(7.8, 8));
    addOrderedModify(&link_list, createTerm(1.2, 2));
    addOrderedModify(&link_list, createTerm(3.4, 4));

    printPoly(link_list);
    freeTerms(link_list);

    // link_list = deleteTerm(link_list, 10);
    // printPoly(link_list);
    // link_list = deleteTerm(link_list, 8);
    // printPoly(link_list);
    // link_list = deleteTerm(link_list, 4);
    // printPoly(link_list);
    // link_list = deleteTerm(link_list, 2);
    // printPoly(link_list);
    // link_list = deleteTerm(link_list, 6);
    // printPoly(link_list);
    // addOrderedModify(&link_list, createTerm(7.8, 8));
    // printPoly(link_list);

    return 0;
}
