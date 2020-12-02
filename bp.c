#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _letter {
        char info;
        struct _letter *next;
} Letter;

// Build a linked list to represent the specified word.
// Return the head of the linked list built.
Letter *buildList(char word[]);

// Print the linked list.
// For example, if the linked list represents CRIMSON,
// it prints C-->R-->I-->M-->S-->O-->N 
void printList(Letter *head);

int main() {
	char word[100];
	printf("Enter a word: ");
	scanf("%s", word);

	Letter *head = buildList(word);

	printList(head);

	return 0;
}
Letter *buildList(char word[]){
	Letter *head = (Letter*)malloc(sizeof(Letter));
	Letter *temp = (Letter*)malloc(sizeof(Letter));
	head->info = word[0];
	head->next = NULL;
	temp = head;

	for (int i = 1; i < strlen(word); i++){
		Letter *node = (Letter*)malloc(sizeof(Letter));
		node->info= word[i];
		node->next = NULL;
		temp->next = node;
		temp = node;
	}
	return head;
}
void printList(Letter *head){
	while(head != NULL){
		printf("%c", head->info);
		if (head->next != NULL)
			printf("-->");
		head = head->next;
	}
	printf("\n");
}


