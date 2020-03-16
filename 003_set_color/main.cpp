#include <igl/readOFF.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/jet.h>

Eigen::MatrixXd V;
Eigen::MatrixXi F;
Eigen::MatrixXd C;

int main(int argc, char *argv[])
{
  // Load a mesh in OFF format
  // igl::readOFF("./screwdriver.off", V, F);
  igl::readOFF("./cube.off", V, F);

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);

  // Use the z coordinate as a scalar field over the surface
  Eigen::VectorXd Z = V.col(2);

  // Compute per-vertex colors
  igl::jet(Z,true,C); // zの値の分布に応じてCに色が入る(zの最大・最小のヒストグラム)。Cは内部でresize
  // 第2引数がfalseだと0-1の範囲で固定される

  // Add per-vertex colors
  viewer.data().set_colors(C);

  // Launch the viewer
  viewer.launch();
}