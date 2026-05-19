#include "gravity.hpp"

namespace nbodies
{
    //Planet's constructor and methods
    Planet::Planet(double m, std::array<double, 2> const &r,
                   std::array<double, 2> const &v, std::array<double, 2> a)
    {
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


    //add functions(single-value and vectors)
    void Planet::add_mass(double m) { double m_{m}; }
    void Planet::add_position(std::array<double, 2> pos)
    {
        r_[0] = pos[0] * nbodies::constants::AU;
        r_[1] = pos[1] * nbodies::constants::AU;
    }
    void Planet::add_position_x(double x) { r_[0] = x * nbodies::constants::AU; }
    void Planet::add_position_y(double y) { r_[1] = y * nbodies::constants::AU; }
    void Planet::add_velocity(std::array<double, 2> vel)
    {
        v_[0] = vel[0];
        v_[1] = vel[1];
    }

    void Planet::add_velocity_x(double x) { v_[0] = x; }
    void Planet::add_velocity_y(double y) { v_[1] = y; }
    void Planet::add_acceleration(std::array<double, 2> acc)
    {
        a_[0] = acc[0];
        a_[1] = acc[1];
    }
    void Planet::add_acceleration_x(double x) { a_[0] = x; }
    void Planet::add_acceleration_y(double y) { a_[1] = y; }
    //end of Planet's constructor and methods

} // namespace nbodies