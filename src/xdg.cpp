#include "./lua/config.hpp"

#include <filesystem>
#include <fstream>

std::vector<Iris::Entry> Iris::xdg::fetch()
{
  std::filesystem::path path = "/usr/share/applications/";
  std::string local = "Name[" + std::locale("").name().erase(2) + "]=";
  std::vector<Iris::Entry> vPairStrStr;
  std::string local_name;
  std::ifstream file;
  std::string buffer;

  for (const std::filesystem::directory_entry path : std::filesystem::directory_iterator(path)) {
    if (path.path().extension() != ".desktop") goto abort;
    local_name.clear();

    file.open(path.path());

    if (file.is_open()) {
      Iris::Entry app;

      while (std::getline(file, buffer)) {
        if (buffer[0] == '[' && buffer != "[Desktop Entry]") break;
        if (buffer == "NoDisplay=true") goto abort;

        if (buffer.find("Exec=", 0, 5) == 0)
          app.command = buffer.substr(5);
        else if (buffer.find("Name=", 0, 5) == 0)
          app.label = buffer.substr(5);
        else if (buffer.find(local.c_str(), 0, local.size()) == 0)
          local_name = buffer.substr(local.size());
      }

      if (local_name != "" && Iris::ConfigRetriever::get_config_retriver()->config.useLocal)
        app.label = local_name;
      vPairStrStr.push_back(app);
    }
  abort:
    file.close();
  }

  return vPairStrStr;
}
