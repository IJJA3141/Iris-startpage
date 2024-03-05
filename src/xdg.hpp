#ifndef _IRIS_XDG
#define _IRIS_XDG

#include <string>
#include <vector>

namespace Iris
{
namespace xdg
{
struct DesktopApplication {
  std::string name;
  std::string commandline;
};

std::vector<Iris::xdg::DesktopApplication> fetch();
}; // namespace xdg
}; // namespace Iris

#endif // !_IRIS_XDG
