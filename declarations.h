#ifndef DECLARATIONS
#define DECLARATIONS

#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <string.h>

#define MAXID 20
#define MAXNUMBER 10
#define MAXSYMBOLES 20
#define MAXINSTRUCTIONS 200
#define MAXMEMORY 200
#define MAXCASE 15

// enums

// tokens

typedef enum {
  // keywords
  PROGRAM_TOKEN,
  BEGIN_TOKEN,
  END_TOKEN,
  CONST_TOKEN,
  VAR_TOKEN,
  IF_TOKEN,
  THEN_TOKEN,
  ELSE_TOKEN,
  WHILE_TOKEN,
  DO_TOKEN,
  REPEAT_TOKEN,
  UNTIL_TOKEN,
  FOR_TOKEN,
  TO_TOKEN,
  DOWNTO_TOKEN,
  CASE_TOKEN,
  OF_TOKEN,
  WRITE_TOKEN,
  READ_TOKEN,

  // special symbols
  SC_TOKEN,
  PT_TOKEN,
  TP_TOKEN,
  CO_TOKEN,
  LP_TOKEN,
  RP_TOKEN,
  LE_TOKEN,
  GE_TOKEN,
  LS_TOKEN,
  GT_TOKEN,
  ASG_TOKEN,
  ASGADD_TOKEN,
  ASGSUB_TOKEN,
  ASGMUL_TOKEN,
  ASGDIV_TOKEN,
  EQUAL_TOKEN,
  DIFF_TOKEN,
  ADD_TOKEN,
  SUB_TOKEN,
  MUL_TOKEN,
  DIV_TOKEN,

  // other
  NUMBER_TOKEN,
  ID_TOKEN,
  EOF_TOKEN,
}
TOKEN_CODE;

// error codes

typedef enum {
  UNRECOGNISED_ERROR,
  MAXID_ERROR,
  MAXNUMBER_ERROR,
  PROGRAM_ERROR,
  BEGIN_ERROR,
  END_ERROR,
  IF_ERROR,
  THEN_ERROR,
  WHILE_ERROR,
  DO_ERROR,
  REPEAT_ERROR,
  UNTIL_ERROR,
  FOR_ERROR,
  CASE_ERROR,
  OF_ERROR,
  WRITE_ERROR,
  READ_ERROR,
  SC_ERROR,
  PT_ERROR,
  TP_ERROR,
  LP_ERROR,
  RP_ERROR,
  ASG_ERROR,
  EQUAL_ERROR,
  NUMBER_ERROR,
  ID_ERROR,
  EOF_ERROR,
  COMMENT_ERROR,
  SYNTAX_ERROR,
  MULTIPLE_ERROR,
  UNDECLARED_ERROR,
  TPROGRAM_ERROR,
  TCONSTANT_ERROR,
  MAXSYMBOLES_ERROR,
  MAXINSTRUCTIONS_ERROR,
  MNEMONIC_ERROR,
}
ERROR_CODE;

// types of symbols

typedef enum {
  TPROGRAM,
  TCONSTANT,
  TVARIABLE,
}
SYM_TYPE;

// mnemonics

typedef enum {
  ADD,
  SUB,
  MUL,
  DIV,
  EQL,
  NEQ,
  GTR,
  LSS,
  GEQ,
  LEQ,
  PRN,
  INN,
  INT,
  LDI,
  LDA,
  LDV,
  STO,
  BRN,
  BZE,
  HLT
}
MNEMONIC;

// structures

// token

typedef struct {
  TOKEN_CODE code;
  char name[MAXID];
  int value;
}
TOKEN;

// symbols table entry

typedef struct {
  char name[MAXID];
  SYM_TYPE type;
  int address;
}
SYM_ENTRY;

// instruction

typedef struct {
  MNEMONIC mnemonic;
  int input;
}
INSTRUCTION;

// function prototypes

// lexer
char read_character();
void read_word();
void read_number();
void read_special_symbol();
void read_token();
void skip_cmts_ws(); // skip comments and whitespaces
void skip_cmts(int divToken);

// parser
void test_symbol(TOKEN_CODE token_code, ERROR_CODE error_code);
void program();
void block();
void constants();
void variables();
void instructions();
void instruction();
void assignment();
void if_();
void while_();
void write();
void read();
void condition();
int assignment_op();
int comparison();
void expression();
int addsub_op();
void term();
int muldiv_op();
void factor();
void repeat();
void for_();
void case_();

// semantic
void show_semantic_error(ERROR_CODE error_code, char * id);
int find_symbol(char * id);
int load_symbol_address(char * id);
void add_symbol(char * id, SYM_TYPE sym_type);
void add_program(char * id);
void add_constant(char * id);
void add_variable(char * id);
void validate_assignment(char * id);
void validate_operation(char * id);

// generator
void generate_one(MNEMONIC mnemonic);
void generate_two(MNEMONIC mnemonic, int input);

// interpreter
void interpret_pcode();
void interpret_instruction(INSTRUCTION instruction);

// exporter
void save_pcode_to_file();
void save_instruction(INSTRUCTION instruction);

// importer
void load_pcode_from_file();
void load_instruction(char * instruction);

// compiler
void show_error(ERROR_CODE error_code);
int start(char * file);

// global variables

FILE * input_file;
FILE * output_file;

TOKEN current_token;
TOKEN previous_token;

char current_character;

SYM_ENTRY sym_table[MAXSYMBOLES];
INSTRUCTION pcode[MAXINSTRUCTIONS];
int case_brn[MAXCASE];
int stack[MAXMEMORY];

int line_count = 1;
int sym_table_size = 0;
int case_brn_size = 0;
int offset = 0;
int pc = 0; // program counter
int sp = 0; // stack pointer

// error messages

const char * errors[] = {
  "LEXICAL ERROR: unrecognized character",
  "LEXICAL ERROR: maximum identifier length exceeded",
  "LEXICAL ERROR: maximum number length exceeded",
  "SYNTAX ERROR: PROGRAM expected",
  "SYNTAX ERROR: BEGIN expected",
  "SYNTAX ERROR: END expected",
  "SYNTAX ERROR: IF expected",
  "SYNTAX ERROR: THEN expected",
  "SYNTAX ERROR: WHILE expected",
  "SYNTAX ERROR: DO expected",
  "SYNTAX ERROR: REPEAT expected",
  "SYNTAX ERROR: UNTIL expected",
  "SYNTAX ERROR: FOR expected",
  "SYNTAX ERROR: CASE expected",
  "SYNTAX ERROR: OF expected",
  "SYNTAX ERROR: WRITE expected",
  "SYNTAX ERROR: READ expected",
  "SYNTAX ERROR: SC expected",
  "SYNTAX ERROR: PT expected",
  "SYNTAX ERROR: TP expected",
  "SYNTAX ERROR: LP expected",
  "SYNTAX ERROR: RP expected",
  "SYNTAX ERROR: ASG expected",
  "SYNTAX ERROR: EQUAL expected",
  "SYNTAX ERROR: NUMBER expected",
  "SYNTAX ERROR: ID expected",
  "SYNTAX ERROR: EOF expected",
  "SYNTAX ERROR: end of comment } expected",
  "SYNTAX ERROR: incorrect syntax",
  "SEMANTIC ERROR: identifier already declared",
  "SEMANTIC ERROR: undeclared identifier",
  "SEMANTIC ERROR: program identifier cannot be used",
  "SEMANTIC ERROR: constant cannot be assigned",
  "GENERATOR ERROR: maximum symboles size reached",
  "GENERATOR ERROR: maximum instruction size reached",
  "GENERATOR ERROR: unrecognized mnemonic",
};

#endif

