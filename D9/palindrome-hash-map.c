#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.c"

int canFormPalindromeUsingHashMap(char* word) {
    hashmap h = hash_init();
    int oddCount = 0;


    for (int i = 0; i < strlen(word); i++) {
        char str[2] = {word[i], '\0'};
        int count = get_or_default(h, str, 0);
        put(&h, str, count + 1);
    }


    for (int i = 0; i < h.bins; i++) {
        for (map_node* it = h.table[i]; it != NULL; it = it->next) {
            if (it->value % 2 != 0) oddCount++;
        }
    }

    return oddCount <= 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <word>\n", argv[0]);
        return 1;
    }

    if (canFormPalindromeUsingHashMap(argv[1])) {
        printf("can become a palindrome\n");
    } else {
        printf("cannot become a palindrome\n");
    }

    return 0;
}