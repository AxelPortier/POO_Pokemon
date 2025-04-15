#pragma once
#include "Pokemon.h"
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





//les phrases épiques des persos viennent d'une collab avec GPT pour plus d'intensité


class Entraineurs {
protected:
	std::string nom;
	std::vector<Pokemon> Equipe;
	bool vaincu = false; //s'il a perdu (tout ses pokemon sont ko)

public:
	Entraineurs(std::string nom, std::vector<Pokemon> Equipe) : nom(nom) { setEquipe(Equipe); }

	void setEquipe(const std::vector<Pokemon>& equipe) {
		if (equipe.size() > 6) {
			std::cout << "Tu ne peux avoir que 6 Pokemon !" << std::endl;
			Equipe = std::vector<Pokemon>(equipe.begin(), equipe.begin() + 6); //on prend que les 6 premiers
		}
		else {
			Equipe = equipe;
		}
	}

	virtual void parler_debutCombat(Entraineurs& ennemis) { //ce que dis le perso au debut du combat
		int random = rand() % 3;
		switch (random) {
		case 0:
			std::cout << "Je suis " << nom << " entraineur Pokémon, prépare-toi à être vaincu " << ennemis.getNom() << "." << std::endl;
			break;
		case 1:
			std::cout << "Mes Pokémon et moi, on a sué sang et eau pour en arriver là... Tu vas vite comprendre ce que ça veut dire d’être prêt à tout pour gagner." << std::endl;
			break;
		case 2:
			std::cout << "J’espère que t’es prêt à encaisser, " << ennemis.getNom() << ". Car moi, je viens pour tout rafler." << std::endl;
			break;
		}
			

	}

	virtual void parler_defaiteCombat(Entraineurs& ennemis) {//ce que dis le perso apres avoir perdu
		int random = rand() % 3; 
		switch (random) {
		case 0:
			std::cout << "Je m'admets vaincu, " << ennemis.getNom() << ". Tu as su prendre le dessus cette fois..." << std::endl;
			break;
		case 1:
			std::cout << "J'ai tout donné, mais ce n'était pas suffisant... Bien joué, " << ennemis.getNom() << "." << std::endl;
			break;
		case 2:
			std::cout << "Cette défaite me brûle, mais je reconnais ta force, " << ennemis.getNom() << ". On se reverra." << std::endl;
			break;
		}
	}

	virtual void parler_victoireCombat(Entraineurs& ennemis){//ce que dis le perso apres avoir gagné
		int random = rand() % 3;
		switch (random) {
		case 0:
			std::cout << "Tu es faible, " << ennemis.getNom() << ". Tu ne faisais pas le poids face au grand " << nom << "." << std::endl;
			break;
		case 1:
			std::cout << "C'était un beau combat, " << ennemis.getNom() << ", mais à la fin, seule ma stratégie pouvait triompher." << std::endl;
			break;
		case 2:
			std::cout << "La victoire est mienne, comme toujours. Ton équipe n'était pas de taille, " << ennemis.getNom() << "." << std::endl;
			break;
		}
	}

	 std::string getNom() const { return nom; }
	 std::vector<Pokemon> getEquipePokemon() const { return Equipe; }
	 bool getVaincu() const { return vaincu; }

	 //sort le i eme pokemon de l'équipe, le if pour éviter les erreurs mais faut gérer ça aussi côté combat genre si ya plus de poke le gars est vaincu (fais gaffe)

	 Pokemon& getPokemon(int i)  { 
		 if (i < Equipe.size()) {
			 return Equipe[i];
		 }
		 throw std::out_of_range("Index hors de l'équipe !");
	 } 

	 void setNom(std::string newNom) { nom = newNom; }
	 //setPokemon
	 void setVaincu(bool Vaincu) { vaincu = Vaincu; }
	

	 bool estVaincu() { //verif si le dresseur est vaincu

		 if (getVaincu()) { return true; }

		 for (Pokemon& poke : Equipe) {
			 if (!poke.getKO()) { return false; }
		 }
		 setVaincu(true);
		 return true;
		
	 }

	 void afficherEquipe() { //va afficher l'equipe du dresseur pour avoir leurs stats (ça servira pour l'interface mais c'est surtout pour verif si ya un bug dans le main)
		 std::cout << " Equipe de " << nom << " : " << std::endl;
		 
		 for (Pokemon& poke : Equipe) {
			 std::cout << poke.getNom() << " : HP = " << poke.getHP() << " : KO = " << poke.getKO() << std::endl;
		 }
	 }
};



class Leaders : public Entraineurs {
private:
	
