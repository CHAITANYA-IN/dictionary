#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hash Function
unsigned long hash_function(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}

// Allocates memory for a Linkedlist pointer
static LinkedList* allocate_list () {
    LinkedList* list = (LinkedList*) malloc (sizeof(LinkedList));
    return list;
}

// Inserts the item onto the Linked List
static LinkedList* linkedlist_insert(LinkedList* list, Ht_item* item) {
    if (!list) {
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }
    else if (list->next == NULL) {
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }
    LinkedList* temp = list;
    while (temp->next->next) {
        temp = temp->next;
    }
    LinkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    return list;
}

// Removes the head from the linked list and returns the item of the popped element
static Ht_item* linkedlist_remove(LinkedList* list) {
    if (!list)
        return NULL;
    if (!list->next)
        return NULL;
    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    Ht_item* it = NULL;
    memcpy(temp->item, it, sizeof(Ht_item));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}

static void free_linkedlist(LinkedList* list) {
    LinkedList* temp = list;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}

// Create the overflow buckets; an array of linkedlists
static LinkedList** create_overflow_buckets(HashTable* table) {
    LinkedList** buckets = (LinkedList**) calloc (table->size, sizeof(LinkedList*));
    for (int i=0; i<table->size; i++)
        buckets[i] = NULL;
    return buckets;
}

// Free all the overflow bucket lists
static void free_overflow_buckets(HashTable* table) {
    LinkedList** buckets = table->overflow_buckets;
    for (int i=0; i<table->size; i++)
        free_linkedlist(buckets[i]);
    free(buckets);
}

// Creates a pointer to a new hash table item
Ht_item* create_item(char* key, char* value) {
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item->key = (char*) malloc (strlen(key) + 1);
    item->value = (char*) malloc (strlen(value) + 1);
    strcpy(item->key, key);
    strcpy(item->value, value);
    return item;
}

// Creates a new HashTable
HashTable* create_table() {
    int size = CAPACITY;
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc (table->size, sizeof(Ht_item*));
    for (int i=0; i<table->size; i++)
        table->items[i] = NULL;
    table->overflow_buckets = create_overflow_buckets(table);
    return table;
}

// Frees an item
void free_item(Ht_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

// Frees the table
void free_table(HashTable* table) {
    for (int i=0; i<table->size; i++) {
        Ht_item* item = table->items[i];
        if (item != NULL)
            free_item(item);
    }
    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

void handle_collision(HashTable* table, unsigned long index, Ht_item* item) {
    LinkedList* head = table->overflow_buckets[index];
    if (head == NULL) { // We need to create the list
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    }
    else { // Insert to the list
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
 }

void ht_insert(HashTable* table, char* key, char* value) {
    Ht_item* item = create_item(key, value); // Create the item
    unsigned long index = hash_function(key); // Compute the index
    Ht_item* current_item = table->items[index];
    if (current_item == NULL) { // Key does not exist.
        if (table->count == table->size) { // Hash Table Full
            printf("Insert Error: Hash Table is full\n"); // Remove the create item
            free_item(item);
            return;
        } // Insert directly
        table->items[index] = item; 
        table->count++;
    }
    else { // Scenario 1: We only need to update value
        if (strcmp(current_item->key, key) == 0) {
            strcpy(table->items[index]->value, value);
            return;
        }
        else { // Scenario 2: Collision
            handle_collision(table, index, item);
            return;
        }
    }
}

char* ht_search(HashTable* table, char* key) { // Searches the key in the hashtable and returns NULL if it doesn't exist
    int index = hash_function(key);
    Ht_item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index]; // Ensure that we move to items which are not NULL
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }
        if (head == NULL)
            return NULL;
        item = head->item;
        head = head->next;
    }
    return NULL;
}

void print_search(HashTable* table, char* key) {
    char* val;
    if ((val = ht_search(table, key)) == NULL)
        printf("%s does not exist\n", key);
    else
        printf("Key:%s, Value:%s\n", key, val);
}

void print_table(HashTable* table) {
    printf("\n-------------------\n");
    for (int i=0; i<table->size; i++) {
        if (table->items[i]) {
            printf("Index:%d, Key:%s, Value:%s", i, table->items[i]->key, table->items[i]->value);
            if (table->overflow_buckets[i]) {
                printf(" => Overflow Bucket => ");
                LinkedList* head = table->overflow_buckets[i];
                while (head) {
                    printf("Key:%s, Value:%s ", head->item->key, head->item->value);
                    head = head->next;
                }
            }
            printf("\n");
        }
    }
    printf("-------------------\n");
}

void sort(HashTable* table) {
	printf("Enter 1 to print ascending :");int reverse;
	scanf("%d",&reverse);
	Ht_item* temp=NULL;
	for (int j = 0; j < table->size - 1; j++) { //O(n^2)
		for (int i = j + 1; i < table->size; i++) {
            if(table->items[i] && table->items[j]) {
                if(reverse==0) {
                    if (strcmp(table->items[j]->key, table->items[i]->key) > 0) {
                        temp = table->items[i];
                        table->items[i] = table->items[j];
                        table->items[j] = temp;
                    }
                }
                else {
                    if (strcmp(table->items[j]->key, table->items[i]->key) < 0) {
                        temp = table->items[i];
                        table->items[i] = table->items[j];
                        table->items[j] = temp;
                    }
                }
            }
		}
	}
}
