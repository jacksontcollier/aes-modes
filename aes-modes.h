typedef struct arg_flags
{
  char *key_file;
  char *in_file;
  char *out_file;
  char *iv_file;
} ArgFlags;

ArgFlags* new_ArgFlags();

ArgFlags* parse_arg_flags(int argc, char * const argv[]);

void print_arg_flags(const ArgFlags *arg_flags);

char* read_file_contents(char *filename);