	std::string Badge;
	std::string Gymnase;
public:
	Leaders(std::string nom,
		std::vector<Pokemon> Equipe,
		std::string Badge,
		std::string Gymnase) : Entraineurs(nom, Equipe), Badge(Badge), Gymnase(Gymnase) {}
		
	std::string getBadge() const { return Badge;  }
	std::string getGymnase() const { return Gymnase; }

	virtual void parler_debutCombat(Entraineurs& ennemis) override { //ce que dis le leader au debut du combat
		int random = rand() % 4;
		switch (random) {
		case 0:
			std::cout << "Je suis " << nom << ", Leader dy gymnase "<<Gymnase<<". Si tu veux mon "<<Badge<<", il va falloir mériter chaque seconde de ce combat, " << ennemis.getNom() << "." << std::endl;
			break;
		
		case 1:
			std::cout << "Ce badge n’est pas qu’un symbole. C’est la preuve que tu peux survivre à ma tempête. Montre-moi ce que tu as dans le ventre !" << std::endl;
			break;
		case 2:
			std::cout << "Ce terrain, c’est mon royaume. Et ici, c’est moi qui dicte les règles. Si tu veux t’imposer, il va falloir m’impressionner." << std::endl;
			break;
		case 3:
			std::cout << "Beaucoup sont entrés ici avec confiance. Peu en sont ressortis avec ce badge. À ton tour d’essayer, " << ennemis.getNom() << "." << std::endl;
			break;
		}

	}

	virtual void parler_defaiteCombat(Entraineurs& ennemis) override {//ce que dis le leader apres avoir perdu
		int random = rand() % 6;
		switch (random) {
		case 0:
			std::cout << "Je m'admets vaincu, " << ennemis.getNom() << ". Tu as su prendre le dessus cette fois..." << std::endl;
			break;
		case 1:
			std::cout << "Ma défaite n'est pas la fin. C'est juste un nouveau début. Félicitations, " << ennemis.getNom() << ", mais je reviendrai encore plus fort !" << std::endl;
			break;
		case 2:
			std::cout << "J'ai tout donné, mais tu as prouvé ta supériorité. Bien joué, " << ennemis.getNom() << ", tu mérites ce badge." << std::endl;
			break;
		case 3:
			std::cout << "Même les plus solides murs peuvent se fissurer… Tu m’as surpris, " << ennemis.getNom() << ", et tu l’as mérité." << std::endl;
			break;
		case 4:
			std::cout << "Je croyais avoir tout vu, mais tu viens de me rappeler qu'on a toujours à apprendre. Félicitations." << std::endl;
			break;
		case 5:
			std::cout << "Tu as franchi mon épreuve avec brio. Ce badge est à toi… mais retiens bien mon nom, " << ennemis.getNom() << "." << std::endl;
			break;
		}
	}

	virtual void parler_victoireCombat(Entraineurs& ennemis) override {//ce que dis le leader apres avoir gagné
		int random = rand() % 6;
		switch (random) {
		case 0:
			std::cout << "Tu as tout donné, " << ennemis.getNom() << ", mais ça n’a pas suffi. La victoire reste mienne, comme toujours." << std::endl;
			break;
		case 1:
			std::cout << "Ce n'était qu'une question de stratégie, " << ennemis.getNom() << ". Comme toujours, ma préparation m'a permis de l'emporter." << std::endl;
			break;
		case 2:
			std::cout << "J'ai prouvé qu'ici, c’est moi qui tiens les rênes. Le badge que tu convoitais, il restera à sa place !" << std::endl;
			break;
		case 3:
			std::cout << "Un combat intéressant, mais à la fin, seul le meilleur reste debout. C’est moi qui suis le Leader ici, " << ennemis.getNom() << "." << std::endl;
			break;
		case 4:
			std::cout << "Tu t'es battu courageusement, mais tu as face à toi un véritable maître de l'arène. Le badge reste sous ma garde." << std::endl;
			break;
		case 5:
			std::cout << "Un combat de plus, une victoire de plus. Quand tu seras prêt, reviens défier ce gymnase." << std::endl;
			break;
		}
	}
};

class Maitres : public Entraineurs {
private:
	//capacité speciale qui augmente de 25% les dégats de leurs pokemon
	float maitrise = 1.25;
public:
	

	Maitres(std::string nom,
		std::vector<Pokemon> Equipe) : Entraineurs(nom, Equipe) {
		for (Pokemon& pokemon : this -> Equipe) {
			pokemon.setDegats(pokemon.getDegats() * maitrise);
		}
	}

	
	

