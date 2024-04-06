#include "config.hpp"

#include <iostream>

Iris::ConfigRetriever *Iris::ConfigRetriever::pConfig_ = nullptr;

Iris::ConfigRetriever *Iris::ConfigRetriever::get_config_retriver()
{
  if (Iris::ConfigRetriever::pConfig_ == nullptr)
    Iris::ConfigRetriever::pConfig_ = new Iris::ConfigRetriever();

  return Iris::ConfigRetriever::pConfig_;
}

Iris::ConfigRetriever::ConfigRetriever()
{
  this->config = {1000, 1000, 500, false, {}};

  return;
}

void Iris::ConfigRetriever::call_function(int _page_id, int _row_id, int _button_id)
{
  std::cout << "Page: " << _page_id << "\nRow: " << _row_id << "\nButton: " << _button_id
            << std::endl;

  return;
}
