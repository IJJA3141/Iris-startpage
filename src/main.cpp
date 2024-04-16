#include "lua/config.hpp"

int main(int _argc, char *_argv[])
{
  Iris::ConfigRetriever::get_config_retriver()->debug_config();

  return 0;
}
