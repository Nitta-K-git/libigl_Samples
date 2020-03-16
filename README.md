# libigl_Samples



# Install

Download from [github release page](https://github.com/libigl/libigl/releases) and unzip file.

set environment variable like `LIBIGL_DIR = C:\dev\libigl-2.1.0`

## Build tutorial

windowsでやる場合、なぜかWIN32のフラグが無効になっているため手動で追加する。

```bash
$ md build
$ cd build
$ cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="/utf-8 /EHsc /DWIN32 /w"
$ cmake --build .
```

# Project Example

[libigl/libigl-example-project: A blank project example showing how to use libigl and cmake.](https://github.com/libigl/libigl-example-project)

```cmake
cmake_minimum_required(VERSION 3.6)

# Create Project
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
# project(${ProjectId} CXX) # if set CXX, build is failed
project(${ProjectId})
message(${ProjectId})

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)

# libigl
option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)

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
    igl::opengl_glfw
)
```

```cpp
#include <igl/opengl/glfw/Viewer.h>

int main(int argc, char *argv[])
{
  // Inline mesh of a cube
  const Eigen::MatrixXd V= (Eigen::MatrixXd(8,3)<<
    0.0,0.0,0.0,
    0.0,0.0,1.0,
    0.0,1.0,0.0,
    0.0,1.0,1.0,
    1.0,0.0,0.0,
    1.0,0.0,1.0,
    1.0,1.0,0.0,
    1.0,1.0,1.0).finished();
  const Eigen::MatrixXi F = (Eigen::MatrixXi(12,3)<<
    1,7,5,
    1,3,7,
    1,4,3,
    1,2,4,
    3,8,7,
    3,4,8,
    5,7,8,
    5,8,6,
    1,5,6,
    1,6,2,
    2,6,8,
    2,8,4).finished().array()-1;

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.data().set_face_based(true);
  viewer.launch();
}
```

# libigl overview

関数のリファレンスはないらしい？

メッシュ用クラスはなく、Eigenの配列データ(頂点、面番号、色など)で管理しているだけ。

# Module Option

GLFWによる描画の機能などはデフォルトではOFFになっているので、CMakeで個別にONにする。

```cmake
# \libigl-2.1.0\CMakeLists.txt
option(LIBIGL_USE_STATIC_LIBRARY "Use libigl as static library" ON)
option(LIBIGL_WITH_COMISO            "Use CoMiso"                   ON)
option(LIBIGL_WITH_EMBREE            "Use Embree"                   ON)
option(LIBIGL_WITH_OPENGL            "Use OpenGL"                   ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"                     ON)
option(LIBIGL_WITH_OPENGL_GLFW_IMGUI "Use ImGui"                    ON)
option(LIBIGL_WITH_PNG               "Use PNG"                      ON)
option(LIBIGL_WITH_TETGEN            "Use Tetgen"                   ON)
option(LIBIGL_WITH_TRIANGLE          "Use Triangle"                 ON)
option(LIBIGL_WITH_PREDICATES        "Use exact predicates"         ON)
option(LIBIGL_WITH_XML               "Use XML"                      ON)
option(LIBIGL_WITH_PYTHON            "Use Python"                   ${LIBIGL_BUILD_PYTHON})

target_link_libraries(${PROJECT_NAME} 
    igl::core
    igl::opengl_glfw
    igl::opengl_glfw_imgui
)
```



# Usage

## Viewer

- [表示するだけ](https://github.com/libigl/libigl/tree/master/tutorial/102_DrawMesh/main.cpp)
- [キーイベント関数の登録](https://github.com/libigl/libigl/tree/master/tutorial/103_Events/main.cpp)
- [色の表示](https://github.com/libigl/libigl/tree/master/tutorial/104_Colors/main.cpp)
  - 頂点に対してRGBの色配列を指定(Open3dと似ている)
- [頂点にラベルを表示](https://github.com/libigl/libigl/tree/master/tutorial/105_Overlays/main.cpp)



