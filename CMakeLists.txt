cmake_minimum_required(VERSION 3.27.7)
project(Up)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-4.0) # look into FindPkgConfig.cmake,
# it contains documentation
# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES
# contain what you expect

pkg_check_modules(GTK_LAYER_SHELL gtk4-layer-shell-0)

add_subdirectory(src)
