#include "aes-modes.h"

int main(int argc, char **argv)
{
  ArgFlags *arg_flags;
  AesKey *aes_key;
  ByteBuf *ctr_ciphertext;
  ByteBuf *ctr_plaintext;

  arg_flags = parse_arg_flags(argc, argv);
  aes_key = get_aes_key(arg_flags->key_file);
  ctr_ciphertext = read_file_contents(arg_flags->in_file);
  ctr_plaintext = ctr_aes_decrypt(aes_key, ctr_ciphertext);
  write_file(ctr_plaintext, arg_flags->out_file);

  return 0;
}
