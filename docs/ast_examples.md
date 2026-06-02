# AST Examples

## Arithmetic

Input:

```text
8*3+1*2
```

AST:

```text
+
├── *
│   ├── 8
│   └── 3
└── *
    ├── 1
    └── 2
```

---

## Comparisons

Input:

```text
1+2<3*4
```

AST:

```text
<
├── +
│   ├── 1
│   └── 2
└── *
    ├── 3
    └── 4
```

---

## Variables

Input:

```text
x+y
```

AST:

```text
+
├── x
└── y
```

---

## Function Calls

Input:

```text
max(1,2)
```

AST:

```text
Call(max)
├── 1
└── 2
```

---

## Nested Function Calls

Input:

```text
max(max(1,2),min(900,1000))
```

AST:

```text
Call(max)
├── Call(max)
│   ├── 1
│   └── 2
└── Call(min)
    ├── 900
    └── 1000
```

---

## Function Calls With Expressions

Input:

```text
max(1+2,3*4)
```

AST:

```text
Call(max)
├── +
│   ├── 1
│   └── 2
└── *
    ├── 3
    └── 4
```

Result:

```text
12
```

---

## Deeply Nested Calls

Input:

```text
max(1,max(2,max(3,4)))
```

AST:

```text
Call(max)
├── 1
└── Call(max)
    ├── 2
    └── Call(max)
        ├── 3
        └── 4
```

Result:

```text
4
```
