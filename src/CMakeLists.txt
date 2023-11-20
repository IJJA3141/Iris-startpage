link_directories(${GTKMM_LIBRARY_DIRS})
link_directories(${GTK_LAYER_SHELL_LIBRARY_DIRS})
link_directories(${JSONCPP_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(${GTK_LAYER_SHELL_INCLUDE_DIRS})
include_directories(${JSONCPP_INCLUDE_DIRS})

add_executable(
  app.out
  main.cpp
  gtk/core/application.cpp
  gtk/core/background.cpp
  pixwrap.cpp
  image_processor.cpp
  gtk/widgets/module.cpp
  gtk/widgets/row.cpp
  gtk/widgets/gif.cpp)

target_link_libraries(app.out ${GTKMM_LIBRARIES})
target_link_libraries(app.out ${GTK_LAYER_SHELL_LIBRARIES})
target_link_libraries(app.out ${JSONCPP_LIBRARIES})