	void parler_debutCombat(Entraineurs& ennemis) override {
		int random = rand() % 3;

		switch (random) {
		case 0 : 		
			std::cout << "Mon chère "<< ennemis.getNom()<<", les flammes de ton courage ont illuminé le chemin jusqu’à ce sanctuaire sacré... Me voilà, gardien du sommet. Prouve-moi que tu peux détrôner le grand " << nom << " et graver ton nom au Panthéon éternel des Dresseurs !" << std::endl; //quel flow
			break;
		case 1:
			std::cout << "Ton parcours jusqu’ici n’est pas le fruit du hasard. Mais sache-le : ici, seul le véritable Maître survit à l’épreuve finale. Approche, " << nom << " t’attend." << std::endl;
			break;

		case 2:
			std::cout << "Chaque badge, chaque victoire… t'ont mené jusqu’à moi, "<<nom<<". Mais l’ultime ascension n’a rien de paisible. Prépare-toi à affronter la tempête, celle que seul un véritable champion peut dompter." << std::endl;
			break;

		}
		
	}

	virtual void parler_defaiteCombat(Entraineurs& ennemis) override { // ce que dit le maitre après avoir perdu
		int random = rand() % 6;
		switch (random) {
		case 0:
			std::cout << "La défaite n'est qu'un écho dans l'éternité. Tu as su me surpasser, " << ennemis.getNom() << ", mais chaque chute prépare le chemin de la revanche." << std::endl;
			break;
		case 1:
			std::cout << "Même les plus grands trébuchent. Tu m'as défait cette fois, mais sache que la sagesse naît de l'échec. Bien joué, " << ennemis.getNom() << "." << std::endl;
			break;
		case 2:
			std::cout << "La victoire t'appartient aujourd'hui, mais souviens-toi : rien n'est éternel. Nous nous croiserons à nouveau, " << ennemis.getNom() << "." << std::endl;
			break;
		case 3:
			std::cout << "J'ai cru avoir tout anticipé, mais tu m'as montré que la route est toujours pleine de surprises. Félicitations, " << ennemis.getNom() << "." << std::endl;
			break;
		case 4:
			std::cout << "Cette défaite résonne comme une leçon gravée dans le temps. Le monde change, et toi aussi. Bien joué, jeune champion." << std::endl;
			break;
		case 5:
			std::cout << "La sagesse réside dans l'acceptation de la défaite. Tu m'as triomphé, " << ennemis.getNom() << ", mais n'oublie pas : chaque défaite nourrit la victoire à venir." << std::endl;
			break;
		}
	}

