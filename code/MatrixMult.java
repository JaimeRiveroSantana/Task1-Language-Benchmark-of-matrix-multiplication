import java.io.*;
import java.util.*;

public class MatrixMult {
    public static double[][] multiply(double[][] A, double[][] B, int n) {
        double[][] C = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double sum = 0.0;
                for (int k = 0; k < n; k++) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = sum;
            }
        }
        return C;
    }

    public static double[][] fillRandomMatrix(int n, Random rand) {
        double[][] mat = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mat[i][j] = rand.nextDouble();
            }
        }
        return mat;
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Uso: java MatrixMult <n> <repeticiones>");
            System.exit(1);
        }

        int n = Integer.parseInt(args[0]);
        int reps = Integer.parseInt(args[1]);
        Random rand = new Random(42); // Semilla fija

        double[][] A = fillRandomMatrix(n, rand);
        double[][] B = fillRandomMatrix(n, rand);

        double[] times = new double[reps];
        for (int r = 0; r < reps; r++) {
            long start = System.nanoTime();
            double[][] C = multiply(A, B, n);
            long end = System.nanoTime();
            double elapsed = (end - start) / 1_000_000_000.0; // nanoseg → seg
            times[r] = elapsed;
            System.out.printf("Rep %d: %.6f s%n", r + 1, elapsed);
        }

        double sum = 0.0;
        for (double t : times) sum += t;
        double avg = sum / reps;
        System.out.printf("Promedio: %.6f s%n", avg);

        // Guardar en CSV
        boolean fileExists = new File("results_java.csv").exists();
        try (PrintWriter pw = new PrintWriter(new FileWriter("results_java.csv", true))) {
            if (!fileExists) {
                pw.println("language,n,reps,avg_time");
            }
            pw.printf("Java,%d,%d,%.6f%n", n, reps, avg);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
