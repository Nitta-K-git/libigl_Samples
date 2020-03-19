cmake_minimum_required(VERSION 3.6)

# Create Project
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
# project(${ProjectId} CXX)
project(${ProjectId})
message(${ProjectId})

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/W1>")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake) # modeuleパスにローカルのFindLIBIGL.cmakeも追加

# cgal
find_package(CGAL)

# libigl
# option(LIBIGL_WITH_COMISO            "Use CoMiso"                   ON)
# option(LIBIGL_WITH_EMBREE            "Use Embree"                   ON)
option(LIBIGL_WITH_OPENGL            "Use OpenGL"                   ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"                     ON)
# option(LIBIGL_WITH_OPENGL_GLFW_IMGUI "Use ImGui"                    ON)
# option(LIBIGL_WITH_PNG               "Use PNG"                      ON)
# option(LIBIGL_WITH_TETGEN            "Use Tetgen"                   ON)
# option(LIBIGL_WITH_TRIANGLE          "Use Triangle"                 ON)
# option(LIBIGL_WITH_PREDICATES        "Use exact predicates"         ON)
# option(LIBIGL_WITH_XML               "Use XML"                      ON)
# option(LIBIGL_WITH_PYTHON            "Use Python"                   ${LIBIGL_BUILD_PYTHON})

find_package(LIBIGL REQUIRED QUIET)

if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX d)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

# Add your project files
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
  PRIVATE
    main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_link_libraries(${PROJECT_NAME} 
  igl::core
  # igl::comiso
  # igl::embree
  igl::opengl
  igl::opengl_glfw
  # igl::opengl_glfw_imgui
  # igl::png
  # igl::tetgen
  # igl::triangle
  # igl::predicates
  # igl::xml
  CGAL::CGAL
)
