#include <iostream>

#include "gravity.hpp"

int main() {
  nbodies::System planets;

  // SETTING TIMES
  double t{0};
  double T;
  std::cout << "How many days is the simulations going to last?" << '\n';
  std::cin >> T;
  T *= 86400.;
  if (nbodies::constants::dt >= T) {
    throw std::runtime_error("ERROR: The time chosen is too short!");
  }

  // READING FILE WITH PLANETS DATA
  planets.read_file("solarsystem.txt");

  // CREATING SFML WINDOW
  const int WIDTH = 800;
  const int HEIGHT = 800;
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "N-BODIES SIMULATION");
  window.setFramerateLimit(60);  // 60 FPS

  std::vector<double> energy;
  std::vector<nbodies::vector> momentum;

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
      // CREATING ENERGY RANGE
      energy.push_back(planets.energy());
      momentum.push_back(planets.momentum());
    }

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

    t += nbodies::constants::dt;
  }

  double mean_energy{nbodies::get_mean(energy)};
  double error_energy{nbodies::get_error(energy)};
  double rel_err_energy{std::abs(error_energy / mean_energy * 100.)};
  std::cout << "ENERGY: " << mean_energy << " +/- " << error_energy
            << " (Relative error: " << rel_err_energy << "%)" << '\n';
  if (rel_err_energy < 1) {
    std::cout << "ENERGY IS CONSERVED" << "\n\n";
  } else {
    std::cout << "ENERGY IS NOT CONSERVED" << "\n\n";
  }

  //NON FUNZIONA PERCHE LE FUNZIONI SONO FATTE PER DEI VECTOR<DOUBLE> E NON VECTOR<NBODIES::VECTOR>
  /*double mean_momentum_x{nbodies::get_mean(momentum.x)};
  double error_momentum_x{nbodies::get_error(momentum.x)};
  double rel_err_momentum_x{
      std::abs(error_momentum.x / mean_momentum.x * 100.)};
  std::cout << "X-MOMENTUM: " << mean_momentum_x << " +/- " << error_momentum_x
            << " (Relative error: " << rel_err_momentum_x << "%)" << '\n';
  if (rel_err_energy < 1) {
    std::cout << "X-MOMENTUM IS CONSERVED" << "\n\n";
  } else {
    std::cout << "X-MOMENTUM IS NOT CONSERVED" << "\n\n";
  }*/
}
