#ifndef GENERATOR
#define GENERATOR

void generate_one(MNEMONIC mnemonic) {
  if (pc == MAXINSTRUCTIONS) {
    show_error(MAXINSTRUCTIONS_ERROR);
  }
  pc++;
  pcode[pc].mnemonic = mnemonic;
}

void generate_two(MNEMONIC mnemonic, int input) {
  if (pc == MAXINSTRUCTIONS) {
    show_error(MAXINSTRUCTIONS_ERROR);
  }
  pc++;
  pcode[pc].mnemonic = mnemonic;
  pcode[pc].input = input;
}

#endif

