#include "aes-modes.h"

int main(int argc, char **argv)
{
  ArgFlags *arg_flags;
  AesKey *aes_key;
  ByteBuf *ctr_plaintext;
  ByteBuf *ctr_ciphertext;
  ByteBuf *iv;

  arg_flags = parse_arg_flags(argc, argv);
  aes_key = get_aes_key(arg_flags->key_file);
  ctr_plaintext = read_file_contents(arg_flags->in_file);
  iv = get_iv(arg_flags->iv_file);
  ctr_ciphertext = ctr_aes_encrypt(aes_key, ctr_plaintext, iv);

  print_arg_flags(arg_flags);
  return 0;
}
