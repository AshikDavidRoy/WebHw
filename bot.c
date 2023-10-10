#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODE_LENGTH 100

char postfix[100];
int pIndex = 0;
int tempIndex = 0;
char tempVar[MAX_CODE_LENGTH][5];

int hasHigherPrecedence(char op1, char op2) {
    if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
        return 1;
    return 0;
}

void generateCode(char op) {
    char temp1[5], temp2[5];
    sprintf(temp1, "t%d", tempIndex++);
    sprintf(temp2, "t%d", tempIndex++);
    
    printf("t%d = ", tempIndex - 2);
    if (op == '+')
        printf("%s + %s\n", temp1, temp2);
    else if (op == '-')
        printf("%s - %s\n", temp1, temp2);
    else if (op == '*')
        printf("%s * %s\n", temp1, temp2);
    else if (op == '/')
        printf("%s / %s\n", temp1, temp2);
    
    strcpy(tempVar[tempIndex - 2], temp1);
}

int main() {
    printf("Enter an infix expression: ");
    scanf("%s", postfix);

    // Display the three-address code in a table format
    printf("Three-Address Code:\n");
    printf("Temp Var | Code\n");
    printf("-----------------\n");

    int i = 0;
    while (postfix[i] != '\0') {
        if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
            generateCode(postfix[i]);
        }
        i++;
    }

    printf("%8s | %s\n", tempVar[tempIndex - 1], postfix);

    return 0;
}
