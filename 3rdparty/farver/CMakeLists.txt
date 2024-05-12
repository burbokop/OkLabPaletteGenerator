add_library(
  farver STATIC
  ${CMAKE_CURRENT_LIST_DIR}/farver/src/ColorSpace.cpp
  ${CMAKE_CURRENT_LIST_DIR}/farver/src/ColorSpace.h
  ${CMAKE_CURRENT_LIST_DIR}/farver/src/Comparison.cpp
  ${CMAKE_CURRENT_LIST_DIR}/farver/src/Comparison.h
  ${CMAKE_CURRENT_LIST_DIR}/farver/src/Conversion.cpp
  ${CMAKE_CURRENT_LIST_DIR}/farver/src/Conversion.h
  ${CMAKE_CURRENT_LIST_DIR}/farver/src/encode.cpp
  ${CMAKE_CURRENT_LIST_DIR}/farver/src/encode.h
  ${CMAKE_CURRENT_LIST_DIR}/farver/src/farver.cpp
  ${CMAKE_CURRENT_LIST_DIR}/farver/src/farver.h
  ${CMAKE_CURRENT_LIST_DIR}/farver/src/init.cpp
  ${CMAKE_CURRENT_LIST_DIR}/farver/src/Utils.h)

target_include_directories(farver PRIVATE /usr/share/R/include)
target_link_libraries(farver R)
