#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "../Headers/BST_stop_words.h"

node* s_insert(node* root, char *key) {
    if(!root){
        root = (node*)malloc(sizeof(node));
        root->key = (char *) malloc(sizeof(char) * strlen(key));
        strcpy(root->key, key);
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    if (strcasecmp(key, root->key) < 0)
        root->left = s_insert(root->left, key); 
    else if (strcasecmp(key, root->key) > 0) 
        root->right = s_insert(root->right, key);
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