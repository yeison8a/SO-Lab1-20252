#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp;
    int count;
    char c;

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }

        // leer bloques de 5 bytes: 4 (int) + 1 (char)
        while (fread(&count, sizeof(int), 1, fp) == 1) {
            if (fread(&c, sizeof(char), 1, fp) != 1) {
                printf("wunzip: file format error\n");
                exit(1);
            }
            for (int j = 0; j < count; j++) {
                putchar(c);
            }
        }

        fclose(fp);
    }

    return 0;
}
