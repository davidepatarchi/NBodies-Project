#include "gravity.hpp"

namespace nbodies {
// METODI DI VECTOR
vector& vector::operator+(vector const& z) {
  x += z.x;
  y += z.y;
  return *this;
}
vector& vector::operator*(double a) {
  x *= a;
  y *= a;
  return *this;
}
vector& vector::operator*(double a) {
  x *= a;
  y *= a;
  return *this;
}
double vector::norm() { return x * x + y * y; }
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
double& Planet::mass() { return m_; }
vector& Planet::position() { return r_; };
vector& Planet::velocity() { return v_; }
vector& Planet::acceleration() { return a_; }
bool Planet::check_m_validity() { return m_ > 0 ? true : false; }
// FINE METODI DI PLANET



// METODI DI SYSTEM
void System::iteration() {
  for (int i{0}; i < planets.size(); ++i) {
    planets[i].position() = planets[i].position() +
                            planets[i].velocity() * 0.01 +
                            planets[i].acceleration() * 0.5 * 0.01 *
                                0.01;  // controlla che il prodotto per uno
                                       // scalare non è commutativo
  }

  std::vector<vector> v;

  for (int i{0}; i < planets.size(); ++i) {
    vector somma{0., 0.};
    v.push_back(planets[i].acceleration());

    // cambia le acc
    for (int j{0}; j < planets.size(); ++j) {
      if (j != i) {
        double a =
            constants::G * planets[j].mass() *
            pow((constants::eps * constants::eps) +
                    pow((planets[j].position() - planets[i].position()).norm(),
                        2),
                -1.5);
        somma = somma + (planets[i].position() - planets[j].position()) * a;
      } else {
        // else what??
      }
    }

    planets[i].acceleration() = somma * (-1);
  }

  for (int i{0}; i < planets.size(); ++i) {
    planets[i].velocity() = planets[i].velocity() +
                            (planets[i].acceleration() + v[i]) * (0.5 * 0.01);
  }
}

void System::read_file(const std::string& filename) {
  std::ifstream file(filename);
  Planet body(0., {0., 0.}, {0., 0.}, {0., 0.});

  while (file >> body.mass() >> body.position().x >> body.position().y >>
         body.velocity().x >> body.velocity().y) {
    planets.push_back(body);
  }
}
// FINE METODI DI SYSTEM

}  // namespace nbodies