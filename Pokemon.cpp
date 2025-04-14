#include "Pokemon.h"
#include "Entraineurs.h"


class Combat {
private:

    //on fait ref au joueur et a son adversaire on les recréer pas en lançant la bagarre donc on met &

    Joueurs& joueur;
    Entraineurs& adversaire; 

  //pointeurs vers le pokemon qui se bagarre actuellement, il va pointer vers diff pokemon au cours du combat du coup
    //en fait on fait pas de pointeur parce que getPokemon() renvoie un Pokemon et pas un pointeur donc c'est foireu

    Pokemon pokemonActuel_Joueur;
    Pokemon pokemonActuel_Adversaire;

    //bool finDuCombat;
    


public:
    Combat(Joueurs& joueur, Entraineurs& adversaire , Pokemon pokemonActuel_Joueur , Pokemon pokemonActuel_Adversaire) : joueur(joueur) , adversaire(adversaire) {
        pokemonActuel_Joueur = joueur.getPokemon();
        pokemonActuel_Adversaire = adversaire.getPokemon();

    }

};

int main() {
    srand(time(0)); //on initialise le random pour les dialogues 
    
    Pokemon Pikachu("Pikachu", { "Electrik" }, 30, "Eclair", "Electrik", 50);
    std::cout << Pikachu.getHP()<<std::endl;
    std::cout << Pikachu.getDegats()<<std::endl;

    Pokemon Kaiminus("Kaiminus", { "eau" }, 50, "Morsure", "Tenebre", 60);
    std::cout << Kaiminus.getHP()<<std::endl;
    std::cout << Kaiminus.getDegats()<<std::endl;

    Entraineurs Sascha("Sascha", { Pikachu });

    Maitres Victor("Victor", { Kaiminus });

    Victor.parler_victoireCombat(Sascha);

    Sascha.parler_defaiteCombat(Victor);

    
}



