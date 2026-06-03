# Mini Expression Language

A small expression language interpreter written in C++ that supports arithmetic, variables, function calls, assignment expressions, logical operators, AST generation, and evaluation.

This project was built as a step toward implementing a complete compiler frontend. The focus was on understanding lexing, parsing, abstract syntax trees, operator precedence, associativity, symbol tables, and basic semantic analysis.

---

## Features

### Arithmetic Operators

```text
+  -  *  /  %  ^
```

Examples:

```text
2 + 3 * 4
(5 + 7) * 2
2 ^ 3 ^ 2
```

---

### Unary Operators

```text
+x
-x
!x
```

Examples:

```text
-5
--5
!(1 < 2)
```

---

### Comparison Operators

```text
<
>
<=
>=
```

Examples:

```text
x < y
x >= 10
```

---

### Equality Operators

```text
==
!=
```

Examples:

```text
x == y
x != 0
```

---

### Logical Operators

```text
&&
||
```

Examples:

```text
x > 0 && y > 0
x == 5 || y == 5
```

---

### Assignment Expressions

Assignments are implemented as expressions and are right-associative.

Examples:

```text
x = 5
y = x + 10
a = b = c = 5
x = (y = 7) + 2
```

---

### Variables

Variables are stored in a symbol table and can be used in subsequent expressions.

Example:

```text
x = 5
x + 10
```

---

### Built-in Functions

Currently supported:

```text
max(a,b)
min(a,b)
convertBool(x)
```

Examples:

```text
max(10,20)
min(5,2)
convertBool(0)
```

---

### Implicit Multiplication

The parser automatically inserts multiplication in cases such as:

```text
2(3+4)
2x
(1+2)(3+4)
```

which are interpreted as:

```text
2*(3+4)
2*x
(1+2)*(3+4)
```

---

## Implementation Overview

### Lexer

The lexer converts source text into tokens.

Example:

```text
x >= 5 && y < 10
```

becomes:

```text
Identifier(x)
Operator(>=)
Number(5)
Operator(&&)
Identifier(y)
Operator(<)
Number(10)
```

---

### Parser

The parser uses a stack-based operator precedence algorithm inspired by the shunting-yard algorithm to construct an Abstract Syntax Tree (AST).

The parser supports:

* Operator precedence
* Left associativity
* Right associativity
* Unary operators
* Function calls
* Assignment expressions

---

### AST

Example:

Input:

```text
x = (y = 7) + 2
```

AST:

```text
=
├── x
└── +
    ├── =
    │   ├── y
    │   └── 7
    └── 2
```

---

### Evaluation

The AST is recursively evaluated.

Features include:

* Variable lookup
* Function evaluation
* Assignment evaluation
* Arithmetic evaluation
* Logical evaluation
* Basic semantic checks

Example semantic error:

```text
5 = x
```

Output:

```text
Error: Left side of assignment must be a variable
```

---

## Example Session

```text
>>> x = 5
5

>>> y = x + 10
15

>>> x >= 3 && y <= 20
1

>>> max(x,y)
15

>>> x = (y = 7) + 2
9

>>> x
9

>>> y
7
```

---

## Concepts Learned

This project was built to explore compiler construction concepts including:

* Lexical analysis
* Parsing
* Abstract Syntax Trees
* Operator precedence
* Associativity
* Recursive evaluation
* Symbol tables
* Semantic checks
* Expression languages

---


## Motivation

This project serves as a learning platform for understanding how programming languages and compiler frontends are implemented. It is intended as a stepping stone toward building a complete compiler.
