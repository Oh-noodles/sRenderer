#include <cstdint>
#include <iostream>
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "geometry.hpp"
#include "model.hpp"
#include "renderer.hpp"
#include "tgaImage.hpp"
#include "shader.hpp"
#include <SFML/Graphics.hpp>

#define PI 3.14159265358979323846

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

    const float angleSpeed = PI * 2 / 6000;
    float angle = 0;

    Renderer renderer(width, height, model);
    sf::Clock clock;
    clock.start();

    // TGAImage image = renderer.render(Vec3f({0, 0, 3}), Vec3f({0, 0, 0}), Vec3f({0, 1, 0}));
    // image.flip_vertically();
    // image.write_tga_file("output1.tga");


    auto window = sf::RenderWindow(sf::VideoMode({(unsigned int)width, (unsigned int)height}), "sRenderer");
    window.setFramerateLimit(60);
    std::uint8_t *imageData = NULL;


    while (window.isOpen()) {
      while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
          window.close();
        }
      }
      window.clear();
      
      float elapsedTime = clock.getElapsedTime().asMilliseconds();
      clock.restart();
      angle += angleSpeed * elapsedTime;
      if (angle > PI*2)
        angle -= PI*2;

      TGAImage image = renderer.render(3.f * Vec3f({std::cos(angle), 0, -std::sin(angle)}), Vec3f({0, 0, 0}), Vec3f({0, 1, 0}));
      image.flip_vertically();

      imageData = image.buffer();
      sf::Image sfImage(sf::Vector2u(width, height), imageData);

      sf::Texture texture;
      bool ret = texture.loadFromImage(sfImage);

      sf::Sprite sprite(texture);
      window.draw(sprite);


      window.display();
    }

    return 0;
}
