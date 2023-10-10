#include <stdio.h>
#include <ctype.h>

int tempCounter = 0;

// Function to generate a new temporary variable
char* newTemp() {
    char tempVar[3];
    sprintf(tempVar, "T%d", tempCounter++);
    return tempVar;
}

// Function to generate and print a three-address code
void genCode(char* op, char* arg1, char* arg2, char* result) {
    printf("%s := %s %s %s\n", result, arg1, op, arg2);
}

// Function to parse E
void E(char* input, int* pos) {
    char T1[3], T2[3];
    T(input, pos);
    while (input[*pos] == '+') {
        (*pos)++;
        char* op = "+";
        T1 = newTemp();
        T(input, pos);
        T2 = newTemp();
        genCode(op, T1, T2, T1);  // Generate code for E
    }
}

// Function to parse T
void T(char* input, int* pos) {
    char F1[3], F2[3];
    F(input, pos);
    while (input[*pos] == '*') {
        (*pos)++;
        char* op = "*";
        F1 = newTemp();
        F(input, pos);
        F2 = newTemp();
        genCode(op, F1, F2, F1);  // Generate code for T
    }
}

// Function to parse F
void F(char* input, int* pos) {
    if (input[*pos] == '(') {
        (*pos)++;
        E(input, pos);
        if (input[*pos] == ')') {
            (*pos)++;
        }
    } else if (isalpha(input[*pos])) {
        char id[2];
        id[0] = input[*pos];
        id[1] = '\0';
        (*pos)++;
        // Generate code for F (copying id to a temporary variable)
        char T1[3] = newTemp();
        genCode(":=", id, "-", T1);
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
