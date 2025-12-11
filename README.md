
# Parallel Permutations Generator

This project implements a parallel backtracking algorithm to generate permutations for the set `{1...n}` using C processes.

It distributes the workload among child processes created via `fork()`, and aggregates results in the parent process using `pipe()` communication.

## Requirements
* Unix-based OS (Linux, macOS, WSL).
* GCC compiler.

## Usage

1. **Build:**
   ```bash
   gcc main.c -o backtrack_fork
````

2.  **Run:**

    ```bash
    ./backtrack_fork
    ```

3.  **Input:**
    Enter the value for `n` when prompted (recommended `n <= 5` for testing).

## Files

  * `main.c`: Complete source code.
