#include <stdio.h>
#include <string.h>

void validateOperator(char *token) {
    if (strcmp(token, "+") == 0)
        printf("%-5s : Valid Arithmetic Operator (Addition)\n", token);
    else if (strcmp(token, "-") == 0)
        printf("%-5s : Valid Arithmetic Operator (Subtraction)\n", token);
    else if (strcmp(token, "*") == 0)
        printf("%-5s : Valid Arithmetic Operator (Multiplication)\n", token);
    else if (strcmp(token, "/") == 0)
        printf("%-5s : Valid Arithmetic Operator (Division)\n", token);
    else
        printf("%-5s : Invalid / Not an Arithmetic Operator (+, -, *, /)\n", token);
}

int main(int argc, char *argv[]) {
    char filename[100] = "sampleexp04.txt";
    if (argc > 1) strcpy(filename, argv[1]);

    FILE *fp = fopen(filename, "r");
    if (fp) {
        printf("VALIDATING OPERATORS FROM %s:\n", filename);
        printf("-------------------------------------------\n");
        char token[50];
        while (fscanf(fp, "%s", token) != EOF) {
            validateOperator(token);
        }
        fclose(fp);
    } else {
        printf("Enter an operator to validate: ");
        char token[50];
        if (scanf("%s", token) == 1) {
            validateOperator(token);
        }
    }
    return 0;
}
