#pragma once
#include "Pokemon.h"
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

//les phrases épiques des persos viennent d'une collab avec GPT pour plus d'intensité


class Entraineurs {
protected:
	std::string nom;
	std::vector<Pokemon> Equipe;

public:
	Entraineurs(std::string nom, std::vector<Pokemon> Equipe) : nom(nom), Equipe(Equipe) {}

	virtual void parler() {
		
		std::cout << "Je suis " << nom << " entraineurs Pokemon, prépare toi à crever." << std::endl;
	}

	 std::string getNom() { return nom; }
	 std::vector<Pokemon> getEquipePokemon() { return Equipe; }
};



class Leaders : public Entraineurs {
private:
	
	std::string Badge;
	std::string Gymnase;
public:
	Leaders(std::string nom,
		std::vector<Pokemon> Equipe,
		std::string Badge,
		std::string Gymnase) : Entraineurs(nom, Equipe), Badge(Badge), Gymnase(Gymnase) {
		parler();
	}
		
	std::string getBadge() { return Badge;  }
	std::string getGymnase() { return Gymnase; }

	void parler() override {
		
		std::cout << "On murmure mon nom, " << nom << ", dans les couloirs de cette arène... Tu veux mon badge ? Alors avance, que la vérité du combat te révèle." << std::endl;
	}
};

class Maitres : public Entraineurs {
private:
	//capacité speciale qui augmente de 25% les dégats de leurs pokemon
	float maitrise = 1.25;
public:
	


	Maitres(std::string nom,
		std::vector<Pokemon> Equipe) : Entraineurs(nom, Equipe) {
		parler();

		for (Pokemon pokemon : Equipe) {

			pokemon.setDegats(pokemon.getDegats() * maitrise);

		}
	}

	
	

	void parler() override {
		
		std::cout << "Les flammes de ton courage ont illuminé le chemin jusqu’à ce sanctuaire sacré... Me voilà, gardien du sommet. Prouve-moi que tu peux détrôner le grand " << nom << " et graver ton nom au Panthéon éternel des Dresseurs !" << std::endl; //quel flow
	}
};


class Joueurs : public Entraineurs {
private:

	int nbBadges;
	int nbVictoires;
	int nbDefaites;

public:
	Joueurs(std::string nom,
		std::vector<Pokemon> Equipe,
		int nbBadges,
		int nbVictoires,
		int nbDefaites) : Entraineurs(nom, Equipe), nbBadges(nbBadges), nbVictoires(nbVictoires),
		nbDefaites(nbDefaites) {}



	int getNbBadges() { return nbBadges; }
	int getNbVictoire() { return nbVictoires; }
	int getNbDefaites() { return nbDefaites; }

	void parlerAdversaire_debutCombat(Entraineurs& adversaire) {
		/*
		dynamic_cast<class*>(&adversaire) verif si l'adversaire est bien de la class qu'on regarde
		et sinon elle renvoie un nullptr qu'on utilise comme condition pour savoir si c'est le bon type d'adversaire
		si on utilisaot static cast ça renverrais juste une erreur de con
		*/
		int random = rand() % 3; //sort un nb entre 0 et 2



		if (dynamic_cast<Leaders*>(&adversaire)) {
			if (nbBadges == 0)
			{
				std::cout << "Ce badge est le début de mon ascension. Prépare-toi, je ne te laisserai aucune chance !" << std::endl;
			}
			else if (nbBadges == 1)
			{
				std::cout << "Je vois bien que tu es un leader respecté, mais mon ambition est plus grande. Ce badge sera mien." << std::endl;
			}
			else if (nbBadges == 2)
			{
				std::cout << "J'ai pris conscience que chaque combat me renforce. Je vais prouver que je suis prêt à faire face à toi." << std::endl;
			}
			else if (nbBadges == 3)
			{
				std::cout << "Ce n'est plus une simple quête pour des badges. C'est une question de dépassement. Aujourd'hui, c'est toi qui m'affronteras." << std::endl;
			}
			else if (nbBadges == 4)
			{
				std::cout << "Je commence à comprendre la profondeur de chaque combat. Mais peu importe, je vais te battre comme tous les autres." << std::endl;
			}
			else if (nbBadges == 5)
			{
				std::cout << "Chaque victoire m'a appris plus que tu ne le penses. Mais aujourd'hui, je n'ai plus de doutes, je suis prêt pour ce combat." << std::endl;
			}
			else if (nbBadges == 6)
			{
				std::cout << "Je n'ai jamais été aussi près de ce but. Mais ce combat n'est qu'une étape. Prépare-toi à ce qu'il se passe." << std::endl;
			}
			else
			{
				std::cout << "Chaque badge m'a forgé un peu plus. Ce n'est pas la victoire qui compte, mais la façon dont on la décroche. Aujourd'hui, ce badge sera mien." << std::endl;
			}
		}


		else if (dynamic_cast<Maitres*>(&adversaire)) {
			if (random == 0)
			{
				std::cout << "J'ai traversé bien des épreuves pour arriver ici, mais aujourd'hui, je viens non seulement pour te défier, mais pour mériter ma place parmi les plus grands. Le Panthéon des Dresseurs doit accueillir une nouvelle légende, et c'est mon heure." << std::endl;
			}
			else if (random == 1)
			{
				std::cout << "Le chemin que j'ai parcouru m'a forgé. Aujourd'hui, je me tiens devant toi, prêt à prouver que je peux accomplir ce que beaucoup pensaient impossible. Ce combat n'est pas qu'une victoire, c'est l'accomplissement d'une destinée." << std::endl;
			}
			else
			{
				std::cout << "Tu as été un grand Maître, c'est incontestable. Mais chaque règne a une fin, et il est temps pour un autre de prendre le flambeau. Aujourd'hui, je vais écrire ma propre légende." << std::endl;
			}
		}

		else if (dynamic_cast<Entraineurs*>(&adversaire)) {
			if (random == 0)
			{
				std::cout << "Je suis " << nom << ", tu vas vite comprendre pourquoi je suis le Dresseur qu'il te faut affronter !" << std::endl;
			}
			else if (random == 1)
			{
				std::cout << "Ce n'est qu'un petit entraînement avant de me frotter aux vrais challenges. Prépare-toi à perdre !" << std::endl;
			}
			else
			{
				std::cout << "Si tu penses que ton équipe est meilleure que la mienne, je suis prêt à te prouver le contraire !" << std::endl;
			}

		}

	}



};
