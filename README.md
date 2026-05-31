# Expression Parser and AST Evaluator

A C++ project that parses arithmetic expressions into an Abstract Syntax Tree (AST) using a stack-based parsing algorithm and recursively evaluates the resulting tree.

This project was created as a learning step toward building a complete programming language compiler.

---

## Features

- Multi-digit integer support
- Operator precedence handling
- Parentheses support
- Implicit multiplication

Examples:

```text
2(3+4)
(1+2)(3+4)
5(2+3)*4
```

- AST generation
- Recursive AST evaluation
- Error handling

```text
Division by zero
Mismatched parentheses
Unknown tokens
```

---

## Supported Operators

| Operator | Meaning |
|-----------|----------|
| + | Addition |
| - | Subtraction |
| * | Multiplication |
| / | Division |

---

## Examples

### Input

```text
8*3+1*2
```

### Generated AST

```text
+
  *
    8
    3
  *
    1
    2
```

### Result

```text
26
```

---

### Input

```text
(1+2)*3
```

### Generated AST

```text
*
  +
    1
    2
  3
```

### Result

```text
9
```

---

## Architecture

```text
Input String
      |
      v
  Tokenizer
      |
      v
 Token Stream
      |
      v
 Stack-Based Parser
      |
      v
      AST
      |
      v
 Recursive Evaluation
      |
      v
    Result
```

---

## Concepts Used

- Abstract Syntax Trees (AST)
- Stack-Based Parsing
- Shunting Yard Inspired Parsing
- Recursive Tree Traversal
- Expression Evaluation
- Dynamic Memory Management

---

## Future Work

- Variables
- Unary Operators
- Floating Point Numbers
- Function Calls
- Compiler Integration

---

## Build

```bash
g++ -std=c++17 main.cpp -o parser
```

Run:

```bash
./parser
```

---

## Motivation

This project was built to understand how compilers transform source code into structured representations before semantic analysis and code generation.
