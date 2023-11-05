cmake_minimum_required(VERSION 3.27.7)
project(Up)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-4.0) # look into FindPkgConfig.cmake,
pkg_check_modules(GTK_LAYER_SHELL gtk4-layer-shell-0)
pkg_check_modules(JSONCPP jsoncpp)

add_subdirectory(src)
