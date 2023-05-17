// #include "grep.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buff_size 1000

typedef struct opt {
  int e;  // Флаг для нескольких слов поиска; содержит кол-во слов, если он есть
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int name;  // Количество файлов для поиска
             // int number_str; // Номер строки в файле
} opt;

void struct_init(opt *options);
int flags_init(opt *options, int argc, char *argv[]);
int check_flag(const char *str, opt *options);
int check_flag_e(const char *str);
int check_flag_f(const char *str);

int *find_word(opt *options, int argc, char *argv[]);
int *find_files(opt *options, int argc, char *argv[], int num_word);

void output(opt *options, int argc, char *argv[]);
void search(opt *options, char *name, char *argv[], int *num_word);

void print_str(opt *options, char *name, char *str, int number_str, char *word);
void print_file(opt *options, char *name, int n);

int strreg(char *str, char *word);
void *s21_to_lower(const char *str);
void errors(int a, char c);
int check_all_flags(opt *options, int argc, char *argv[], char *symb);

int main(int argc, char *argv[]) {
  opt options;
  struct_init(&options);
  char c;
  if (!check_all_flags(&options, argc, argv, &c)) {
    // printf("Output3\n");
    errors(3, c);
  } else if (argc == 3 && strcmp(argv[argc - 1], "-e") != 0 &&
             strcmp(argv[argc - 1], "-") != 0) {
    int m = flags_init(&options, argc, argv);
    if (m == 0) {
      // printf("Output3\n");
      // output(argv[i], &options);
      output(&options, argc, argv);
    } else {
      errors(0, 'A');
    }
  } else if (argc > 3 && strcmp(argv[argc - 1], "-e") != 0 &&
             strcmp(argv[argc - 1], "-") != 0) {
    output(&options, argc, argv);
  } else if (strcmp(argv[argc - 1], "-") == 0) {
    errors(0, 'A');
  } else if (strcmp(argv[argc - 1], "-e") == 0) {
    errors(1, 'A');
  } else if ((argc == 2 && argv[1][0] == '-') || argc == 1) {
    errors(2, 'A');
  } else {
    printf("Error\n");
  }
  return 0;
}

void struct_init(opt *options) {
  options->e = 0;
  options->i = 0;
  options->v = 0;
  options->c = 0;
  options->l = 0;
  options->n = 0;
  options->h = 0;
  options->s = 0;
  options->f = 0;
  options->o = 0;
  options->name = 0;
}

int flags_init(opt *options, int argc, char *argv[]) {
  int res = 0;
  for (int i = 1; i < argc; i++) {
    if (check_flag(argv[i], options)) {
      res++;
    } else if (check_flag_e(argv[i])) {
      options->e++;
      i++;
    }
    // } else if (check_flag_f(argv[i])) {
    //     options->f++;
    // }
  }
  return res;
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
        // case 'e':
        //     options->e = 1;
        //     res = 1;
        //     break;
        case 'i':
          options->i = 1;
          res = 1;
          break;
        case 'v':
          options->v = 1;
          res = 1;
          break;
        case 'c':
          options->c = 1;
          res = 1;
          break;
        case 'l':
          options->l = 1;
          res = 1;
          break;
        case 'n':
          options->n = 1;
          res = 1;
          break;
        case 'h':
          options->h = 1;
          res = 1;
          break;
        case 's':
          options->s = 1;
          res = 1;
          break;
        // case 'f':
        //     options->f = 1;
        //     res = 1;
        //     break;
        case 'o':
          options->o = 1;
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
  }

  return res;
}

int check_flag_e(const char *str) {
  int res = 0;
  if (!strcmp(str, "-e")) {
    // options->e++;
    res = 1;
  }
  return res;
}

