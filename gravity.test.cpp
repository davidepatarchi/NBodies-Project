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
  CHECK(vsum1.y == -2.);

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
  CHECK(vprod1.x == 2.);
  CHECK(vprod1.y == 4.);

  // multiplying by 0
  nbodies::vector vprod2 = v * 0;
  CHECK(vprod2.x == 0.);
  CHECK(vprod2.y == 0.);

  // multiplying by a negative number
  nbodies::vector vprod3 = v * (-2);
  CHECK(vprod3.x == -2.);
  CHECK(vprod3.y == -4.);
}

TEST_CASE("Testing: operator/") {
  nbodies::vector v{4., 2.};

  // dividing by a positive number
  nbodies::vector vdiv1 = v / 2;
  CHECK(vdiv1.x == 2.);
  CHECK(vdiv1.y == 1.);

  // dividing by 0
  CHECK_THROWS_AS(v / 0, std::invalid_argument);

  // dividing by a negative number
  nbodies::vector vdiv2 = v / (-2);
  CHECK(vdiv2.x == -2.);
  CHECK(vdiv2.y == -1.);
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
  CHECK_THROWS_AS((nbodies::Planet{-1., {2., 3.}, {4., 5.}, {6., 7.}, 8.}),
                  std::invalid_argument);
  CHECK_THROWS_AS((nbodies::Planet{0., {2., 3.}, {4., 5.}, {6., 7.}, 8.}),
                  std::invalid_argument);
  double nan = std::numeric_limits<double>::quiet_NaN();

  CHECK_THROWS_AS((nbodies::Planet{nan, nbodies::vector{0.0, 0.0},
                                   nbodies::vector{0.0, 0.0},
                                   nbodies::vector{0., 0.}, 1.0}),
                  std::invalid_argument);

  // invalid radius
  CHECK_THROWS_AS((nbodies::Planet{1., {2., 3.}, {4., 5.}, {6., 7.}, -8.}),
                  std::invalid_argument);
  CHECK_THROWS_AS((nbodies::Planet{1., {2., 3.}, {4., 5.}, {6., 7.}, 0.}),
                  std::invalid_argument);
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

// SYSTEM'S TESTS
TEST_CASE("Testing: check_size()") {
  nbodies::System planets9;
  CHECK_THROWS_AS(planets9.read_file("data_test/test9.txt"),
                  std::runtime_error);
}
TEST_CASE("Testing: read_file(), size() and get_planet()") {
  nbodies::System planets1;
  planets1.read_file("data_test/test1.txt");

  // checking system's size
  CHECK(planets1.size() == 2);

  // checking the second planet
  nbodies::Planet body = planets1.get_planet(1);
  CHECK(body.mass() == 1.2);
  CHECK(body.position().x == 2.2);
  CHECK(body.position().y == 3.2);
  CHECK(body.velocity().x == 4.2);
  CHECK(body.velocity().y == 5.2);
  CHECK(body.radius() == 6.2);

  // checking second planet's accelerations
  CHECK(body.acceleration().x == doctest::Approx(7.337e-9));
  CHECK(body.acceleration().y == doctest::Approx(7.337e-9));
  planets1.read_file("data_test/test2.txt");
  CHECK(planets1.size() == size_t(1.));
  CHECK_THROWS_AS(planets1.get_planet(2), std::runtime_error);
  // checking not-existing file
  nbodies::System planets2;
  CHECK_THROWS_AS(planets2.read_file("fake_file.txt"), std::runtime_error);
  // checking wrong file
  CHECK_THROWS_AS(planets2.read_file("data_test/test10.txt"),
                  std::runtime_error);
  CHECK_THROWS_AS(planets2.read_file("data_test/test11.txt"),
                  std::runtime_error);
}

TEST_CASE("Testing: iteration()") {
  // single planet's system
  nbodies::System planets1;
  planets1.read_file("data_test/test2.txt");
  planets1.iteration();
  nbodies::Planet body1 = planets1.get_planet(0);

  CHECK(body1.position().x == doctest::Approx(120.));
  CHECK(body1.position().y == 0.);
  CHECK(body1.velocity().x == 2.);
  CHECK(body1.velocity().y == 0.);
  CHECK(body1.acceleration().x == 0.);
  CHECK(body1.acceleration().y == 0.);

  // two planets' system
  nbodies::System planets2;
  planets2.read_file("data_test/test3.txt");
  planets2.iteration();
  nbodies::Planet body2 = planets2.get_planet(0);

  CHECK(body2.position().x == doctest::Approx(6.9967).epsilon(1e-4));
  CHECK(body2.position().y == 0.);
  CHECK(body2.velocity().x == doctest::Approx(-0.15232).epsilon(1e-4));
  CHECK(body2.velocity().y == 0.);
  CHECK(body2.acceleration().x == doctest::Approx(-3.405e-3).epsilon(1e-4));
  CHECK(body2.acceleration().y == 0.);
}
TEST_CASE("Testing: collision()") {
  // two planet collision
  nbodies::System planets1;
  planets1.read_file("data_test/test7.txt");
  planets1.collision();
  nbodies::Planet body1 = planets1.get_planet(0);
  CHECK(planets1.size() == 1);
  CHECK(body1.mass() == 8.e24);
  CHECK(body1.position().x == doctest::Approx(-1.e6).epsilon(1e-4));
  CHECK(body1.position().y == 0.);
  CHECK(body1.velocity().x == doctest::Approx(4375.).epsilon(1e-4));
  CHECK(body1.velocity().y == doctest::Approx(3000.0).epsilon(1e-4));
  CHECK(body1.radius() == doctest::Approx(7.211e6).epsilon(1e-4));

  // three planets' system
  nbodies::System planets2;
  planets2.read_file("data_test/test8.txt");
  planets2.collision();
  nbodies::Planet bodyid = planets2.get_planet(0);
  nbodies::Planet body2 = planets2.get_planet(1);
  CHECK(planets2.size() == 2);
  CHECK(bodyid.mass() == 2.e27);
  CHECK(bodyid.position().x == 1.0e11);
  CHECK(bodyid.position().y == 1.0e11);
  CHECK(bodyid.velocity().x == 0.0);
  CHECK(bodyid.velocity().y == -13000.0);
  CHECK(bodyid.radius() == 7.0e7);
  CHECK(body2.mass() == 8.e24);
  CHECK(body2.position().x == doctest::Approx(-1.e6).epsilon(1e-4));
  CHECK(body2.position().y == 0.);
  CHECK(body2.velocity().x == doctest::Approx(4375.).epsilon(1e-4));
  CHECK(body2.velocity().y == doctest::Approx(3000.0).epsilon(1e-4));
  CHECK(body2.radius() == doctest::Approx(7.211e6).epsilon(1e-4));
}

TEST_CASE("Testing: energy() and scale_energy()") {
  // single planet's system
  nbodies::System planets1;
  planets1.read_file("data_test/test2.txt");
  CHECK(planets1.energy() == 2.);
  CHECK(planets1.scale_energy() == 2.);

  // two planets' system
  nbodies::System planets2;
  planets2.read_file("data_test/test4.txt");
  CHECK(planets2.energy() == doctest::Approx(249.96665).epsilon(1e-4));
  CHECK(planets2.scale_energy() == doctest::Approx(250.03335).epsilon(1e-4));
}

TEST_CASE("Testing: momentum() and scale_momentum()") {
  // single planet's system
  nbodies::System planets1;
  planets1.read_file("data_test/test2.txt");
  CHECK(planets1.momentum() == nbodies::vector{2., 0.});
  CHECK(planets1.scale_momentum() == nbodies::vector{2., 0.});

  // two planets' system
  nbodies::System planets2;
  planets2.read_file("data_test/test4.txt");
  CHECK(planets2.momentum() == nbodies::vector{0., 0.});
  CHECK(planets2.scale_momentum() == nbodies::vector{10000., 0.});
}

TEST_CASE("Testing: angular_momentum() and scale_angular_momentum()") {
  // single planet's system
  nbodies::System planets1;
  planets1.read_file("data_test/test5.txt");
  CHECK(planets1.angular_momentum() == -25.);
  CHECK(planets1.scale_angular_momentum() == 25.);

  // two planets' system
  nbodies::System planets2;
  planets2.read_file("data_test/test6.txt");
  CHECK(planets2.angular_momentum() == 0.);
  CHECK(planets2.scale_angular_momentum() == 60.);
}
// END OF SYSTEM'S TESTS

// SFML FUNCTIONS' TESTS
TEST_CASE("Testing: AU_pixel_x() and AU_pixel_y()") {
  double x1{0.};
  double x2{nbodies::constants::AU};
  double y1{0.};
  double y2{nbodies::constants::AU};

  CHECK(nbodies::AU_pixel_x(x1) == 400.f);
  CHECK(nbodies::AU_pixel_x(x2) == 760.f);
  CHECK(nbodies::AU_pixel_y(y1) == 400.f);
  CHECK(nbodies::AU_pixel_y(y2) == 40.f);
}

TEST_CASE("Testing: pixel_radius()") {
  double r1{4.9e5};
  double r2{5.e5};

  CHECK(nbodies::pixel_radius(r1) == 5.f);
  CHECK(nbodies::pixel_radius(r2) == 6.f);
}
// END OF SFML FUNCTIONS' TESTS