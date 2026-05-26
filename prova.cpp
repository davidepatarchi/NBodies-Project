#include <array>
#include <fstream>
#include <iostream>
#include <vector>

struct Planet {
    double rx;
    double ry;
    double vx;
    double vy;
  };

struct System {
    std::vector<Planet> planets;

    void read_file (const std::string& filename) {
        std::ifstream file(filename);
        Planet body;
        while (file >> body.rx >> body.ry >> body.vx >> body.vy) {
            planets.push_back(body);
        }
    }

  };

int main() {

  System s;
  s.read_file("dati.txt");
  int N = s.planets.size();

  for(int i{0}; i < N; ++i) {
        std::cout << "Posizione del pianeta " << i+1 << ":" << s.planets[i].rx << ", " << s.planets[i].ry << '\n';
        std::cout << "Velocità del pianeta " << i+1 << ":" << s.planets[i].vx << ", " << s.planets[i].vy << '\n';
    }
}
