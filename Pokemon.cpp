#include "Pokemon.h"
#include "Entraineurs.h"

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <Windows.h>
#include <unordered_map>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour time()


/*
idée pour la suite, quand je vais mettre plusieurs attaques par pokemon, le joueur choisis mais l'adversaire aura une IA ultra basique
genre il calcul juste les degats qu'il peut faire avec chaques attaques et prend celle qui tape le plus fort
ultra simple


Rappel des class

Pokemon( string nom, {types} , int HP , string attaque , string type attaue , int degats , int vitesse)

Entraineurs (string nom , Pokemon{equipe})

Leaders (string nom , Pokemon{equipe} , string Badge , string Gym)

Maitres(string nom , Pokemon{equipe})

Joueurs (string nom , Pokemon{equipe} , int nbBadges , int nbVictoires , int nbDefaites)
*/

class Combat {
private:

    //on fait ref au joueur et a son adversaire on les recréer pas en lançant la bagarre donc on met &

    Joueurs& joueur;
    int numPokemon_Joueur = 0; //le num du poke qu'on envoie, faudra verif qu'il depasse Equipe.size
    Entraineurs& adversaire; 
    int numPokemon_Adversaire = 0;

  //pointeurs vers le pokemon qui se bagarre actuellement, il va pointer vers diff pokemon au cours du combat du coup
    //en fait on fait pas de pointeur parce que getPokemon() renvoie un Pokemon et pas un pointeur donc c'est foireu

   // Pokemon pokemonActuel_Joueur;
    // Pokemon pokemonActuel_Adversaire;

    //bool finDuCombat;
    


public:
    Combat(Joueurs& joueur, Entraineurs& adversaire) : joueur(joueur), adversaire(adversaire)
    {
        bagarre();
    }
    
    
    
    void bagarre() {

        //2 pointeurs qui pointent vers le pokemon au combat

        Pokemon* pokemonActuel_Joueur = &joueur.getPokemon(numPokemon_Joueur); 
        Pokemon* pokemonActuel_Adversaire = &adversaire.getPokemon(numPokemon_Adversaire);


        std::cout << "Le combat entre " << joueur.getNom() << " et " << adversaire.getNom() << " peut commencer !" << std::endl;
        joueur.parler_debutCombat(adversaire);
        adversaire.parler_debutCombat(joueur);
        std::cout << joueur.getNom() << " envoie "  << pokemonActuel_Joueur->getNom() << " !" << std::endl;
        std::cout << adversaire.getNom() << " envoie " << pokemonActuel_Adversaire->getNom() << " !" << std::endl;


        while (!joueur.getVaincu() and !adversaire.getVaincu()) {
            std::cout << "on commence une nouvelle boucle" << std::endl;
            joueur.afficherEquipe();
            adversaire.afficherEquipe();



            //attention si un pokemon est ko le prochain pokemon peut attaquer si le dresseur a pas encroe joué, le poke le plus rapide peut pas buter le poke et attaquer celui qui arrive direct
    
            int vitesseJoueur = pokemonActuel_Joueur->getVitesse();
            int vitesseAdversaire = pokemonActuel_Adversaire->getVitesse(); //pour savoir qui attaque en prems

            //si joueur est plus rapide
            if (vitesseJoueur >= vitesseAdversaire) { //joueur attaque

    //si je traduis cette phrase ça donne : utiliser la fonction attaquer du pokemon pointé par pokemonActuel_Adversaire sur ce que pointe pokemonActuel_Joueur

                pokemonActuel_Joueur->attaquer(*pokemonActuel_Adversaire); //la fonction estKO est appelé dans la fonction attaque donc si l'attaque bute le poke son etat ets mis a jours direct
                //peut etre que la phrase qui dis que la cible est KO devrait aller dans la fonction attaquer

                //la fonction recevoir degats est intégré donc la cible devrait voir ses hp diminuer

                if (pokemonActuel_Adversaire->getKO()) {
                    std::cout << pokemonActuel_Adversaire->getNom() << " est KO !" << std::endl;

                    adversaire.estVaincu();//verif s'il est vaincu et met a jours son statut si oui

                    if (!adversaire.getVaincu()) {

                        numPokemon_Adversaire++; //pourra pas dépacer Equipe.size vu que le gars sera vaincu

                        pokemonActuel_Adversaire = &adversaire.getPokemon(numPokemon_Adversaire); //on envoie le poke suivant
                        std::cout << adversaire.getNom() << " envoie " << pokemonActuel_Adversaire->getNom() << std::endl;

                    }
                        continue; //on passe a la boucle suivante, il a perdu son pokempn donc peut pas riposter
                }


                //adversaire riposte
                pokemonActuel_Adversaire->attaquer(*pokemonActuel_Joueur);

                if (pokemonActuel_Joueur->getKO()) {
                    std::cout << pokemonActuel_Joueur->getNom() << " est KO !" << std::endl;
                    joueur.estVaincu();

                    if (!joueur.getVaincu()) {
                        numPokemon_Joueur++;
                        pokemonActuel_Joueur = &joueur.getPokemon(numPokemon_Joueur);
                        std::cout << joueur.getNom() << " envoie " << pokemonActuel_Joueur->getNom() << std::endl;

                    }

                }

            }

            //si adversaire est plus rapide
            else  { //adversaire attaque
                //si j'ai bien fais la classe pokemon j'ai juste a dire pokemon attaque (cible)
                pokemonActuel_Adversaire->attaquer(*pokemonActuel_Joueur);

                //la fonction recevoir degats est intégré donc la cible devrait voir ses hp diminuer
                if (pokemonActuel_Joueur->getKO()) {

                    std::cout << pokemonActuel_Joueur->getNom() << " est KO !" << std::endl;
                    joueur.estVaincu();
                    if (!joueur.getVaincu()) {
                        numPokemon_Joueur++; //pourra pas dépacer Equipe.size vu que le gars sera vaincu
                        pokemonActuel_Joueur = &joueur.getPokemon(numPokemon_Joueur); //on envoie le poke suivant
                        std::cout << joueur.getNom() << " envoie " << pokemonActuel_Joueur->getNom() << std::endl;

                    }

                    continue; //on passe a la boucle suivante, il a perdu son pokempn donc peut pas riposter

                }


                //joueur riposte (s'il a pas perdu son pokemon)
                pokemonActuel_Joueur->attaquer(*pokemonActuel_Adversaire);

                if (pokemonActuel_Adversaire->getKO()) {
                    std::cout << pokemonActuel_Adversaire->getNom() << " est KO !" << std::endl;
                    adversaire.estVaincu();

                    if (!adversaire.getVaincu()) {
                        numPokemon_Adversaire++; //pourra pas dépacer Equipe.size vu que le gars sera vaincu
                        pokemonActuel_Adversaire = &adversaire.getPokemon(numPokemon_Adversaire);
                        std::cout << adversaire.getNom() << " envoie " << pokemonActuel_Adversaire->getNom() << std::endl;

                    }

                }

            }



        }

        //combat finis

        if (joueur.getVaincu()) {
            std::cout << joueur.getNom() << " a perdu le combat !" << std::endl;
            joueur.parler_defaiteCombat(adversaire);
            adversaire.parler_victoireCombat(joueur);

        }
        else {
            std::cout << joueur.getNom() << " a remporté le combat !" << std::endl;
            joueur.parler_victoireCombat(adversaire);
            adversaire.parler_defaiteCombat(joueur);

        }
    }

    
   

};

