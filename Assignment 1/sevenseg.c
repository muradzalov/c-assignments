#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_LEN 100
#define NUM_DIGITS 10
#define MAX_OUTPUT_SIZE 1024

// Checks that user input is a number
int isValidNumber(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i]) && str[i] != '\n') {
            return 0;
        }
    }
    return 1;
}

// Ensures that the assignment input rules are followed
int getValidSegmentLength(const char* prompt, int min, int max, int relation, int horizontal) {
    int segment_length;
    char input[MAX_LEN + 1];
    while (1) {
        printf("%s", prompt);
        if (!fgets(input, MAX_LEN, stdin)) {
            // printf("\nUnexpected input error.\n");
            exit(1);
        }
        input[strcspn(input, "\n")] = 0;
        if (!isValidNumber(input)) {
            printf("Input is not a valid number. Please try again.\n");
            continue;
        }
        segment_length = atoi(input);
        if (segment_length < min || segment_length > max) {
            printf("The given value is not acceptable!\n");
        } else if (relation != 0 && (segment_length > relation * horizontal || (2 * segment_length) < horizontal)) {
						printf("The given value is not acceptable!\n");
        } else {
            break;
        }
    }
    return segment_length;
}

void printBlankHorizontal() {
    for (int i = 0; i < 2; i++) { 
        printf("    ");
        printf("\n");
    }
}

void printFilledHorizontal(int segment_width, int segment_height) {
		printf("  ");
    for (int i = 0; i < segment_width; i++) {
        printf("*");
    }
    printf("  \n  ");
    for (int i = 0; i < segment_width; i++) {
        printf("*");
    }
		printf("\n");
}

void printLeftVerticalSingle(int segment_width, int segment_height) {
    for (int i = 0; i < segment_height; i++) {
        printf("**");
        for (int j = 0; j < segment_width; j++) {
            printf(" ");
        }
        printf("\n");
    }
}

void printRightVerticalSingle(int segment_width, int segment_height) {
    for (int i = 0; i < segment_height; i++) {
        for (int j = 0; j < segment_width + 2; j++) {
            printf(" ");
        }
        printf("**\n");
    }
}

void printDoubleVerticals(int segment_width, int segment_height) {
    for (int i = 0; i < segment_height; i++) {
        printf("**");
					for (int j = 0; j < segment_width; j++) {
							printf(" ");
					}
					printf("**\n");
    }
}

