#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashset.c"  

int canFormPalindromeUsingHashSet(char* word) {
    hashset h = set_init();
    for (int i = 0; i < strlen(word); i++) {
        char str[2] = {word[i], '\0'};
        if (search(h, str)) {
            eliminate(&h, str);
        } else {
            insert(&h, str);
        }
    }

    return h.size <= 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <word>\n", argv[0]);
        return 1;
    }

    if (canFormPalindromeUsingHashSet(argv[1])) {
        printf("can become a palindrome\n");
    } else {
        printf("cannot become a palindrome\n");
    }

    return 0;
}