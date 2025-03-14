#include <iostream>
#include "geometry.hpp"
#include "model.hpp"
#include "renderer.hpp"
#include "tgaImage.hpp"
#include "shader.hpp"

int width = 800;
int height = 800;

int main() {
    Model model("obj/african_head.obj", "texture/african_head_diffuse.tga");
    std::cout << "nverts: " << model.nverts() << std::endl;
    std::cout << "nfaces: " << model.nfaces() << std::endl;

    Vec3f v0({1, 2, 3});
    Vec3f v1({3, 8, -2});
    std::cout << (v0 - v1).normalize() << std::endl;
    v1.normalize();
    std::cout << v1 << std::endl;

    TGAImage image = TGAImage(width, height, TGAImage::RGB);
    // line(image, 300, 200, 100, 200);

    Renderer renderer(image, model);
    renderer.render();

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}
