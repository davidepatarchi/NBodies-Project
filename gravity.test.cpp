#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "gravity.hpp"

#include "doctest.h"

// VECTOR'S TESTS
TEST_CASE("Testing: operator+") {
  nbodies::vector v1{1., 2.};
  nbodies::vector v2{3., 4.};
  nbodies::vector v3{0., 0.};
  nbodies::vector v4{-3., -4.};

  // adding a positive vector
  nbodies::vector vsum1 = v1 + v2;
  CHECK(vsum1.x == 4.);
  CHECK(vsum1.y == 6.);

  // adding a null vector
  nbodies::vector vsum2 = v1 + v3;
  CHECK(vsum2.x == v1.x);
  CHECK(vsum2.y == v1.y);

  // adding a negative vector
  nbodies::vector vsum3 = v1 + v4;
  CHECK(vsum3.x == -2.);
  CHECK(vsum3.y == -2.);
}

TEST_CASE("Testing: operator-") {
  nbodies::vector v1{1., 2.};
  nbodies::vector v2{3., 4.};
  nbodies::vector v3{0., 0.};
  nbodies::vector v4{-3., -4.};

  // subtracting a positive vector
  nbodies::vector vsum1 = v1 - v2;
  CHECK(vsum1.x == -2.);
  CHECK(vsum1.y = -2.);

  // subtracting a null vector
  nbodies::vector vsum2 = v1 - v3;
  CHECK(vsum2.x == v1.x);
  CHECK(vsum2.y == v1.y);

  // subtracting a negative vector
  nbodies::vector vsum3 = v1 - v4;
  CHECK(vsum3.x == 4.);
  CHECK(vsum3.y == 6.);
}

TEST_CASE("Testing: operator*") {
  nbodies::vector v{1., 2.};

  // multiplying by a positive number
  nbodies::vector vprod1 = v * 2;
  CHECK(vprod1.x = 2.);
  CHECK(vprod1.y = 4.);

  // multiplying by 0
  nbodies::vector vprod2 = v * 0;
  CHECK(vprod2.x = 0.);
  CHECK(vprod2.y = 0.);

  // multiplying by a negative number
  nbodies::vector vprod3 = v * (-2);
  CHECK(vprod3.x = -2.);
  CHECK(vprod3.y = -4.);
}

TEST_CASE("Testing: operator==") {
  nbodies::vector v1{1., 2.};
  nbodies::vector v2{1., 2.};
  nbodies::vector v3{1., -2.};
  nbodies::vector v4{-1., 2.};

  CHECK(v1 == v2);
  CHECK_FALSE(v1 == v3);
  CHECK_FALSE(v1 == v4);
}

TEST_CASE("Testing: norm()") {
  nbodies::vector v1{3., 4.};
  nbodies::vector v2{0., 0.};
  nbodies::vector v3{-3., -4.};

  // norm of a positive vector
  CHECK(v1.norm() == 5.);

  // norm of a null vector
  CHECK(v2.norm() == 0.);

  // norm of a negative vector
  CHECK(v3.norm() == 5.);
}
// END OF VECTOR'S TESTS

// PLANET'S TESTS
TEST_CASE("Testing: constructor and getter functions") {
  nbodies::Planet body{1., {2., 3.}, {4., 5.}, {6., 7.}, 8.};

  CHECK(body.mass() == 1.);
  CHECK(body.position().x == 2.);
  CHECK(body.position().y == 3.);
  CHECK(body.velocity().x == 4.);
  CHECK(body.velocity().y == 5.);
  CHECK(body.acceleration().x == 6.);
  CHECK(body.acceleration().y == 7.);
  CHECK(body.radius() == 8.);
}

TEST_CASE("Testing: check_mass() and check_radius()") {
  // invalid mass
  CHECK_THROWS(nbodies::Planet{-1., {2., 3.}, {4., 5.}, {6., 7.}, 8.});

  // invalid radius
  CHECK_THROWS(nbodies::Planet{1., {2., 3.}, {4., 5.}, {6., 7.}, -8.});
}

TEST_CASE("Testing: non-const getter functions") {
  nbodies::Planet body{1., {2., 3.}, {4., 5.}, {6., 7.}, 8.};

  // modifying position, velocity, acceleration
  body.position().x = 20.;
  body.velocity().x = 40.;
  body.acceleration().x = 60.;

  CHECK(body.position().x == 20.);
  CHECK(body.velocity().x == 40.);
  CHECK(body.acceleration().x == 60.);
}
// END OF PLANET'S TESTS