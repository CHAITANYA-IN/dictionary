typedef struct node {
    char *key;
    int height;
    struct node* left;
    struct node* right;
} node;

int nodeheight(node *p);
int bfactor(node *p);
node *RR(node *p);
node *LR(node *p);
node *LRR(node *p);
node *RLR(node *p);
node* s_insert(node* root, char *key);
node* s_search(node* root, char *key);
void s_inorder(node* root);