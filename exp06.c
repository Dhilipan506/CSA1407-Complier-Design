#include <stdio.h>
#include <string.h>
#include <ctype.h>

char keywords[32][10] = {
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if",
    "int","long","register","return","short","signed","sizeof","static",
    "struct","switch","typedef","union","unsigned","void","volatile","while"
};

int isKeyword(char *str) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], str) == 0)
            return 1;
    }
    return 0;
}

void validateIdentifier(char *id) {
    int len = strlen(id);
    while (len > 0 && (id[len - 1] == '\r' || id[len - 1] == '\n' || id[len - 1] == ' ')) {
        id[--len] = '\0';
    }
    if (len == 0) {
        printf("Token: \"\" -> INVALID (Empty identifier)\n");
        return;
    }
    if (len > 31) {
        printf("Token: \"%-15s\" -> INVALID (Length exceeds 31 characters limit)\n", id);
        return;
    }
    if (isKeyword(id)) {
        printf("Token: \"%-15s\" -> INVALID (Reserved C keyword)\n", id);
        return;
    }
    if (!isalpha(id[0]) && id[0] != '_') {
        printf("Token: \"%-15s\" -> INVALID (First character must be letter or underscore)\n", id);
        return;
    }
    for (int i = 1; i < len; i++) {
        if (!isalnum(id[i]) && id[i] != '_') {
            printf("Token: \"%-15s\" -> INVALID (Contains invalid character '%c')\n", id, id[i]);
            return;
        }
    }
    printf("Token: \"%-15s\" -> VALID Identifier\n", id);
}

int main(int argc, char *argv[]) {
    char filename[100] = "sampleexp06.txt";
    if (argc > 1) {
        snprintf(filename, sizeof(filename), "%s", argv[1]);
    }
    FILE *fp = fopen(filename, "r");
    if (fp) {
        printf("IDENTIFIER VALIDATION (from %s):\n", filename);
        printf("----------------------------------------------------\n");
        char id[100];
        while (fgets(id, sizeof(id), fp)) {
            validateIdentifier(id);
        }
        fclose(fp);
    } else {
        char id[100];
        printf("Enter an identifier to test: ");
        if (scanf("%99s", id) == 1) {
            validateIdentifier(id);
        }
    }
    return 0;
}
