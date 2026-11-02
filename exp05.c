#include <stdio.h>

int main(int argc, char *argv[]) {
    char filename[100] = "sampleexp05.txt";
    if (argc > 1) {
        snprintf(filename, sizeof(filename), "%s", argv[1]);
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Cannot open file %s\n", filename);
        return 1;
    }

    int spaces = 0, tabs = 0, newlines = 0;
    char ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == ' ')
            spaces++;
        else if (ch == '\t')
            tabs++;
        else if (ch == '\n')
            newlines++;
    }
    fclose(fp);

    printf("WHITESPACE ANALYSIS FOR: %s\n", filename);
    printf("------------------------------------\n");
    printf("Number of spaces             : %d\n", spaces);
    printf("Number of tabs (\\t)          : %d\n", tabs);
    printf("Number of newlines (\\n)      : %d\n", newlines);
    printf("Total whitespace characters  : %d\n", spaces + tabs + newlines);

    return 0;
}
