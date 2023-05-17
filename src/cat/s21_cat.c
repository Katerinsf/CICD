// #include "cat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buff_size 1000

typedef struct opt {
  int b;
  int e;
  int n;
  int s;
  int t;
  // GNU:
  int v;
  int T;
  int E;
} opt;

int check_all_flags(opt *options, int argc, char *argv[], char *symb);

void output(char *name, opt *options);
int check_flag(const char *str, opt *options);

void struct_init(opt *options);
int count_files(opt *options, int argc, char *argv[]);

int main(int argc, char *argv[]) {
  opt options;
  struct_init(&options);
  char symb;
  if (!check_all_flags(&options, argc, argv, &symb)) {
    printf("cat: illegal option -- %c\n", symb);
    printf("usage: cat [-benstuv] [file ...]\n");
  } else if (argc > 1) {
    opt options;
    struct_init(&options);
    int n_file = count_files(&options, argc,
                             argv);  // С какого аргумента начинаются файлы

    // printf("%d\n", n_file);
    if (n_file < argc) {
      for (int i = n_file; i < argc; i++) {
        output(argv[i], &options);
      }
    } else {
      printf("Wrong format\n");
    }
  } else {
    printf("Wrong format\n");
  }

  return 0;
}

void output(char *name, opt *options) {
  FILE *file;
  file = fopen(name, "r");
  if (file != NULL) {
    // printf("Name: %s\n", name);

    char c, c0 = 'C';
    int n = 1;      //  Число строк
    int count = 0;  // Число символов
    int flag_empty = 0;

    while (!feof(file)) {
      c = fgetc(file);

      if (c != EOF) {
        if (options->s && c == '\n' && c0 == '\n') {
          if (flag_empty) {
            continue;
          } else {
            flag_empty = 1;
          }
        } else {
          flag_empty = 0;
        }

        if (count == 0 || c0 == '\n') {
          if (options->b && !(c == '\n')) {
            printf("%6d\t", n);
            n++;
          }
          if (options->n && !options->b) {
            printf("%6d\t", n);
            n++;
          }
        }

        if ((options->t || options->e || options->v) && c != '\n' &&
            c != '\t') {
          if (c < 32 && c >= 0 && c != 10) {
            printf("%c%c", '^', c + 64);
          } else if (c >= 127) {
            printf("%c%c", '^', c + 1);
          } else {
            printf("%c", c);
          }
        } else if ((options->e || options->E) && c == '\n') {
          printf("%c", '$');
          printf("%c", c);
        } else if ((options->t || options->T) && c == '\t') {
          printf("%c%c", '^', 'I');
        } else {
          printf("%c", c);
        }

        c0 = c;
      }
      count++;
    }

    fclose(file);
  } else {
    printf("cat: %s: No such file or directory\n", name);
  }
}

void struct_init(opt *options) {
  options->b = 0;
  options->e = 0;
  options->n = 0;
  options->s = 0;
  options->t = 0;
  // GNU:
  options->v = 0;
  options->T = 0;
  options->E = 0;
}

int count_files(opt *options, int argc, char *argv[]) {
  int res = 0;
  int count_file = 1;
  for (int i = 1; i < argc; i++) {
    res = check_flag(argv[i], options);
    if (res) {
      count_file++;
    } else {
      break;
    }
  }
  return count_file;
}

int check_flag(const char *str, opt *options) {
  int res = 0;

  if (str[0] == '-') {
    int j = 1;
    if (!*(str + j)) {
      res = 0;
    }
    while (*(str + j)) {
      switch (str[j]) {
        case 'b':
          options->b = 1;
          res = 1;
          break;
        case 'e':
          options->e = 1;
          res = 1;
          break;
        case 'n':
          options->n = 1;
          res = 1;
          break;
        case 's':
          options->s = 1;
          res = 1;
          break;
        case 't':
          options->t = 1;
          res = 1;
          break;
        // GNU:
        case 'T':
          options->T = 1;
          res = 1;
          break;
        case 'E':
          options->E = 1;
          res = 1;
          break;
        case 'v':
          options->v = 1;
          res = 1;
          break;
        default:
          res = 0;
          break;
      }
      if (res == 0) {
        break;
      }
      j++;
    }
    if (!res) {
      if (strcmp(str, "--number-nonblank") == 0) {
        options->b = 1;
        res = 1;
      } else if (strcmp(str, "--number") == 0) {
        options->n = 1;
        res = 1;
      } else if (strcmp(str, "--squeeze-blank") == 0) {
        options->s = 1;
        res = 1;
      }
    }
  }
  return res;
}

int check_all_flags(opt *options, int argc, char *argv[], char *symb) {
  int res = 1;
  char c[] = "- ";
  int j;
  int flag_true;
  int flag_false;
  for (int i = 1; i < argc; i++) {
    if (!check_flag(argv[i], options) && argv[i][0] == '-') {
      flag_true = 0;
      flag_false = 0;
      *symb = '\0';
      j = 1;
      while (argv[i][j]) {
        c[1] = argv[i][j];
        if (check_flag(c, options)) {
          flag_true++;
        } else {
          if (*symb == '\0') {
            *symb = c[1];
          }
          flag_false++;
        }
        j++;
      }
      if (flag_true) {
        res = 0;
        break;
      }
    }
  }
  return res;
}