int check_flag_f(const char *str) {
  int res = 0;
  if (!strcmp(str, "-f")) {
    res = 1;
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
    if (check_flag_e(argv[i])) {
      i++;
    } else if (!check_flag(argv[i], options) && !check_flag_e(argv[i]) &&
               argv[i][0] == '-') {
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

int *find_word(opt *options, int argc, char *argv[]) {
  int k = options->e ? options->e : 1;
  int *num_word = (int *)calloc(k, sizeof(int));  // Массив с номерами слов
  if (num_word != NULL) {
    if (!options->e) {
      for (int i = 1; i < argc; i++) {
        if (!check_flag(argv[i], options)) {
          num_word[0] = i;
          break;
        }
      }
      // num_word[0] = 1;
    } else {
      for (int i = 1, j = 0; i < argc && j < k; i++) {
        if (check_flag_e(argv[i])) {
          num_word[j] = i + 1;
          i++;
          j++;
          // printf("num_word: %d\n", i);
        }
      }
    }
  }
  return num_word;
}

int *find_files(opt *options, int argc, char *argv[], int num_word) {
  int f = options->name;
  int *num_file = (int *)calloc(f, sizeof(int));  // Массив с номерами файлов
  if (num_file != NULL) {
    for (int i = 1, j = 0; i < argc && j < f; i++) {
      // if (!check_flag_e(argv[i]) && !check_flag_e(argv[i-1])
      // && !check_flag(argv[i], options)) {

      if (!options->e && !check_flag(argv[i], options) && i != num_word) {
        num_file[j] = i;
        j++;
      }
      if (options->e && !check_flag(argv[i], options)) {
        if (check_flag_e(argv[i])) {
          i++;
        } else {
          num_file[j] = i;
          j++;
        }
        // num_file[j] = i;
        // j++;
      }
    }
  }
  return num_file;
}

void output(opt *options, int argc, char *argv[]) {
  // FILE *file;

  int m = flags_init(options, argc, argv);  // кол-во команд
  // int k = amount_word(options, argc, argv);  // кол-во слов
  int k = options->e ? options->e : 1;  // кол-во слов
  // int w = options->f ? options->f : 0;  // кол-во файлов со словами
  int f = argc - 1 - 2 * k - m;  // кол-во файлов
  if (!options->e) {
    f++;
  }
  options->name = f;

  if (f) {
    int *num_word = find_word(options, argc, argv);
    int *num_file = options->e ? find_files(options, argc, argv, 0)
                               : find_files(options, argc, argv, num_word[0]);

    for (int i = 0; i < f; i++) {
      // search(options, argv[num_file[i]], argv, argc);
      search(options, argv[num_file[i]], argv, num_word);
    }

    free(num_word);
    free(num_file);
  } else {
    printf("grep: No files\n");
  }
}

void search(opt *options, char *name, char *argv[], int *num_word) {
  FILE *file = NULL;
  file = fopen(name, "r");
  char str[1000];

  int flag_v = 0;
  int number_str = 0;  // номер строки с файле, где ищем
  int n = 0;           // кол-во совпадающих строк
  int *num_word0 = num_word;
  int k = options->e ? options->e : 1;  // кол-во слов

  if (file != NULL) {
    while (!feof(file)) {
      num_word0 = num_word;

      if (fgets(str, buff_size, file) != NULL) {
        number_str++;
        for (int i = 0; i < k; i++) {
          num_word0 = num_word + i;
          if (!options->v &&
              ((strstr(str, argv[*num_word0]) != NULL && !options->i) ||
               (options->i && strreg(str, argv[*num_word0]) != -1))) {
            print_str(options, name, str, number_str, argv[*num_word0]);
            n++;
            break;
          } else if (options->v &&
                     ((strstr(str, argv[*num_word0]) == NULL && !options->i) ||
                      (options->i && strreg(str, argv[*num_word0]) == -1))) {
            flag_v = 1;
          } else if (options->v) {
            flag_v = 0;
            break;
          }
        }
        if (flag_v && options->v) {
          print_str(options, name, str, number_str, argv[*num_word0]);
          n++;
        }
      }
    }
    print_file(options, name, n);
    // fclose(file);
  } else if (!options->s) {
    printf("grep: %s: No such file or directory\n", name);
  }

  fclose(file);
}

void print_str(opt *options, char *name, char *str, int number_str,
               char *word) {
  if (!options->c && !options->l) {
    if (options->name != 1 && !options->h) {
      printf("%s:", name);
    }
    if (options->n == 1) {
      printf("%d:", number_str);
    }

    // if (options->o && !options->v) {
    //     printf("%s\n", word);
    // } else if (!options->o) {
    //     printf("%s", str);
    //     if (str[strlen(str)-1] != '\n') {
    //         printf("\n");
    //     }
    // }

    if (!options->o || options->v) {
      printf("%s", str);
      if (str[strlen(str) - 1] != '\n') {
        printf("\n");
      }
    } else /* if (options->i)*/ {
      // char *word_temp = strndup(str+ strreg(str, word), strlen(word));

      // char *word_temp = calloc(strlen(word), sizeof(char));
      // word_temp = strncpy (word_temp, str+ strreg(str, word), strlen(word));
      // printf("%s\n", word_temp);

      char *word_temp = calloc(strlen(word), sizeof(char));
      int j = 0;
      while ((strstr(str + j, word) != NULL && !options->i) ||
             (options->i && strreg(str + j, word) != -1)) {
        word_temp =
            strncpy(word_temp, str + j + strreg(str + j, word), strlen(word));
        j += strlen(word);
        printf("%s\n", word_temp);
      }
      free(word_temp);
    }
  }
}

void print_file(opt *options, char *name, int n) {
  if (options->c) {
    if (options->name != 1 && !options->h) {
      printf("%s:", name);
    }
    if (options->l) {
      if (n != 0) {
        printf("%d\n", 1);
        printf("%s\n", name);
      } else {
        printf("%d\n", 0);
      }
    } else {
      printf("%d\n", n);
    }
  } else if (options->l && n) {
    printf("%s\n", name);
  }
}

int strreg(char *str, char *word) {
  int res = -1;
  char *str0 = (char *)s21_to_lower(str);
  char *word0 = (char *)s21_to_lower(word);

  // printf("--------------\n");
  // printf("Stroka: %s", str0);
  // printf("Word: %s\n", word0);

  // if (strstr(str0, word0) == NULL) {
  //     res = -1;
  // } else {
  //     res = strstr(str0, word0)-str0;
  //     printf("ptr: %p\n", strstr(str0, word0));
  // }
  // printf("res: %d\n", res);

  res = strstr(str0, word0) == NULL ? -1 : strstr(str0, word0) - str0;
  // printf("Files: %p\n", strstr(str0, word0));

  free(str0);
  free(word0);
  return res;
}

void *s21_to_lower(const char *str) {
  char *res = NULL;
  if (str != NULL) {
    size_t n = strlen(str);
    res = (char *)calloc(n + 1, sizeof(char));
    if (res != NULL) {
      for (size_t i = 0; i < n; i++) {
        if (str[i] <= 'Z' && str[i] >= 'A') {
          res[i] = str[i] + ('a' - 'A');
        } else {
          res[i] = str[i];
        }
      }
      res[n] = '\0';
    }
  }
  return res;
}

void errors(int a, char c) {
  switch (a) {
    case 0:
      printf("Wrong format\n");
      break;
    case 1:
      printf("grep: option requires an argument -- e\n");
      printf(
          "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
          "[-C[num]]\n");
      printf(
          "\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
      printf(
          "\t[--context[=num]] [--directories=action] [--label] "
          "[--line-buffered]\n");
      printf("\t[--null] [pattern] [file ...]\n");
      break;
    case 2:
      printf(
          "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
          "[-C[num]]\n");
      printf(
          "\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
      printf(
          "\t[--context[=num]] [--directories=action] [--label] "
          "[--line-buffered]\n");
      printf("\t[--null] [pattern] [file ...]\n");
      break;
    case 3:
      printf("invalid option -- %c\n", c);
      printf(
          "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
          "[-C[num]]\n");
      printf(
          "\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
      printf(
          "\t[--context[=num]] [--directories=action] [--label] "
          "[--line-buffered]\n");
      printf("\t[--null] [pattern] [file ...]\n");
      break;
  }
}
