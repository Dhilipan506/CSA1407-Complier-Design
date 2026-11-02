#include <stdio.h>
#include <string.h>
#include <ctype.h>

void checkComment(char *line) {
    int i = 0;
    int len = strlen(line);
    while (line[len - 1] == '\r' || line[len - 1] == '\n') {
        line[--len] = '\0';
    }
    while (isspace(line[i])) i++;

    if (line[i] == '/' && line[i + 1] == '/') {
        printf("Line: \"%s\"\nResult: It is a single-line comment.\n\n", line);
    } else if (line[i] == '/' && line[i + 1] == '*') {
        int foundEnd = 0;
        for (int j = i + 2; j < len - 1; j++) {
            if (line[j] == '*' && line[j + 1] == '/') {
                foundEnd = 1;
                break;
            }
        }
        if (foundEnd)
            printf("Line: \"%s\"\nResult: It is a multi-line comment.\n\n", line);
        else
            printf("Line: \"%s\"\nResult: It is an unclosed comment / start of multi-line comment.\n\n", line);
    } else {
        printf("Line: \"%s\"\nResult: It is NOT a comment.\n\n", line);
    }
}

int main(int argc, char *argv[]) {
    char line[256];
    if (argc > 1) {
        FILE *fp = fopen(argv[1], "r");
        if (!fp) {
            printf("Cannot open file %s\n", argv[1]);
            return 1;
        }
        while (fgets(line, sizeof(line), fp)) {
            checkComment(line);
        }
        fclose(fp);
    } else {
        FILE *fp = fopen("sampleexp02.txt", "r");
        if (fp) {
            printf("Testing with sampleexp02.txt:\n-----------------------------\n");
            while (fgets(line, sizeof(line), fp)) {
                checkComment(line);
            }
            fclose(fp);
        } else {
            printf("Enter a line: ");
            if (fgets(line, sizeof(line), stdin)) {
                checkComment(line);
            }
        }
    }
    return 0;
}
