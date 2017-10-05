#include "aes-modes.h"

int main(int argc, char **argv)
{
  ArgFlags *arg_flags = parse_arg_flags(argc, argv);
  print_arg_flags(arg_flags);
  return 0;
}
