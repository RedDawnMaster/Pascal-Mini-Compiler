# Pascal Mini Compiler

This is a mini compiler for a simplified version of the Pascal programming language, implemented in C. The compiler consists of several modules responsible for lexical analysis, parsing, semantic analysis, code generation, interpretation, and file handling. 

## Files

- `declarations.h`: Header file containing declarations of data structures and functions used throughout the compiler.
- `lexer.h`: Header file for the lexical analyzer module.
- `parser.h`: Header file for the parser module.
- `semantic.h`: Header file for the semantic analysis module.
- `generator.h`: Header file for the code generation module.
- `interpreter.h`: Header file for the interpreter module.
- `exporter.h`: Header file for exporting compiled code.
- `importer.h`: Header file for importing code for interpretation.
- `compiler.h`: Header file containing the main compiler logic and includes all other header files.
- `main.c`: Main entry point.

## Grammar

```plaintext
PROGRAM ::= program ID ; BLOCK .
BLOCK ::= CONSTANTS VARIABLES INSTRUCTIONS
CONSTANTS ::= const ID = NUMBER ; { ID = NUMBER ; } | e
VARIABLES ::= var ID { , ID } ; | e
INSTRUCTIONS ::= begin INSTRUCTION { ; INSTRUCTION } end
INSTRUCTION ::= INSTRUCTIONS | ASSIGNMENT | IF | WHILE | WRITE | READ | REPEAT | FOR | CASE | e
ASSIGNMENT ::= ID ASSIGNMENT_OP EXPRESSION
IF ::= if CONDITION then INSTRUCTION [ else INSTRUCTION | e ]
WHILE ::= while CONDITION do INSTRUCTION
WRITE ::= write ( EXPRESSION { , EXPRESSION } )
READ ::= read ( ID { , ID } )
CONDITION ::= EXPRESSION COMPARISON EXPRESSION
ASSIGNMENT_OP ::= := | :=+ | :=- | :=* | :=/
COMPARISON ::= = | <> | < | > | <= | >=
EXPRESSION ::= TERM { ADDSUB_OP TERM }
ADDSUB_OP ::= + | -
TERM ::= FACTOR { MULDIV_OP FACTOR }
MULDIV_OP ::= * | /
FACTOR ::= ID | NUMBER | ( EXPRESSION )
REPEAT ::= repeat INSTRUCTION until CONDITION
FOR ::= for ID := NUMBER [ to | downto ] NUMBER do INSTRUCTION
CASE ::= case ID of NUMBER : INSTRUCTION { NUMBER : INSTRUCTION }  [ else INSTRUCTION | e ] end
COMMENT ::= { * } | // * \n

ID ::= Letter { Letter | Digit }
NUMBER ::= Digit { Digit }
Digit ::= 0|..|9
Letter ::= a|b|..|z|A|..|Z
```

In the grammar provided:

- Non-terminal symbols are symbols that can be expanded into other symbols during parsing. These include `PROGRAM`, `BLOCK`, `CONSTANTS`, and others.

- Terminal symbols are symbols that represent actual tokens in the language, such as keywords (`program`, `const`, `begin`, `end`, etc.), identifiers (`ID`), numbers (`NUMBER`), and operators (`:=`, `+`, `-`, `*`, `/`, etc.).

- `{}` indicates repetition of the enclosed symbols zero or more times. For example, `{ ID = NUMBER ; }` means zero or more occurrences of an identifier followed by an equal sign and a number, separated by semicolons.

- `[]` indicates a choice between the enclosed symbols. For example, `[ to | downto ]` means either the keyword `to` or `downto`.

- `*` within `COMMENT` represents any character or sequence of characters within comments. This notation is used to indicate that comments can contain any text, including whitespace, symbols, and alphanumeric characters. For example, `{ * }` means that comments can contain any sequence of characters enclosed between the `{` and `}` symbols.

- `e` represents the empty string or epsilon.

- `|` represents alternatives or choices. For example, `COMPARISON ::= = | <> | < | > | <= | >=` means that `COMPARISON` can be any of the listed comparison operators.

These symbols and conventions help define the structure of the Pascal language and guide the parsing process in the compiler.

## Usage

Write your Pascal code in `program.pas` located in the `files` folder.

## Notes

- This compiler supports a subset of Pascal features.
- This project is for educational purposes and may not be suitable for production use.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
