# Parse Tree

## Node
In the diagrams nodes are represented by rectangles. Each node can be connect too two other nodes one for the flow of the program and the other for any branching from that node.

_Node Layout_

![Node](ptree/node.svg)

## Expression
In the diagrams expressions are represented by ellipses. Each expression connects to two other expression but also stores a series of tokens genreally the operator being applied else it shall a the value to be used.

_Expression Layout_

![Expression](ptree/expression.svg)

## Trees

### Assignment example
Here is a simple example of an assignment and some expressiosns in basic five and the example of the generated parse tree.

_Code:_
```basic
dim x = 1 + (2 * 3)
```

_Tree:_

![Example Tree 1](ptree/tree-example-1.svg)
