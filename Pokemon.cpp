/*
Bienvenu sur le code du Projet Pokemon de Pitigliano Victor et Portier Axel 
note importante, nous avons réussis à surcharger les opérateurs tard dans le projet donc certaines fonctions sont inutiles, si elles sont encore présentes dasn le code final 
c'est un simple oublis

*/





#include "raylib.h"




#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <string>
//#include <Windows.h> je tej parce que ca rentre en conflit avec raylib
#include <unordered_map>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour time()

#include "Pokemon.h"
#include "Entraineurs.h"
#include "Données.h"
#include "Combat.h"


//donner aux pokemons 4 attaques de bases et les overrides avec les dresseurs pour les adapter, comme ça je peux
//instancier des pokemons sans ecrire toutes leurs attaques a la main et en meme temps les 
//leaders et autres ont leurs attaques fetiches

//relire tout le code et verif les liens entre les fonctions, si les & et * sont bien utilisés.


Pokemon Mia("Mia", { "Ténèbre" }, 100, "Morsure", "Ténèbre", 60, 12);
Pokemon Marius("Marius", { "Sol" }, 160, "Seisme", "Sol", 100, 5);
Pokemon Kaiminus("Kaiminus", { "Eau" }, 100, "Hydrocanon", "Eau", 150, 10);


Joueurs Victor("Victor", { Mia , Marius , Kaiminus }, 0, 0, 0);
Maitres Blue = defMaitres("Blue");

int main() {
    srand(time(0)); //on initialise le random pour les dialogues 

    Combat combat(Victor, Blue);

    std::cout << Victor;

  
 
    return 0;

    

}




