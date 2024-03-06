#include "xdg.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

std::vector<Iris::xdg::DesktopApplication> Iris::xdg::fetch()
{
  std::filesystem::path path = "/usr/share/applications/";
  std::string local = "Name[" + std::locale("").name().erase(2) + "]=";
  std::vector<Iris::xdg::DesktopApplication> vStr;
  std::ifstream file;
  std::string str;

  for (const std::filesystem::directory_entry path : std::filesystem::directory_iterator(path)) {
    if (path.path().extension() != ".desktop") goto abort;

    file.open(path.path());

    if (file.is_open()) {
      Iris::xdg::DesktopApplication app = {"", ""};

      while (std::getline(file, str)) {
        if (str.compare(0, 5, "Name=") == 0) {
          app.name = str.substr(5);
        } else if (str.compare(0, 9, local) == 0) {
          app.name = str.substr(9);
        } else if (str.compare(0, 5, "Exec=") == 0) {
          app.commandline = str.substr(5);
        } else if (str == "NoDisplay=true") {
          goto abort;
        }
      }

      vStr.push_back(app);
    }

  abort:
    file.close();
  }

  return vStr;
}
