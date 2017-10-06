#include "aes-modes.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

ByteBuf* new_ByteBuf()
{
  ByteBuf* byte_buf;

  byte_buf = (ByteBuf *) malloc(sizeof(ByteBuf));
  byte_buf->data = NULL;
  byte_buf->len = 0;

  return byte_buf;
}

AesKey* new_AesKey()
{
  AesKey* aes_key;
  aes_key = (AesKey *) malloc(sizeof(AesKey));
  aes_key->hex_encoding = NULL;
  aes_key->byte_encoding = NULL;
  aes_key->hex_len = 0;
  aes_key->byte_len = 0;
  aes_key->bit_len = 0;

  return aes_key;
}

ByteBuf* read_file_contents(char *filename)
{
  FILE* fin;
  ByteBuf* file_buf;
  size_t file_len;

  fin = fopen(filename, "r");
  fseek(fin, 0, SEEK_END);
  file_len = ftell(fin);
  fseek(fin, 0, SEEK_SET);

  file_buf = new_ByteBuf();
  file_buf->data = (unsigned char *) malloc(file_len);

  if (file_buf != NULL && file_buf->data != NULL) {
    file_buf->len = fread(file_buf->data, sizeof(unsigned char), file_len, fin);
  }
  fclose(fin);

  return file_buf;
}

AesKey* get_aes_key(char* key_file)
{
  AesKey* aes_key;

  aes_key = new_AesKey();
  aes_key->hex_encoding = read_file_contents(key_file);
  aes_key->hex_len = aes_key->hex_encoding->len;
  aes_key->byte_len = (aes_key->hex_len / 2);
  aes_key->bit_len = aes_key->byte_len * 8;
  aes_key->byte_encoding = hex_decode(aes_key->hex_encoding);

  return aes_key;
}

unsigned char hex_2_dec(unsigned char hex_char)
{
  if (hex_char >= '0' && hex_char <= '9') {
    return hex_char - '0';
  }

  if (hex_char >= 'A' && hex_char <= 'F') {
    return (hex_char - 'A') + 10;
  }

  if (hex_char >= 'a' && hex_char <= 'f') {
    return (hex_char - 'a') + 10;
  }

  return hex_char;
}

ByteBuf* hex_decode(ByteBuf* hex_buf)
{
  size_t i;
  size_t buf_size;
  ByteBuf* bytes;

  buf_size = (hex_buf->len / 2) + (hex_buf->len % 2);
  bytes = new_ByteBuf();
  bytes->data = (unsigned char *) malloc(buf_size);
  bytes->len = buf_size;

  if (bytes != NULL) {
    for (i = 0; i < hex_buf->len; i += 2) {
      bytes->data[i/2] = hex_2_dec(hex_buf->data[i]) << 4;
      if (i + 1 >= hex_buf->len) break;
      bytes->data[i/2] |= hex_2_dec(hex_buf->data[i+1]);
    }
  }

  return bytes;
}

