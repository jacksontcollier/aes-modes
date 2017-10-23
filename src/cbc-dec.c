#include "aes-modes.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  ArgFlags *arg_flags;
  AesKey *aes_key;
  ByteBuf *cbc_ciphertext;
  ByteBuf *decrypted_cbc_ciphertext;

  arg_flags = parse_arg_flags(argc, argv);
  aes_key = get_aes_key(arg_flags->key_file);
  cbc_ciphertext = read_file_contents(arg_flags->in_file);
  decrypted_cbc_ciphertext = cbc_aes_decrypt(aes_key, cbc_ciphertext);
  write_cbc_decrypted_ciphertext(decrypted_cbc_ciphertext, arg_flags->out_file);

  return 0;
}
