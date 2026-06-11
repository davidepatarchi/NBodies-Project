#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "gravity.hpp"
using namespace nbodies;
TEST_CASE("somma vettori") {
    vector v1{1.0, 2.0};
    vector v2{3.4, 5.7};
    vector v3{4.4, 7.7};

    vector vsum = v1 + v2;

    CHECK(vsum==v3);
}

TEST_CASE("sottrazione vettori") {
    vector v1{5.0, 7.0};
    vector v2{2.0, 3.0};
    vector v3{3.0, 4.0};
    
    vector v = v1 - v2;

    CHECK(v==v3);;
}

TEST_CASE("prodotto per scalare") {
    vector v1{2.0, -3.0};
    vector v2{4.0, -6.0};

    vector p = v1 * 2.0;

    CHECK(v2==p);
}

TEST_CASE("norma") {
    vector v{3.0, 4.0};

    CHECK(v.norm() == 5.);
}
