#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }

    // Iterar sobre cada archivo pasado como argumento
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");

        // Si fopen falla, imprimir mensaje de error y salir con estado 1
        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            return 1;
        }

        // Leer línea por línea e imprimir
        char buffer[4096]; // Tamaño del buffer suficientemente grande para líneas largas
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }

        fclose(fp); 
    }

    return 0; 
}
