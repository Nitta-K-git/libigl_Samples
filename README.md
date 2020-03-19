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

# cgal
# find_package(CGAL)

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
  # CGAL::CGAL
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

- 関数のリファレンスはないらしい？(ヘッダファイルに一応記載されてるものもある)
- Eigenの配列データ(頂点、面番号、色など)で管理しているだけ。Eigenをnumpyのように使って、データ処理するのが基本になる。
- メッシュ用クラスは強いて言えば`ViewerData`クラス
- `igl::opengl::glfw::Viewer`が`igl::opengl::ViewerData`をVector型で持っている。
- MATLABを参考に作られている機能が多い。MATLABと連携できる。
- hole fillingの機能はない
- Boolean演算はCGALとの連携が必要
  - オプションにcgalをつけると自動でダウンロードしてくる(自分の環境ではダウンロードが失敗した)
  - find_packageで環境構築済みのCGALを見つけるようにしたらうまくいった
- デフォルトのviewerの操作感はいまいち。オブジェクトをひっくり返すと回転方向が逆になってしまう
  - VCGのtrackballの方が使いやすい



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
)
```



# Usage

## Create Data

Eigenでデータ作るだけ

```cpp
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
```



## Viewer

```cpp
#include <igl/readOFF.h>
#include <igl/opengl/glfw/Viewer.h>
Eigen::MatrixXd V;
Eigen::MatrixXi F;
int main(int argc, char *argv[]){
  igl::readOFF(TUTORIAL_SHARED_PATH "/bunny.off", V, F);
  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.launch();
}
```

### [表示するだけ](https://libigl.github.io/tutorial/#visualizing-surfaces)
### [キーイベント関数の登録](https://libigl.github.io/tutorial/#interaction-with-keyboard-and-mouse)

### [表示データの切り替え](https://libigl.github.io/tutorial/#interaction-with-keyboard-and-mouse)

### [色の表示](https://libigl.github.io/tutorial/#scalar-field-visualization)
- 頂点に対してRGBの色配列を指定(Open3dと似ている)
### [頂点にラベルを表示](https://libigl.github.io/tutorial/#overlays)
### [描画画面内にGUI追加](https://libigl.github.io/tutorial/#viewer-menu)
- GUI描画用のコールバック関数を登録する
- コールバック関数内で分岐処理させる
### [複数データの読み込みと削除](https://libigl.github.io/tutorial/#multiple-meshes)
- 複数データの読み込みにデフォルトで対応している。インデックスで管理
### [複数視点からの表示を並べる](https://libigl.github.io/tutorial/#multiple-views)
- 31個のマルチビューを作成できる

## Viewer Function Sample

```cpp
viewer.callback_key_down = &key_down;
viewer.data().show_lines = false;
viewer.data().set_mesh(V, F);
viewer.data().set_normals(N_faces);
```

## [Other Matlab-style Functions](https://libigl.github.io/tutorial/#other-matlab-style-functions)



## Read/Write

[libigl file formats](https://libigl.github.io/file-formats/#libigl-file-formats)

```cpp
#include <igl/readOFF.h>
#include <igl/writeOBJ.h>
Eigen::MatrixXd V;
Eigen::MatrixXi F;
igl::readOFF("./in.off", V, F);
igl::writeOBJ("./out.obj",V,F);
```

## Set Normals

```cpp
#include <igl/per_vertex_normals.h>
#include <igl/per_face_normals.h>
#include <igl/per_corner_normals.h>

// Compute per-face normals
igl::per_face_normals(V,F,N_faces);
// Compute per-vertex normals
igl::per_vertex_normals(V,F,N_vertices);
// Compute per-corner normals, |dihedral angle| > 20 degrees --> crease
igl::per_corner_normals(V,F,20,N_corners);

viewer.data().set_normals(N_faces);
```

## Curvature

```cpp
VectorXd K;
// Compute integral of Gaussian curvature
igl::gaussian_curvature(V,F,K);

```

## Mass matrix

[知っておきたい振動解析 その 2](https://www.structure.jp/column36/column36_8.html)

## [remesh_self_intersections](https://github.com/libigl/libigl/blob/master/include/igl/copyleft/cgal/remesh_self_intersections.h)

メッシュの自己交差を解消する機能。tutorialは[ここ](https://libigl.github.io/tutorial/#generalized-winding-number)に記載あり。

## [Picking](https://libigl.github.io/tutorial/#picking)

## [Repair mesh intersection](https://github.com/libigl/libigl/blob/master/include/igl/copyleft/cgal/remesh_self_intersections.h)

自己交差が起きているメッシュを分割して修正する

CGALのリンクが必要

```cpp
#include <igl/readOFF.h>
#include <igl/writeOFF.h>
#include <igl/copyleft/cgal/remesh_self_intersections.h>
#include <igl/remove_unreferenced.h>

Eigen::MatrixXd V,VV,SV;
Eigen::MatrixXi F,FF,SF;
Eigen::MatrixXi IF,J,IM,UIM;

int main(int argc, char *argv[]){
	igl::readOFF("./intersect.off", V, F);
	// resolve intersections
	igl::copyleft::cgal::RemeshSelfIntersectionsParam params;
	igl::copyleft::cgal::remesh_self_intersections(V,F,params,VV,FF,IF,J,IM);
	// _apply_ duplicate vertex mapping IM to FF
	std::for_each(FF.data(),FF.data()+FF.size(),[&](int & a){a=IM(a);});
	// remove any vertices now unreferenced after duplicate mapping.
	igl::remove_unreferenced(VV,FF,SV,SF,UIM);
	
	igl::writeOFF("./intersect_out.off", VV,FF);
	igl::writeOFF("./intersect_out2.off", SV,SF);
}
```



# Eigen Usage

- [【C++】Eigen関数一覧 - Qiita](https://qiita.com/kenichi-t/items/616b50e8366d5d341db9)

## Bounding Box

```cpp
Eigen::Vector3d m = V.colwise().minCoeff();
Eigen::Vector3d M = V.colwise().maxCoeff();
```

## Create Vertex,Face,Edge

```cpp
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
Eigen::MatrixXi E_box(12,2);
E_box <<
    0, 1,
    1, 2,
    2, 3,
    3, 0,
    4, 5,
    5, 6,
    6, 7,
    7, 4,
    0, 4,
    1, 5,
    2, 6,
    7 ,3;
// Plot the edges of the bounding box
for (unsigned i=0;i<E_box.rows(); ++i)
    viewer.data().add_edges(
        V_box.row(E_box(i,0)),
        V_box.row(E_box(i,1)),
        Eigen::RowVector3d(1,0,0)
	);
```

## リサイズ(自己変換)

- m.resize(r, c)	自己変換：r×c行列にリサイズ※値は0クリア
- m.conservativeResize(r, c)　自己変換：r×c行列にリサイズ※値は保持、変更しない行/列はEigen::NoChange 