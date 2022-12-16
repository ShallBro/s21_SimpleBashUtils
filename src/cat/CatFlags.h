#ifndef SRC_CAT_CATFLAGS_H_
#define SRC_CAT_CATFLAGS_H_

typedef struct {
  bool number_null;    // b
  bool numbering_all;  // n
  bool show_endl;      // e
  bool squeeze;        // s
  bool show_tab;       // t
  bool dontprint;      // v
} Infoflags;

Infoflags ReadFlags(int argc, char *argv[]);
void CatSetTable(const char *table[static 256]);
void CatEndlDollar(const char *table[static 256]);
void CatTabs(const char *table[static 256]);
void CatDontPrintable(const char *table[static 256]);
void CatFile(int argc, char *argv[], Infoflags flags,
             const char *table[static 256]);
void CatInput(FILE *fp, Infoflags flags, const char *table[static 256]);

#endif  // SRC_CAT_CATFLAGS_H_"