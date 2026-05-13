#include "gravity.hpp"
#include <random>
#include <iostream>
#include <vector>

int main()
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> generate_mass_value(0., 9.);        // valore senza esponente masse
    std::uniform_int_distribution<int> generate_mass_exp(23, 30);              // esponente più alto e più basso massa(sole e mercurio)
    std::uniform_real_distribution<double> generate_position(-60., 60.);       // 60 UA è il raggio dell'orbita di nettuno
    std::uniform_real_distribution<double> generate_velocity(-47.4e3, 47.4e3); // è la vel più alta del sist solare, che è mercurio
    // dobbiamo fare un ciclo che crei sti valori per ogni pianeta del sistema(N pianeti cheìiesto in input)
    
    int N;
    std::cout << "Quanti pianeti?" << '\n';
    std::cin >> N;

    std::vector<nbodies::Planet> Planets_start{0};
    for (int i{0}; i < N; i++)
    {
        Planets_start[i].nbodies::Planet::add_mass(pow(generate_mass_value(eng), generate_mass_exp(eng)));

        Planets_start[i].nbodies::Planet::add_position_x(generate_position(eng));
        Planets_start[i].nbodies::Planet::add_position_y(generate_position(eng));

        Planets_start[i].nbodies::Planet::add_velocity_x(generate_velocity(eng));
        Planets_start[i].nbodies::Planet::add_velocity_y(generate_velocity(eng));

        Planets_start[i].nbodies::Planet::add_acceleration_x(0.);
        Planets_start[i].nbodies::Planet::add_acceleration_y(0.);
    }

    std::vector<nbodies::Planet> Planet_end{0};
}