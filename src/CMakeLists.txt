link_directories(${GTKMM_LIBRARY_DIRS})
link_directories(${GTK_LAYER_SHELL_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(${GTK_LAYER_SHELL_INCLUDE_DIRS})

add_executable(
  iris.out 
  main.cpp
  ./ui/window.cpp
  ./ui/page.cpp
  )

target_link_libraries(iris.out ${GTKMM_LIBRARIES})
target_link_libraries(iris.out ${GTK_LAYER_SHELL_LIBRARIES})
