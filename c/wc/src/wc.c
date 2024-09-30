//
// Created by Jeremy Novak on 9/29/24.
//

#include "wc.h"

int count_words(const char *str) {
  int count = 0;
  int in_word = 0;

  while (*str) {
    if (isspace(*str)) {
      in_word = 0;
    } else if (!in_word) {
      in_word = 1;
      ++count;
    }

    ++str;
  }

  return count;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *filename = argv[1];
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file '%s': %s\n", filename, strerror(errno));
    return EXIT_FAILURE;
  }

  char line[MAX_LINE_LENGTH];
  int total_words = 0;

  while(fgets(line, sizeof(line), file) != NULL) {
    total_words += count_words(line);
  }

  if (ferror(file)) {
    fprintf(stderr, "Error reading file '%s': %s\n", filename, strerror(errno));
    fclose(file);
    return EXIT_FAILURE;
  }

  fclose(file);
  printf("Word count: %d\n", total_words);

  return EXIT_SUCCESS;
}