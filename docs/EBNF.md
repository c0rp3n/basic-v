# Extended Backus–Naur form

### Program
```ebnf
program = block;
```

### Block
```ebnf
block = [ "def" "sub" identifier ; ]
        [ "data" identifier "=" data type { "," identifier "=" data type } ]
        [ "dim" identifier [ "=" data type ] { "," identifier [ "=" data type ] } ]
        { "sub" identifier ";" block ";" } statement ;
```
Example Basic V code.
```basic
data constantInteger = 1
dim Var_String1 = "Hello World!"
```

### Statement
```ebnf
statement = [ identifier "=" expression
            | "call" identifier
            | "?" identifier
            | "!" expression
            | "begin" statement {";" statement } "end"
            | "if" condition "then" statement
            | "while" condition "do" statement ] ;
```

### Condition
```ebnf
condition = expression ( "=" | "<" | "<=" | ">" | ">=" | "<<" | ">>" ) expression ;
```

### Expression
```ebnf
expression = [ "+" | "-" ] term { ( "+" | "-" ) term } ;
```

### Term
```ebnf
term = factor { ( "*" | "/" ) factor } ;
```

### Factor
```ebnf
factor = identifier | number | "(" expression ")" ;
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
