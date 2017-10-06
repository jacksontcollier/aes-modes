#include "aes-modes.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

const char *arg_flag_options = "k:i:o:v:";

ArgFlags* new_ArgFlags()
{
  ArgFlags *arg_flags = (ArgFlags *) malloc(sizeof(ArgFlags));

  arg_flags->key_file = NULL;
  arg_flags->in_file = NULL;
  arg_flags->out_file = NULL;
  arg_flags->iv_file = NULL;

  return arg_flags;
}

ArgFlags* parse_arg_flags(int argc, char * const argv[])
{
  int option;
  ArgFlags *arg_flags;

  arg_flags = new_ArgFlags();

  while ((option = getopt(argc, argv, arg_flag_options)) != -1) {
    switch(option) {
      case 'k':
        arg_flags->key_file = optarg;
        break;
      case 'i':
        arg_flags->in_file = optarg;
        break;
      case 'o':
        arg_flags->out_file = optarg;
        break;
      case 'v':
        arg_flags->iv_file = optarg;
        break;
      default:
        fprintf(stderr, "Unknown option\n");
        exit(1);
    }
  }

  if (arg_flags->key_file == NULL || arg_flags->in_file == NULL ||
      arg_flags->out_file == NULL) {
    fprintf(stderr, "-k -i -o options are required\n");
    exit(1);
  }

  return arg_flags;
}

void print_arg_flags(const ArgFlags *arg_flags)
{
  if (arg_flags->key_file != NULL) {
    printf("Key file: %s\n", arg_flags->key_file);
  }
  if (arg_flags->in_file != NULL) {
    printf("Input file: %s\n", arg_flags->in_file);
  }
  if (arg_flags->out_file != NULL) {
    printf("Output file: %s\n", arg_flags->out_file);
  }
  if (arg_flags->iv_file != NULL) {
    printf("IV file: %s\n", arg_flags->iv_file);
  }
}

char* read_file_contents(char *filename)
{
  FILE* fin;
  char* file_buf;
  size_t file_length;
  size_t bytes_read;
  size_t end;

  fin = fopen(filename, "r");
  fseek(fin, 0, SEEK_END);
  file_length = ftell(fin);
  fseek(fin, 0, SEEK_SET);
  file_buf = (char *) malloc(sizeof(char) * (file_length + 1));

  if (file_buf != NULL) {
    bytes_read = fread(file_buf, sizeof(char), file_length, fin);
    end = bytes_read < file_length - 1 ? bytes_read : file_length - 1;
    file_buf[end] = '\0';
  }
  fclose(fin);

  return file_buf;
}

