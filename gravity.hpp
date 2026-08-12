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
inline constexpr double G = 6.67e-11;
inline constexpr double eps = 1e-12;
inline constexpr double dt = 86400.;
inline constexpr long int AU = 149597870700;

}  // namespace constants

struct vector {
  double x;
  double y;

  vector operator+(vector const& z) const;
  vector operator*(double a) const;
  // vedi se fare il prodotto simmetrico(overload di operatore fuori da vector)
  vector operator-(vector const& z) const;
  bool operator==(vector const& z) const;
  double norm() const;
};

class Planet {
 private:
  double m_{0.};       // mass
  vector r_{0., 0.};   // position
  vector v_{0., 0.};   // velocity
  vector a_{0., 0.};   // acceleration
  double radius_{0.};  // raggio per collisioni
  bool check_m_validity() const;
  bool check_radius() const;  // invariante di classe raggio

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
  void read_file(const std::string& filename);  // aggiunto il raggio
  double energy();
  vector momentum();
  double angular_momentum();
  void urti();
};

float AU_pixel_x(double x);
float AU_pixel_y(double y);

}  // namespace nbodies

#endif