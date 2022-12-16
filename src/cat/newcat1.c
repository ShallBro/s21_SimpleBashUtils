#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "CatFlags.h"

int main(int argc, char *argv[]) {
  Infoflags flags = ReadFlags(argc, argv);
  const char *table[256];
  CatSetTable(table);
  if (flags.show_endl) CatEndlDollar(table);
  if (flags.show_tab) CatTabs(table);
  if (flags.dontprint) CatDontPrintable(table);
  CatFile(argc, argv, flags, table);
}

Infoflags ReadFlags(int argc, char *argv[]) {
  struct option longopts[] = {{"number-nonblank", 0, NULL, 'b'},
                              {"number", 0, NULL, 'n'},
                              {"squeeze-blank", 0, NULL, 's'},
                              {NULL, 0, NULL, 0}};
  Infoflags flags = {false, false, false, false, false, false};
  int curr_flag;
  while ((curr_flag = getopt_long(argc, argv, "+bevEnstT", longopts, 0)) !=
         -1) {
    switch (curr_flag) {
      case 'b':
        flags.number_null = true;
        break;
      case 'e':
        flags.show_endl = true;
        flags.dontprint = true;
        break;
      case 'v':
        flags.dontprint = true;
        break;
      case 'E':
        flags.show_endl = true;
        break;
      case 'n':
        flags.numbering_all = true;
        break;
      case 's':
        flags.squeeze = true;
        break;
      case 't':
        flags.show_tab = true;
        flags.dontprint = true;
        break;
      case 'T':
        flags.show_tab = true;
    }
  }
  return flags;
}

void CatFile(int argc, char *argv[], Infoflags flags,
             const char *table[static 256]) {
  for (char **file = &argv[1], **end = &argv[argc]; file != end; file++) {
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
    CatInput(filename, flags, table);
    fclose(filename);
  }
}

void CatInput(FILE *fp, Infoflags flags, const char *table[static 256]) {
  int a = 0;
  char last = '\n';
  bool last2 = false;
  int numbers = 1;
  while (fread(&a, 1, 1, fp) > 0) {
    if (last == '\n') {
      if (flags.squeeze && a == '\n') {
        if (last2) continue;  // s
        last2 = true;
      } else
        last2 = false;
      if (flags.number_null) {  // b
        if (a != '\n') printf("%6d\t", numbers++);
      } else if (flags.numbering_all) {  // n
        printf("%6d\t", numbers++);
      }
    }
    printf("%s", table[a]);
    last = a;
  }
}
