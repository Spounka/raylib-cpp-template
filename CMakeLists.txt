cmake_minimum_required(VERSION 3.20)
project("template")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_)
set(DEPS_DIR "${CMAKE_SOURCE_DIR}/extern")

include(FetchContent)


if(EMSCRIPTEN)
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY"
  )
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} -s GL_ENABLE_GET_PROC_ADDRESS=1")
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} -sINITIAL_MEMORY=536870912")
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} -s EXPORTED_RUNTIME_METHODS=HEAPF32")
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} --preload-file ${ASSETS_FOLDER}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sFORCE_FILESYSTEM=1")
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} --shell-file=${CMAKE_SOURCE_DIR}/shell.html")

  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -msse -msse2 -msse3 -msimd128 -fsanitize=undefined")
  set(CMAKE_C_FLAGS
      "${CMAKE_C_FLAGS} -msse -msse2 -msse3 -msimd128 -fsanitize=undefined")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")


endif()
set(BUILD_EXAMPLES
    OFF
    CACHE BOOL "" FORCE)
set(USE_EXTERNAL_GLFW
    OFF
    CACHE BOOL "" FORCE)
set(USE_WAYLAND_DISPLAY
    OFF
    CACHE BOOL "" FORCE)
set(SUPPORT_DRM
    OFF
    CACHE BOOL "" FORCE)


add_subdirectory(extern/raylib)
add_subdirectory(extern/raylib-cpp)

include_directories(src/)
include_directories(extern/raylib/src)
include_directories(extern/raylib-cpp/include)
if(BUILD_INCLUDE_BOX2D)
  set(BOX2D_BUILD_TESTBED
      OFF
      CACHE BOOL "" FORCE)

  set(BOX2D_BUILD_UNIT_TESTS
      OFF
      CACHE BOOL "" FORCE)
  FetchContent_Declare(box2d_dep GIT_REPOSITORY https://github.com/erincatto/box2d GIT_TAG 411acc3 GIT_SHALLOW FALSE
                        SOURCE_DIR     "${DEPS_DIR}/box2d"
                        BINARY_DIR     "${CMAKE_BINARY_DIR}/_deps/box2d"
  )
  FetchContent_GetProperties(box2d_dep)
  if(NOT box2d_dep_POPULATED)
    FetchContent_Populate(box2d_dep)
    add_subdirectory("${box2d_dep_SOURCE_DIR}" "${box2d_dep_BINARY_DIR}")
  endif()
  # include_directories(extern/box2d/include)
endif()

file(GLOB_RECURSE PROJECT_SOURCE_FILES "src/*.cpp" "src/*.c" "include/*.cpp")

add_custom_command(
  OUTPUT "${CMAKE_SOURCE_DIR}/compile_commands.json"
  COMMAND
    ${CMAKE_COMMAND} -E create_symlink
    "${CMAKE_BINARY_DIR}/compile_commands.json"
    "${CMAKE_SOURCE_DIR}/compile_commands.json"
  DEPENDS "${CMAKE_BINARY_DIR}/compile_commands.json"
  COMMENT "Copying compile_commands.json to project root")

add_custom_target(SymlinkCompileCommands ALL
                  DEPENDS "${CMAKE_SOURCE_DIR}/compile_commands.json")



add_executable(${PROJECT_NAME} main.cpp ${PROJECT_SOURCE_FILES})
add_dependencies(${PROJECT_NAME} SymlinkCompileCommands)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(BUILD_INCLUDE_BOX2D)
  target_link_libraries(${PROJECT_NAME} PRIVATE box2d)
endif()

