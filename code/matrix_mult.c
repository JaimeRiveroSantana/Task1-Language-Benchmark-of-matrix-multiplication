#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void multiply_matrices(double** A, double** B, double** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

double** allocate_matrix(int n) {
    double** mat = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        mat[i] = (double*)malloc(n * sizeof(double));
    }
    return mat;
}

void free_matrix(double** mat, int n) {
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}

void fill_random_matrix(double** mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <n> <repeticiones>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int reps = atoi(argv[2]);
    srand(42);

    double** A = allocate_matrix(n);
    double** B = allocate_matrix(n);
    double** C = allocate_matrix(n);
    fill_random_matrix(A, n);
    fill_random_matrix(B, n);

    double* times = malloc(reps * sizeof(double));
    struct timespec start, end;

    for (int r = 0; r < reps; r++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        multiply_matrices(A, B, C, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        times[r] = elapsed;
        printf("Rep %d: %.6f s\n", r + 1, elapsed);
    }

    double sum = 0.0;
    for (int r = 0; r < reps; r++) sum += times[r];
    double avg = sum / reps;
    printf("Promedio: %.6f s\n", avg);

    FILE* f = fopen("results_c.csv", "a");
    if (f) {
        if (ftell(f) == 0) fprintf(f, "language,n,reps,avg_time\n");
        fprintf(f, "C,%d,%d,%.6f\n", n, reps, avg);
        fclose(f);
    }

    free(times);
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);
    return 0;
}
