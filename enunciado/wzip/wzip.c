#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp;
    int count = 0;
    int c;
    char prev = '\0';
    int first = 1;  // bandera para la primera iteración

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        while ((c = fgetc(fp)) != EOF) {
            if (first) {
                prev = (char)c;
                count = 1;
                first = 0;
            } else if ((char)c == prev) {
                count++;
            } else {
                fwrite(&count, sizeof(int), 1, stdout);
                fwrite(&prev, sizeof(char), 1, stdout);
                prev = (char)c;
                count = 1;
            }
        }
        fclose(fp);
    }

    // Escribir el último bloque acumulado
    if (!first) {
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&prev, sizeof(char), 1, stdout);
    }

    return 0;
}
