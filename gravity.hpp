#ifndef NBODIES_GRAVITY_HPP
#define NBODIES_GRAVITY_HPP

#include <array>
#include <cmath>
#include <vector>

namespace nbodies
{
    struct vector {
        double x;



           double y;
        vector& operator+(vector const& z);
        vector& operator*(double a);
        vector& operator-(vector const& z);
    };

    namespace constants
    {
        inline constexpr double G = 6.67e-11;
        inline constexpr double eps = 1e-12;
        inline constexpr double dt = 0.001;
        inline constexpr long int AU = 149597870700;

    } // namespace constants
    
    class Planet
    {
        double m_{0.}; //mass
        std::array<double, 2> r_{0., 0.}; //position
        std::array<double, 2> v_{0., 0.}; //velocity
        std::array<double, 2> a_{0., 0.}; //acceleration

    public:
        Planet(double m, std::array<double, 2> const &r, std::array<double, 2> const &v, std::array<double, 2> const &a);
        
        double mass() const;
        vector & position();
        vector & velocity();
        vector & acceleration();

        
    };

    std::vector<Planet> iteration(int n, std::vector<Planet> const &start, std::vector<Planet> &end)
    {
        for (int i{0}; i < n; ++i)
        {
            double a_fin_x{0};
            for (int j{0}; j < n; ++j)
            {
                if (j != i)
                {
                    a_fin_x +=
                }
            }
        }
    }

} // namespace nbodies

#endif