/* References
    s - number of stop words
    p - number of paragraph words
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "./Headers/AVL_main.h"
#include "./Headers/AVL_stop_words.h"

Node* para_words = NULL; // 
node* stop_words = NULL; // 

int charcheck(char c) {
    return ((c > 64 && c < 91) || (c > 96 && c < 123));
}

int numcheck(char c) {
    return (c > 47 && c < 58);
}

void stopWords(char *filename) { // reading stop_words.txt and creating nodes for each words
    int i = 0, fd = open(filename, O_RDONLY);
    if(fd == -1) {
        puts("Wrong stop words file");
        exit(1);
    }
    char c, *word = malloc(sizeof(char) * 50);
    while(read(fd, &c, 1)) {
        if(c == '\n') {
            if(i)
                stop_words = s_insert(stop_words, word);
            memset(word, 0, i + 1);
            i = 0;
            continue;
        }
        else
            word[i++] = c;
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    if(argc == 1 || argc == 2) {
        puts("Pass all argument supplied"); // passing 3 arguments is correct.
        exit(1);
    }
    struct timeval start, final;
    gettimeofday(&start, NULL);
    stopWords(argv[2]); // O(s) arg[2] is stop_words.txt
    int i = 0, line = 1, fd = open(argv[1], O_RDONLY, 0);
    if(fd == -1) {
        puts("File does not exist");
        exit(1);
    }
    char *word = malloc(sizeof(char)*50);
    char c;
    while(read(fd, &c, 1)) {
        if( charcheck(c) || numcheck(c) || c == '_') {
                word[i++] = c;
        }
        else {
            c == '\n'?line++:0; // if newline encountered, number is incremented. 
            if(c == '\'') {
                read(fd, &c, 1);
                lseek(fd, -1, SEEK_CUR);
                if(charcheck(word[i-1]))// && charcheck(c))
                    word[i++] = '\'';
                    continue;
            }
            if(i) {
                if(s_search(stop_words, word) == NULL) // O(log (s))
                    para_words = p_insert(para_words, word, line); // O(log (p))
            }
            memset(word, '\0', i+1);
            i = 0;
        }
    }
    close(fd);
    p_inorder(para_words);
    gettimeofday(&final, NULL);
    printf("\n\nBurst Time:\t%ld\n", (final.tv_sec - start.tv_sec)*1000000 + final.tv_usec - start.tv_usec);
    return 0;
}