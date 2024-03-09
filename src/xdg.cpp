#include "xdg.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

std::vector<std::pair<std::string, std::string>> Iris::Xdg::fetch()
{
  std::filesystem::path path = "/usr/share/applications/";
  std::string local = "Name[" + std::locale("").name().erase(2) + "]=";
  std::vector<std::pair<std::string, std::string>> vPairStrStr;
  std::ifstream file;
  std::string buffer;

  bool _ = false;

  for (const std::filesystem::directory_entry path : std::filesystem::directory_iterator(path)) {
    if (path.path().extension() != ".desktop") goto abort;

    file.open(path.path());

    if (file.is_open()) {
      std::pair<std::string, std::string> app("", "");

      std::cout << "?????" << std::endl;

      while (std::getline(file, buffer)) {
        if (buffer.compare(0, 5, "Name=") == 0) {
          app.first = buffer.substr(5);
          if (buffer == "Name=Firefox Developer Edition") _ = true;
        } else if (buffer.compare(0, 9, local) == 0) {
          app.first = buffer.substr(9);
          std::cout << app.first << std::endl;
        } else if (buffer.compare(0, 5, "Exec=") == 0) {
          app.second = buffer.substr(5);
        } else if (buffer == "NoDisplay=true") {
          goto abort;
        }
      }

      vPairStrStr.push_back(app);
    }
  abort:
    file.close();
  }

  return vPairStrStr;
}
