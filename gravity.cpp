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
double vector::norm(){
    return x*x + y*y;
  }

double const& Planet::mass() const { return m_; }
vector& Planet::position() { return r_; };
vector& Planet::velocity() { return v_; }
vector& Planet::acceleration() { return a_; }
void System::iteration() {
    for(int i{0}; i<s.size(); ++i) {
      s[i].position()=s[i].position()+s[i].velocity()*0.01+s[i].acceleration()*0.5*0.01*0.01;//controlla che il prodotto per uno scalare non è commutativo
    }
    std::vector<vector> v;
    for(int i{0}; i<s.size(); ++i) {
      vector somma{0.,0.};
      v.push_back(s[i].acceleration());
      //cambia le acc
      for(int j{0}; j<s.size(); ++j) {
        if(j!=i) {
          double a=constants::G*s[j].mass()*pow((constants::eps*constants::eps)+pow((s[j].position()-s[i].position()).norm(),2),-1.5); 
          somma= somma+(s[i].position()-s[j].position())*a;
        }
        else{}
      }
      s[i].acceleration()=somma*(-1);
    }
    for(int i{0}; i<s.size(); ++i) {
      s[i].velocity()=s[i].velocity()+(s[i].acceleration()+v[i])*(0.5*0.01); 
    }
  }

}  // namespace nbodies