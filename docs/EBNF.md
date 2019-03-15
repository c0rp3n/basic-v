# Extended Backus–Naur form

### Program
```ebnf
program = { "def", "sub", identifier, "(", [ identifier, { "," identifier } ], ")", white space },
          block,
          { "sub", identifier, white space, block, "end", "sub", white space } ;
```
```basic
def sub PrintVal (num)

...

sub PrintVal (num)
    print num
end sub
```

### Block
```ebnf
block = { "data", identifier, "=", data type, { ",", identifier, "=", data type }, white space
        | "dim", identifier, [ "=", data type ] { ",", identifier, [ "=", data type ] }, white space
        | statement, white space } ;
```
```basic
data constantInteger = 1
dim Var_Hello1 = "Hello", Var_Hellow2

Var_Hellow2 = "World!"
```

### Statement
```ebnf
statement = [ identifier, "=", expression
            | "call", identifier
            | "!", expression
            | "for", identifier "=" ( identifier | integer ) to ( identifier | integer )
            | "if", condition, "then", statement
            | "while", condition, "do", statement ] ;
```
```basic
dim var = 2

var = 3
call PrintDoubleVal (var)
if !(var <> 2) then print var

for i = 0 to var
    ...
next i
```

### Condition
```ebnf
condition = expression, ( "<>" | "<" | "<=" | ">" | ">=" ), expression ;
```
```basic
data val = 1
if val <= 1 then
    ...
end if
```

### Expression
```ebnf
expression = [ "+" | "-" ], term, { ( "+" | "-" ), term } ;
```
```basic
dim var = 1 + (4 - 2)
```

### Term
```ebnf
term = factor, { ( "*" | "/" | "<<" | ">>" ), factor } ;
```
```basic
dim var = 2 * 3
var = var / 2
var = var << var
```

### Factor
```ebnf
factor = identifier | number | "(", expression, ")" ;
```
```basic
dim var = 1 << 3 * (16 / 2)
```

### Types
```ebnf
letter = "A" | "B" | "C" | "D" | "E" | "F" | "G"
       | "H" | "I" | "J" | "K" | "L" | "M" | "N"
       | "O" | "P" | "Q" | "R" | "S" | "T" | "U"
       | "V" | "W" | "X" | "Y" | "Z" | "a" | "b"
       | "c" | "d" | "e" | "f" | "g" | "h" | "i"
       | "j" | "k" | "l" | "m" | "n" | "o" | "p"
       | "q" | "r" | "s" | "t" | "u" | "v" | "w"
       | "x" | "y" | "z" ;
```

```ebnf
digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
```

```ebnf
white space = ? white space characters ? ;
```

```ebnf
all characters = ? all visible characters ? ;
```

```ebnf
identifier = letter, { letter | digit | "_" } ;
```

```ebnf
integer = [ "-" ], digit, { digit } ;
```

```ebnf
real = [ "-" ], digit, { digit }, ".", "digit", { digit } ;
```

```ebnf
string = '"' , { all characters - '"' }, '"' ;
```

```ebnf
number = integer | real ;
```

```ebnf
data types = integer | real | string ;
```
