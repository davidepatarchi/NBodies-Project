#include "gravity.hpp"
#include <iostream>

namespace nbodies {

// METODI DI VECTOR
vector vector::operator+(vector const& z) const { return {x + z.x, y + z.y}; }
vector vector::operator*(double a) const { return {x * a, y * a}; }
vector vector::operator-(vector const& z) const { return {x - z.x, y - z.y}; }
bool vector::operator==(vector const& z)
    const {  // da capire se ha senso o se nei test farli separati x e y
  return x == z.x && y == z.y;
}

double vector::norm() const { return sqrt(x * x + y * y); }

// FINE METODI DI VECTOR

// METODI DI PLANET
Planet::Planet(double m, vector const& r, vector const& v, vector const& a) {
  m_ = m;
  r_.x = r.x;
  r_.y = r.y;
  v_.x = v.x;
  v_.y = v.y;
  a_.x = a.x;
  a_.y = a.y;
}
bool Planet::check_m_validity() { return m_ > 0 ? true : false; }

double& Planet::mass() {
  check_m_validity();
  return m_;
}
vector& Planet::position() { return r_; };
vector& Planet::velocity() { return v_; }
vector& Planet::acceleration() { return a_; }
// FINE METODI DI PLANET

// METODI DI SYSTEM
Planet& System::get_planet(size_t i) { return planets[i]; }

size_t System::size() const { return planets.size(); }

void System::iteration() {
  size_t N = planets.size();
  // evolving position
  for (size_t i{0}; i < N; ++i) {
    planets[i].position() =
        planets[i].position() + planets[i].velocity() * nbodies::constants::dt +
        planets[i].acceleration() * 0.5 *
            pow(nbodies::constants::dt, 2);  // controlla che il prodotto per
                                             // uno scalare non è commutativo
  }

  // saving initial acceleration and evolving acceleration
  std::vector<vector> init_acc;
  for (size_t i{0}; i < N; ++i) {
    vector somma{0., 0.};
    init_acc.push_back(planets[i].acceleration());

    for (size_t j{0}; j < N; ++j) {
      if (j != i) {
        double new_acc =
            constants::G * planets[j].mass() *
            pow((constants::eps * constants::eps) +
                    pow((planets[j].position() - planets[i].position()).norm(),
                        2),
                -1.5);
        somma =
            somma + (planets[i].position() - planets[j].position()) * new_acc;
      }
    }
    planets[i].acceleration() = somma * (-1);
  }

  // evolving velocity
  for (size_t i{0}; i < N; ++i) {
    planets[i].velocity() =
        planets[i].velocity() + (planets[i].acceleration() + init_acc[i]) *
                                    (0.5 * nbodies::constants::dt);
  }
}

void System::read_file(const std::string& filename) {
  std::ifstream file(filename);
  double mass;
  double position_x;
  double position_y;
  double velocity_x;
  double velocity_y;

  if (!file.is_open()) {
    std::cout << "PROBLEMA" <<'\n'; // Gestire eventuale errore di apertura file

  }

  while (file >> mass >> position_x >> position_y >> velocity_x >> velocity_y) {
    Planet body(mass, {position_x, position_y}, {velocity_x, velocity_y},
                {0., 0.});
    planets.push_back(body);
  }
}

double System::energy() {
  size_t N = planets.size();
  double kinetic{0.};
  for (size_t i{0}; i < N; ++i) {
    kinetic += 0.5 * planets[i].mass() * pow(planets[i].velocity().norm(), 2);
  }

  double potential{0.};
  for (size_t i{0}; i < N; ++i) {
    for (size_t j{0}; j < i; ++j) {
      potential += -nbodies::constants::G *
                   (planets[i].mass() * planets[j].mass()) /
                   (planets[i].position() - planets[j].position()).norm();
    }
  }
  return kinetic + potential;
}
// FINE METODI DI SYSTEM

//FUNZONI PER SFML
float AU_pixel_x(double x){
  return float((1 + x/nbodies::constants::AU)*400.);
}
float AU_pixel_y(double y){
  return float((1 - y/nbodies::constants::AU)*400.);
}

}  // namespace nbodies