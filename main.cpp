#include <iostream>

#include "gravity.hpp"

int main() {
  nbodies::System planets;

  // SETTING TIMES
  double t{0};
  double T;
  std::cout << "How many days is the simulations going to last?\n";
  std::cin >> T;
  T *= 86400.;
  if (nbodies::constants::dt >= T) {
    throw std::runtime_error("ERROR: The time chosen is too short!");
  }

  // READING FILE WITH PLANETS DATA
  planets.read_file("collision2.txt");

  // CREATING SFML WINDOW
  const int WIDTH = 800;
  const int HEIGHT = 800;
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "N-BODIES SIMULATION");
  window.setFramerateLimit(60);  // 60 FPS

  double init_energy{planets.energy()};
  nbodies::vector init_momentum{planets.momentum()};
  double init_angular_momentum{planets.angular_momentum()};

  // GRAPHIC EVOLUTION OF THE SYSTEM
  while (window.isOpen()) {
    sf::Event event;

    // CHECKING WINDOW'S INTERACTIONS
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (t <= T) {
      planets.iteration();
      planets.urti();
    }

    // SETTING FIGURES AND COLORS
    window.clear(sf::Color::Black);
    std::vector<sf::Color> palette = {sf::Color::Yellow,
                                      sf::Color::Red,
                                      sf::Color::Green,
                                      sf::Color(139, 69, 19) /*Brown*/,
                                      sf::Color::Magenta,
                                      sf::Color::Cyan,
                                      sf::Color::Blue};

    // CREATING ALL THE PLANETS
    for (size_t i{0}; i < planets.size(); ++i) {
      float x_pixel = nbodies::AU_pixel_x(planets.get_planet(i).position().x);
      float y_pixel = nbodies::AU_pixel_y(planets.get_planet(i).position().y);

      // CREATING A CIRCLE
      sf::CircleShape planet_shape(5.f);  // 5 PIXELS RADIUS
      planet_shape.setFillColor(palette[i % palette.size()]);
      planet_shape.setOrigin(5.f, 5.f);

      // SETTING COORDINATES
      planet_shape.setPosition(x_pixel, y_pixel);

      // DRAWING THE PLANET
      window.draw(planet_shape);
    }
    window.display();

    t += nbodies::constants::dt;
  }

  double fin_energy{planets.energy()};
  nbodies::vector fin_momentum{planets.momentum()};
  double fin_angular_momentum{planets.angular_momentum()};

  std::cout << '\n';
  std::cout << "ENERGY RATIO: " << std::abs(fin_energy / init_energy) << '\n';
  std::cout << "MOMENTUM RATIO: "
            << std::abs(fin_momentum.norm() / init_momentum.norm()) << '\n';
  std::cout << "ANGULAR MOMENTUM RATIO: "
            << std::abs(fin_angular_momentum / init_angular_momentum) << '\n';
  std::cout << '\n';
}
