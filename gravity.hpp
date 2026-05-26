#ifndef NBODIES_GRAVITY_HPP
#define NBODIES_GRAVITY_HPP

#include <cmath>
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
  vector& operator*(double a);
  vector& operator-(vector const& z);
};

class Planet {
  double m_{0.};      // mass
  vector r_{0., 0.};  // position
  vector v_{0., 0.};  // velocity
  vector a_{0., 0.};  // acceleration
  bool check_m_validity();

 public:
  Planet(double m, vector const& r, vector const& v, vector const& a);

  double const& mass() const;
  vector& position();      // get position
  vector& velocity();      // get velocity
  vector& acceleration();  // get acceleration
};
struct System {
  std::vector<Planet> s;
  System iteration() {
    for(int i{0}; i<s.size(); i++) {
      s[i].position()=s[i].position()+s[]
    }

  }


};
/*std::vector<Planet> iteration(int n, vector const& start) {
  for (int i{0}; i < n; ++i) {
    double a_fin_x{0};
    for (int j{0}; j < n; ++j) {
      if (j != i) {
        a_fin_x +=
      }
    }
  }
}*/

}  // namespace nbodies

#endif