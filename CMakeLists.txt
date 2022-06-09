cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
set(PROJECT_NAME sonar_image)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV 4.0 REQUIRED)

# output paths in the build directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# include path
include_directories(${PROJECT_SOURCE_DIR}/src)

# source files
set(SONAR_IMAGE_SOURCE_FILES
  src/parameter.h
  src/filter.h
  src/fourier.h
  src/data.h
  src/map.h
  src/basic-process.h
	src/filter.cpp
  src/fourier.cpp
  src/map.cpp
	)

# main library
add_library(sonar_image_lib SHARED ${SONAR_IMAGE_SOURCE_FILES})
target_link_libraries(sonar_image_lib
  ${OpenCV_LIBS})

add_executable(sonar_image src/main.cpp)
target_link_libraries(sonar_image sonar_image_lib)

# install rules
install (TARGETS sonar_image sonar_image_lib
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)