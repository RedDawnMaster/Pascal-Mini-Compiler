#ifndef PARSER
#define PARSER

void test_symbol(TOKEN_CODE token_code, ERROR_CODE error_code) {
  if (current_token.code == token_code) {
    read_token();
  } else {
    show_error(error_code);
  }
}

void program() {
  test_symbol(PROGRAM_TOKEN, PROGRAM_ERROR);
  test_symbol(ID_TOKEN, ID_ERROR);
  add_symbol(previous_token.name, TPROGRAM);
  test_symbol(SC_TOKEN, SC_ERROR);
  block();
  test_symbol(PT_TOKEN, PT_ERROR);
  test_symbol(EOF_TOKEN, EOF_ERROR);
  generate_one(HLT);
}

void block() {
  constants();
  variables();
  pcode[0].mnemonic = INT;
  pcode[0].input = offset;
  instructions();
}

void constants() {
  switch (current_token.code) {
  case CONST_TOKEN:
    read_token();
    test_symbol(ID_TOKEN, ID_ERROR);
    add_symbol(previous_token.name, TCONSTANT);
    generate_two(LDA, load_symbol_address(previous_token.name));
    test_symbol(EQUAL_TOKEN, EQUAL_ERROR);
    test_symbol(NUMBER_TOKEN, NUMBER_ERROR);
    generate_two(LDI, previous_token.value);
    generate_one(STO);
    test_symbol(SC_TOKEN, SC_ERROR);
    while (current_token.code == ID_TOKEN) {
      read_token();
      add_symbol(previous_token.name, TCONSTANT);
      generate_two(LDA, load_symbol_address(previous_token.name));
      test_symbol(EQUAL_TOKEN, EQUAL_ERROR);
      test_symbol(NUMBER_TOKEN, NUMBER_ERROR);
      generate_two(LDI, previous_token.value);
      generate_one(STO);
      test_symbol(SC_TOKEN, SC_ERROR);
    }
    break;
  case VAR_TOKEN:
    break;
  case BEGIN_TOKEN:
    break;
  default:
    show_error(SYNTAX_ERROR);
  }
}

void variables() {
  switch (current_token.code) {
  case VAR_TOKEN:
    read_token();
    test_symbol(ID_TOKEN, ID_ERROR);
    add_symbol(previous_token.name, TVARIABLE);
    while (current_token.code == CO_TOKEN) {
      read_token();
      test_symbol(ID_TOKEN, ID_ERROR);
      add_symbol(previous_token.name, TVARIABLE);
    }
    test_symbol(SC_TOKEN, SC_ERROR);
    break;
  case BEGIN_TOKEN:
    break;
  default:
    show_error(SYNTAX_ERROR);
  }
}

void instructions() {
  test_symbol(BEGIN_TOKEN, BEGIN_ERROR);
  instruction();
  while (current_token.code == SC_TOKEN) {
    read_token();
    instruction();
  }
  test_symbol(END_TOKEN, END_ERROR);
}

void instruction() {
  switch (current_token.code) {
  case BEGIN_TOKEN:
    instructions();
    break;
  case ID_TOKEN:
    assignment();
    break;
  case IF_TOKEN:
    if_();
    break;
  case WHILE_TOKEN:
    while_();
    break;
  case WRITE_TOKEN:
    write();
    break;
  case READ_TOKEN:
    read();
    break;
  case REPEAT_TOKEN:
    repeat();
    break;
  case FOR_TOKEN:
    for_();
    break;
  case CASE_TOKEN:
    case_();
    break;
  case SC_TOKEN:
    break;
  case END_TOKEN:
    break;
  case ELSE_TOKEN:
    break;
  case UNTIL_TOKEN:
    break;
  case NUMBER_TOKEN:
    break;
  default:
    show_error(SYNTAX_ERROR);
  }
}

void assignment() {
  int mnemonic;
  validate_assignment(current_token.name);
  test_symbol(ID_TOKEN, ID_ERROR);
  generate_two(LDA, load_symbol_address(previous_token.name));
  mnemonic = assignment_op();
  expression();
  if (mnemonic != 333) generate_one(mnemonic);
  generate_one(STO);
}

