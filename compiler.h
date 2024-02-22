#ifndef COMPILER
#define COMPILER

#include "declarations.h"

#include "lexer.h"

#include "parser.h"

#include "semantic.h"

#include "generator.h"

#include "interpreter.h"

#include "exporter.h"

#include "importer.h"

void show_error(ERROR_CODE error_code) {
  printf("\nline %d # %s", line_count, errors[error_code]);
  exit(1);
}

int start(char * file) {
  input_file = fopen(file, "r");
  if (input_file == NULL) {
    perror("error opening file");
    return -1;
  }
  read_character();
  read_token();
  program();
  fclose(input_file);
  save_pcode_to_file();
  load_pcode_from_file(); // in case you want to run pcode directly from a file
  interpret_pcode();
  return 0;
}

#endif

