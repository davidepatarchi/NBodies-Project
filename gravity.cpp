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
Planet::Planet(double m, vector const& r, vector const& v, vector const& a, double radius) {
  m_ = m;
  r_.x = r.x;
  r_.y = r.y;
  v_.x = v.x;
  v_.y = v.y;
  a_.x = a.x;
  a_.y = a.y;
  radius_ = radius;
}
bool Planet::check_m_validity() const { return m_ > 0 ? true : false; }
bool Planet::check_radius() const {return radius_ > 0 ? true : false; }

double Planet::mass() const {
  if (check_m_validity() == true) {
    return m_;
  }
  throw std::runtime_error("ERROR: Invalid mass!");
}
double Planet::radius() const {
  if (check_radius()==true) {
    return radius_;
  }
  throw std::runtime_error("ERROR: Invalid radius!");
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
bool System::remove(size_t i) {
  if(i<planets.size()) {
    planets.erase(planets.begin()+i-1);
    return true;
  }
  return false;
}

void System::iteration() {
  
  size_t N = planets.size();
  for(size_t i{0}; i<N; ++i) {
    for(size_t j{0}; j<N; ++j) {
      if (i!=j) {
        if ((planets[i].position() - planets[j].position()).norm()<=planets[i].radius()+planets[j].radius()) {
          planets.remove(i);//da capire perchè non gli va bene
          planets.remove(j);
        }
      }
    }
  }
  // evolving position
  std::for_each(planets.begin(), planets.end(), [](Planet& body) {
    body.position() =
        body.position() + body.velocity() * nbodies::constants::dt +
        body.acceleration() * 0.5 * pow(nbodies::constants::dt, 2);
  });

  // saving initial acceleration
  std::vector<vector> init_acc;
  init_acc.reserve(N);
  std::transform(planets.begin(), planets.end(), std::back_inserter(init_acc),
                 [](Planet const& body) { return body.acceleration(); });

  // evolving acceleration
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
  double radius;

  if (!file.is_open()) {
    throw std::runtime_error("ERROR: File opening failed");
  }

  while (file >> mass >> position_x >> position_y >> velocity_x >> velocity_y >> radius) {
    Planet body(mass, {position_x, position_y}, {velocity_x, velocity_y},
                {0., 0.}, radius);
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

double System::angular_momentum() {
  return std::accumulate(
      planets.begin(), planets.end(), 0.0, [](double sum, Planet const& body) {
        return sum + body.mass() * (body.position().x * body.velocity().y -
                                    body.position().y * body.velocity().x);
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
// END OF SFML FUNCTIONS

}  // namespace nbodies

/*void System::iteration() {
  size_t N = planets.size();

  // evolving position
  std::for_each(planets.begin(), planets.end(), [](Planet& body) {
    body.position() =
        body.position() + body.velocity() * nbodies::constants::dt +
        body.acceleration() * 0.5 * pow(nbodies::constants::dt, 2);
  });

  // saving initial acceleration
  std::vector<vector> init_acc;
  init_acc.reserve(N);
  std::transform(planets.begin(), planets.end(), std::back_inserter(init_acc),
                 [](Planet const& body) { return body.acceleration(); });

  // evolving acceleration
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

  // evolving velocity
  for (size_t i{0}; i < N; ++i) {
    planets[i].velocity() =
        planets[i].velocity() + (planets[i].acceleration() + init_acc[i]) *
                                    (0.5 * nbodies::constants::dt);
  }
}*/