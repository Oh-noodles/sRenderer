#include <iostream>
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "geometry.hpp"
#include "model.hpp"
#include "renderer.hpp"
#include "tgaImage.hpp"
#include "shader.hpp"
#include <SFML/Graphics.hpp>

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

    Renderer renderer(width, height, model);
    TGAImage image = renderer.render(Vec3f({0, 0, 3}), Vec3f({0, 0, 0}), Vec3f({0, 1, 0}));

    image.flip_vertically();
    image.write_tga_file("output.tga");


    auto window = sf::RenderWindow(sf::VideoMode({(unsigned int)width, (unsigned int)height}), "sRenderer");
    window.setFramerateLimit(144);

    while (window.isOpen()) {
      while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
          window.close();
        }
      }

      window.clear();
      window.display();
    }

    return 0;
}
