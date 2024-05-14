link_directories(${LUA_LIBRARY_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
link_directories(${GTK_LAYER_SHELL_LIBRARY_DIRS})

include_directories(${LUA_INCLUDE_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(${GTK_LAYER_SHELL_INCLUDE_DIRS})

add_executable(
  iris 
  main.cpp
  app.cpp
  xdg.cpp
  lua/config.cpp
  lua/debugger.cpp
  ui/window.cpp
  ui/search.cpp
  ui/page.cpp
)

target_link_libraries(iris ${LUA_LIBRARIES})
target_link_libraries(iris ${GTKMM_LIBRARIES})
target_link_libraries(iris ${GTK_LAYER_SHELL_LIBRARIES})
