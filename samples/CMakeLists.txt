cmake_minimum_required(VERSION 3.0.0)
project(cpp-file-manager-samples VERSION 0.1.0)

include(CTest)
enable_testing()

# add_library(libcpp-file-manager)

add_executable(main sample.cpp)
target_link_libraries(main ${CMAKE_CURRENT_SOURCE_DIR}/libcpp-file-manager.a)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