	virtual void parler_victoireCombat(Entraineurs& ennemis) override { // ce que dit le mitre après avoir gagné
		int random = rand() % 6;
		switch (random) {
		case 0:
			std::cout << "Il n'y a pas de honte à perdre, " << ennemis.getNom() << ". Mais sache que chaque victoire me rapproche de l'éternité. Le chemin de l'excellence est solitaire." << std::endl;
			break;
		case 1:
			std::cout << "Ta bravoure n'a pas suffi, " << ennemis.getNom() << ". La victoire appartient à ceux qui savent que la vérité se trouve au-delà du simple effort." << std::endl;
			break;
		case 2:
			std::cout << "Le combat était beau, mais il est clair que la sagesse et l'expérience se taillent toujours un chemin vers la victoire." << std::endl;
			break;
		case 3:
			std::cout << "Le destin t'a conduit ici, mais c'est ma préparation qui m'a permis de sortir victorieux. La route est encore longue, jeune challenger." << std::endl;
			break;
		case 4:
			std::cout << "Cette victoire, je la porte avec humilité. Le chemin vers la grandeur ne se fait pas sans sacrifice, mais je reste maître de cet endroit." << std::endl;
			break;
		case 5:
			std::cout << "Tu as voulu défier le Maître, mais tu as sous-estimé la profondeur de l'expérience. La route de la Ligue est semée d'embûches." << std::endl;
			break;
		}
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



	int getNbBadges() const { return nbBadges; }
	int getNbVictoire() const { return nbVictoires; }
	int getNbDefaites() const { return nbDefaites; }

	void parler_debutCombat(Entraineurs& ennemis) override {
		/*
		dynamic_cast<class*>(&adversaire) verif si l'adversaire est bien de la class qu'on regarde
		et sinon elle renvoie un nullptr qu'on utilise comme condition pour savoir si c'est le bon type d'adversaire
		si on utilisaot static cast ça renverrais juste une erreur de con
		*/
		int random = rand() % 3; //sort un nb entre 0 et 2



		if (dynamic_cast<Leaders*>(&ennemis)) {
			if (nbBadges == 0)
			{
				std::cout << "Ce badge est le début de mon ascension, " << ennemis.getNom() << ". Prépare-toi, je ne te laisserai aucune chance !" << std::endl;
			}
			else if (nbBadges == 1)
			{
				std::cout << "Je vois bien que tu es un leader respecté, " << ennemis.getNom() << ", mais mon ambition est plus grande. Ce badge sera mien." << std::endl;
			}
			else if (nbBadges == 2)
			{
				std::cout << "J'ai pris conscience que chaque combat me renforce, " << ennemis.getNom() << ". Je vais prouver que je suis prêt à faire face à toi." << std::endl;
			}
			else if (nbBadges == 3)
			{
				std::cout << "Ce n'est plus une simple quête pour des badges. C'est une question de dépassement, " << ennemis.getNom() << ". Aujourd'hui, c'est toi qui m'affronteras." << std::endl;
			}
			else if (nbBadges == 4)
			{
				std::cout << "Je commence à comprendre la profondeur de chaque combat, " << ennemis.getNom() << ". Mais peu importe, je vais te battre comme tous les autres." << std::endl;
			}
			else if (nbBadges == 5)
			{
				std::cout << "Chaque victoire m'a appris plus que tu ne le penses, " << ennemis.getNom() << ". Mais aujourd'hui, je n'ai plus de doutes, je suis prêt pour ce combat." << std::endl;
			}
			else if (nbBadges == 6)
			{
				std::cout << "Je n'ai jamais été aussi près de ce but, " << ennemis.getNom() << ". Mais ce combat n'est qu'une étape. Prépare-toi à ce qu'il se passe." << std::endl;
			}
			else
			{
				std::cout << "Chaque badge m'a forgé un peu plus, " << ennemis.getNom() << ". Ce n'est pas la victoire qui compte, mais la façon dont on la décroche. Aujourd'hui, ce badge sera mien." << std::endl;
			}
		}


		else if (dynamic_cast<Maitres*>(&ennemis)) {
			if (random == 0)
			{
				std::cout << "J'ai traversé bien des épreuves pour arriver ici, " << ennemis.getNom() << ", mais aujourd'hui, je viens non seulement pour te défier, mais pour mériter ma place parmi les plus grands. Le Panthéon des Dresseurs doit accueillir une nouvelle légende, et c'est mon heure." << std::endl;
			}
			else if (random == 1)
			{
				std::cout << "Le chemin que j'ai parcouru m'a forgé, " << ennemis.getNom() << ". Aujourd'hui, je me tiens devant toi, prêt à prouver que je peux accomplir ce que beaucoup pensaient impossible. Ce combat n'est pas qu'une victoire, c'est l'accomplissement d'une destinée." << std::endl;
			}
			else
			{
				std::cout << "Tu as été un grand Maître, " << ennemis.getNom() << ", c'est incontestable. Mais chaque règne a une fin, et il est temps pour un autre de prendre le flambeau. Aujourd'hui, je vais écrire ma propre légende." << std::endl;
			}
		}

		else if (dynamic_cast<Entraineurs*>(&ennemis)) {
			if (random == 0)
			{
				std::cout << "Je suis " << nom << ", " << ennemis.getNom() << ". Tu vas vite comprendre pourquoi je suis le Dresseur qu'il te faut affronter !" << std::endl;
			}
			else if (random == 1)
			{
				std::cout << "Ce n'est qu'un petit entraînement avant de me frotter aux vrais challenges. Prépare-toi à perdre, " << ennemis.getNom() << " !" << std::endl;
			}
			else
			{
				std::cout << "Si tu penses que ton équipe est meilleure que la mienne, " << ennemis.getNom() << ", je suis prêt à te prouver le contraire !" << std::endl;
			}

		}

	}

	void parler_victoireCombat(Entraineurs& ennemis) override {
		int random = rand() % 3;

		if (dynamic_cast<Leaders*>(&ennemis)) {
			switch (nbBadges) {
			case 0:
				std::cout << "Premier badge en poche ! Ce n’était qu’un début, " << ennemis.getNom() << ". Je vais devenir le meilleur !" << std::endl;
				break;
			case 1:
				std::cout << "Un deuxième badge ! Je sens que je prends de l’assurance. Merci pour ce combat, " << ennemis.getNom() << "." << std::endl;
				break;
			case 2:
				std::cout << "Trois badges maintenant… Ce n’est plus de la chance. Je deviens vraiment fort." << std::endl;
				break;
			case 3:
				std::cout << "Je ne suis plus un débutant. Ce badge prouve que je suis prêt à viser plus haut, " << ennemis.getNom() << "." << std::endl;
				break;
			case 4:
				std::cout << "Encore un badge… Et encore une preuve que rien ne peut m’arrêter." << std::endl;
				break;
			case 5:
				std::cout << "Cinq, six… peu importe le nombre. À chaque combat, je m’approche un peu plus de mon objectif." << std::endl;
				break;
			case 6:
				std::cout << "Ce badge est presque le dernier. Mon parcours touche à son sommet." << std::endl;
				break;
			default:
				std::cout << "Ce dernier badge marque la fin d’un chapitre, mais le vrai défi ne fait que commencer." << std::endl;
				break;
			}
		}
		else if (dynamic_cast<Maitres*>(&ennemis)) {
			switch (random) {
			case 0:
				std::cout << "C’est fait... Je t’ai vaincu, " << ennemis.getNom() << ". Je suis maintenant le nouveau Maître Pokémon." << std::endl;
				break;
			case 1:
				std::cout << "Ce combat était épique, " << ennemis.getNom() << ". Mais aujourd’hui, l’élève a surpassé le Maître." << std::endl;
				break;
			case 2:
				std::cout << "Je n’oublierai jamais ce moment. Merci pour ce combat légendaire, " << ennemis.getNom() << "." << std::endl;
				break;
			}
		}
		else {
			switch (random) {
			case 0:
				std::cout << "Bien joué, " << ennemis.getNom() << ", mais aujourd’hui la victoire m’appartient !" << std::endl;
				break;
			case 1:
				std::cout << "Un bon entraînement ! Ce genre de combat me pousse à progresser encore plus." << std::endl;
				break;
			case 2:
				std::cout << "Tu m’as donné du fil à retordre, " << ennemis.getNom() << ", mais j’ai fini par l’emporter." << std::endl;
				break;
			}
		}
	}

	void parler_defaiteCombat(Entraineurs& ennemis) override {
		int random = rand() % 3;

		if (dynamic_cast<Leaders*>(&ennemis)) {
			switch (nbBadges) {
			case 0:
				std::cout << "Ouch... Premier vrai défi, et première vraie claque. Je ne m'attendais pas à ça, " << ennemis.getNom() << "." << std::endl;
				break;
			case 1:
				std::cout << "Je croyais avoir pris de l'assurance, mais visiblement ce n'est pas encore suffisant... Bien joué, " << ennemis.getNom() << "." << std::endl;
				break;
			case 2:
				std::cout << "Aïe... Peut-être que je me suis un peu trop reposé sur mes lauriers. Ce badge attendra." << std::endl;
				break;
			case 3:
				std::cout << "Ce combat m’a ramené sur terre. Merci pour la leçon, " << ennemis.getNom() << "." << std::endl;
				break;
			case 4:
				std::cout << "Je pensais avoir tout vu... mais tu viens de me rappeler que je peux encore échouer." << std::endl;
				break;
			case 5:
				std::cout << "Encore une défaite... Juste avant la fin. Ça pique. Mais je reviendrai plus fort." << std::endl;
				break;
			case 6:
				std::cout << "Le dernier obstacle... et je tombe. Mais crois-moi, " << ennemis.getNom() << ", ce n’est que partie remise." << std::endl;
				break;
			default:
				std::cout << "Même avec tous ces badges... je peux encore perdre. C’est ça, être un dresseur." << std::endl;
				break;
			}
		}
		else if (dynamic_cast<Maitres*>(&ennemis)) {
			switch (random) {
			case 0:
				std::cout << "J’étais si près du but… Mais tu as prouvé pourquoi tu es Maître. Je reviendrai, " << ennemis.getNom() << "." << std::endl;
				break;
			case 1:
				std::cout << "Cette défaite fait mal, mais elle est aussi nécessaire. Je vais grandir grâce à ce combat." << std::endl;
				break;
			case 2:
				std::cout << "Tu m’as stoppé juste avant le sommet. Mais je gravirai cette montagne, peu importe le temps que ça prendra." << std::endl;
				break;
			}
		}
		else {
			switch (random) {
			case 0:
				std::cout << "T'as gagné cette fois, " << ennemis.getNom() << ", mais la prochaine sera différente. Compte là-dessus." << std::endl;
				break;
			case 1:
				std::cout << "Pas mon jour… Mais chaque défaite m’enseigne quelque chose. Merci pour ce combat." << std::endl;
				break;
			case 2:
				std::cout << "Tu m'as eu… Bien joué. Mais j’apprendrai de cette erreur, et la prochaine fois, je te surprendrai." << std::endl;
				break;
			}
		}
	}


};


