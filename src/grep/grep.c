#define _GNU_SOURCE  // for getline
#include "grep.h"

#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  Infoflags flags = ReadFlags(argc, argv);
  GrepFile(argc, argv, flags);
  if (flags.error) {
    return flags.error;
  }
}

Infoflags ReadFlags(int argc, char *argv[]) {
  Infoflags flags = {0, false, false, false, false, false};
  int curr_flags;

  while ((curr_flags = getopt_long(argc, argv, "e:ivcln", 0, 0)) !=
         -1) {  // : значит после этой опции обязательно получает аргумент
    switch (curr_flags) {
      case 'e':
        flags.regex_flag = true;
        break;
      case 'i':
        flags.regex_flag |= REG_ICASE;
        break;
      case 'v':
        flags.invertor = true;
        break;
      case 'c':
        flags.print_check_strings = true;
        break;
      case 'l':
        flags.print_check_files = true;
        break;
      case 'n':
        flags.print_number_strings = true;
        break;
      default:
        flags.error = true;
    }
  }
  return flags;
}

bool GrepFile(int argc, char *argv[], Infoflags flags) {
  if (argc <= 2) {
    fprintf(stderr, "no pattern");
    flags.error = true;
  } else {
    char **pattern = &argv[1];
    char **end = &argv[argc];
    regex_t preg_storage_compile;
    regex_t *preg = &preg_storage_compile;
    for (; pattern != end && pattern[0][0] == '-'; pattern++) {
    }
    if (regcomp(preg, *pattern, flags.regex_flag)) {
      fprintf(stderr, "fail compile regex");
      flags.error = true;
    }
    if (!flags.error) {
      int countfile = GrepCountFiles(pattern, end);
      for (char **file = pattern + 1; file != end; file++) {
        if (**file == '-') {
          continue;
        }
        FILE *filename = fopen(*file, "rb");
        if (errno) {
          fprintf(stderr, "%s", argv[0]);
          perror(*file);
          errno = 0;
          continue;
        }
        if (flags.print_check_strings) {  // -c
          GrepCountStrings(filename, *file, preg, argc, argv);
        } else
          GrepInput(filename, flags, preg, *file, countfile);
        fclose(filename);
      }
      regfree(preg);
    }
  }
  return flags.error;
}

int GrepCountFiles(char **pattern, char **end) {
  int count = 0;
  for (char **filename = pattern + 1; filename != end; filename++) {
    if (**filename == '-') continue;
    count++;
    if (count >= 2) break;
  }
  return count;
}

void GrepCountStrings(FILE *filename, char const *file, regex_t *preg, int argc,
                      char *argv[]) {
  char **pattern = &argv[1];
  char **end = &argv[argc];
  int count_file = 0;
  int checker = 0;
  char **check = pattern;
  if (**check == '-') {
    checker = 2;
  } else
    checker = 1;
  for (char **filename1 = pattern + checker; filename1 != end; filename1++) {
    count_file++;
    if (count_file >= 2) {
      break;
    }
  }
  char *str = 0;
  size_t length = 0;
  regmatch_t struct_match;
  int count = 0;
  while (getline(&str, &length, filename) != -1) {
    if (!regexec(preg, str, 1, &struct_match, 0)) {
      count += 1;
    }
  }
  if (count_file == 1) {
    printf("%i\n", count);
  } else
    printf("%s:%i\n", file, count);
  free(str);
}

void GrepInput(FILE *filename, Infoflags flags, regex_t *preg, char const *file,
               int countfile) {
  char *str = 0;
  int count = 0;
  size_t length = 0;
  regmatch_t struct_match;
  while (getline(&str, &length, filename) != -1) {
    count++;
    if (flags.invertor) {
      if (regexec(preg, str, 1, &struct_match, 0)) printf("%s", str);
    } else {
      if (!regexec(preg, str, 1, &struct_match, 0)) {
        if (flags.print_number_strings)
          printf("%i:%s", count, str);
        else {
          if (flags.print_check_files) {
            if (countfile >= 2) {
              GrepCheckFiles(file, countfile);
            } else {
              printf("%s", file);
              break;
            }
          } else {
            if (countfile >= 2)
              printf("%s:%s", file, str);
            else
              printf("%s", str);
          }
        }
        if (flags.print_check_files && countfile >= 2) break;
      }
    }
  }
  free(str);
}

void GrepCheckFiles(char const *file, int countfile) {
  for (int counter = 0; counter != countfile - 1; counter++) {
    printf("%s\n", file);
  }
}
