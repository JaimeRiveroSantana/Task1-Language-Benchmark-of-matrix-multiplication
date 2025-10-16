# Assignment 1: Basic Matrix Multiplication in Different Languages

This repository contains the implementation and benchmarking of the basic \(O(n^3)\) matrix multiplication algorithm in **C**, **Java**, and **Python** for the Big Data course (ULPGC).

##  Structure
- `code/`: Source code for the three implementations
- `data/`: Benchmark results in CSV format
- `paper/`: LaTeX report (`report.tex`)

## How to Run

### C

```c
clang -O2 -o matrix_mult code/matrix_mult.c
./matrix_mult 500 3
```

### Java
```java
javac code/MatrixMult.java
java MatrixMult 500 3
```

### Python
```python
python3 code/matrix_mult.py 500 3
```

##  Results Summary

| Matrix Size (n) | C (s)     | Java (s)  | Python (s) |
|-----------------|-----------|-----------|------------|
| 100             | 0.001843  | 0.001331  | 0.051941   |
| 200             | 0.008965  | 0.006810  | 0.404254   |
| 500             | 0.119080  | 0.082889  | 6.560263   |
| 1000            | 0.956151  | 0.766837  | 55.027762  |

- **C and Java** show highly efficient performance (sub-second for 1000×1000).
- **Python** is 28x–58x slower due to its interpreted nature.
- Execution time scales with $O(n^3)$, as expected.

##  Report
The full analysis is available in [`paper/report.tex`](paper/report.tex).  
Compile with:  
```bash
pdflatex paper/report.tex
```
**Due Date**:

October 20, 2024

**Degree**:

Data Science and Engineering







