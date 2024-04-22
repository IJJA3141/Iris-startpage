#include "config.hpp"
#include "../const/error.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

const std::string buttonsRowName[3] = {"top_button", "center_button", "bottom_button"};

Iris::ConfigRetriever *Iris::ConfigRetriever::pConfig_ = nullptr;

Iris::ConfigRetriever *Iris::ConfigRetriever::get_config_retriver()
{
  if (Iris::ConfigRetriever::pConfig_ == nullptr)
    Iris::ConfigRetriever::pConfig_ = new Iris::ConfigRetriever();

  return Iris::ConfigRetriever::pConfig_;
}

Iris::ConfigRetriever::ConfigRetriever()
{
  this->L_ = luaL_newstate();
  luaL_openlibs(this->L_);

  int err = luaL_dofile(this->L_, "/usr/local/etc/iris/config.lua");

  if (err != LUA_OK) {
    std::cout << lua_tostring(this->L_, -1) << std::endl;
    exit(1);
  }

  this->debugger_.set_stack(this->L_);
  lua_getglobal(this->L_, "Config");

  this->config.imageWidth = this->get_float("image_width");
  this->config.width = this->get_float("width");
  this->config.height = this->get_float("height");
  this->config.useLocal = this->get_bool("use_local");
  this->config.isOverlay = this->get_bool("is_overlay");
  this->config.entryNumber = this->get_float("entry_number");

  lua_pushstring(this->L_, "pages");
  lua_gettable(this->L_, 1);

  if (!lua_istable(this->L_, -1)) {
    std::cout << ERROR_LUA_CONFIG_NOT_A_TABLE << std::endl;
    exit(1);
  }

  lua_remove(this->L_, 1);

  size_t tableSize = lua_rawlen(this->L_, 1);
  // for f*ck's sake one based indexing
  for (int i = 1; i <= tableSize; i++) {
    Iris::Config::Page page;

    lua_rawgeti(this->L_, 1, i);

    page.name = this->get_string("name");
    page.image = this->get_string("image");

    for (int j = 0; j < 3; j++) {
      lua_pushstring(this->L_, buttonsRowName[j].c_str());
      lua_gettable(this->L_, 2);

      page.aRow[j].title = this->get_string("title", -2, true);

      lua_pushstring(this->L_, "buttons");
      lua_gettable(this->L_, -2);

      page.aRow[j].vButton = this->iterate_table(i - 1, j);

      lua_remove(this->L_, -1);
      lua_remove(this->L_, -1);
    }

    this->config.vPage.push_back(page);
    lua_remove(this->L_, -1);
  }

  return;
}

bool Iris::ConfigRetriever::get_bool(std::string _name, int _tableIndex)
{
  lua_pushstring(this->L_, _name.c_str());
  lua_gettable(this->L_, _tableIndex);

  if (!lua_isboolean(this->L_, -1)) {
    std::cout << ERROR_LUA_CONFIG_BOOLEAN(_name) << std::endl;
    exit(1);
  }

  bool r = lua_toboolean(this->L_, -1);
  lua_remove(this->L_, -1);

  return r;
}

float Iris::ConfigRetriever::get_float(std::string _name, int _tableIndex)
{
  lua_pushstring(this->L_, _name.c_str());
  lua_gettable(this->L_, _tableIndex);
  if (!lua_isnumber(this->L_, -1)) {
    std::cout << ERROR_LUA_CONFIG_NUMBER(_name) << std::endl;
    exit(1);
  }

  float r = lua_tonumber(this->L_, -1);
  lua_remove(this->L_, -1);

  return r;
}

std::string Iris::ConfigRetriever::get_string(std::string _name, int _tableIndex,
                                              bool _handle_error)
{
  std::string r = "";

  lua_pushstring(this->L_, _name.c_str());
  lua_gettable(this->L_, _tableIndex);

  if (!lua_isstring(this->L_, -1)) {
    if (!_handle_error) {
      std::cout << ERROR_LUA_CONFIG_STRING(_name) << std::endl;
      exit(1);
    }

    lua_remove(this->L_, -1);
    return r;
  }

  r = lua_tostring(this->L_, -1);
  lua_remove(this->L_, -1);

  return r;
}

std::vector<Iris::Config::Button> Iris::ConfigRetriever::iterate_table(int _page_id, int _row_id)
{
  std::vector<Iris::Config::Button> r = {};

  int tableSize = lua_rawlen(this->L_, -1);
  for (int i = 1; i <= tableSize; i++) {
    Iris::Config::Button button;

    lua_rawgeti(this->L_, -1, i);

    button.label = this->get_string("label");
    button.image = this->get_string("image");

    button.button_id = i - 1;
    button.row_id = _row_id;
    button.page_id = _page_id;

    r.push_back(button);
    lua_remove(this->L_, -1);
  }

  return r;
}

void Iris::ConfigRetriever::call_function(int _page_id, int _row_id, int _button_id)
{
  std::cout << "Page: " << _page_id << "\nRow: " << _row_id << "\nButton: " << _button_id
            << std::endl;

  return;
};

void Iris::ConfigRetriever::debug_config()
{
  std::string str = "[LUA CONFIG] config:\n";

  (str += "width: ") += std::to_string(this->config.width) += "\n";
  (str += "height: ") += std::to_string(this->config.height) += "\n";
  (str += "image_width: ") += std::to_string(this->config.imageWidth) += "\n";

  str += "use_local: ";
  if (this->config.useLocal)
    str += "true";
  else
    str += "false";
  str += "\n";

  str += "is_overlay: ";
  if (this->config.isOverlay)
    str += "true";
  else
    str += "false";
  str += "\n";

  for (int k = 0; k < this->config.vPage.size(); k++) {
    (str += "\n[Page ") += std::to_string(k) += "]\n";
    (str += "name: ") += this->config.vPage[k].name += "\n";
    (str += "image: ") += this->config.vPage[k].image += "\n";

    for (int i = 0; i < 3; i++) {
      ((str += "\n[") += buttonsRowName[i]) += "]:\n";
      (str += "title: ") += this->config.vPage[k].aRow[i].title += "\n";

      for (int j = 0; j < this->config.vPage[k].aRow[i].vButton.size(); j++) {
        str += "{\n";

        (str += "\tlabel: ") += this->config.vPage[k].aRow[i].vButton[j].label += "\n";
        (str += "\timage: ") += this->config.vPage[k].aRow[i].vButton[j].image += "\n\n";

        (str += "\tpage id: ") +=
            std::to_string(this->config.vPage[k].aRow[i].vButton[j].page_id) += "\n";
        (str += "\trow id: ") += std::to_string(this->config.vPage[k].aRow[i].vButton[j].row_id) +=
            "\n";
        (str += "\tbutton id: ") +=
            std::to_string(this->config.vPage[k].aRow[i].vButton[j].button_id) += "\n";

        str += "}\n";
      }
    }
  }

  std::cout << str << std::endl;

  return;
}