int main() {
    srand(time(0)); //on initialise le random pour les dialogues 
    
    Pokemon Pikachu("Pikachu", { "Electrik" }, 70 , "Eclair", "Electrik", 50 , 15);
    //std::cout << Pikachu.getHP()<<std::endl;
    //std::cout << Pikachu.getDegats()<<std::endl;
    Pokemon Salameche("Salameche", { "Feu" }, 100, "flameche", "feu", 30, 10);
    Pokemon Carapuce("Carapuce", { "eau" }, 100, "pistolet a o", "eau", 30, 8);
    Pokemon Bulbizarre("Bulbizarre", { "plante" }, 100, "fouet liane", "plante", 30, 6);


    Pokemon Mia("Mia", { "tenebre" }, 100, "Morsure", "tenebre", 60 , 12);
    Pokemon Marius("Marius", { "sol" }, 120, "Seisme", "sol", 100, 5);


    //std::cout << Mia.getHP()<<std::endl;
    //std::cout << Mia.getHPmax()<<std::endl;

    Leaders Sascha("Sascha", { Pikachu ,Salameche , Carapuce , Bulbizarre } , "Badge de poule" , "poulailler");

    Joueurs Victor("Victor", { Mia , Marius }, 0, 0, 0);

    //Victor.parler_victoireCombat(Sascha);

    //Sascha.parler_defaiteCombat(Victor);

    Combat(Victor, Sascha);
    //Pokemon Mia("Mia", { "glace" , "plante" }, 50, "morsure", "spectre", 60, 40);
    //Mia.afficherFaiblesses();
    
}

/*
le prblm viens de la methode getKO de pokemon et estVaincu de entraineur vu qu'elle y fait ref, ya aussi la simu de combat qui tourne a l'inf et jpense c'est juste un prblm avec estvaincu vu que 
l'arret du while end epend

ok j'ai redef les fcts estKO et estVaincu, j'ai rajouté des get set pour mettre a jour direct les attributs bool KO de pokemon et bool vaincu de entraineur
du coup j'ai setKO qui met KO a true ou false, setVaincu qui met vaincu a true ou false
maintenant faut que ces fonction soit appelées quelquepart

le probleme viens probablement du fait que j'ai oublié de mettre un & dans une fonction et du coup l'ordi taf sur des copies 
et non sur l'equipe de poke et les dresseurs direct du coup ça met pas bien a jours leurs statut

j'ai enfin trouvé le probleme, en fait j'utilisaos pas des pointeurs pour le pokemon actuel parce que je suis le roi des cons
j'utilisais une ref et du coup quand on changeait le pokemon actuel il effaçait l'ancien pokemon et le remplaçait par le nouveau
du coup ça modifiait l'equipe du dresseur et ça causait des prblms pour mettre a jours les attribus des poke et donc du dresseur
donc cause des soucis dans le combat
*/



