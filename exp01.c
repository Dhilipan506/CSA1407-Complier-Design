#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>' || ch == '%');
}

int main(int argc, char *argv[]) {
    char filename[100] = "sampleexp01.c";
    if (argc > 1) {
        strcpy(filename, argv[1]);
    }
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file %s\n", filename);
        return 1;
    }

    char ch, buffer[32];
    int idx = 0;

    printf("LEXICAL ANALYSIS RESULT:\n");
    printf("------------------------\n");

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '/') {
            char next = fgetc(fp);
            if (next == '/') {
                while ((ch = fgetc(fp)) != EOF && ch != '\n');
                continue;
            } else if (next == '*') {
                while ((ch = fgetc(fp)) != EOF) {
                    if (ch == '*') {
                        if ((ch = fgetc(fp)) == '/') break;
                    }
                }
                continue;
            } else {
                ungetc(next, fp);
            }
        }

        if (ch == ' ' || ch == '\t' || ch == '\n') {
            continue;
        }

        if (isalpha(ch) || ch == '_') {
            idx = 0;
            buffer[idx++] = ch;
            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_')) {
                if (idx < 31) buffer[idx++] = ch;
            }
            buffer[idx] = '\0';
            ungetc(ch, fp);
            if (isKeyword(buffer))
                printf("Keyword    : %s\n", buffer);
            else
                printf("Identifier : %s\n", buffer);
        } else if (isdigit(ch)) {
            idx = 0;
            buffer[idx++] = ch;
            while ((ch = fgetc(fp)) != EOF && (isdigit(ch) || ch == '.')) {
                if (idx < 31) buffer[idx++] = ch;
            }
            buffer[idx] = '\0';
            ungetc(ch, fp);
            printf("Constant   : %s\n", buffer);
        } else if (isOperator(ch)) {
            char next = fgetc(fp);
            if ((ch == '+' && next == '+') || (ch == '-' && next == '-') ||
                (ch == '=' && next == '=') || (ch == '<' && next == '=') ||
                (ch == '>' && next == '=') || (ch == '!' && next == '=')) {
                printf("Operator   : %c%c\n", ch, next);
            } else {
                ungetc(next, fp);
                printf("Operator   : %c\n", ch);
            }
        } else if (ch == '"') {
            idx = 0;
            buffer[idx++] = ch;
            while ((ch = fgetc(fp)) != EOF && ch != '"') {
                if (idx < 30) buffer[idx++] = ch;
            }
            buffer[idx++] = '"';
            buffer[idx] = '\0';
            printf("Literal    : %s\n", buffer);
        }
    }

    fclose(fp);
    return 0;
}
