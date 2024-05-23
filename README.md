# System Programming - Ex2 - By Uriel Shapiro

## Makefile Documentation

### `all`

- Compiles the `demo` and `test` targets, which are the primary executables for running the program and tests.

### `run`

- Executes the `demo` target, which is the main program.

### `test`

- Compiles the `TestCounter.o`, `Test.o`, and other object files into the `test` executable and runs it.

### `tidy`

- Runs `clang-tidy` on the source files with a set of predefined checks for bugs, performance, portability, and readability. It treats warnings as errors except for those explicitly allowed.

### `valgrind`

- Runs Valgrind on both the `demo` and `test` executables to detect memory leaks and other memory-related issues.

### `clean`

- Removes all generated object files and executables, cleaning up the build directory.

## Usage

To run the demo use:
```bash
make run
```

To run the tests, use:
```bash
make test
```


# Operators on Graphs

In this exercise we needed to overload all of the following operators so that they would work on Graph objects.

## Equality/Inequality operators

**`==`**: First, we check if the graphs are empty, if they are - we call them equal.
If not, we check them as said in the exercise instructions: Check if their edges are the same, and if g1 <= g2 and g2 <= g1.
At the end I return the result of an OR gate between the two conditions.

**`!=`**: The opposite of **`==`**.

## Unary Operations

**`+`**: returns the original graph.
**`-`**: returns the graph * (-1) as a scalar.
Prefix **`++`**: adds 1 to each edge of the graph (which is not 0) and returns a reference to the graph.
Postfix **`++`**: Saves the original graph in a temporary object. Increment the graph edges using the prefix ++. returns the temporary graph (the graph before the increment).
Postfix **`--`** and Prefix **`--`** are with the same logic as Prefix and Postfix **`++`**.

## Binary Operations
**`+`**: The function first check if the graphs are of the same size.
If the are, it creates a new graph using the sum of each 2 edges of the graphs.

**`-`**: Exactly the same logic as the **`+`**.

**`*`** By scalar: If the scalar is 0, we return a graph with no edges (zero matrix).
If the scalar is 1, we return the same graph.
Otherwise, we create a new graph which is the original graph multiplied by the scalar.

**`/`** By scalar: If the scalar is 0, we throw exception.
Otherwise, we do exactly the same as multiplying by a scalar.

**`*`** By a Graph: Because the graph adjacency matrix is a squere matrix, we check if both adjacency matrices are of the same order - so that we could multiply them.
If they are of the same order, We create a new matrix which is the multiplication of the 2 matrices.
Afterwards, we return the graph which that adjacency matrix represents.

### X= Operations
Each operation uses the same logic:
***`Graph1 X= Graph2 -> Graph1 = Graph1 X Graph2`*** For X an operator $`\in`$ { * , + , -, / }

### Comparison Operators
In order to compate 2 graphs we use 2 functions:
* ***`GridSearch`***: Checks if Graph g1 is contained in the adjacency matrix of Graph g2 (Using an optimized $`O(n^4)`$ grid search).
* ***`compare`***: This function returns a java like comparison. It uses the comparison logic from the instructions and returns 0 if the graphs are totally equal (same adjacency matrices), 1 if g1 > g2. And -1 if g2 > g1.

Each comparison operator uses the result of the ***`compare`*** function.

### ***`<<`*** Operator
The ***`<<`*** operator prints the adjacency matrix of the graphs using a given reference to an ostream.
