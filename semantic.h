#ifndef SEMANTIC
#define SEMANTIC

void show_semantic_error(ERROR_CODE error_code, char * id) {
  printf("\nline %d # %s => %s", line_count, errors[error_code], id);
  exit(1);
}

int find_symbol(char * id) {
  int i;
  for (i = 0; i < sym_table_size; i++) {
    if (strcmp(sym_table[i].name, id) == 0) {
      return i;
    }
  }
  return -1;
}

int load_symbol_address(char * id) {
  int index = find_symbol(id);
  return sym_table[index].address;
}

void add_symbol(char * id, SYM_TYPE sym_type) {
  if (sym_table_size < 20) {
    switch (sym_type) {
    case TPROGRAM:
      add_program(id);
      break;
    case TCONSTANT:
      add_constant(id);
      break;
    case TVARIABLE:
      add_variable(id);
    }
  } else {
    show_error(MAXSYMBOLES_ERROR);
  }
}

void add_program(char * id) {
  sym_table[sym_table_size].type = TPROGRAM;
  strcpy(sym_table[sym_table_size].name, id);
  sym_table_size++;
}

void add_constant(char * id) {
  if (find_symbol(id) == -1) {
    sym_table[sym_table_size].type = TCONSTANT;
    strcpy(sym_table[sym_table_size].name, id);
    sym_table[sym_table_size].address = offset++;
    sym_table_size++;
  } else {
    show_semantic_error(MULTIPLE_ERROR, id);
  }
}

void add_variable(char * id) {
  if (find_symbol(id) == -1) {
    sym_table[sym_table_size].type = TVARIABLE;
    strcpy(sym_table[sym_table_size].name, id);
    sym_table[sym_table_size].address = offset++;
    sym_table_size++;
  } else {
    show_semantic_error(MULTIPLE_ERROR, id);
  }
}

void validate_assignment(char * id) {
  int index = find_symbol(id);
  if (index != -1) {
    SYM_TYPE sym_type = sym_table[index].type;
    switch (sym_table[index].type) {
    case TVARIABLE:
      break;
    case TCONSTANT:
      show_semantic_error(TCONSTANT_ERROR, id);
      break;
    case TPROGRAM:
      show_semantic_error(TPROGRAM_ERROR, id);
    }
  } else {
    show_semantic_error(UNDECLARED_ERROR, id);
  }
}

void validate_operation(char * id) {
  int index = find_symbol(id);
  if (index != -1) {
    SYM_TYPE sym_type = sym_table[index].type;
    if (sym_type == TPROGRAM) {
      show_semantic_error(TPROGRAM_ERROR, id);
    }
  } else {
    show_semantic_error(UNDECLARED_ERROR, id);
  }
}

#endif

