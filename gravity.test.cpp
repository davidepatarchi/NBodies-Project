#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "gravity.hpp"
using namespace nbodies::vector;
TEST_CASE("somma vettori") {
    vector v1{1.0, 2.0};
    vector v2{3.4, 5.7};

    vector vsum = v1 + v2;

    CHECK(vsum == vector v{4.4,7.7});
}

TEST_CASE("sottrazione vettori") {
    vector v1{5.0, 7.0};
    vector v2{2.0, 3.0};
    
vector v = v1 - v2;

    CHECK(v == vector v(3.0));;
}

TEST_CASE("prodotto per scalare") {
    vector v{2.0, -3.0};

    vector p = v * 2.0;

    CHECK(p.x == doctest::Approx(4.0));
    CHECK(p.y == doctest::Approx(-6.0));
}

TEST_CASE("norma") {
    vector v{3.0, 4.0};

    CHECK(v.norm() == doctest::Approx(5.0));
}

}
