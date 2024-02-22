#ifndef IMPORTER
#define IMPORTER

void load_pcode_from_file() {
  input_file = fopen("files/generated_pcode.txt", "r");
  if (input_file == NULL) {
    perror("error opening file");
    return;
  }
  pc = 0;
  char instruction[10];
  while (fscanf(input_file, "%s", instruction) != EOF) {
    if (pc >= MAXINSTRUCTIONS) {
      show_error(MAXINSTRUCTIONS_ERROR);
    }
    load_instruction(instruction);
    pc++;
  }
  pc--;
  fclose(input_file);
}

void load_instruction(char * instruction) {
  int input;
  if (strcmp(instruction, "ADD") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = ADD;
  } else if (strcmp(instruction, "SUB") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = SUB;
  } else if (strcmp(instruction, "MUL") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = MUL;
  } else if (strcmp(instruction, "DIV") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = DIV;
  } else if (strcmp(instruction, "EQL") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = EQL;
  } else if (strcmp(instruction, "NEQ") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = NEQ;
  } else if (strcmp(instruction, "GTR") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = GTR;
  } else if (strcmp(instruction, "LSS") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = LSS;
  } else if (strcmp(instruction, "GEQ") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = GEQ;
  } else if (strcmp(instruction, "LEQ") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = LEQ;
  } else if (strcmp(instruction, "PRN") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = PRN;
  } else if (strcmp(instruction, "INN") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = INN;
  } else if (strcmp(instruction, "INT") == 0) {
    pcode[pc].mnemonic = INT;
    fscanf(input_file, " \t %d \n", & input);
    pcode[pc].input = input;
  } else if (strcmp(instruction, "LDI") == 0) {
    pcode[pc].mnemonic = LDI;
    fscanf(input_file, " \t %d \n", & input);
    pcode[pc].input = input;
  } else if (strcmp(instruction, "LDA") == 0) {
    pcode[pc].mnemonic = LDA;
    fscanf(input_file, " \t %d \n", & input);
    pcode[pc].input = input;
  } else if (strcmp(instruction, "LDV") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = LDV;
  } else if (strcmp(instruction, "STO") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = STO;
  } else if (strcmp(instruction, "BRN") == 0) {
    pcode[pc].mnemonic = BRN;
    fscanf(input_file, " \t %d \n", & input);
    pcode[pc].input = input;
  } else if (strcmp(instruction, "BZE") == 0) {
    pcode[pc].mnemonic = BZE;
    fscanf(input_file, " \t %d \n", & input);
    pcode[pc].input = input;
  } else if (strcmp(instruction, "HLT") == 0) {
    fscanf(input_file, " \n");
    pcode[pc].mnemonic = HLT;
  } else {
    show_error(MNEMONIC_ERROR);
  }
}

#endif