void printNumber0(int segment_width, int segment_height) {
	printFilledHorizontal(segment_width, segment_height);
	printDoubleVerticals(segment_width, segment_height);
	printBlankHorizontal();
	printDoubleVerticals(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
}

void printNumber1(int segment_width, int segment_height) {
	printBlankHorizontal();
	printRightVerticalSingle(segment_width, segment_height);
	printBlankHorizontal();
	printRightVerticalSingle(segment_width, segment_height);
	printBlankHorizontal();
}

void printNumber2(int segment_width, int segment_height) {
	printFilledHorizontal(segment_width, segment_height);
	printRightVerticalSingle(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
	printLeftVerticalSingle(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
}

void printNumber3(int segment_width, int segment_height) {
	printFilledHorizontal(segment_width, segment_height);
	printRightVerticalSingle(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
	printRightVerticalSingle(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
}

void printNumber4(int segment_width, int segment_height) {
	printBlankHorizontal();
	printDoubleVerticals(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
	printRightVerticalSingle(segment_width, segment_height);
	printBlankHorizontal();
}

void printNumber5(int segment_width, int segment_height) {
	printFilledHorizontal(segment_width, segment_height);
	printLeftVerticalSingle(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
	printRightVerticalSingle(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
}

void printNumber6(int segment_width, int segment_height) {
	printFilledHorizontal(segment_width, segment_height);
	printLeftVerticalSingle(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
	printDoubleVerticals(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
}

void printNumber7(int segment_width, int segment_height) {
	printFilledHorizontal(segment_width, segment_height);
	printRightVerticalSingle(segment_width, segment_height);
	printBlankHorizontal();
	printRightVerticalSingle(segment_width, segment_height);
	printBlankHorizontal();
}

void printNumber8(int segment_width, int segment_height) {
	printFilledHorizontal(segment_width, segment_height);
	printDoubleVerticals(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
	printDoubleVerticals(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
}

void printNumber9(int segment_width, int segment_height) {
	printFilledHorizontal(segment_width, segment_height);
	printDoubleVerticals(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
	printRightVerticalSingle(segment_width, segment_height);
	printFilledHorizontal(segment_width, segment_height);
}

void printFirstRow(int segment_width, int segment_height, const int *digits, int numDigits) {
    char outputString[MAX_OUTPUT_SIZE] = "  ";
    char filledSegment[segment_width + 1];
    char blankSegment[segment_width + 1];
    for (int i = 0; i < segment_width; i++) {
        filledSegment[i] = '*';
        blankSegment[i] = ' ';
    }
    filledSegment[segment_width] = '\0';
    blankSegment[segment_width] = '\0';
    for (int i = 0; i < numDigits; i++) {
        switch (digits[i]) {
            case 0: case 2: case 3: case 5: case 6: case 7: case 8: case 9:
                strcat(outputString, filledSegment);
                break;
            case 1: case 4:
                strcat(outputString, blankSegment);
                break;
        }
        if (i < numDigits - 1) {
            strcat(outputString, "      ");
        }
    }
    printf("%s\n", outputString);
}

void printMiddleRow(int segment_width, int segment_height, const int *digits, int numDigits) {
    char outputString[MAX_OUTPUT_SIZE] = "  ";
    char filledSegment[segment_width + 1];
    char blankSegment[segment_width + 1];
    for (int i = 0; i < segment_width; i++) {
        filledSegment[i] = '*';
        blankSegment[i] = ' ';
    }
    filledSegment[segment_width] = '\0';
    blankSegment[segment_width] = '\0';
    for (int i = 0; i < numDigits; i++) {
        switch (digits[i]) {
            case 2: case 3: case 4: case 5: case 6: case 8: case 9:
                strcat(outputString, filledSegment);
                break;
            case 0: case 1: case 7:
                strcat(outputString, blankSegment);
                break;
        }
        if (i < numDigits - 1) {
            strcat(outputString, "      ");
        }
    }
    printf("%s\n", outputString);
}

void printBottomRow(int segment_width, int segment_height, const int *digits, int numDigits) {
    char outputString[MAX_OUTPUT_SIZE] = "  ";
    char filledSegment[segment_width + 1];
    char blankSegment[segment_width + 1];
    for (int i = 0; i < segment_width; i++) {
        filledSegment[i] = '*';
        blankSegment[i] = ' ';
    }
    filledSegment[segment_width] = '\0';
    blankSegment[segment_width] = '\0';
    for (int i = 0; i < numDigits; i++) {
        switch (digits[i]) {
            case 0: case 2: case 3: case 5: case 6: case 8: case 9:
                strcat(outputString, filledSegment);
                break;
            case 1: case 4: case 7:
                strcat(outputString, blankSegment);
                break;
        }
        if (i < numDigits - 1) {
            strcat(outputString, "      ");
        }
    }
    printf("%s\n", outputString);
}

void printTopHalfVerticalRow(int segment_width, int segment_height, const int *digits, int numDigits) {
    char outputString[MAX_OUTPUT_SIZE] = "";
    for (int i = 0; i < numDigits; i++) {
        char startSegment[3] = "  ";
        char endSegment[3] = "  ";
        switch (digits[i]) {
            case 1: case 2: case 3: case 7:
                strcpy(endSegment, "**");
                break;
            case 6: case 5:
                strcpy(startSegment, "**");
                break;
            case 0: case 8: case 4: case 9:
                strcpy(startSegment, "**");
                strcpy(endSegment, "**");
                break;
        }
        strcat(outputString, startSegment);
        if (i < numDigits - 1 || digits[i] != 5) {
            for (int j = 0; j < segment_width; j++) {
                strcat(outputString, " ");
            }
            strcat(outputString, endSegment);
        }
        if (i < numDigits - 1) {
            strcat(outputString, "  ");
        }
    }
    printf("%s\n", outputString);
}

void printBottomHalfVerticalRow(int segment_width, int segment_height, const int *digits, int numDigits) {
    char outputString[MAX_OUTPUT_SIZE] = "";
    for (int i = 0; i < numDigits; i++) {
        char startSegment[3] = "  ";
        char endSegment[3] = "  ";
        switch (digits[i]) {
            case 1: case 3: case 4: case 7: case 9: case 5:
                strcpy(endSegment, "**");
                break;
            case 2:
                strcpy(startSegment, "**");
                break;
            case 0: case 6: case 8:
                strcpy(startSegment, "**");
                strcpy(endSegment, "**");
                break;
        }
        strcat(outputString, startSegment);
        if (i < numDigits - 1 || digits[i] != 2) {
            for (int j = 0; j < segment_width; j++) {
                strcat(outputString, " ");
            }
            strcat(outputString, endSegment);
        }
        if (i < numDigits - 1) {
            strcat(outputString, "  ");
        }
    }
    printf("%s\n", outputString);
}


void printAnyNumber(int segment_width, int segment_height, const int *digits, int numDigits) {
		// print first two rows
		printFirstRow(segment_width, segment_height, digits, numDigits);
		printFirstRow(segment_width, segment_height, digits, numDigits);

		// print top half vertical segment
		for (int i=0; i<segment_height; i++) {
			printTopHalfVerticalRow(segment_width, segment_height, digits, numDigits);
		}

		// print middle two rows
		printMiddleRow(segment_width, segment_height, digits, numDigits);
		printMiddleRow(segment_width, segment_height, digits, numDigits);

		// print bottom half vertical segment
		for (int i=0; i<segment_height; i++) {
			printBottomHalfVerticalRow(segment_width, segment_height, digits, numDigits);
		}

		// print bottom two rows
		printBottomRow(segment_width, segment_height, digits, numDigits);
		printBottomRow(segment_width, segment_height, digits, numDigits);
}

int main(void) {
    printf("This is a 7-segment display! Press \"Enter\" after providing any number in keyboard.\n");
    int segment_width = getValidSegmentLength("Please enter the length of horizontal segments (from 3 to 40):\n", 3, 40, 0, 0);
    int segment_height = getValidSegmentLength("Now, enter the length of vertical segments (from 3 to 40):\n", 3, 40, 2, segment_width);
    char input[MAX_LEN + 1];
    int length, numDigits, number;
    int digits[MAX_LEN];
		int isThisTheVeryFirstPrompt = 1;

    while (1) {
        if (isThisTheVeryFirstPrompt) {
            printf("Enter a positive integer: \n");
            isThisTheVeryFirstPrompt = 0;
        } else {
            printf("Enter a positive integer:\n");
        }
        if (!fgets(input, MAX_LEN, stdin)) {
            if (feof(stdin)) {
                break;
            } else {
                continue;
            }
        }

        input[strcspn(input, "\n")] = 0;

        if (!isValidNumber(input)) {
            printf("Input is not a valid positive integer. Please try again.\n");
            continue;
        }

        length = strlen(input);
        numDigits = 0;

        if (length == 1) {
            number = atoi(input);
            switch (number) {
                case 0:
										printNumber0(segment_width, segment_height);
                    break;
                case 1:
										printNumber1(segment_width, segment_height);
                    break;
								case 2:
                    printNumber2(segment_width, segment_height);
                    break;
                case 3:
										printNumber3(segment_width, segment_height);
                    break;
                case 4:
										printNumber4(segment_width, segment_height);
                    break;
								case 5:
                    printNumber5(segment_width, segment_height);
                    break;
								case 6:
                    printNumber6(segment_width, segment_height);
                    break;
                case 7:
										printNumber7(segment_width, segment_height);
                    break;
                case 8:
										printNumber8(segment_width, segment_height);
                    break;
								case 9:
                    printNumber9(segment_width, segment_height);
                    break;
            }
        } else {
            // multi-digit numbers
            for (int i = 0; i < length; i++) {
                if (isdigit(input[i])) {
                    digits[numDigits++] = input[i] - '0';
                }
            }
            printAnyNumber(segment_width, segment_height, digits, numDigits);
        }
    }
    printf("END\n");
    return 0;
}
