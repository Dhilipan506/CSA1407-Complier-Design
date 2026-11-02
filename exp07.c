#include <stdio.h>
#include <string.h>
#include <ctype.h>

char productions[10][50];
int n = 0;

void addToSet(char *set, char ch) {
    if (ch == '\0') return;
    for (int i = 0; set[i] != '\0'; i++) {
        if (set[i] == ch) return;
    }
    int len = strlen(set);
    set[len] = ch;
    set[len + 1] = '\0';
}

void findFirst(char symbol, char *result) {
    if (!isupper(symbol)) {
        addToSet(result, symbol);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (productions[i][0] == symbol) {
            char *rhs = &productions[i][3];
            if (strcmp(rhs, "#") == 0 || strcmp(rhs, "@") == 0 || strcmp(rhs, "e") == 0) {
                addToSet(result, '#');
                continue;
            }

            for (int j = 0; rhs[j] != '\0'; j++) {
                char temp[50] = "";
                findFirst(rhs[j], temp);
                int hasEpsilon = 0;
                for (int k = 0; temp[k] != '\0'; k++) {
                    if (temp[k] == '#') hasEpsilon = 1;
                    else addToSet(result, temp[k]);
                }
                if (!hasEpsilon) break;
                if (rhs[j + 1] == '\0') addToSet(result, '#');
            }
        }
    }
}

int main(int argc, char *argv[]) {
    char filename[100] = "sampleexp07.txt";
    if (argc > 1) snprintf(filename, sizeof(filename), "%s", argv[1]);

    FILE *fp = fopen(filename, "r");
    if (fp) {
        char line[50];
        while (fgets(line, sizeof(line), fp)) {
            int len = strlen(line);
            while (len > 0 && (line[len - 1] == '\r' || line[len - 1] == '\n' || line[len - 1] == ' ')) line[--len] = '\0';
            if (len > 0) strcpy(productions[n++], line);
        }
        fclose(fp);
    } else {
        strcpy(productions[0], "S->AaAb");
        strcpy(productions[1], "S->BbBa");
        strcpy(productions[2], "A->#");
        strcpy(productions[3], "B->#");
        n = 4;
    }

    printf("GIVEN GRAMMAR (Note: '#' denotes epsilon):\n");
    printf("------------------------------------------\n");
    for (int i = 0; i < n; i++) printf("%s\n", productions[i]);

    printf("\nFIRST SET COMPUTATION:\n");
    printf("---------------------\n");

    char nonTerminals[10] = "";
    for (int i = 0; i < n; i++) {
        char nt = productions[i][0];
        addToSet(nonTerminals, nt);
    }

    for (int i = 0; nonTerminals[i] != '\0'; i++) {
        char firstSet[50] = "";
        findFirst(nonTerminals[i], firstSet);
        printf("FIRST( %c ) = { ", nonTerminals[i]);
        for (int j = 0; firstSet[j] != '\0'; j++) {
            if (firstSet[j] == '#') printf("#(epsilon)");
            else printf("%c", firstSet[j]);
            if (firstSet[j + 1] != '\0') printf(", ");
        }
        printf(" }\n");
    }

    return 0;
}
