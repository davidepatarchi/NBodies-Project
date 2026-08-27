#include "gravity.hpp"

#include <algorithm>
#include <numeric>

namespace nbodies {

// VECTOR'S METHODS
vector vector::operator+(vector const& z) const { return {x + z.x, y + z.y}; }
vector vector::operator*(double a) const { return {x * a, y * a}; }
vector vector::operator/(double a) const {
  if (a == 0) {
    throw std::runtime_error("Error: division by 0");
  }
  return {x / a, y / a};
}
vector vector::operator-(vector const& z) const { return {x - z.x, y - z.y}; }
bool vector::operator==(vector const& z) const { return x == z.x && y == z.y; }
double vector::norm() const { return sqrt(x * x + y * y); }
// END OF VECTOR'S METHODS

// PLANET'S METHODS
void Planet::check_mass() const {
  if (mass_ <= 0 || !std::isfinite(mass_)) {
    throw std::runtime_error("ERROR: Invalid mass!");
  }
}
void Planet::check_radius() const {
  if (radius_ <= 0 || !std::isfinite(radius_)) {
    throw std::runtime_error("ERROR: Invalid radius!");
  }
}

Planet::Planet(double mass, vector const& position, vector const& velocity,
               vector const& acceleration, double radius)
    : mass_(mass),
      position_(position),
      velocity_(velocity),
      acceleration_(acceleration),
      radius_(radius) {
  check_mass();
  check_radius();
}

double Planet::mass() const { return mass_; }
double Planet::radius() const { return radius_; }

// non-const version
vector& Planet::position() { return position_; }
vector& Planet::velocity() { return velocity_; }
vector& Planet::acceleration() { return acceleration_; }

// const version
vector const& Planet::position() const { return position_; }
vector const& Planet::velocity() const { return velocity_; }
vector const& Planet::acceleration() const { return acceleration_; }
// END OF PLANET'S METHODS

// SYSTEM'S METHODS
void System::check_size() const {
  if (planets.size() <= 0) {
    throw std::runtime_error{"ERROR: Empty file!"};
  }
}
Planet& System::get_planet(size_t i) { return planets[i]; }

size_t System::size() const { return planets.size(); }

void System::iteration() {
  size_t N = planets.size();
  // evolving position
  std::for_each(planets.begin(), planets.end(), [](Planet& body) {
    body.position() = body.position() +
                      body.velocity() * nbodies::constants::dt +
                      body.acceleration() * 0.5 * nbodies::constants::dt *
                          nbodies::constants::dt;
  });

  // saving initial acceleration
  std::vector<vector> init_acc;
  init_acc.reserve(N);
  std::transform(planets.begin(), planets.end(), std::back_inserter(init_acc),
                 [](Planet const& body) { return body.acceleration(); });

  // evolving acceleration
  for (size_t i{0}; i < N; ++i) {
    vector sum{0., 0.};

    for (size_t j{0}; j < N; ++j) {
      if (j != i) {
        double new_acc =
            constants::G * planets[j].mass() /
            ((planets[j].position() - planets[i].position()).norm() *
             (planets[j].position() - planets[i].position()).norm() *
             (planets[j].position() - planets[i].position()).norm());
        sum = sum - (planets[i].position() - planets[j].position()) * new_acc;
      }
    }
    planets[i].acceleration() = sum;
  }

  // evolving velocity

  for (size_t i{0}; i < N; ++i) {
    planets[i].velocity() =
        planets[i].velocity() + (planets[i].acceleration() + init_acc[i]) *
                                    (0.5 * nbodies::constants::dt);
  }
}

void System::collision() {
  for (size_t i{0}; i < planets.size();) {
    size_t init_size = planets.size();
    for (size_t j = i + 1; j < planets.size(); ++j) {
      if ((planets[i].position() - planets[j].position()).norm() <=
          planets[i].radius() + planets[j].radius()) {
        // creating new coordinates
        vector new_position = (planets[i].position() * planets[i].mass() +
                               planets[j].position() * planets[j].mass()) /
                              (planets[i].mass() + planets[j].mass());
        vector new_velocity = (planets[i].velocity() * planets[i].mass() +
                               planets[j].velocity() * planets[j].mass()) /
                              (planets[i].mass() + planets[j].mass());
        vector new_acceleration{0., 0.};
        double new_mass = planets[i].mass() + planets[j].mass();
        double new_radius = sqrt(planets[i].radius() * planets[i].radius() +
                                 planets[j].radius() * planets[j].radius());

        planets.erase(planets.begin() + static_cast<std::ptrdiff_t>(j));
        planets.erase(planets.begin() + static_cast<std::ptrdiff_t>(i));

        // creating a new planet
        Planet new_planet{new_mass, new_position, new_velocity,
                          new_acceleration, new_radius};
        size_t M = planets.size();
        vector sum{0., 0.};
        for (size_t k{0}; k < M; ++k) {
          double new_acc =
              nbodies::constants::G * planets[k].mass() /
              ((planets[k].position() - new_planet.position()).norm() *
               (planets[k].position() - new_planet.position()).norm() *
               (planets[k].position() - new_planet.position()).norm());
          sum = sum - (new_planet.position() - planets[k].position()) * new_acc;
        }
        new_planet.acceleration() = sum;
        planets.push_back(new_planet);
        break;  // in order to start a new iteration check
      }
    }
    if (planets.size() < init_size) {
      i = 0;
    } else {
      ++i;
    }
  }
  check_size();
}

void System::read_file(const std::string& filename) {
  std::ifstream file(filename);
  double mass;
  double position_x;
  double position_y;
  double velocity_x;
  double velocity_y;
  double radius;

  //erase an old configuration
  planets.clear();

  if (!file.is_open()) {
    throw std::runtime_error("ERROR: File opening failed");
  }

  while (file >> mass >> position_x >> position_y >> velocity_x >> velocity_y >>
         radius) {
    Planet body(mass, {position_x, position_y}, {velocity_x, velocity_y},
                {0., 0.}, radius);
    planets.push_back(body);
  }
  // setting initial accelerations from data
  size_t N = planets.size();
  for (size_t i{0}; i < N; ++i) {
    vector sum{0., 0.};

    for (size_t j{0}; j < N; ++j) {
      if (j != i) {
        double new_acc =
            constants::G * planets[j].mass() /
            ((planets[j].position() - planets[i].position()).norm() *
             (planets[j].position() - planets[i].position()).norm() *
             (planets[j].position() - planets[i].position()).norm());
        sum = sum - (planets[i].position() - planets[j].position()) * new_acc;
      }
    }
    planets[i].acceleration() = sum;
  }
  check_size();
}

double System::energy() {
  double kinetic = std::accumulate(
      planets.begin(), planets.end(), 0.0, [](double sum, Planet const& body) {
        return sum + 0.5 * body.mass() * body.velocity().norm() *
                         body.velocity().norm();
      });

  size_t N = planets.size();
  double potential{0.0};
  for (size_t i{0}; i < N; ++i) {
    double tot = std::accumulate(
        planets.begin(), planets.begin() + static_cast<std::ptrdiff_t>(i), 0.0,
        [&](double sum, Planet const& body) {
          return sum - nbodies::constants::G *
                           (planets[i].mass() * body.mass()) /
                           (planets[i].position() - body.position()).norm();
        });
    potential += tot;
  }
  return kinetic + potential;
}

double System::scale_energy() {
  double kinetic = std::accumulate(
      planets.begin(), planets.end(), 0.0, [](double sum, Planet const& body) {
        return sum + 0.5 * body.mass() * body.velocity().norm() *
                         body.velocity().norm();
      });

  size_t N = planets.size();
  double potential{0.0};
  for (size_t i{0}; i < N; ++i) {
    double tot = std::accumulate(
        planets.begin(), planets.begin() + static_cast<std::ptrdiff_t>(i), 0.0,
        [&](double sum, Planet const& body) {
          return sum + nbodies::constants::G *
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
  return momentum;
}

vector System::scale_momentum() {
  vector momentum;
  momentum.x = std::accumulate(
      planets.begin(), planets.end(), 0.0, [](double sum, Planet const& body) {
        return sum + std::abs(body.velocity().x * body.mass());
      });
  momentum.y = std::accumulate(
      planets.begin(), planets.end(), 0.0, [](double sum, Planet const& body) {
        return sum + std::abs(body.velocity().y * body.mass());
      });
  return momentum;
}

double System::angular_momentum() {
  return std::accumulate(
      planets.begin(), planets.end(), 0.0, [](double sum, Planet const& body) {
        return sum + body.mass() * (body.position().x * body.velocity().y -
                                    body.position().y * body.velocity().x);
      });
}

double System::scale_angular_momentum() {
  return std::accumulate(
      planets.begin(), planets.end(), 0.0, [](double sum, Planet const& body) {
        return sum +
               std::abs(body.mass() * (body.position().x * body.velocity().y -
                                       body.position().y * body.velocity().x));
      });
}
// END OF SYSTEM'S METHODS

// SFML FUNCTIONS
float AU_pixel_x(double x) {
  return float((1 + (x / nbodies::constants::AU) * 0.9) * 400.);
}
float AU_pixel_y(double y) {
  return float((1 - (y / nbodies::constants::AU) * 0.9) * 400.);
}
float pixel_radius(double r) {
  if (r < 10) {
    return 1.f;
  }

  int exp = int(std::log10(r));
  double base = r / pow(10, exp);
  if (base < 5) {
    return float(exp);
  }
  return float(exp + 1);
}

// END OF SFML FUNCTIONS

}  // namespace nbodies
