typedef struct list {
    int info;
    struct list *next;
} list;

typedef struct Node {
    char *key;
    list *lines;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

int Nodeheight(Node *p);
int balanceFactor(Node *p);
Node *RRotation(Node *p);
Node *LRotation(Node *p);
Node *LRRotation(Node *p);
Node *RLRotation(Node *p);
Node *p_search(Node *root, char *key);
Node *insert(Node *root, char *key, int value);
Node *p_insert(Node *root, char *key, int value);
void inorder(Node *root, FILE *fp);
void p_inorder(Node *root);