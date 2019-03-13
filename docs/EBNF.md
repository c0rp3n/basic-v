# Extended Backus–Naur form

### Program
```ebnf
program = block "." .
```

### Block
```ebnf
block = [ "const" ident "=" number {"," ident "=" number} ";"]
        [ "var" ident {"," ident} ";"]
        { "procedure" ident ";" block ";" } statement .
```

### Statement
```ebnf
statement = [ ident ":=" expression
            | "call" ident
            | "?" ident
            | "!" expression
            | "begin" statement {";" statement } "end"
            | "if" condition "then" statement
            | "while" condition "do" statement ].
```

### Condition
```ebnf
condition = expression ("="|"#"|"<"|"<="|">"|">="|"<<"|">>") expression .
```

### Expression
```ebnf
expression = [ "+"|"-"] term { ("+"|"-") term}.
```

### Term
```ebnf
term = factor {("*"|"/") factor}.
```

### Factor
```ebnf
factor = ident | number | "(" expression ")".
```
