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

  double init_scale_energy{planets.scale_energy()};
  nbodies::vector init_scale_momentum{planets.scale_momentum()};
  double init_scale_angular_momentum{planets.scale_angular_momentum()};

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
      for (int tau{0}; tau < 86400; tau += nbodies::constants::dt){
        planets.iteration();
        planets.collision();
      }
    }

    // SETTING FIGURES AND COLORS
    window.clear(sf::Color::Black);
    std::vector<sf::Color> palette = {
        sf::Color::Yellow,  sf::Color::Red,
        sf::Color::Green,   sf::Color(139, 69, 19) /*Brown*/,
        sf::Color::Magenta, sf::Color::Cyan,
        sf::Color::Blue};

    // CREATING ALL THE PLANETS
    for (size_t i{0}; i < planets.size(); ++i) {
      float x_pixel = nbodies::AU_pixel_x(planets.get_planet(i).position().x);
      float y_pixel = nbodies::AU_pixel_y(planets.get_planet(i).position().y);

      // CREATING A CIRCLE
      sf::CircleShape planet_shape(float(nbodies::pixel_radius(
          planets.get_planet(i).radius())));  // 5 PIXELS RADIUS
      planet_shape.setFillColor(palette[i % palette.size()]);
      planet_shape.setOrigin(5.f, 5.f);

      // SETTING COORDINATES
      planet_shape.setPosition(x_pixel, y_pixel);

      // DRAWING THE PLANET
      window.draw(planet_shape);
    }
    window.display();

    t += 86400.;
  }

  double fin_energy{planets.energy()};
  nbodies::vector fin_momentum{planets.momentum()};
  double fin_angular_momentum{planets.angular_momentum()};

  double fin_scale_energy{planets.scale_energy()};
  nbodies::vector fin_scale_momentum{planets.scale_momentum()};
  double fin_scale_angular_momentum{planets.scale_angular_momentum()};

  std::cout << '\n';
  std::cout << "INITIAL AND FINAL ENERGIES: " << init_energy << ", "
            << fin_energy << " J \n";
  std::cout << "INITIAL AND FINAL SCALE ENERGIES: " << init_scale_energy << ", "
            << fin_scale_energy << " J \n";
  if (init_energy == fin_energy) {
    std::cout << "ENERGY CONSERVED!"<< '\n';
  } else {
    double mean_scale_energy = (fin_scale_energy + init_scale_energy) / 2;
    double err_energy = std::abs(fin_energy - init_energy);
    double rel_err_energy = std::abs(err_energy / mean_scale_energy);
    std::cout << "RELATIVE ERROR: " << rel_err_energy * 100;

    if (rel_err_energy <= 0.01) {
      std::cout << " -> ENERGY CONSERVED!" << "\n\n";
    } else {
      std::cout << " -> ENERGY NOT CONSERVED!" << "\n\n";
    }
  }

  std::cout << "INITIAL AND FINAL MOMENTUMS: (" << init_momentum.x << "; "
            << init_momentum.y << ") kg m/s, (" << fin_momentum.x << "; " << fin_momentum.y << ") kg m/s \n"; 
            std::cout << "INITIAL AND FINAL SCALE MOMENTUMS: (" << init_scale_momentum.x << "; "
            << init_scale_momentum.y << ") kg m/s, (" << fin_scale_momentum.x << "; " << fin_scale_momentum.y << ") kg m/s \n"; 
  if (init_momentum == fin_momentum) {
    std::cout << "MOMENTUM CONSERVED!" << '\n';
  } else {
    double mean_scale_momentum = (fin_scale_momentum.norm() + init_scale_momentum.norm()) / 2;
    double err_momentum = std::abs(fin_momentum.norm() - init_momentum.norm());
    double rel_err_momentum = err_momentum / mean_scale_momentum;
    std::cout << "RELATIVE ERROR: " << rel_err_momentum * 100;

    if (rel_err_momentum <= 0.01) {
      std::cout << " -> MOMENTUM CONSERVED!" << "\n\n";
    } else {
      std::cout << " -> MOMENTUM NOT CONSERVED!" << "\n\n";
    }
  }

  std::cout << "INITIAL AND FINAL ANGULAR MOMENTUMS: " << init_angular_momentum << ", "
            << fin_angular_momentum << " kg m^2/s \n";
  std::cout << "INITIAL AND FINAL SCALE ANGULAR MOMENTUMS: " << init_scale_angular_momentum << ", "
            << fin_scale_angular_momentum << " kg m^2/s \n";
  if (init_angular_momentum == fin_angular_momentum) {
    std::cout << "ANGULAR MOMENTUM CONSERVED!" << '\n';
  } else {
    double mean_scale_angular_momentum = (fin_scale_angular_momentum + init_scale_angular_momentum) / 2;
    double err_angular_momentum = (std::abs(fin_angular_momentum - init_angular_momentum));
    double rel_err_angular_momentum = std::abs(err_angular_momentum / mean_scale_angular_momentum);
    std::cout << "RELATIVE ERROR: " << rel_err_angular_momentum * 100;

    if (rel_err_angular_momentum <= 0.01) {
      std::cout << " -> ANGULAR MOMENTUM CONSERVED!" << '\n';
    } else {
      std::cout << " -> ANGULAR MOMENTUM NOT CONSERVED!" << '\n';
    }
  }
  std::cout << '\n';
}
