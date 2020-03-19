#include <igl/readOFF.h>
#include <igl/writeOFF.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/copyleft/cgal/remesh_self_intersections.h>
#include <igl/remove_unreferenced.h>
#include <iostream>

Eigen::MatrixXd V;
Eigen::MatrixXi F;

Eigen::MatrixXd VV;
Eigen::MatrixXi FF;
Eigen::MatrixXi IF;
Eigen::VectorXi J;
Eigen::VectorXi IM;
Eigen::VectorXi UIM;

Eigen::MatrixXd SV;
Eigen::MatrixXi SF;

// This function is called every time a keyboard button is pressed
bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier)
{
	std::cout<<"Key: "<<key<<" "<<(unsigned int)key<<std::endl;
	if (key == '1'){
		// Clear should be called before drawing the mesh
		viewer.data().clear();
		// Draw_mesh creates or updates the vertices and faces of the displayed mesh.
		// If a mesh is already displayed, draw_mesh returns an error if the given V and
		// F have size different than the current ones
		viewer.data().set_mesh(V, F);
		viewer.core().align_camera_center(V,F);
	}else if (key == '2'){
		viewer.data().clear();
		viewer.data().set_mesh(VV, FF);
		viewer.core().align_camera_center(VV,FF);
	}
	return false;
}

int main(int argc, char *argv[])
{
	// Load two meshes
	igl::readOFF("./intersect.off", V, F);
	igl::copyleft::cgal::RemeshSelfIntersectionsParam params;
	// resolve intersections
	igl::copyleft::cgal::remesh_self_intersections(V,F,params,VV,FF,IF,J,IM);
	// _apply_ duplicate vertex mapping IM to FF
	std::for_each(FF.data(),FF.data()+FF.size(),[&](int & a){a=IM(a);});
	// remove any vertices now unreferenced after duplicate mapping.
	igl::remove_unreferenced(VV,FF,SV,SF,UIM);
	
//	std::cout<<"J:"<<J<<std::endl;
//	std::cout<<"IM:"<<IM<<std::endl;
	std::cout<<"IF:"<<IF<<std::endl;
	
	igl::writeOFF("./intersect_out.off", VV,FF);
	igl::writeOFF("./intersect_out2.off", SV,SF);
	
	std::cout<<R"(
			   1 Switch to default mesh
			   2 Switch to remesh mesh
			   )";
	igl::opengl::glfw::Viewer viewer;
	// Register a keyboard callback that allows to switch between
	// the two loaded meshes
	viewer.callback_key_down = &key_down;
	viewer.data().set_mesh(V, F);
	viewer.launch();
}
