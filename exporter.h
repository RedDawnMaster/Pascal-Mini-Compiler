#ifndef EXPORTER
#define EXPORTER

void save_pcode_to_file() {
  output_file = fopen("files/generated_pcode.txt", "w+");
  if (output_file == NULL) {
    perror("error opening file");
  }
  int i;
  for (i = 0; i <= pc; i++) {
    save_instruction(pcode[i]);
  }
  fclose(output_file);
}

void save_instruction(INSTRUCTION instruction) {
  switch (instruction.mnemonic) {
  case ADD:
    fprintf(output_file, "%s \n", "ADD");
    break;
  case SUB:
    fprintf(output_file, "%s \n", "SUB");
    break;
  case MUL:
    fprintf(output_file, "%s \n", "MUL");
    break;
  case DIV:
    fprintf(output_file, "%s \n", "DIV");
    break;
  case EQL:
    fprintf(output_file, "%s \n", "EQL");
    break;
  case NEQ:
    fprintf(output_file, "%s \n", "NEQ");
    break;
  case GTR:
    fprintf(output_file, "%s \n", "GTR");
    break;
  case LSS:
    fprintf(output_file, "%s \n", "LSS");
    break;
  case GEQ:
    fprintf(output_file, "%s \n", "GEQ");
    break;
  case LEQ:
    fprintf(output_file, "%s \n", "LEQ");
    break;
  case PRN:
    fprintf(output_file, "%s \n", "PRN");
    break;
  case INN:
    fprintf(output_file, "%s \n", "INN");
    break;
  case INT:
    fprintf(output_file, "%s \t %d \n", "INT", instruction.input);
    break;
  case LDI:
    fprintf(output_file, "%s \t %d \n", "LDI", instruction.input);
    break;
  case LDA:
    fprintf(output_file, "%s \t %d \n", "LDA", instruction.input);
    break;
  case LDV:
    fprintf(output_file, "%s \n", "LDV");
    break;
  case STO:
    fprintf(output_file, "%s \n", "STO");
    break;
  case BRN:
    fprintf(output_file, "%s \t %d \n", "BRN", instruction.input);
    break;
  case BZE:
    fprintf(output_file, "%s \t %d \n", "BZE", instruction.input);
    break;
  case HLT:
    fprintf(output_file, "%s \n", "HLT");
    break;
  default:
    show_error(MNEMONIC_ERROR);
  }
}

#endif

