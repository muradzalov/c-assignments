#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Checks whether a string CLA is a positive integer
bool isPositiveInteger(char *arg) {
  for (int i=0; arg[i] != '\0'; i++) {
    if (!isdigit(arg[i])) {
      return false;
    }
  }
  return true;
}

// Checks whether all CLA argv[1], argv[2],... are positive integers
void validateArgumentsArePositiveIntegers(int argc, char *argv[]) {
  for (int i=1; i<argc; i++) {
    if (!isPositiveInteger(argv[i])) {
      printf("railcipher: Fatal error! First CLA must be a valid integer.\n");
      exit(1);
    }
  }
}

// Checks that the first CLA (representing length of encryption key) is less than 26
void isFirstCLALessThan26(char *lengthArg) {
  int length = atoi(lengthArg);
  if (length>26 || length<=0) {
    printf("railcipher: Fatal error! The encryption key length cannot exceed 26.\n");
    exit(1);
  }
}

// Checks that the encryption key provided is valid: 0 < values < lengthFirstCLA
void areCLAsValidPermutation(int argc, char *argv[]) {
  int length = atoi(argv[1]);
  for (int i=2; i<argc; i++) {
    int val = atoi(argv[i]);
    if (val<1 || val>length) {
      printf("railcipher: Fatal error! The encryption key passed as CLAs is not valid.\n");
      exit(1);
    }
  }
}

// Removes non-alphabetical letters like punctuation and white spaces and lowercases
void cleanMessage(char* input, char* output) {
  int a=0;
  for (int i=0; input[i] != '\0'; i++) {
    if (isalpha(input[i])) {
      output[a++] = tolower(input[i]);
    }
  }
  output[a] = '\0';
  // printf("Cleaned message: %s\n", output);
}

// // RAILCIPHER ENCRYPT
void encrypt(char* plaintext, int keyLength, int* keyOrder) {
  char cleanText[256];
  cleanMessage(plaintext, cleanText);
  int cleanTextLength = strlen(cleanText);
  int numRows = ceil((double)cleanTextLength / keyLength);
  char matrix[numRows][keyLength];
  memset(matrix, 0, sizeof(matrix));
  char ciphertext[256] = {0};
  int idx = 0;

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < keyLength; j++) {
      if (idx < cleanTextLength) {
        matrix[i][j] = cleanText[idx++];
      } else {
        int paddingOffset = idx++ - cleanTextLength;
        matrix[i][j] = 'x' + (paddingOffset % 26); // keep seeing repetitive Zs
      }
    }
  }
   
  int readOrder[keyLength];
  for (int i = 0; i < keyLength; i++) {
      readOrder[keyOrder[i] - 1] = i;
  }

  idx = 0;
  for (int k = 0; k < keyLength; k++) {
      int col = readOrder[k];
      for (int row = 0; row < numRows; row++) {
          if (matrix[row][col] != 0) {
              ciphertext[idx++] = toupper(matrix[row][col]);
          }
      }
  }
  printf("%s\n", ciphertext);
}

// RAILCIPHER DECRYPT
void decrypt(char* ciphertext, int keyLength, int* keyOrder) {
  int cipherTextLength = strlen(ciphertext);
  int numRows = cipherTextLength / keyLength;
  char matrix[numRows][keyLength];
  char decryptedText[cipherTextLength + 1];
  int index = 0;
  memset(decryptedText, 0, sizeof(decryptedText));
  for (int col = 0; col < keyLength; col++) {
    int actualCol = keyOrder[col] - 1;
      for (int row = 0; row < numRows; row++) {
        int cipherIndex = actualCol * numRows + row;
          if (cipherIndex < cipherTextLength) {
            matrix[row][col] = ciphertext[cipherIndex];
          }
      }
  }
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < keyLength; col++) {
      if (matrix[row][col] != 0) {
        decryptedText[index++] = matrix[row][col];
      }
    }
  }
  printf("%s\n", decryptedText);
}


void processUserProgramCommandInput(char* command, int keyLength, int* keyOrder) {
  if (strncmp(command, "encrypt ", 8) == 0) {
    encrypt(command + 8, keyLength, keyOrder);
  } else if (strncmp(command, "decrypt ", 8) == 0) {
    decrypt(command + 8, keyLength, keyOrder);
  } else if (strcmp(command, "quit") == 0) {
    // quit program
  }
}

void main(int argc, char *argv[]) {
  // command-line argument validations
  validateArgumentsArePositiveIntegers(argc, argv);
  isFirstCLALessThan26(argv[1]);
  areCLAsValidPermutation(argc, argv);

  // user input command handling
  char userProgramCommandInput[256];
  int keyLength = atoi(argv[1]);
  int keyOrder[keyLength];
  for (int i=0; i<keyLength; i++) {
    keyOrder[i] = atoi(argv[i+2]);
  }

  while(9) {
    if (fgets(userProgramCommandInput, sizeof(userProgramCommandInput), stdin) == NULL) {
      break;
    }
    userProgramCommandInput[strcspn(userProgramCommandInput, "\n")] = '\0';

    if (strcmp(userProgramCommandInput, "quit") == 0) {
      break;
    }
    processUserProgramCommandInput(userProgramCommandInput, keyLength, keyOrder);
  }
}
