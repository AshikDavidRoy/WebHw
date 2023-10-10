#include <stdio.h>
#include <ctype.h>

int tempCounter = 0;

// Function to generate a new temporary variable
char newTemp() {
    return 'T' + tempCounter++;
}

// Function to generate and print a three-address code
void genCode(char op, char arg1, char arg2, char result) {
    printf("%c = %c %c %c\n", result, arg1, op, arg2);
}

// Function to parse E
void E(char* input, int* pos);

// Function to parse T
void T(char* input, int* pos);

// Function to parse F
void F(char* input, int* pos) {
    if (isalpha(input[*pos])) {
        char id = input[*pos];
        (*pos)++;
        genCode('=', id, ' ', id);  // Generate code for F (copying id to id)
    } else if (input[*pos] == '(') {
        (*pos)++;
        E(input, pos);
        if (input[*pos] == ')') {
            (*pos)++;
        }
    }
}

// Function to parse T
void T(char* input, int* pos) {
    F(input, pos);
    while (input[*pos] == '*') {
        char op = input[*pos];
        (*pos)++;
        char id1 = newTemp();
        F(input, pos);
        char id2 = newTemp();
        genCode(op, id1, id2, id1);  // Generate code for T
    }
}

// Function to parse E
void E(char* input, int* pos) {
    T(input, pos);
    while (input[*pos] == '+') {
        char op = input[*pos];
        (*pos)++;
        char id1 = newTemp();
        T(input, pos);
        char id2 = newTemp();
        genCode(op, id1, id2, id1);  // Generate code for E
    }
}

int main() {
    char input[100];  // Adjust the size as needed
    printf("Enter an expression: ");
    scanf("%s", input);
    int pos = 0;
    E(input, &pos);
    return 0;
}
