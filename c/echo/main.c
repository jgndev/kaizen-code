#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void print_usage() {
  printf("Usage: echo [OPTION]... [STRING]...\n");
  printf("Echo the STRING(s) to standard output.\n");
  printf("\nOptions:\n");
  printf("  -n  do not enable the trailing newline\n");
  printf("  -e  enable interpretation of backslash escapes\n");
  printf("  -E  disable interpretation of backslash escapes (default)\n");
  printf("  -h  display this help message and exit\n");
  printf("\nExamples:\n");
  printf("  echo Hello World      Output 'Hello World'\n");
  printf("  echo -n Hello World   Output 'Hello World' without newline\n");
  printf("  echo -e \"Hello\\nWorld\"  Output 'Hello' and 'World' on separate lines");
}

void process_escapes(char *str) {
  char *read = str, *write = str;

  while (*read) {
    if (*read == '\\') {
      read++;
      switch(*read) {
        case 'n':
          *write++ = '\n';
          break;
        case 't':
          *write++ = '\t';
          break;
        case '\\':
          *write++ = '\\';
          break;
        default:
          *write++ = '\\';
          *write++ = *read;

      }
    } else {
      *write++ = *read;
    }
  }

  *write = '\0';
}

int main(int argc, char *argv[]) {
  if (argc == 1 || (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))) {
    print_usage();
    return 0;
  }

  bool no_newline = false;
  bool enable_escapes = false;
  char output[1024] = "";

  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-n") == 0) {
      no_newline = true;
    } else if (strcmp(argv[i], "-e") == 0) {
      enable_escapes = true;
    } else if (strcmp(argv[i], "-E") == 0) {
      enable_escapes = false;
    } else {
      if (output[0] != '\0') {
        strcat(output, " ");
        strcat(output, argv[i]);
      }
    }
  }

  if (enable_escapes) {
    process_escapes(output);
  }

  printf("%s", output);

  if (!no_newline) {
    printf("\n");
  }

  return 0;
}