# JavaLexer

Java source code lexer. Tokenizes Java code with syntax highlighting and detailed token analysis.

## Features

- Lexical analysis of Java source code
- Colorized syntax highlighting  
- Detailed token listing with positions
- Support for all major Java language constructs

## Build
mkdir build && cd build
cmake ..
make
## Usage
### Colorized output
./Lexer example.java color
### Token list  
./Lexer example.java list
## Output Modes
color - Syntax highlighted code

list - Detailed token table with line/column information
