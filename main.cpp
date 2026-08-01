#include <iostream>
#include "gravity.hpp"

int main() {
  double T;
  std::cout << "How many seconds will the simulation last?" << '\n';
  std::cin >> T;

  nbodies::System planets;
  planets.read_file("dati.txt");
  size_t N = planets.size();
  /*for (int i{0}; i < N; ++i) {
    planets.get_planet(i).position().x *= nbodies::constants::AU;
    planets.get_planet(i).position().x *= nbodies::constants::AU;
  }*/

  /*//CONTROLLO SULLE MASSE DA FARE
  int width = 800;
  int height = 800;
  sf::RenderWindow window(sf::VideoMode(width, height), "NBodies");
  window.setFramerateLimit(60);
  //per farli vedere su sfml devi riscalare sugli assi di sfml, dobbiamo capire di quanto scalare in base a quale caso si tratta
  double scale = 1e-9;
  while (window.isOpen()) {
        
        // --- A. Gestione Eventi (Input dell'utente) ---
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }*/

  for (double t{nbodies::constants::dt}; t <= T; t += nbodies::constants::dt) {
    planets.iteration();

    std::cout << "ITERATION NUMBER: " << t << '\n';
    for (size_t i{0}; i < N; ++i) { 
      std::cout << "Mass : " << planets.get_planet(i).mass() << '\n';
      std::cout << "Position : " << planets.get_planet(i).position().x << ", "
                << planets.get_planet(i).position().y << '\n';
      std::cout << "Velocity : " << planets.get_planet(i).velocity().x << ", "
                << planets.get_planet(i).velocity().y << '\n';
      std::cout << "Acceleration : " << planets.get_planet(i).acceleration().x
                << ", " << planets.get_planet(i).acceleration().y << '\n';
      /*//usando questo stesso ciclo dobbiamo riscalare tutte le posizioni in modo che siano in accordo con la cartella di sfml
      //con questa formula
      //float x_schermo = static_cast<float>((x_fisica * scale) + (WIDTH / 2.0));
       //     float y_schermo = static_cast<float>((-y_fisica * scale) + (HEIGHT / 2.0));
       //creiamo anche il cerchio che indichi i vari pianeti
       sf::CircleShape planet_shape(5.0); // Raggio di 5 pixel
            planet_shape.setFillColor(sf::Color::White);
            
            // Centra l'origine della forma SFML in modo che venga disegnata centrata sulla coordinata
            planet_shape.setOrigin(5.0, 5.0); 
            
            // Sposta la forma alle coordinate calcolate
            planet_shape.setPosition(x_schermo, y_schermo);

            // Disegna il pianeta sulla finestra
            window.draw(planet_shape);*/

    }
    std::cout << "Energy: " << planets.energy() << "\n\n";
    //window.display();


  }
}
