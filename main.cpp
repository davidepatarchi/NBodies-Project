#include <iostream>

#include "gravity.hpp"

int main() {
  int N;
  std::cout << "How many planets are request?" << '\n';
  std::cin >> N;
  double T;
  std::cout << "How many seconds will the simulation last?" << '\n';
  std::cin >> T;

  nbodies::System planets;
  planets.read_file("dati.txt");

  for (int t{0}; t < T; t += nbodies::constants::dt) {
    planets.iteration();

    std::cout << "ITERATION NUMBER: " << t << '\n';
    for (int i{0}; i < N; ++i) {
      std::cout << "Mass : " << planets.get_planet(i).mass() << '\n';
      std::cout << "Position : " << planets.get_planet(i).position().x << ", "
                << planets.get_planet(i).position().y << '\n';
      std::cout << "Velocity : " << planets.get_planet(i).velocity().x << ", "
                << planets.get_planet(i).velocity().y << '\n';
      std::cout << "Velocity : " << planets.get_planet(i).acceleration().x
                << ", " << planets.get_planet(i).acceleration().y << '\n';
    }
    std::cout << "Energy: " << planets.energy() << "\n\n";
  }
}