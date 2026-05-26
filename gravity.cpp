#include "gravity.hpp"

namespace nbodies {
bool Planet::check_m_validity() { return m_ > 0 ? true : false; }

Planet::Planet(double m, vector const& r, vector const& v, vector const& a) {
  m_ = m;
  r_.x = r.x;
  r_.y = r.y;
  v_.x = v.x;
  v_.y = v.y;
  a_.x = a.x;
  a_.y = a.y;
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

double const& Planet::mass() const { return m_; }
vector& Planet::position() { return r_; };
vector& Planet::velocity() { return v_; }
vector& Planet::acceleration() { return a_; }

}  // namespace nbodies