#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    char inName[100] = "sampleexp03.c";
    char outName[100] = "outputexp03.c";
    if (argc > 1) strcpy(inName, argv[1]);
    if (argc > 2) strcpy(outName, argv[2]);

    FILE *fin = fopen(inName, "r");
    if (!fin) {
        printf("Error opening input file %s\n", inName);
        return 1;
    }
    FILE *fout = fopen(outName, "w");
    if (!fout) {
        printf("Error creating output file %s\n", outName);
        fclose(fin);
        return 1;
    }

    char ch;
    int inSpace = 0;
    int atLineStart = 1;

    printf("PROCESSED OUTPUT (Redundant spaces, tabs, newlines, and comments removed):\n");
    printf("========================================================================\n");

    while ((ch = fgetc(fin)) != EOF) {
        if (ch == '/') {
            char next = fgetc(fin);
            if (next == '/') {
                while ((ch = fgetc(fin)) != EOF && ch != '\n');
                continue;
            } else if (next == '*') {
                while ((ch = fgetc(fin)) != EOF) {
                    if (ch == '*') {
                        if ((ch = fgetc(fin)) == '/') break;
                    }
                }
                continue;
            } else {
                ungetc(next, fin);
            }
        }

        if (ch == ' ' || ch == '\t') {
            if (!inSpace && !atLineStart) {
                putchar(' ');
                fputc(' ', fout);
                inSpace = 1;
            }
            continue;
        }

        if (ch == '\r') continue;

        if (ch == '\n') {
            if (!atLineStart) {
                putchar('\n');
                fputc('\n', fout);
                atLineStart = 1;
                inSpace = 0;
            }
            continue;
        }

        putchar(ch);
        fputc(ch, fout);
        inSpace = 0;
        atLineStart = 0;
    }

    fclose(fin);
    fclose(fout);
    printf("\n\nCleaned code written to %s successfully.\n", outName);
    return 0;
}
