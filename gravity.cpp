#include "gravity.hpp"

#include <numeric>

namespace nbodies {

// VECTOR'S METHODS
vector vector::operator+(vector const& z) const { return {x + z.x, y + z.y}; }
vector vector::operator*(double a) const { return {x * a, y * a}; }
vector vector::operator-(vector const& z) const { return {x - z.x, y - z.y}; }
bool vector::operator==(vector const& z)
    const {  // da capire se ha senso o se nei test farli separati x e y
  return x == z.x && y == z.y;
}

double vector::norm() const { return sqrt(x * x + y * y); }

// END OF VECTOR'S METHODS

// PLANET'S METHODS
Planet::Planet(double m, vector const& r, vector const& v, vector const& a) {
  m_ = m;
  r_.x = r.x;
  r_.y = r.y;
  v_.x = v.x;
  v_.y = v.y;
  a_.x = a.x;
  a_.y = a.y;
}
bool Planet::check_m_validity() const { return m_ > 0 ? true : false; }

double Planet::mass() const {
  if (check_m_validity() == true) {
    return m_;
  }
  throw std::runtime_error("ERROR: Invalid mass!");
}
// non-costant version
vector& Planet::position() { return r_; }
vector& Planet::velocity() { return v_; }
vector& Planet::acceleration() { return a_; }

// costant version
vector const& Planet::position() const { return r_; }
vector const& Planet::velocity() const { return v_; }
vector const& Planet::acceleration() const { return a_; }
// END OF PLANET'S METHODS

// SYSTEM'S METHODS
Planet& System::get_planet(size_t i) { return planets[i]; }

size_t System::size() const { return planets.size(); }

void System::iteration() {
  size_t N = planets.size();

  // evolving position
  for (size_t i{0}; i < N; ++i) {
    planets[i].position() =
        planets[i].position() + planets[i].velocity() * nbodies::constants::dt +
        planets[i].acceleration() * 0.5 * pow(nbodies::constants::dt, 2);
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
    std::cout << "ERROR IN FILE OPENING" << '\n';
  }

  while (file >> mass >> position_x >> position_y >> velocity_x >> velocity_y) {
    Planet body(mass, {position_x, position_y}, {velocity_x, velocity_y},
                {0., 0.});
    planets.push_back(body);
  }
  // setting initial accelerations from data
  size_t N = planets.size();
  for (size_t i{0}; i < N; ++i) {
    vector somma{0., 0.};

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
}

double System::energy() {
  double kinetic = std::accumulate(
      planets.begin(), planets.end(), 0.0, [](double sum, Planet const& body) {
        return sum + 0.5 * body.mass() * pow(body.velocity().norm(), 2);
      });

  size_t N = planets.size();
  double potential{0.0};
  for (size_t i{0}; i < N; ++i) {
    double tot = std::accumulate(
        planets.begin(), planets.begin() + int(i), 0.0,
        [&](double sum, Planet const& body) {
          return sum - nbodies::constants::G *
                           (planets[i].mass() * body.mass()) /
                           (planets[i].position() - body.position()).norm();
        });
    potential += tot;
  }
  return kinetic + potential;
}

vector System::momentum() {
  vector momentum;
  momentum.x = std::accumulate(planets.begin(), planets.end(), 0.0,
                               [](double sum, Planet const& body) {
                                 return sum + body.velocity().x * body.mass();
                               });
  momentum.y = std::accumulate(planets.begin(), planets.end(), 0.0,
                               [](double sum, Planet const& body) {
                                 return sum + body.velocity().y * body.mass();
                               });
  return {momentum.x, momentum.y};
}
// END OF SYSTEM'S METHODS

// SFML FUNCTIONS
float AU_pixel_x(double x) {
  return float((1 + (x / nbodies::constants::AU) * 0.9) * 400.);
}
float AU_pixel_y(double y) {
  return float((1 - (y / nbodies::constants::AU) * 0.9) * 400.);
}
// END OF SFML FUNCTIONS

// OUTPUT FUNCTIONS
double get_mean(std::vector<double> const& vec) {
  return std::accumulate(vec.begin(), vec.end(), 0.0) / double(vec.size());
}
double get_error(std::vector<double> const& vec) {
  std::vector<double> vec2(vec.size());
  std::transform(vec.begin(), vec.end(), vec2.begin(),
                 [](double x) { return x * x; });
  return sqrt((get_mean(vec2) - get_mean(vec) * get_mean(vec)) /
              double(vec.size()));
}

}  // namespace nbodies