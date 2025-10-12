import time
import random
import sys
import csv
import os

def multiply_matrices(A, B, n):
    C = [[0.0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            total = 0.0
            for k in range(n):
                total += A[i][k] * B[k][j]
            C[i][j] = total
    return C

def fill_random_matrix(n):
    return [[random.random() for _ in range(n)] for _ in range(n)]

def main():
    if len(sys.argv) != 3:
        print(f"Uso: {sys.argv[0]} <n> <repeticiones>")
        sys.exit(1)

    n = int(sys.argv[1])
    reps = int(sys.argv[2])
    random.seed(42)  # Reproducibilidad

    # Crear matrices (fuera del cronometraje)
    A = fill_random_matrix(n)
    B = fill_random_matrix(n)

    times = []
    for r in range(reps):
        start = time.perf_counter()
        C = multiply_matrices(A, B, n)
        end = time.perf_counter()
        elapsed = end - start
        times.append(elapsed)
        print(f"Rep {r + 1}: {elapsed:.6f} s")

    avg = sum(times) / len(times)
    print(f"Promedio: {avg:.6f} s")

    # Guardar en CSV
    file_exists = os.path.isfile('results_python.csv')
    with open('results_python.csv', 'a', newline='') as f:
        writer = csv.writer(f)
        if not file_exists:
            writer.writerow(['language', 'n', 'reps', 'avg_time'])
        writer.writerow(['Python', n, reps, f"{avg:.6f}"])

if __name__ == "__main__":
    main()