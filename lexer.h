#ifndef LEXER
#define LEXER

char read_character() {
  current_character = fgetc(input_file);
}

void read_word() {
  char word[MAXID];
  int i = 0;
  word[i++] = current_character;
  read_character();
  while (isalnum(current_character) || current_character == '_') {
    if (i < MAXID - 1) {
      word[i++] = current_character;
      read_character();
    } else {
      show_error(MAXID_ERROR);
    }
  }
  word[i] = '\0';
  strcpy(current_token.name, word);
  if (stricmp(word, "PROGRAM") == 0) {
    current_token.code = PROGRAM_TOKEN;
  } else if (stricmp(word, "BEGIN") == 0) {
    current_token.code = BEGIN_TOKEN;
  } else if (stricmp(word, "END") == 0) {
    current_token.code = END_TOKEN;
  } else if (stricmp(word, "CONST") == 0) {
    current_token.code = CONST_TOKEN;
  } else if (stricmp(word, "VAR") == 0) {
    current_token.code = VAR_TOKEN;
  } else if (stricmp(word, "IF") == 0) {
    current_token.code = IF_TOKEN;
  } else if (stricmp(word, "THEN") == 0) {
    current_token.code = THEN_TOKEN;
  } else if (stricmp(word, "ELSE") == 0) {
    current_token.code = ELSE_TOKEN;
  } else if (stricmp(word, "WHILE") == 0) {
    current_token.code = WHILE_TOKEN;
  } else if (stricmp(word, "DO") == 0) {
    current_token.code = DO_TOKEN;
  } else if (stricmp(word, "REPEAT") == 0) {
    current_token.code = REPEAT_TOKEN;
  } else if (stricmp(word, "UNTIL") == 0) {
    current_token.code = UNTIL_TOKEN;
  } else if (stricmp(word, "FOR") == 0) {
    current_token.code = FOR_TOKEN;
  } else if (stricmp(word, "TO") == 0) {
    current_token.code = TO_TOKEN;
  } else if (stricmp(word, "DOWNTO") == 0) {
    current_token.code = DOWNTO_TOKEN;
  } else if (stricmp(word, "CASE") == 0) {
    current_token.code = CASE_TOKEN;
  } else if (stricmp(word, "OF") == 0) {
    current_token.code = OF_TOKEN;
  } else if (stricmp(word, "WRITE") == 0) {
    current_token.code = WRITE_TOKEN;
  } else if (stricmp(word, "READ") == 0) {
    current_token.code = READ_TOKEN;
  } else {
    current_token.code = ID_TOKEN;
  }
}

void read_number() {
  char number[MAXNUMBER];
  int i = 0;
  number[i++] = current_character;
  read_character();
  while (isdigit(current_character)) {
    if (i < MAXNUMBER - 1) {
      number[i++] = current_character;
      read_character();
    } else {
      show_error(MAXNUMBER_ERROR);
    }
  }
  number[i] = '\0';
  strcpy(current_token.name, number);
  current_token.value = atoi(number);
  current_token.code = NUMBER_TOKEN;
}

void read_special_symbol() {
  switch (current_character) {
  case ';':
    current_token.code = SC_TOKEN;
    read_character();
    break;
  case '.':
    current_token.code = PT_TOKEN;
    read_character();
    break;
  case ',':
    current_token.code = CO_TOKEN;
    read_character();
    break;
  case '(':
    current_token.code = LP_TOKEN;
    read_character();
    break;
  case ')':
    current_token.code = RP_TOKEN;
    read_character();
    break;
  case '<':
    read_character();
    if (current_character == '=') {
      current_token.code = LE_TOKEN;
      read_character();
    } else if (current_character == '>') {
      current_token.code = DIFF_TOKEN;
      read_character();
    } else {
      current_token.code = LS_TOKEN;
    }
    break;
  case '>':
    read_character();
    if (current_character == '=') {
      current_token.code = GE_TOKEN;
      read_character();
    } else {
      current_token.code = GT_TOKEN;
    }
    break;
  case ':':
    read_character();
    if (current_character == '=') {
      read_character();
      switch (current_character) {
      case '+':
        current_token.code = ASGADD_TOKEN;
        read_character();
        break;
      case '-':
        current_token.code = ASGSUB_TOKEN;
        read_character();
        break;
      case '*':
        current_token.code = ASGMUL_TOKEN;
        read_character();
        break;
      case '/':
        current_token.code = ASGDIV_TOKEN;
        read_character();
        break;
      default:
        current_token.code = ASG_TOKEN;
      }
    } else {
      current_token.code = TP_TOKEN;
    }
    break;
  case '=':
    current_token.code = EQUAL_TOKEN;
    read_character();
    break;
  case '+':
    current_token.code = ADD_TOKEN;
    read_character();
    break;
  case '-':
    current_token.code = SUB_TOKEN;
    read_character();
    break;
  case '*':
    current_token.code = MUL_TOKEN;
    read_character();
    break;
  case '/':
    current_token.code = DIV_TOKEN;
    read_character();
    break;
  case EOF:
    current_token.code = EOF_TOKEN;
    read_character();
    break;
  default:
    show_error(UNRECOGNISED_ERROR);
  }
}

void read_token() {
  previous_token = current_token;
  skip_cmts_ws();
  if (isalpha(current_character)) {
    read_word();
  } else if (isdigit(current_character)) {
    read_number();
  } else {
    read_special_symbol();
  }
}

void skip_cmts_ws() {
  int divToken = 0;
  while (current_character == ' ' || current_character == '\n' || current_character == '\t' || current_character == '{' || current_character == '/') {
    if (current_character == '\n') {
      line_count++;
    }
    if (current_character == ' ' || current_character == '\n' || current_character == '\t') read_character();
    else skip_cmts(divToken);
    if (divToken == 1) break;
  }
}

void skip_cmts(int divToken) {
  if (current_character == '{') {
    while (current_character != '}' && current_character != EOF) {
      if (current_character == '\n') {
        line_count++;
      }
      read_character();
    }
    if (current_character == '}') {
      read_character();
    } else {
      show_error(COMMENT_ERROR);
    }
  } else if (current_character == '/') {
    read_character();
    if (current_character == '/') {
      while (current_character != '\n' && current_character != EOF) {
        read_character();
      }
      if (current_character == '\n') {
        line_count++;
        read_character();
      }
    } else {
      ungetc(current_character, input_file);
      current_character = '/';
      divToken = 1;
    }
  }

}

#endif

