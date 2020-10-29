#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "../Headers/BST_main.h"

Node* p_search(Node* root, char *key) {
    if (root == NULL || strcasecmp(root->key, key) == 0) 
       return root;
    if (strcasecmp(root->key, key) < 0) 
       return p_search(root->right, key); 
    return p_search(root->left, key);
} 

Node* insert(Node* root, char *key, int value) {
    if(!root){
        root = (Node*)malloc(sizeof(Node));
        root->key = (char *) malloc(sizeof(char) * strlen(key));
        strcpy(root->key, key);
        list *newLine = malloc(sizeof(list));
        newLine->info = value;
        newLine->next = NULL;
        root->lines = newLine;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    if (strcasecmp(key, root->key) < 0)
        root->left = insert(root->left, key, value); 
    else if (strcasecmp(key, root->key) > 0) 
        root->right = insert(root->right, key, value);  
    return root;
}

Node* p_insert(Node* root, char *key, int value){
    Node *n;
    if((n = p_search(root, key))){
        list *newLine = malloc(sizeof(list));
        newLine->info = value;
        newLine->next = NULL;
        if(n->lines) {
            list *temp = n->lines;
            while(temp->next)
                temp = temp->next;
            temp->next = newLine;
        }
        return root;
    }
    else
        return insert(root, key, value);
}

void inorder(Node *root, FILE *fp){
    if(root) {
        p_inorder(root->left);
        fprintf(fp, "%s\t:\t", root->key);
        list *traverser = root->lines;
        while(traverser){
            fprintf(fp, "%d\t", traverser->info);
            traverser = traverser->next;
        }
        fputs("\n", fp);
        p_inorder(root->right);
    }
}

void p_inorder(Node* root) {
    FILE *fp = fopen("output.txt", "a+");
    inorder(root, fp);
    fclose(fp);
}