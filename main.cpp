#include "gravity.hpp"
#include <random>
#include <iostream>
#include <vector>

int main()
{
    
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