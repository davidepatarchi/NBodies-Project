#include "gravity.hpp"

namespace nbodies {

// METODI DI VECTOR
vector vector::operator+(vector const& z) const {
  return {x+z.x,y+z.y};
}
vector vector::operator*(double a) const {
  return {x*a,y*a};
}
vector vector::operator-(vector const& z) const {
  return {x-z.x, y-z.y};
}
bool vector::operator==(vector const& z) const {//da capire se ha senso o se nei test farli separati x e y
    return x==z.x && y == z.x;
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

double System::energy() {
  double kinetic{0.};
  for (int i{0}; i < planets.size(); ++i) {
    kinetic += 0.5 * planets[i].mass() * pow(planets[i].velocity().norm(), 2);
  }

  double potential{0.};
  for (int i{0}; i < planets.size(); ++i) {
    for (int j{0}; j < i; ++j) {
      potential += -nbodies::constants::G *
                   (planets[i].mass() * planets[j].mass()) /
                   (planets[i].position() - planets[j].position()).norm();
    }
  }
  return kinetic + potential;
}
// FINE METODI DI SYSTEM

}  // namespace nbodies