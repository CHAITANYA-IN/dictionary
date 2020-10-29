/*
Time complexity 
Best case O(n) Worst case (n^2)
Space Complexity
0(n) here n is based on the capacity, in this example capacity is 50,000.
*/
#include "dictionary.h"

int main() {
    HashTable* ht = create_table();
    ht_insert(ht, "1", "First address");
    ht_insert(ht, "2", "Second address");
    ht_insert(ht, "Hel", "Third address");
    ht_insert(ht, "Cau", "Fourth address");
    print_search(ht, "1");
    print_search(ht, "2");
    print_search(ht, "3");
    print_search(ht, "Hel");
    print_search(ht, "Cau");  // Collision!
    print_table(ht); 
    sort(ht);
    print_table(ht);
    free_table(ht);
    return 0;
}