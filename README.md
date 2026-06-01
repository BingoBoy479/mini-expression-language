# AST-Based Expression Interpreter

A C++ interactive expression language that parses expressions into an Abstract Syntax Tree (AST) and evaluates them.

This project was built as a stepping stone toward implementing a full compiler frontend. Instead of directly evaluating expressions, the interpreter first constructs an AST, making the architecture similar to real language implementations.

---

## Features

### Expressions

Supported operators:

| Operator | Description |
|-----------|------------|
| + | Addition |
| - | Subtraction |
| * | Multiplication |
| / | Division |
| < | Less Than |
| > | Greater Than |

### Variables

```text
x = 10
y = 20
x + y
```

### Parentheses

```text
(1 + 2) * 3
```

### Implicit Multiplication

```text
2(3 + 4)
(1 + 2)(3 + 4)
```

are automatically interpreted as

```text
2 * (3 + 4)
(1 + 2) * (3 + 4)
```

### AST Visualization

Input:

```text
1 + 2 < 3 * 4
```

Generated AST:

```text
<
  +
    1
    2
  *
    3
    4
```

### Interactive REPL

```text
>>> x = 8
x = 8

>>> y = 2
y = 2

>>> x < y
0

>>> x + 10
18
```

---

## Example

### Input

```text
1+2<3*4
```

### AST

```text
<
  +
    1
    2
  *
    3
    4
```

### Evaluation

```text
1
```

---

## Architecture

```text
Input
  |
  v
Tokenizer
  |
  v
Token Stream
  |
  v
Stack-Based AST Builder
  |
  v
Abstract Syntax Tree
  |
  v
Recursive Evaluation
```

---

## Internal Design

The parser uses:

- Operand Stack
- Operator Stack
- Precedence-Based Reduction

to construct an AST.

Example:

```text
8 * 3 + 1 * 2
```

becomes

```text
+
├── *
│   ├── 8
│   └── 3
└── *
    ├── 1
    └── 2
```

before evaluation.

---

## AST Node Types

### Number

```text
42
```

### Variable

```text
x
```

### Binary Expression

```text
x + y
```

```text
+
├── x
└── y
```

---

## Build

Compile:

```bash
g++ -std=c++17 parser.cpp -o parser
```

Run:

```bash
./parser
```

---

## Motivation

This project was created to understand:

- Abstract Syntax Trees
- Expression Parsing
- Operator Precedence
- Recursive Tree Traversal
- Interpreter Design
- Compiler Frontend Architecture

The code serves as a prototype for a larger compiler project currently under development.

---

## Future Work

- Unary Operators
- Function Calls
- Nested Function Calls
- Additional Comparison Operators

```text
<=
>=
==
!=
```

- Logical Operators

```text
&&
||
!
```



---

## Sample Session

```text
>>> x = 8
x = 8

>>> y = 2
y = 2

>>> x < y
<
  x
  y
0

>>> 1+2<3*4
<
  +
    1
    2
  *
    3
    4
1
```

---
