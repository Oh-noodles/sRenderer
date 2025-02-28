#include <iostream>
#include "geometry.hpp"
#include "model.hpp"
#include "renderer.hpp"
#include "tgaImage.hpp"
#include "shader.hpp"

int width = 800;
int height = 800;

int main() {
    Model model("obj/cube.obj");
    std::cout << "nverts: " << model.nverts() << std::endl;
    std::cout << "nfaces: " << model.nfaces() << std::endl;

    int d[] = {1, 2, 3};
    Vec<int, 3> v(d);
    // v[1] = 1;
    // v[2] = 2;
    // std::cout << v[0] << ", " << v[1] << ", " << v[2] << std::endl;
    // std::cout << v << std::endl;
    std::cout << embed<2>(v) << std::endl;
    std::cout << embed<4>(v) << std::endl;


    float m[] = {1,2,3,1,4,5,6,1,7,8,9,1,1,1,1,1};
    Matrix44f mat1({1,2,3,1,4,5,6,1,7,8,9,1,1,1,1,1});
    std::cout << mat1 << std::endl;
    Matrix44f mat2 = mat1.inverse();
    std::cout << mat2 << std::endl;
    Matrix44f mat3 = mat1.transpose();
    std::cout << mat3 << std::endl;

    float m4[] = {
        0 , 1 , -1 , 8 , 
        -9 , -7 , 1 , -3 , 
        -5 , 5 , 1 , -5 , 
        1 , -9 , 7 , -6
    };
    float m5[] = {
        2 , -8 , -4 , 4 , 
        -2 , -6 , -4 , 5 , 
        2 , -9 , -4 , -5 , 
        -5 , -3 , 0 , -5
    };
    std::cout << Matrix44f(m4) * Matrix44f(m5) << std::endl;

    TGAImage image = TGAImage(width, height, TGAImage::RGB);
    // line(image, 300, 200, 100, 200);

    Renderer renderer(image, model);
    // renderer.render();

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}
