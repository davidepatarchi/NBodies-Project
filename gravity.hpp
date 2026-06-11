#ifndef NBODIES_GRAVITY_HPP
#define NBODIES_GRAVITY_HPP

#include <cmath>
#include <fstream>
#include <vector>

namespace nbodies {

namespace constants {
inline constexpr double G = 6.67e-11;
inline constexpr double eps = 1e-12;
inline constexpr double dt = 0.001;
inline constexpr long int AU = 149597870700;

}  // namespace constants

struct vector {
  double x;
  double y;

  vector& operator+(vector const& z);
  vector& operator*(double a);  // vedi se fare il prodotto simmetrico(overload
                                // di operatore fuori da vector)
  vector& operator-(vector const& z);
  bool operator==(vector const& z);
  double norm();
};

class Planet {
  double m_{0.};      // mass
  vector r_{0., 0.};  // position
  vector v_{0., 0.};  // velocity
  vector a_{0., 0.};  // acceleration
  bool check_m_validity();

 public:
  Planet(double m, vector const& r, vector const& v, vector const& a);

  double & mass();
  vector& position();      // get position
  vector& velocity();      // get velocity
  vector& acceleration();  // get acceleration
};

class System {
 private:
  std::vector<Planet> planets;

 public:
  void iteration();
  void read_file (const std::string& filename);

  double energy() {
    double kinetic{0.};
    for (int i{0}; i < planets.size(); ++i) {
      kinetic += 0.5 * planets[i].mass() * pow(planets[i].velocity().norm(), 2);
    }
    double potential() {}
  }
};

}  // namespace nbodies

#endif