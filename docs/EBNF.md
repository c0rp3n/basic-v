# Extended Backus–Naur form

The formal language definition for the Basic V containing all of the meta-syntax of the language as well as structured examples of each piece of grammer.

- [Extended Backus–Naur form](#extended-backus%E2%80%93naur-form)
    - [Program](#program)
    - [Block](#block)
    - [Statement](#statement)
      - [Assignment](#assignment)
      - [Function Call](#function-call)
      - [If Statement](#if-statement)
      - [Switch](#switch)
      - [For Loop](#for-loop)
      - [Repeat Until](#repeat-until)
      - [While Loop](#while-loop)
    - [Condition](#condition)
    - [Expression](#expression)
    - [Term](#term)
    - [Factor](#factor)
    - [Function](#function)
    - [Types](#types)


### Program
```ebnf
program = { "def", "sub", identifier, "(", [ identifier, { "," identifier } ], ")", new line },
          block,
          { "sub", identifier, "(", [ identifier, { "," identifier } ], ")", new line, block, "end", "sub", new line } ;
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
block = { "data", identifier, "=", data type, { ",", identifier, "=", data type }, new line
        | "dim", identifier, [ "=", data type ] { ",", identifier, [ "=", data type ] }, new line
        | statement, new line } ;
```
```basic
data constantInteger = 1
dim Var_Hello1 = "Hello", Var_Hellow2

Var_Hellow2 = "World!"
```

### Statement
```ebnf
statement = [ identifier, "=", ( expression | string )
            | function
            | "if", condition, "then",
                ( new line, block, "end", "if"
                | statement )
            | "case", identifier, "of", new line,
                { "when", data types, { ",", data types }, ":", block },
                [ "otherwise", ":", block ], "end", "case"
            | "for", identifier, "=", ( identifier | integer ), "to", ( identifier | integer ),
                ( new line, block, "next", identifier
                | statement )
            | "while", condition, "do",
                ( new line, block, "end", "while"
                | statement )
            ] ;
```

#### Assignment
```basic
dim var = 2
var = 3
```

#### Function Call
```basic
call Void ()
call PrintDoubleVal (2, var)
```

#### If Statement
```basic
dim var = "Hello World"
if var <> "help" then
    ...
end if
```

*Shorthand*
```basic
if var < 2 then print var
```

#### Switch
```basic
dim var = 1
case var of
    when 0: print "Values: 0"
    when 1: print "Values: 1"
    otherwise: pring "Error: val out of range 0,1."
end case
```

#### For Loop
```basic
data var = 5
for i = 0 to var
    ...
next i
```

*Shorthand*
```basic
for i = 1 to 10 print i
```

#### Repeat Until
```basic
dim var = false
repeat
    ...
    done = true
until done
```

#### While Loop
```basic
dim var = 1
while var == 1
    ...
end while
```

### Condition
```ebnf
condition = "!", factor
            | expression, ( "==" ,"<>" | "<" | "<=" | ">" | ">=" ), expression ;
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
var = var + call SomeFunction(2)
```

### Factor
```ebnf
factor = function | identifier | number | "(", expression, ")" ;
```
```basic
dim var = 1 << 3 * (16 / 2)
```

### Function
```ebnf
function = "call", `identifier`, "(", [ expression | string, { ",", expression | string } ], ")"
```
```basic
call Void ()
call PrintDoubleVal (2, var)
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
new line = ? new line characters ? ;
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
