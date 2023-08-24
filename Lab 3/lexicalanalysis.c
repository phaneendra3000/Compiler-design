#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Symbol Table
#define MAX_SYMBOLS 100
char symbolTable[MAX_SYMBOLS][50];
int symbolCount = 0;

// Keywords
char *keywords[] = {
    "if", "else", "while", "for", "int", "float", "return", "break", "continue", "switch"
};
int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

// Token types
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_INTEGER,
    TOKEN_RELATIONAL_OPERATOR,
    TOKEN_KEYWORD
} TokenType;

// Structure to represent a token
typedef struct {
    TokenType type;
    char lexeme[50];
} Token;

// Function to check if a string is a keyword
int isKeyword(char *str) {
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


void addToSymbolTable(char *identifier) {
    if (symbolCount < MAX_SYMBOLS) {
        strcpy(symbolTable[symbolCount], identifier);
        symbolCount++;
    }
}


Token getNextToken(FILE *inputFile) {
    Token token;
    char currentChar = fgetc(inputFile);

    // Skip whitespace
    while (isspace(currentChar)) {
        currentChar = fgetc(inputFile);
    }

    if (currentChar == EOF) {
        strcpy(token.lexeme, "");
        token.type = EOF;
        return token;
    }

    // Identifier or Keyword
    if (isalpha(currentChar)) {
        int index = 0;
        while (isalnum(currentChar)) {
            token.lexeme[index++] = currentChar;
            currentChar = fgetc(inputFile);
        }
        token.lexeme[index] = '\0';

        if (isKeyword(token.lexeme)) {
            token.type = TOKEN_KEYWORD;
        } else {
            token.type = TOKEN_IDENTIFIER;
            addToSymbolTable(token.lexeme);
        }

        ungetc(currentChar, inputFile);
    }
    else if (isdigit(currentChar)) {
        int index = 0;
        while (isdigit(currentChar)) {
            token.lexeme[index++] = currentChar;
            currentChar = fgetc(inputFile);
        }
        token.lexeme[index] = '\0';
        token.type = TOKEN_INTEGER;
        ungetc(currentChar, inputFile);
    }
    else if (currentChar == '<' || currentChar == '>' || currentChar == '=') {
        token.lexeme[0] = currentChar;
        token.lexeme[1] = '\0';
        token.type = TOKEN_RELATIONAL_OPERATOR;
        char nextChar = fgetc(inputFile);
        if ((currentChar == '<' && nextChar == '=') ||
            (currentChar == '>' && nextChar == '=') ||
            (currentChar == '=' && nextChar == '=')) {
            token.lexeme[1] = nextChar;
            token.lexeme[2] = '\0';
        } else {
            ungetc(nextChar, inputFile);
        }
    }
    else {
        token.lexeme[0] = currentChar;
        token.lexeme[1] = '\0';
        token.type = currentChar;
    }

    return token;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("File error\n");
        return 1;
    }

    Token token;
    do {
        token = getNextToken(inputFile);
        switch (token.type) {
            case TOKEN_IDENTIFIER:
                fprintf(outputFile, "Identifier: %s\n", token.lexeme);
                break;
            case TOKEN_INTEGER:
                fprintf(outputFile, "Integer: %s\n", token.lexeme);
                break;
            case TOKEN_RELATIONAL_OPERATOR:
                fprintf(outputFile, "Relational Operator: %s\n", token.lexeme);
                break;
            case TOKEN_KEYWORD:
                fprintf(outputFile, "Keyword: %s\n", token.lexeme);
                break;
            case EOF:
                fprintf(outputFile, "End of File\n");
                break;
            default:
                fprintf(outputFile, "Other: %s\n", token.lexeme);
                break;
        }
    } while (token.type != EOF);

    fclose(inputFile);
    fclose(outputFile);

    printf("Symbol Table:\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%d: %s\n", i + 1, symbolTable[i]);
    }

    return 0;
}
