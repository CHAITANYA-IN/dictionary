// Define the Hash Table Item here
typedef struct Ht_item {
    char* key;
    char* value;
} Ht_item;

// Define the Linkedlist here
typedef struct LinkedList {
    Ht_item* item; 
    struct LinkedList* next;
} LinkedList;

// Define the Hash Table here
typedef struct HashTable {
    Ht_item** items; // Contains an array of pointers to items
    LinkedList** overflow_buckets;
    int size;
    int count;
} HashTable;

#define CAPACITY 50000 // Size of the Hash Table

unsigned long hash_function(char* str); // Hash Function
static LinkedList* allocate_list ();// Allocates memory for a Linkedlist pointer
static LinkedList* linkedlist_insert(LinkedList* list, Ht_item* item);// Inserts the item onto the Linked List
static Ht_item* linkedlist_remove(LinkedList* list);// Removes the head from the linked list and returns the item of the popped element
static void free_linkedlist(LinkedList* list);
static LinkedList** create_overflow_buckets(HashTable* table);// Create the overflow buckets; an array of linkedlists
static void free_overflow_buckets(HashTable* table);// Free all the overflow bucket lists
Ht_item* create_item(char* key, char* value);// Creates a pointer to a new hash table item
HashTable* create_table(); // Creates a new HashTable
void free_item(Ht_item* item); // Frees an item
void free_table(HashTable* table); // Frees the table
void handle_collision(HashTable* table, unsigned long index, Ht_item* item);
void ht_insert(HashTable* table, char* key, char* value);
char* ht_search(HashTable* table, char* key);
void print_search(HashTable* table, char* key);
void print_table(HashTable* table);
void sort(HashTable* table);