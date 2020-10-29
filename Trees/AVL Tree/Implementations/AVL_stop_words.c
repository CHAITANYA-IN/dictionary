#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "../Headers/AVL_stop_words.h"

int nodeheight(node *p) {
    int hl, hr;
    hl = p && p->left ? p->left->height : 0;
    hr = p && p->right ? p->right->height : 0;
    return hl > hr ? hl + 1 : hr + 1;
}

//Calculate Balance Factor
int bfactor(node *p) {
    int hl, hr;
    hl = p && p->left ? p->left->height : 0;
    hr = p && p->right ? p->right->height : 0;
    return hl - hr;
}

//Right Rotation
node *RR(node *p) {
    node *pl = p->left;
    node *T2 = pl->right;
    pl->right = p;
    p->left = T2;
    p->height = nodeheight(p);
    pl->height = nodeheight(pl);
    return pl;
}

//Left Rotation
node *LR(node *p) {
    node *pl = p->right;
    node *T2 = pl->left;
    pl->left = p;
    p->right = T2;
    p->height = nodeheight(p);
    pl->height = nodeheight(pl);
    return pl;
}

//Left-Right Rotation
node *LRR(node *p) {
    p->left = LR(p->left);
    return RR(p);
}

//Right-Left Rotation
node *RLR(node *p) {
    p->right = RR(p->right);
    return LR(p);
}

node* s_insert(node* root, char *key) {
    if(!root) {
        root = (node*)malloc(sizeof(node));
        root->key = (char *) malloc(sizeof(char) * strlen(key));
        strcpy(root->key, key);
        root->height=1;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    if (strcasecmp(key, root->key) < 0)
        root->left = s_insert(root->left, key); 
    else if (strcasecmp(key, root->key) > 0) 
        root->right = s_insert(root->right, key);
    root->height = nodeheight(root);

    if (bfactor(root) == 2 && bfactor(root->left) == 1)
        return RR(root);
    else if (bfactor(root) == -2 && bfactor(root->right) == -1)
        return LR(root);
    else if (bfactor(root) == -2 && bfactor(root->right) == 1)
        return RLR(root);
    else if (bfactor(root) == 2 && bfactor(root->left) == -1)
        return LRR(root);

    return root;
}

node* s_search(node* root, char *key) {
    if (root == NULL || strcasecmp(root->key, key) == 0) 
       return root;
    if (strcasecmp(root->key, key) < 0) 
       return s_search(root->right, key); 
    return s_search(root->left, key);
}

void s_inorder(node* root) {
    if(root) {
        s_inorder(root->left);
        printf("%s\n", root->key);
        s_inorder(root->right);
    }
}