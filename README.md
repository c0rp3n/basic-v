# Basic-V

[![Build Status](https://travis-ci.com/c0rp3n/basic-v.svg?token=1eAJNuAjQDrssYuuMWC9&branch=master)](https://travis-ci.com/c0rp3n/basic-v)

Basic V is a compiler for a new subset of Basic to Risc V. The subset is designed around BBC BASIC as well as some incorporations from Visual Basic. The language is designed to be minimal and bloat free to allow it to easily run on up and coming embedded systems using the Risc V architecture.

#### Status
_This project is still under active development and has not yet reached a stable version until v1.0 it is not recommended for any production work as there is currently no guarantee of backwards compatibility and features may be added, removed or changed as the team see fit._

### Design
The project is modularised with each stage of compilation having its own independent compile target as to provide a more stable program and to allow each one to be easily developed independently though with some shared files and data for consistency.

The current modules are:
 - Lexer - Parses a text input and output a series of tokens.
 - Parser - Checks the syntax of the program and generates an AST (Abstract syntax tree).
 - Compiler - Handles assembly code generation from the AST.

## Style guide
[STYLEGUIDE](STYLEGUIDE.md "STYLEGUIDE")

## License
[MIT](LICENSE.md "MIT")
