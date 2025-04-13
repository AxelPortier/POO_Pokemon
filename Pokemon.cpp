#include "Pokemon.h"
#include "Entraineurs.h"
#include <iostream>
#include <vector>
#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <Windows.h>

class Bagarre {
private:
    Joueurs joueur;
    Entraineurs adversaire;

public:
    Bagarre(Joueurs joueur, Entraineurs adversaire) : joueur(joueur) , adversaire(adversaire) {}
};

int main() {
    Pokemon pikachu("Pikachu", { "Electrik" }, 100, "Eclair", "Electrik", 40);
    Pokemon bulbizarre("Bulbizarre", { "Plante" , "Poison" }, 80, "Fouet Lianes", "Plante", 30);
    Pokemon kaiminus("Kaiminus", { "Eau" }, 50, "Morsure", "Tenebres", 60);
    Pokemon topiqueur("Topiqueur", { "Sol" }, 50, "Seisme", "Sol", 100);


    std::cout << kaiminus.getDegats() << std::endl;

   

    //pika attaque top

    pikachu.attaquer(topiqueur);


    //le roi Kai attaque pika

    kaiminus.attaquer(pikachu);



}



