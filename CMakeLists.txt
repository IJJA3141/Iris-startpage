cmake_minimum_required(VERSION 3.27.7)
project(Iris)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0 REQUIRED) # look into FindPkgConfig.cmake,
pkg_check_modules(GTK_LAYER_SHELL gtk4-layer-shell-0 REQUIRED)
pkg_check_modules(LUA lua5.4 REQUIRED)

add_subdirectory(src)
