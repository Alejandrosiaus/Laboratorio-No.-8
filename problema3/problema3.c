#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#define DISPOSITIVO_NULO "NUL"

static double tiempo_actual(void) {
    LARGE_INTEGER frecuencia, contador;
    QueryPerformanceFrequency(&frecuencia);
    QueryPerformanceCounter(&contador);
    return (double)contador.QuadPart / (double)frecuencia.QuadPart;
}
#else
#include <time.h>
#define DISPOSITIVO_NULO "/dev/null"

static double tiempo_actual(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (double)t.tv_sec + (double)t.tv_nsec / 1e9;
}
#endif

void function(int n) {
    int i, j;
    for (i = 1; i <= n / 3; i++) {
        for (j = 1; j <= n; j += 4) {
            printf("Sequence\n");
        }
    }
}

static double medir(int n) {
    long repeticiones = 0;
    double inicio = tiempo_actual();
    double transcurrido = 0.0;
    do {
        function(n);
        repeticiones++;
        transcurrido = tiempo_actual() - inicio;
    } while (transcurrido < 0.05);
    return transcurrido / (double)repeticiones;
}

int main(int argc, char *argv[]) {
    int valores_por_defecto[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    int cantidad = 7;
    int *valores = valores_por_defecto;
    FILE *archivo = NULL;
    int k;

    if (argc > 1) {
        cantidad = argc - 1;
        valores = malloc(sizeof(int) * (size_t)cantidad);
        if (valores == NULL) return 1;
        for (k = 0; k < cantidad; k++) valores[k] = atoi(argv[k + 1]);
    } else {
        archivo = fopen("resultados/problema3.csv", "w");
        if (archivo == NULL) {
            fprintf(stderr, "No se pudo crear resultados/problema3.csv, ejecute desde la raiz del repositorio\n");
            return 1;
        }
        fprintf(archivo, "n,tiempo_segundos\n");
    }

    if (freopen(DISPOSITIVO_NULO, "w", stdout) == NULL) return 1;
    setvbuf(stdout, NULL, _IOFBF, 1 << 20);

    fprintf(stderr, "Problema 3\n");
    fprintf(stderr, "%12s %20s\n", "n", "tiempo (s)");
    for (k = 0; k < cantidad; k++) {
        double tiempo = medir(valores[k]);
        fprintf(stderr, "%12d %20.9f\n", valores[k], tiempo);
        if (archivo != NULL) {
            fprintf(archivo, "%d,%.9f\n", valores[k], tiempo);
            fflush(archivo);
        }
    }

    if (archivo != NULL) fclose(archivo);
    if (argc > 1) free(valores);
    return 0;
}
