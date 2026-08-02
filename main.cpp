#include <iostream>

#include "gravity.hpp"

int main() {
  nbodies::System planets;

  // READING FILE WITH PLANETS DATA
  planets.read_file("figure8.txt");

  // CREATING SFML WINDOW
  const int WIDTH = 800;
  const int HEIGHT = 800;
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "N-BODIES SIMULATION");
  window.setFramerateLimit(60);  // 60 FPS

  // GRAPHIC EVOLUTION OF THE SYSTEM
  while (window.isOpen()) {
    sf::Event event;

    // CHECKING WINDOW'S INTERACTIONS
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    planets.iteration();

    // SETTING FIGURES AND COLORS
    window.clear(sf::Color::Black);

    // CREATING ALL THE PLANETS
    for (size_t i{0}; i < planets.size(); ++i) {
      float x_pixel = nbodies::AU_pixel_x(planets.get_planet(i).position().x);
      float y_pixel = nbodies::AU_pixel_y(planets.get_planet(i).position().y);

      // CREATING A CIRCLE
      sf::CircleShape planet_shape(5.f);  // 5 PIXELS RADIUS
      planet_shape.setFillColor(sf::Color::Red);
      planet_shape.setOrigin(5.f, 5.f);

      // SETTING COORDINATES
      planet_shape.setPosition(x_pixel, y_pixel);

      // DRAWING THE PLANET
      window.draw(planet_shape);
    }
    window.display();
  }
}