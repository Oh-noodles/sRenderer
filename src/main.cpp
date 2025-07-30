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


std::string modelFiles[][2] = {
  {"obj/african_head.obj", "texture/african_head_diffuse.tga"},
  {"obj/shark.obj", "texture/shark_diffuse.tga"},
  {"obj/tree.obj", "texture/tree_diffuse.tga"}
};


int pickModel() {
    int modelIdx = -1;
    do {
      std::cout << "Choose a model blew:" << std::endl;
      std::cout << "0. head" << std::endl;
      std::cout << "1. shark" << std::endl;
      std::cout << "2. tree" << std::endl;
      std::cout << "Your choice [0-2]: ";
      std::cin >> modelIdx;
    } while(!(0 <= modelIdx && modelIdx < 3));
    return modelIdx;
}

int main() {
    int modelIdx = pickModel();

    Model model(modelFiles[modelIdx][0].c_str(), modelFiles[modelIdx][1].c_str());
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
    // image.write_tga_file("output.tga");

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

      float cameraDist = 2.f;
      TGAImage image = renderer.render(cameraDist * Vec3f({std::cos(angle), 0, -std::sin(angle)}), Vec3f({0, 0, 0}), Vec3f({0, 1, 0}));
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
