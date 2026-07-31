#include <iostream>

#include "gravity.hpp"

int main() {
  double T;
  std::cout << "How many seconds will the simulation last?" << '\n';
  std::cin >> T;

  nbodies::System planets;
  planets.read_file("dati.txt");
  int N = planets.size();

  for (double t{nbodies::constants::dt}; t <= T; t += nbodies::constants::dt) {
    planets.iteration();

    std::cout << "ITERATION NUMBER: " << t << '\n';
    for (int i{0}; i < N; ++i) {
      std::cout << "Mass : " << planets.get_planet(i).mass() << '\n';
      std::cout << "Position : " << planets.get_planet(i).position().x << ", "
                << planets.get_planet(i).position().y << '\n';
      std::cout << "Velocity : " << planets.get_planet(i).velocity().x << ", "
                << planets.get_planet(i).velocity().y << '\n';
      std::cout << "Acceleration : " << planets.get_planet(i).acceleration().x
                << ", " << planets.get_planet(i).acceleration().y << '\n';
    }
    std::cout << "Energy: " << planets.energy() << "\n\n";
  }
}