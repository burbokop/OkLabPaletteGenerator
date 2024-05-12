cmake_minimum_required(VERSION 3.24.2)

project(
  cpp_palette_generator
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appcpp_palette_generator main.cpp)

qt_add_qml_module(
  appcpp_palette_generator
  URI
  org.burbokop.cpp_palette_generator
  VERSION
  1.0
  QML_FILES
  Main.qml
  SOURCES
  Palette.h
  Palette.cpp
  PaletteView.h
  PaletteView.cpp
  ColorUtils.h)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1. If
# you are developing for iOS or macOS you should consider setting an explicit,
# fixed bundle identifier manually though.
set_target_properties(
  appcpp_palette_generator
  PROPERTIES # MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appcpp_palette_generator
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
             MACOSX_BUNDLE TRUE
             WIN32_EXECUTABLE TRUE)

add_subdirectory(3rdparty/farver)
target_link_libraries(appcpp_palette_generator PRIVATE Qt6::Quick farver)

include(GNUInstallDirs)
install(
  TARGETS appcpp_palette_generator
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
