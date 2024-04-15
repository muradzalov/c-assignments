#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void main(void) {
    char buffer[BUFFER_SIZE];
    char *token;

    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        token = strtok(buffer, ",");
        while (token != NULL) {
            printScientificNotation(token);
            printf("\t");
            token = strtok(NULL, ",");
        }
        printf("%s", "\n");
    }
}

void printScientificNotation(char *token) {
    double num = atof(token);
    printf("%-25e", num);
}