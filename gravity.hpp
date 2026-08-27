#ifndef NBODIES_GRAVITY_HPP
#define NBODIES_GRAVITY_HPP
#include <cmath>
#include <fstream>
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
  vector operator/(double a) const;
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
  Planet(double mass, vector const& position, vector const& velocity,
         vector const& acceleration, double radius);

  double mass() const;
  vector& position();
  vector& velocity();
  vector& acceleration();
  vector const& position() const;
  vector const& velocity() const;
  vector const& acceleration() const;
  double radius() const;
};

class System {
 private:
  std::vector<Planet> planets;
  void check_size() const;

 public:
  Planet& get_planet(size_t i);
  size_t size() const;
  void iteration();
  void collision();
  void read_file(const std::string& filename);
  double const& energy();
  double const& scale_energy();
  vector const& momentum();
  vector const& scale_momentum();
  double const& angular_momentum();
  double const& scale_angular_momentum();
};

float AU_pixel_x(double x);
float AU_pixel_y(double y);
float pixel_radius(double r);

// namespace nbodies
}  // namespace nbodies
#endif
