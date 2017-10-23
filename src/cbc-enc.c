#include "aes-modes.h"

int main(int argc, char **argv)
{
  ArgFlags *arg_flags;
  AesKey* aes_key;
  ByteBuf* cbc_plaintext;
  ByteBuf* cbc_ciphertext;
  ByteBuf* iv;

  arg_flags = parse_arg_flags(argc, argv);
  aes_key = get_aes_key(arg_flags->key_file);
  cbc_plaintext = get_cbc_plaintext(arg_flags->in_file);
  iv = get_iv(arg_flags->iv_file);

  cbc_ciphertext = cbc_aes_encrypt(aes_key, cbc_plaintext, iv);

  write_file(cbc_ciphertext, arg_flags->out_file);

  return 0;
}
