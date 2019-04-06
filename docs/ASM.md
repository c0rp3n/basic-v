# Assembly Generation

## Data and variable declarations
```basic
data constantInteger = 1 << 2
data constantFloat = 3.142
data constantString = "3.142"

dim varInteger = 5 * (2 + 1)
dim varFloat = 5.00
dim varString = "Hello World\n"
```

```asm
.section .text

.section .rodata
constantInteger:
    .word 2
constantFloat:
    .single 3.142
constantString:
    .string "3.142"

.section .data
varInteger:
    .word 15
varFloat:
    .single 5.0
varString:
    .string "Hello World\n"
```

## Loading data and adding data
```asm
.section .text
.globl _start
_start:
    lui a0, constInt
    addi, a0, a0, constInt
    jal ra, puts
2:
    j 2b

.section .rodata
constInt:
    .word 2
```
