#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    char *searchterm = argv[1];
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Caso: leer desde stdin si no hay archivos
    if (argc == 2) {
        while ((read = getline(&line, &len, stdin)) != -1) {
            if (strstr(line, searchterm) != NULL) {
                printf("%s", line);
            }
        }
    } else {
        // Leer archivos
        for (int i = 2; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                exit(1);
            }

            while ((read = getline(&line, &len, fp)) != -1) {
                if (strstr(line, searchterm) != NULL) {
                    printf("%s", line);
                }
            }

            fclose(fp);
        }
    }

    free(line);
    return 0;
}
