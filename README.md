# Expression Interpreter

A C++ AST-based expression interpreter built as a stepping stone toward implementing a full compiler frontend.

The interpreter tokenizes user input, constructs an Abstract Syntax Tree (AST), visualizes the generated tree structure, and recursively evaluates expressions.

---

## Features

### Arithmetic Expressions

Supported operators:

```text
+
-
*
/
%
^
!
Unary Minus
Unary Plus
```

Examples:

```text
1 + 2 * 3
(1 + 2) * 3
8 * 9 - 70
```

---

### Comparison Operators

Supported operators:

```text
<
>
```

Examples:

```text
x < y
10 > 5
1 + 2 < 3 * 4
```

---

### Variables

Create and use variables interactively:

```text
>>> x = 8
x = 8

>>> y = 2
y = 2

>>> x + y
10
```

---

### Built-in Functions

Supported functions:

```text
max(a,b)
min(a,b)
convertBool(x)
```

Examples:

```text
max(10,20)
min(5,3)
convertBool(0)
convertBool(42)
```

---

### Nested Function Calls

Function calls can be nested arbitrarily.

Example:

```text
max(
    max(1,2),
    min(900,1000)
)
```

Generated AST:

```text
Call(max)
  Call(max)
    1
    2
  Call(min)
    900
    1000
```

---

### Implicit Multiplication

The interpreter automatically inserts multiplication where appropriate.

Examples:

```text
2(3+4)
(1+2)(3+4)
2x
```

become:

```text
2*(3+4)
(1+2)*(3+4)
2*x
```

---

### AST Visualization

Input:

```text
max(1+2,3*4)
```

Generated AST:

```text
Call(max)
  +
    1
    2
  *
    3
    4
```

Result:

```text
12
```

---

## Architecture

```text
User Input
    │
    ▼
Tokenizer
    │
    ▼
Token Stream
    │
    ▼
AST Builder
    │
    ▼
Abstract Syntax Tree
    │
    ▼
Recursive Evaluation
```

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
+
├── 1
└── 2
```

### Function Call

```text
Call(max)
├── 1
└── 2
```

---

## Example Session

```text
>>> x = 8
x = 8

>>> y = 2
y = 2

>>> x < y
0

>>> max(max(1,2),8*9-70)

Call(max)
  Call(max)
    1
    2
  -
    *
      8
      9
    70

2
```

---

## Error Handling

The interpreter detects and reports:

```text
Undefined variables
Division by zero
Mismatched parentheses
Invalid function calls
Incorrect argument counts
Malformed expressions
```

Examples:

```text
Error: Undefined variable: x
Error: Division by zero
Error: Function Error:: Missing ')'
```

---

## Build

Compile:

```bash
g++ -O2 -s parser.cpp -o parser
```

Run:

```bash
./parser
```

---

## Motivation

This project was built to understand:

* Lexical Analysis
* Abstract Syntax Trees
* Expression Parsing
* Recursive Tree Traversal
* Operator Precedence
* Interpreter Design
* Compiler Frontend Architecture

The long-term goal is to use the ideas developed here in a larger custom language and compiler project.

---

## Future Work

* Additional Comparison Operators

```text
<=
>=
==
!=
```

* Logical Operators

```text
&&
||
!
```
