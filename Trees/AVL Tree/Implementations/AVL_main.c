#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "../Headers/AVL_main.h"

int Nodeheight(Node *p) {
    int hl, hr;
    hl = p && p->left ? p->left->height : 0;
    hr = p && p->right ? p->right->height : 0;
    return hl > hr ? hl + 1 : hr + 1;
}

//Calculate Balance Factor
int balanceFactor(Node *p) {
    int hl, hr;
    hl = p && p->left ? p->left->height : 0;
    hr = p && p->right ? p->right->height : 0;
    return hl - hr;
}

//Right Rotation
Node *RRotation(Node *p) {
    Node *pl = p->left;
    Node *T2 = pl->right;
    pl->right = p;
    p->left = T2;
    p->height = Nodeheight(p);
    pl->height = Nodeheight(pl);
    return pl;
}

//Left Rotation
Node *LRotation(Node *p) {
    Node *pl = p->right;
    Node *T2 = pl->left;
    pl->left = p;
    p->right = T2;
    p->height = Nodeheight(p);
    pl->height = Nodeheight(pl);
    return pl;
}

//Left-Right Rotation
Node *LRRotation(Node *p) {
    p->left = LRotation(p->left);
    return RRotation(p);
}

//Right-Left Rotation
Node *RLRotation(Node *p) {
    p->right = RRotation(p->right);
    return LRotation(p);
}

Node *p_search(Node *root, char *key) {
    if (root == NULL || strcasecmp(root->key, key) == 0)
        return root;
    if (strcasecmp(root->key, key) < 0)
        return p_search(root->right, key);
    return p_search(root->left, key);
}

Node *insert(Node *root, char *key, int value) {
    if (!root) {
        root = (Node *)malloc(sizeof(Node));
        root->key = (char *)malloc(sizeof(char) * strlen(key));
        strcpy(root->key, key);
        list *newLine = malloc(sizeof(list));
        newLine->info = value;
        newLine->next = NULL;
        root->lines = newLine;
        root->height = 1;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    if (strcasecmp(key, root->key) < 0)
        root->left = insert(root->left, key, value);
    else if (strcasecmp(key, root->key) > 0)
        root->right = insert(root->right, key, value);

    root->height = Nodeheight(root);

    if (balanceFactor(root) == 2 && balanceFactor(root->left) == 1)
        return RRotation(root);
    else if (balanceFactor(root) == -2 && balanceFactor(root->right) == -1)
        return LRotation(root);
    else if (balanceFactor(root) == -2 && balanceFactor(root->right) == 1)
        return RLRotation(root);
    else if (balanceFactor(root) == 2 && balanceFactor(root->left) == -1)
        return LRRotation(root);

    return root;
}

Node *p_insert(Node *root, char *key, int value) {
    Node *n;
    if ((n = p_search(root, key))) {
        list *newLine = malloc(sizeof(list));
        newLine->info = value;
        newLine->next = NULL;
        if (n->lines) {
            list *temp = n->lines;
            while (temp->next)
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
        fprintf(fp, "%s : ", root->key);
        list *traverser = root->lines;
        while(traverser){
            fprintf(fp, "%d, ", traverser->info);
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