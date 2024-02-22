#ifndef INTERPRETER
#define INTERPRETER

void interpret_pcode() {
  pc = 0;
  while (pcode[pc].mnemonic != HLT)
    interpret_instruction(pcode[pc]);
}

void interpret_instruction(INSTRUCTION instruction) {
  int x, y, address;
  switch (instruction.mnemonic) {
  case ADD: {
    y = stack[sp--];
    x = stack[sp];
    stack[sp] = x + y;
    pc++;
    break;
  }
  case SUB: {
    y = stack[sp--];
    x = stack[sp];
    stack[sp] = x - y;
    pc++;
    break;
  }
  case MUL: {
    y = stack[sp--];
    x = stack[sp];
    stack[sp] = x * y;
    pc++;
    break;
  }
  case DIV: {
    y = stack[sp--];
    x = stack[sp];
    stack[sp] = x / y;
    pc++;
    break;
  }
  case EQL: {
    y = stack[sp--];
    x = stack[sp];
    stack[sp] = (x == y) ? 1 : 0;
    pc++;
    break;
  }
  case NEQ: {
    y = stack[sp--];
    x = stack[sp];
    stack[sp] = (x != y) ? 1 : 0;
    pc++;
    break;
  }
  case GTR: {
    y = stack[sp--];
    x = stack[sp];
    stack[sp] = (x > y) ? 1 : 0;
    pc++;
    break;
  }
  case LSS: {
    y = stack[sp--];
    x = stack[sp];
    stack[sp] = (x < y) ? 1 : 0;
    pc++;
    break;
  }
  case GEQ: {
    y = stack[sp--];
    x = stack[sp];
    stack[sp] = (x >= y) ? 1 : 0;
    pc++;
    break;
  }
  case LEQ: {
    y = stack[sp--];
    x = stack[sp];
    stack[sp] = (x <= y) ? 1 : 0;
    pc++;
    break;
  }
  case PRN: {
    printf("%d\n", stack[sp--]);
    pc++;
    break;
  }
  case INN: {
    address = stack[sp--];
    scanf("%d", & stack[address]);
    pc++;
    break;
  }
  case INT: {
    sp += instruction.input;
    pc++;
    break;
  }
  case LDI: {
    stack[++sp] = instruction.input;
    pc++;
    break;
  }
  case LDA: {
    stack[++sp] = instruction.input;
    pc++;
    break;
  }
  case LDV: {
    address = stack[sp];
    stack[sp] = stack[address];
    pc++;
    break;
  }
  case STO: {
    y = stack[sp--];
    x = stack[sp--];
    stack[x] = y;
    pc++;
    break;
  }
  case BRN: {
    pc = instruction.input;
    break;
  }
  case BZE: {
    if (stack[sp] == 0) pc = instruction.input;
    else pc++;
    break;
  }
  case HLT: {
    exit(0);
  }
  default: {
    show_error(MNEMONIC_ERROR);
  }
  }
}

#endif

