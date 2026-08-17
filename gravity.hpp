#ifndef NBODIES_GRAVITY_HPP
#define NBODIES_GRAVITY_HPP
#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace nbodies {

namespace constants {
inline constexpr double G = 6.6743e-11;
inline constexpr int dt = 60;
inline constexpr long int AU = 149597870700;

}  // namespace constants

struct vector {
  double x;
  double y;

  vector operator+(vector const& z) const;
  vector operator-(vector const& z) const;
  vector operator*(double a) const;
  // vedi se fare il prodotto simmetrico(overload di operatore fuori da vector)
  bool operator==(vector const& z) const;
  double norm() const;
};

class Planet {
 private:
  double mass_{0.};
  vector position_{0., 0.};
  vector velocity_{0., 0.};
  vector acceleration_{0., 0.};
  double radius_{0.};
  void check_mass() const;
  void check_radius() const;

 public:
  Planet(double m, vector const& r, vector const& v, vector const& a,
         double radius_);

  double mass() const;
  vector& position();      // get position
  vector& velocity();      // get velocity
  vector& acceleration();  // get acceleration
  vector const& position() const;
  vector const& velocity() const;
  vector const& acceleration() const;
  double radius() const;  // funzione per prendere il raggio
};

class System {
 private:
  std::vector<Planet> planets;

 public:
  Planet& get_planet(size_t i);
  size_t size() const;
  void iteration();
  void collision();
  void read_file(const std::string& filename);
  double energy();
  double scale_energy();
  vector momentum();
  vector scale_momentum();
  double angular_momentum();
  double scale_angular_momentum();
};

float AU_pixel_x(double x);
float AU_pixel_y(double y);
float pixel_radius(double r);

}  // namespace nbodies

#endif