void if_() {
  int bze_index, brn_index;
  test_symbol(IF_TOKEN, IF_ERROR);
  condition();
  generate_one(BZE);
  bze_index = pc;
  test_symbol(THEN_TOKEN, THEN_ERROR);
  instruction();
  generate_two(BRN, pc + 2);
  brn_index = pc;
  pcode[bze_index].input = pc + 1;
  switch (current_token.code) {
  case ELSE_TOKEN:
    read_token();
    instruction();
    pcode[brn_index].input = pc + 1;
    break;
  case SC_TOKEN:
    break;
  case END_TOKEN:
    break;
  case UNTIL_TOKEN:
    break;
  case NUMBER_TOKEN:
    break;
  default:
    show_error(SYNTAX_ERROR);
  }
}

void while_() {
  int while_index = pc + 1, bze_index;
  test_symbol(WHILE_TOKEN, WHILE_ERROR);
  condition();
  generate_one(BZE);
  bze_index = pc;
  test_symbol(DO_TOKEN, DO_ERROR);
  instruction();
  generate_two(BRN, while_index);
  pcode[bze_index].input = pc + 1;
}

void write() {
  test_symbol(WRITE_TOKEN, WRITE_ERROR);
  test_symbol(LP_TOKEN, LP_ERROR);
  expression();
  generate_one(PRN);
  while (current_token.code == CO_TOKEN) {
    read_token();
    expression();
    generate_one(PRN);
  }
  test_symbol(RP_TOKEN, RP_ERROR);
}

void read() {
  test_symbol(READ_TOKEN, READ_ERROR);
  test_symbol(LP_TOKEN, LP_ERROR);
  test_symbol(ID_TOKEN, ID_ERROR);
  validate_assignment(previous_token.name);
  generate_two(LDA, load_symbol_address(previous_token.name));
  generate_one(INN);
  while (current_token.code == CO_TOKEN) {
    read_token();
    test_symbol(ID_TOKEN, ID_ERROR);
    validate_assignment(previous_token.name);
    generate_two(LDA, load_symbol_address(previous_token.name));
    generate_one(INN);
  }
  test_symbol(RP_TOKEN, RP_ERROR);
}

void condition() {
  int mnemonic;
  expression();
  mnemonic = comparison();
  expression();
  generate_one(mnemonic);
}

int assignment_op() {
  int mnemonic;
  switch (current_token.code) {
  case ASG_TOKEN:
    mnemonic = 333;
    read_token();
    break;
  case ASGADD_TOKEN:
    generate_two(LDA, load_symbol_address(previous_token.name));
    generate_one(LDV);
    mnemonic = ADD;
    read_token();
    break;
  case ASGSUB_TOKEN:
    generate_two(LDA, load_symbol_address(previous_token.name));
    generate_one(LDV);
    mnemonic = SUB;
    read_token();
    break;
  case ASGMUL_TOKEN:
    generate_two(LDA, load_symbol_address(previous_token.name));
    generate_one(LDV);
    mnemonic = MUL;
    read_token();
    break;
  case ASGDIV_TOKEN:
    generate_two(LDA, load_symbol_address(previous_token.name));
    generate_one(LDV);
    mnemonic = DIV;
    read_token();
    break;
  default:
    show_error(SYNTAX_ERROR);
  }
  return mnemonic;
}

int comparison() {
  switch (current_token.code) {
  case EQUAL_TOKEN:
    read_token();
    return EQL;
  case DIFF_TOKEN:
    read_token();
    return NEQ;
  case LS_TOKEN:
    read_token();
    return LSS;
  case GT_TOKEN:
    read_token();
    return GTR;
  case LE_TOKEN:
    read_token();
    return LEQ;
  case GE_TOKEN:
    read_token();
    return GEQ;
  default:
    show_error(SYNTAX_ERROR);
  }
}

void expression() {
  int mnemonic;
  term();
  while (current_token.code == ADD_TOKEN || current_token.code == SUB_TOKEN) {
    mnemonic = addsub_op();
    term();
    generate_one(mnemonic);
  }
}

int addsub_op() {
  switch (current_token.code) {
  case ADD_TOKEN:
    read_token();
    return ADD;
  case SUB_TOKEN:
    read_token();
    return SUB;
  default:
    show_error(SYNTAX_ERROR);
  }
}

void term() {
  int mnemonic;
  factor();
  while (current_token.code == MUL_TOKEN || current_token.code == DIV_TOKEN) {
    mnemonic = muldiv_op();
    factor();
    generate_one(mnemonic);
  }
}

