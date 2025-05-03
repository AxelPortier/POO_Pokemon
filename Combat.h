

#pragma once


#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <string>
//#include <Windows.h>
#include <unordered_map>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour time()

#include <thread>   // pour sleep_for
#include <chrono>   // pour chrono::milliseconds

#include "Pokemon.h"
#include "Entraineurs.h"
#include "Données.h"

//pour un meilleurs rendu j'aimerais mettre un timer entre les phrases et ne pas tout afficher a la suite mais parfois
//remplacer les lignes avce les bibli thread et chrono

//idées et rappels
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


si je veux ameliorer le combat il faut que je fasse des fonctions d'attaque liées aux dresseurs
plutot que d'appeler fct attaquer du pokemon dans le main je dois appeler attaquer.joueur et attaquer.dresseur qui font appels a la fonction attaquer.pokemon
du coup jdois faire en sorte que le dresseurs ais acces au pokemin actuel et coder la logique de combat
les entrainneurs ont la meme methode attaquer sauf les joueurs que je vais override, faut que le joueurs demande a l'utilisateur quelle attaque effectuer
les entrainneurs je leurs fais une logique de combat simple, pour commencer il va choisir l'attaque qui fais le plus de degats mais si j'ajoute les problemes de stauts je devrais l'ameliorer

faut vois aussi si la fonction attaquer du pokemon pourrait etre fait autrement parce qu'elle attaque et verif si la cible est Ko jpense qu'on devrait séparer les 2
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
        std::cout << joueur.getNom() << " envoie " << pokemonActuel_Joueur->getNom() << " !" << std::endl;
        std::cout << adversaire.getNom() << " envoie " << pokemonActuel_Adversaire->getNom() << " !" << std::endl;

        int tour = 1;

        while (!joueur.getVaincu() && !adversaire.getVaincu()) {
            bool attaquer = false;
         
            std::cout << "Tour " << tour << std::endl;
            while (true) {
                std::cout << "voulez-vous : 1) Attaquer   |  2) Changer de Pokemon " << std::endl;
                int choix;
                std::cin >> choix;

                if (choix == 1) {
                    attaquer = true; //le joueur décide d'attaquer ce tour
                    break;
                }

                else if (choix == 2) {
                    numPokemon_Joueur = changerPokemon(joueur, numPokemon_Joueur);
                    pokemonActuel_Joueur = &joueur.getPokemon(numPokemon_Joueur);
                    std::cout << joueur.getNom() << " envoie " << pokemonActuel_Joueur->getNom() << std::endl;

                    break;
                }
                else {
                    std::cout << "entrée incorect" << std::endl;
                    continue;
                }

            }

            //attention si un pokemon est ko le prochain pokemon peut attaquer si le dresseur a pas encroe joué, le poke le plus rapide peut pas buter le poke et attaquer celui qui arrive direct

            int vitesseJoueur = pokemonActuel_Joueur->getVitesse();
            int vitesseAdversaire = pokemonActuel_Adversaire->getVitesse(); //pour savoir qui attaque en prems

            //si joueur est plus rapide
            if (vitesseJoueur >= vitesseAdversaire) { //joueur attaque

//j'ai un soucis, le joueur doit pouvoir faire son choix avant que l'adversaire attaque, je choisis atatque ou changer poke,
// si je change de poke je jiue en premier meme si jsuis plus lent et adve attaque ensuite, si j'attauqe c'est le plus rapide qui tape
                if (attaquer) {
                    pokemonActuel_Joueur->attaquer(*pokemonActuel_Adversaire); //la fonction estKO est appelé dans la fonction attaque donc si l'attaque bute le poke son etat ets mis a jours direct
                }
                
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
            else { //adversaire attaque

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
                if (attaquer) {
                    pokemonActuel_Joueur->attaquer(*pokemonActuel_Adversaire); //la fonction estKO est appelé dans la fonction attaque donc si l'attaque bute le poke son etat ets mis a jours direct
                }

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
            tour++;



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


    //fonctions utiles pour le gui

    int getNumPokemon_Joueur() { return numPokemon_Joueur; }
    int getNumPokemon_Adversaire() { return numPokemon_Adversaire; }

    //get Joeuurs faudra adapter pour gérer le pvp apres

    Joueurs getJoueur() const { return joueur; }
    Entraineurs getAdversaire() const { return adversaire; }

    //les setters meme si je doute en avoir besoin

    void setNumPokemon_Joueur(int num) { numPokemon_Joueur = num; }
    void setNumPokemon_Adversaire(int num) { numPokemon_Adversaire = num; }

    void setJoueur(Joueurs newJoueur) { joueur = newJoueur; }
    void setAdversaire(Entraineurs newAdversaire ) { adversaire = newAdversaire; }


    //renvoie une liste de pointeurs vers les pokemon pas KO pour gérer le changement de pokemon


    int changerPokemon(Entraineurs& e , int numActuel) {
        std::cout << "Equipe Pokemon"<< std::endl;
        
        std::vector<Pokemon>& equipe = e.getEquipePokemon(); 

        
        
        int numPoke;
        while (true) {
            std::cout << "Quel Pokemon choisissez-vous ?"<<std::endl;

            int i = 1;

            for (Pokemon& poke : equipe) {
                std::cout << i << ") " << poke << std::endl;
                ++i;
            }

            std::cin >> numPoke;
            numPoke--; //je retire 1 pour que ça corresponde aux indices et evite de crash
            if (numPoke > equipe.size()) { std::cout << "Entré invalide."; continue; }

            else if (!equipe[numPoke].getKO() && numPoke != numActuel) {
                break;
            }
            else if (equipe[numPoke].getKO()) {
                std::cout << "Ce Pokemon est KO ! Vous ne pouvez plus l'envoyer au combat" << std::endl;
                continue;
            }
            else if (numPoke == numActuel) {
                std::cout << "Ce Pokemon est dèjà sur le terrain !" << std::endl;
                continue;
            }
        }
        return numPoke;
    }

    void afficherTexteDelais(const std::string& texte, int delaisMs = 20) {
        for (char c : texte) {
            std::cout << c << std::flush; //flush pour que ça apparraisse au fur et a mesure apparement
            std::this_thread::sleep_for(std::chrono::milliseconds(delaisMs));

        }
        std::cout << std::endl;
    }

    void choisirAttaque(Pokemon& pokemonActuel) const {
        std::cout << "Choissir l'attaque : " << std::endl;
        //faut changer tout le code pour transfo l'attaque du pokemon qui est un string en unorderd map avec attaque : type attaque
    }

       
};
