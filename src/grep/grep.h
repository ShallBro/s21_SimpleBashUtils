#ifndef SRC_GREP_GREP_H_
#define SRC_GREP_GREP_H_
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  int regex_flag;             // -e and -i ++
  bool invertor;              // -v +
  bool print_check_strings;   // -c +
  bool print_check_files;     // -l  -
  bool print_number_strings;  // -n +
  bool error;
} Infoflags;

Infoflags ReadFlags(int argc, char *argv[]);
bool GrepFile(int argc, char *argv[], Infoflags flags);
int GrepCountFiles(char **pattern, char **end);
void GrepCountStrings(FILE *filename, char const *file, regex_t *preg, int argc,
                      char *argv[]);
void GrepInput(FILE *filename, Infoflags flags, regex_t *preg, char const *file,
               int countfile);
void GrepCheckFiles(char const *file, int countfile);

#endif  // SRC_GREP_GREP_H_"