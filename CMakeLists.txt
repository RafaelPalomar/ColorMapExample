project(ColorMapExample)

cmake_minimum_required(VERSION 2.8)

find_package(VTK REQUIRED)

include(${VTK_USE_FILE})

add_executable(ColorMapExample
  ColorMapExample.cxx
)

target_link_libraries(ColorMapExample
  ${VTK_LIBRARIES}
)
