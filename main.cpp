#include "gravity.hpp"
#include <iostream>

int main()
{   
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
        /*for (int i{0}; i < planets.size(); ++i) {
            std::cout << "Mass : " << planets[i].mass() << '\n';
            std::cout << "Position : " << planets[i].position().x << ', ' << planets[i].position().y << '\n';
        }*/
        std::cout << planets.energy();
    }

}