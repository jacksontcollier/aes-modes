#include <stddef.h>

typedef struct arg_flags
{
  char *key_file;
  char *in_file;
  char *out_file;
  char *iv_file;
} ArgFlags;

ArgFlags* new_ArgFlags();

ArgFlags* parse_arg_flags(int argc, char * const argv[]);

typedef struct aes_key
{
  char* hex_encoding;
  unsigned char* byte_encoding;
  size_t hex_len;
  size_t byte_len;
  size_t bit_len;
} AesKey;

AesKey* new_AesKey();

AesKey* get_aes_key(char* key_file);

void print_arg_flags(const ArgFlags *arg_flags);

char* read_file_contents(char *filename);

unsigned char hex_2_dec(char hex_char);

unsigned char* hex_decode(char* hex_string);

