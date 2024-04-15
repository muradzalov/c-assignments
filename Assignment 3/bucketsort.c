#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Structs
struct node {
    char* string;
    struct node* next;
};

struct bucket {
    char* min_word;
    struct node* head;
};

// Method prototypes
int find_bucket(struct bucket* buckets, int num_buckets, char* word);
void insert_into_bucket(struct bucket* buckets, int bucket_index, char* word);
void print_buckets(struct bucket* buckets, int num_buckets);
void free_memory(struct bucket* buckets, int num_buckets);

int main(int argc, char *argv[]) {
    // Test case 1: Insufficient CLAs
    if (argc < 2) {
        printf("bucketsort: Fatal error! There must be at-least one CLA.\n");
        return 1;
    }

    // Test case 2: CLAs not in alphabetical order
    for (int i = 2; i < argc; i++) {
        if (strcasecmp(argv[i - 1], argv[i]) > 0) {
            printf("bucketsort: Fatal error! CLAs must be entered in alphabetical order\n");
            return 1;
        }
    }

    // CLAs in correct order. Computational step:
    int num_buckets = argc;
    struct bucket* buckets = malloc(sizeof(struct bucket) * num_buckets);
    buckets[0].min_word = "";
    for (int i = 1; i < num_buckets; ++i) {
        buckets[i].min_word = argv[i];
        buckets[i].head = NULL;
    }
    char input[256];
    while (scanf("%255s", input) != EOF) {
        int bucket_index = find_bucket(buckets, num_buckets, input);
        if (bucket_index >= 0) {
            insert_into_bucket(buckets, bucket_index, input);
        }
    }

    // Output step
    print_buckets(buckets, num_buckets);
    
    // Cleanup step
    free_memory(buckets, num_buckets);
    free(buckets);
    return 0;
}

// Locate the bucket that the word should be placed into
int find_bucket(struct bucket* buckets, int num_buckets, char* word) {
    for (int i = 1; i < num_buckets; i++) {
        if (strcasecmp(word, buckets[i].min_word) < 0) return i - 1;
    }
    return num_buckets - 1;
}

// Perform insertion into bucket for the word from the STDIN
void insert_into_bucket(struct bucket* buckets, int bucket_index, char* word) {
    struct node **current = &(buckets[bucket_index].head), *new_node = malloc(sizeof(struct node));
    new_node->string = strdup(word);
    new_node->next = NULL;
    while (*current != NULL && strcasecmp((*current)->string, word) < 0) {
        current = &((*current)->next);
    }
    new_node->next = *current;
    *current = new_node;
}

// Loop through each bucket and print their contents
void print_buckets(struct bucket* buckets, int num_buckets) {
    for (int i = 0; i < num_buckets; i++) {
        struct node* current = buckets[i].head;
        if (current == NULL) continue;
        printf("bucket %d:", i);
        int isFirst = 1;
        while (current != NULL) {
            if (isFirst) {
                printf(" %s", current->string);
                isFirst = 0;
            } else {
                printf(" %s", current->string);
            }
            current = current->next;
        }
        printf("\n");
    }
}

// Free memory to avoid memory leaks
void free_memory(struct bucket* buckets, int num_buckets) {
    for (int i = 0; i < num_buckets; i++) {
        struct node* current = buckets[i].head;
        while (current != NULL) {
            struct node* temp = current;
            current = current->next;
            free(temp->string);
            free(temp);
        }
    }
}
