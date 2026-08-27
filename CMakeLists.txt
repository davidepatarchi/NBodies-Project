cmake_minimum_required(VERSION 3.28)
project(progettopf VERSION 0.1.0)

include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

string(APPEND CMAKE_CXX_FLAGS
      " -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion"
      " -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast"
      " -fno-omit-frame-pointer")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  string(APPEND CMAKE_CXX_FLAGS " -D_GLIBCXX_ASSERTIONS")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  string(APPEND CMAKE_CXX_FLAGS " -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE")
endif()

string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined")
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  string(APPEND CMAKE_CXX_FLAGS " -D_GLIBCXX_SANITIZE_STD_ALLOCATOR")
endif()
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined")

find_package(SFML 2.6 COMPONENTS graphics REQUIRED)

add_executable(progetto main.cpp gravity.cpp)
target_link_libraries(progetto PRIVATE sfml-graphics)

file(COPY data data_test fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY data data_test fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)

if (BUILD_TESTING)

  add_executable(progetto.t gravity.test.cpp gravity.cpp)
  file(COPY data_test DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  add_test(NAME progetto.t COMMAND progetto.t)

endif()