int muldiv_op() {
  switch (current_token.code) {
  case MUL_TOKEN:
    read_token();
    return MUL;
  case DIV_TOKEN:
    read_token();
    return DIV;
  default:
    show_error(SYNTAX_ERROR);
  }
}

void factor() {
  switch (current_token.code) {
  case ID_TOKEN:
    validate_operation(current_token.name);
    generate_two(LDA, load_symbol_address(current_token.name));
    generate_one(LDV);
    read_token();
    break;
  case NUMBER_TOKEN:
    generate_two(LDI, current_token.value);
    read_token();
    break;
  case LP_TOKEN:
    read_token();
    expression();
    test_symbol(RP_TOKEN, RP_ERROR);
    break;
  default:
    show_error(SYNTAX_ERROR);
  }
}

void repeat() {
  int repeatIndex = pc + 1;
  test_symbol(REPEAT_TOKEN, REPEAT_ERROR);
  instruction();
  test_symbol(UNTIL_TOKEN, UNTIL_ERROR);
  condition();
  generate_two(BZE, repeatIndex);
}

void for_() {
  int type, address, for_index, bze_index;
  test_symbol(FOR_TOKEN, FOR_ERROR);
  test_symbol(ID_TOKEN, ID_ERROR);
  validate_assignment(previous_token.name);
  address = load_symbol_address(previous_token.name);
  generate_two(LDA, address);
  test_symbol(ASG_TOKEN, ASG_ERROR);
  test_symbol(NUMBER_TOKEN, NUMBER_ERROR);
  generate_two(LDI, previous_token.value);
  generate_one(STO);
  switch (current_token.code) {
  case TO_TOKEN:
    type = TO_TOKEN;
    read_token();
    break;
  case DOWNTO_TOKEN:
    type = DOWNTO_TOKEN;
    read_token();
    break;
  default:
    show_error(SYNTAX_ERROR);
  }
  test_symbol(NUMBER_TOKEN, NUMBER_ERROR);
  for_index = pc + 1;
  generate_two(LDA, address);
  generate_one(LDV);
  generate_two(LDI, previous_token.value);
  generate_one(LEQ);
  generate_one(BZE);
  bze_index = pc;
  test_symbol(DO_TOKEN, DO_ERROR);
  instruction();
  generate_two(LDA, address);
  generate_two(LDA, address);
  generate_one(LDV);
  generate_two(LDI, 1);
  if (type == TO_TOKEN) generate_one(ADD);
  else generate_one(SUB);
  generate_one(STO);
  generate_two(BRN, for_index);
  pcode[bze_index].input = pc + 1;
}

void case_() {
  int i, bze_index, address;
  test_symbol(CASE_TOKEN, CASE_ERROR);
  test_symbol(ID_TOKEN, ID_ERROR);
  address = load_symbol_address(previous_token.name);
  generate_two(LDA, address);
  generate_one(LDV);
  validate_operation(previous_token.name);
  test_symbol(OF_TOKEN, OF_ERROR);
  test_symbol(NUMBER_TOKEN, NUMBER_ERROR);
  generate_two(LDI, previous_token.value);
  generate_one(EQL);
  generate_one(BZE);
  bze_index = pc;
  test_symbol(TP_TOKEN, TP_ERROR);
  instruction();
  generate_one(BRN);
  case_brn[case_brn_size++] = pc;
  pcode[bze_index].input = pc + 1;
  while (current_token.code == NUMBER_TOKEN) {
    generate_two(LDA, address);
    generate_one(LDV);
    generate_two(LDI, current_token.value);
    generate_one(EQL);
    generate_one(BZE);
    bze_index = pc;
    read_token();
    test_symbol(TP_TOKEN, TP_ERROR);
    instruction();
    generate_one(BRN);
    case_brn[case_brn_size++] = pc;
    pcode[bze_index].input = pc + 1;
  }
  switch (current_token.code) {
  case ELSE_TOKEN:
    read_token();
    instruction();
    break;
  case END_TOKEN:
    break;
  default:
    show_error(SYNTAX_ERROR);
  }
  for (i = 0; i < case_brn_size; i++) {
    pcode[case_brn[i]].input = pc + 1;
  };
  test_symbol(END_TOKEN, END_ERROR);
}

#endif

