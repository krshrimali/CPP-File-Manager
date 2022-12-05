cmake_minimum_required(VERSION 3.0.0)
project(cpp-file-manager-samples VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
enable_testing()

include_directories("../include")
add_executable(fmanager sample.cpp)
target_link_libraries(fmanager ${CMAKE_CURRENT_SOURCE_DIR}/libcpp-file-manager.a)
add_definitions(-DNDEBUG)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
