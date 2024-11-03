# N-Queens Parallel Implementation Comparison

This project compares the parallel implementations of the N-Queens problem using **Pthreads** and **OpenMP**. The N-Queens problem is a classic combinatorial challenge, and by implementing it with different parallel programming models, we aim to evaluate performance and efficiency.

## Overview

The N-Queens problem involves placing N queens on an N×N chessboard such that no two queens threaten each other. This project implements parallel solutions for the N-Queens problem using:

1. **Pthreads** (POSIX threads)
2. **OpenMP**

We will compare these approaches based on performance, scalability, and ease of implementation.

## How to Run

The project includes a `Makefile` that compiles the source code, runs the executables and show the results. The following sections describe how to run the different implementations.

### Serialized Version

To run the serialized version of the N-Queens problem, run the following commands:

```bash
make run
```

### Pthreads

To run the Pthreads implementation, run the following commands:
    
```bash
make run_pthreads
```

### OpenMP

To run the OpenMP implementation, run the following commands:
    
```bash
make run_openmp
```

### Clean

To clean the executables, run the following commands:

```bash
make clean
```
