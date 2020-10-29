typedef struct node {
    char *key;
    struct node* left;
    struct node* right;
} node;

node* s_insert(node* root, char *key);
node* s_search(node* root, char *key);
void s_inorder(node* root);