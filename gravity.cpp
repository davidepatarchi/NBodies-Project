#include "gravity.hpp"

namespace nbodies {
// Planet's constructor and methods
Planet::Planet(double m, std::array<double, 2> const& r,
               std::array<double, 2> const& v, std::array<double, 2> a) {
  m_ = m;
  r_[0] = r[0];
  r_[1] = r[1];
  v_[0] = v[0];
  v_[1] = v[1];
  a_[0] = a[0];
  a_[1] = a[1];
}
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

double& Planet::mass() const { return m_; }
vector& Planet::position() { return r_; };
vector& Planet::velocity() { return v_; }
vector& Planet::acceleration() { return a_; }

}  // namespace nbodies