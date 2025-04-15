#pragma once
#include <iostream>
#include "Pokemon.h"
#include <string>
#include <vector>
using namespace std;




//les phrases épiques des persos viennent d'une collab avec GPT pour plus d'intensité


class Entraineurs {
protected:
	string nom;
	vector<Pokemon> Equipe;
	bool vaincu = false; //s'il a perdu (tout ses pokemon sont ko)

public:
	Entraineurs(string nom, vector<Pokemon> Equipe) : nom(nom) { setEquipe(Equipe); }

	void setEquipe(const vector<Pokemon>& equipe) {
		if (equipe.size() > 6) {
			cout << "Tu ne peux avoir que 6 Pokemon !" << endl;
			Equipe = vector<Pokemon>(equipe.begin(), equipe.begin() + 6); //on prend que les 6 premiers
		}
		else {
			Equipe = equipe;
		}
	}

	virtual void parler_debutCombat(Entraineurs& ennemis) { //ce que dis le perso au debut du combat
		int random = rand() % 3;
		switch (random) {
		case 0:
			cout << "Je suis " << nom << " entraineur Pokémon, prépare-toi à être vaincu " << ennemis.getNom() << "." << endl;
			break;
		case 1:
			cout << "Mes Pokémon et moi, on a sué sang et eau pour en arriver là... Tu vas vite comprendre ce que ça veut dire d’être prêt à tout pour gagner." << endl;
			break;
		case 2:
			cout << "J’espère que t’es prêt à encaisser, " << ennemis.getNom() << ". Car moi, je viens pour tout rafler." << endl;
			break;
		}
	}

	virtual void parler_defaiteCombat(Entraineurs& ennemis) {//ce que dis le perso apres avoir perdu
		int random = rand() % 3; 
		switch (random) {
		case 0:
			cout << "Je m'admets vaincu, " << ennemis.getNom() << ". Tu as su prendre le dessus cette fois..." << endl;
			break;
		case 1:
			cout << "J'ai tout donné, mais ce n'était pas suffisant... Bien joué, " << ennemis.getNom() << "." << endl;
			break;
		case 2:
			cout << "Cette défaite me brûle, mais je reconnais ta force, " << ennemis.getNom() << ". On se reverra." << endl;
			break;
		}
	}

	virtual void parler_victoireCombat(Entraineurs& ennemis){//ce que dis le perso apres avoir gagné
		int random = rand() % 3;
		switch (random) {
		case 0:
			cout << "Tu es faible, " << ennemis.getNom() << ". Tu ne faisais pas le poids face au grand " << nom << "." << endl;
			break;
		case 1:
			cout << "C'était un beau combat, " << ennemis.getNom() << ", mais à la fin, seule ma stratégie pouvait triompher." << endl;
			break;
		case 2:
			cout << "La victoire est mienne, comme toujours. Ton équipe n'était pas de taille, " << ennemis.getNom() << "." << endl;
			break;
		}
	}

	 string getNom() const { return nom; }
	 vector<Pokemon> getEquipePokemon() const { return Equipe; }

	 Pokemon getPokemon() const { return Equipe[0]; } //sort le 1er pokemon de l'équipe

	 bool estVaincu() { //verif si le dresseur est vaincu
		 bool estVaincu = false;
		 int p = 0;
		 for (Pokemon poke : Equipe) {
			 if (poke.estKO()) {
				 ++p;
			 }

		 }
		 if (p == Equipe.size()) {
			 estVaincu = true;
		 }
		 return estVaincu;
	 }
};



class Leaders : public Entraineurs {
private:
	
	string Badge;
	string Gymnase;
public:
	Leaders(string nom,
		vector<Pokemon> Equipe,
		string Badge,
		string Gymnase) : Entraineurs(nom, Equipe), Badge(Badge), Gymnase(Gymnase) {}
		
	string getBadge() const { return Badge;  }
	string getGymnase() const { return Gymnase; }

	virtual void parler_debutCombat(Entraineurs& ennemis) override { //ce que dis le leader au debut du combat
		int random = rand() % 4;
		switch (random) {
		case 0:
			cout << "Je suis " << nom << ", Leader dy gymnase "<<Gymnase<<". Si tu veux mon "<<Badge<<", il va falloir mériter chaque seconde de ce combat, " << ennemis.getNom() << "." << endl;
			break;
		
		case 1:
			cout << "Ce badge n’est pas qu’un symbole. C’est la preuve que tu peux survivre à ma tempête. Montre-moi ce que tu as dans le ventre !" << endl;
			break;
		case 2:
			cout << "Ce terrain, c’est mon royaume. Et ici, c’est moi qui dicte les règles. Si tu veux t’imposer, il va falloir m’impressionner." << endl;
			break;
		case 3:
			cout << "Beaucoup sont entrés ici avec confiance. Peu en sont ressortis avec ce badge. À ton tour d’essayer, " << ennemis.getNom() << "." << endl;
			break;
		}

	}

	virtual void parler_defaiteCombat(Entraineurs& ennemis) override {//ce que dis le leader apres avoir perdu
		int random = rand() % 6;
		switch (random) {
		case 0:
			cout << "Je m'admets vaincu, " << ennemis.getNom() << ". Tu as su prendre le dessus cette fois..." << endl;
			break;
		case 1:
			cout << "Ma défaite n'est pas la fin. C'est juste un nouveau début. Félicitations, " << ennemis.getNom() << ", mais je reviendrai encore plus fort !" << endl;
			break;
		case 2:
			cout << "J'ai tout donné, mais tu as prouvé ta supériorité. Bien joué, " << ennemis.getNom() << ", tu mérites ce badge." << endl;
			break;
		case 3:
			cout << "Même les plus solides murs peuvent se fissurer… Tu m’as surpris, " << ennemis.getNom() << ", et tu l’as mérité." << endl;
			break;
		case 4:
			cout << "Je croyais avoir tout vu, mais tu viens de me rappeler qu'on a toujours à apprendre. Félicitations." << endl;
			break;
		case 5:
			cout << "Tu as franchi mon épreuve avec brio. Ce badge est à toi… mais retiens bien mon nom, " << ennemis.getNom() << "." << endl;
			break;
		}
	}

	virtual void parler_victoireCombat(Entraineurs& ennemis) override {//ce que dis le leader apres avoir gagné
		int random = rand() % 6;
		switch (random) {
		case 0:
			cout << "Tu as tout donné, " << ennemis.getNom() << ", mais ça n’a pas suffi. La victoire reste mienne, comme toujours." << endl;
			break;
		case 1:
			cout << "Ce n'était qu'une question de stratégie, " << ennemis.getNom() << ". Comme toujours, ma préparation m'a permis de l'emporter." << endl;
			break;
		case 2:
			cout << "J'ai prouvé qu'ici, c’est moi qui tiens les rênes. Le badge que tu convoitais, il restera à sa place !" << endl;
			break;
		case 3:
			cout << "Un combat intéressant, mais à la fin, seul le meilleur reste debout. C’est moi qui suis le Leader ici, " << ennemis.getNom() << "." << endl;
			break;
		case 4:
			cout << "Tu t'es battu courageusement, mais tu as face à toi un véritable maître de l'arène. Le badge reste sous ma garde." << endl;
			break;
		case 5:
			cout << "Un combat de plus, une victoire de plus. Quand tu seras prêt, reviens défier ce gymnase." << endl;
			break;
		}
	}
};

class Maitres : public Entraineurs {
private:
	//capacité speciale qui augmente de 25% les dégats de leurs pokemon
	float maitrise = 1.25;
public:
	

	Maitres(string nom,
		vector<Pokemon> Equipe) : Entraineurs(nom, Equipe) {
		for (Pokemon& pokemon : this -> Equipe) {
			pokemon.setDegats(pokemon.getDegats() * maitrise);
		}
	}

	
	

	void parler_debutCombat(Entraineurs& ennemis) override {
		int random = rand() % 3;

		switch (random) {
		case 0 : 		
			cout << "Mon chère "<< ennemis.getNom()<<", les flammes de ton courage ont illuminé le chemin jusqu’à ce sanctuaire sacré... Me voilà, gardien du sommet. Prouve-moi que tu peux détrôner le grand " << nom << " et graver ton nom au Panthéon éternel des Dresseurs !" << endl; //quel flow
			break;
		case 1:
			cout << "Ton parcours jusqu’ici n’est pas le fruit du hasard. Mais sache-le : ici, seul le véritable Maître survit à l’épreuve finale. Approche, " << nom << " t’attend." << endl;
			break;

		case 2:
			cout << "Chaque badge, chaque victoire… t'ont mené jusqu’à moi, "<<nom<<". Mais l’ultime ascension n’a rien de paisible. Prépare-toi à affronter la tempête, celle que seul un véritable champion peut dompter." << endl;
			break;

		}
		
	}

	virtual void parler_defaiteCombat(Entraineurs& ennemis) override { // ce que dit le maitre après avoir perdu
		int random = rand() % 6;
		switch (random) {
		case 0:
			cout << "La défaite n'est qu'un écho dans l'éternité. Tu as su me surpasser, " << ennemis.getNom() << ", mais chaque chute prépare le chemin de la revanche." << endl;
			break;
		case 1:
			cout << "Même les plus grands trébuchent. Tu m'as défait cette fois, mais sache que la sagesse naît de l'échec. Bien joué, " << ennemis.getNom() << "." << endl;
			break;
		case 2:
			cout << "La victoire t'appartient aujourd'hui, mais souviens-toi : rien n'est éternel. Nous nous croiserons à nouveau, " << ennemis.getNom() << "." << endl;
			break;
		case 3:
			cout << "J'ai cru avoir tout anticipé, mais tu m'as montré que la route est toujours pleine de surprises. Félicitations, " << ennemis.getNom() << "." << endl;
			break;
		case 4:
			cout << "Cette défaite résonne comme une leçon gravée dans le temps. Le monde change, et toi aussi. Bien joué, jeune champion." << endl;
			break;
		case 5:
			cout << "La sagesse réside dans l'acceptation de la défaite. Tu m'as triomphé, " << ennemis.getNom() << ", mais n'oublie pas : chaque défaite nourrit la victoire à venir." << endl;
			break;
		}
	}

	virtual void parler_victoireCombat(Entraineurs& ennemis) override { // ce que dit le mitre après avoir gagné
		int random = rand() % 6;
		switch (random) {
		case 0:
			cout << "Il n'y a pas de honte à perdre, " << ennemis.getNom() << ". Mais sache que chaque victoire me rapproche de l'éternité. Le chemin de l'excellence est solitaire." << endl;
			break;
		case 1:
			cout << "Ta bravoure n'a pas suffi, " << ennemis.getNom() << ". La victoire appartient à ceux qui savent que la vérité se trouve au-delà du simple effort." << endl;
			break;
		case 2:
			cout << "Le combat était beau, mais il est clair que la sagesse et l'expérience se taillent toujours un chemin vers la victoire." << endl;
			break;
		case 3:
			cout << "Le destin t'a conduit ici, mais c'est ma préparation qui m'a permis de sortir victorieux. La route est encore longue, jeune challenger." << endl;
			break;
		case 4:
			cout << "Cette victoire, je la porte avec humilité. Le chemin vers la grandeur ne se fait pas sans sacrifice, mais je reste maître de cet endroit." << endl;
			break;
		case 5:
			cout << "Tu as voulu défier le Maître, mais tu as sous-estimé la profondeur de l'expérience. La route de la Ligue est semée d'embûches." << endl;
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
	Joueurs(string nom,
		vector<Pokemon> Equipe,
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
				cout << "Ce badge est le début de mon ascension, " << ennemis.getNom() << ". Prépare-toi, je ne te laisserai aucune chance !" << endl;
			}
			else if (nbBadges == 1)
			{
				cout << "Je vois bien que tu es un leader respecté, " << ennemis.getNom() << ", mais mon ambition est plus grande. Ce badge sera mien." << endl;
			}
			else if (nbBadges == 2)
			{
				cout << "J'ai pris conscience que chaque combat me renforce, " << ennemis.getNom() << ". Je vais prouver que je suis prêt à faire face à toi." << endl;
			}
			else if (nbBadges == 3)
			{
				cout << "Ce n'est plus une simple quête pour des badges. C'est une question de dépassement, " << ennemis.getNom() << ". Aujourd'hui, c'est toi qui m'affronteras." << endl;
			}
			else if (nbBadges == 4)
			{
				cout << "Je commence à comprendre la profondeur de chaque combat, " << ennemis.getNom() << ". Mais peu importe, je vais te battre comme tous les autres." << endl;
			}
			else if (nbBadges == 5)
			{
				cout << "Chaque victoire m'a appris plus que tu ne le penses, " << ennemis.getNom() << ". Mais aujourd'hui, je n'ai plus de doutes, je suis prêt pour ce combat." << endl;
			}
			else if (nbBadges == 6)
			{
				cout << "Je n'ai jamais été aussi près de ce but, " << ennemis.getNom() << ". Mais ce combat n'est qu'une étape. Prépare-toi à ce qu'il se passe." << endl;
			}
			else
			{
				cout << "Chaque badge m'a forgé un peu plus, " << ennemis.getNom() << ". Ce n'est pas la victoire qui compte, mais la façon dont on la décroche. Aujourd'hui, ce badge sera mien." << endl;
			}
		}


		else if (dynamic_cast<Maitres*>(&ennemis)) {
			if (random == 0)
			{
				cout << "J'ai traversé bien des épreuves pour arriver ici, " << ennemis.getNom() << ", mais aujourd'hui, je viens non seulement pour te défier, mais pour mériter ma place parmi les plus grands. Le Panthéon des Dresseurs doit accueillir une nouvelle légende, et c'est mon heure." << endl;
			}
			else if (random == 1)
			{
				cout << "Le chemin que j'ai parcouru m'a forgé, " << ennemis.getNom() << ". Aujourd'hui, je me tiens devant toi, prêt à prouver que je peux accomplir ce que beaucoup pensaient impossible. Ce combat n'est pas qu'une victoire, c'est l'accomplissement d'une destinée." << endl;
			}
			else
			{
				cout << "Tu as été un grand Maître, " << ennemis.getNom() << ", c'est incontestable. Mais chaque règne a une fin, et il est temps pour un autre de prendre le flambeau. Aujourd'hui, je vais écrire ma propre légende." << endl;
			}
		}

		else if (dynamic_cast<Entraineurs*>(&ennemis)) {
			if (random == 0)
			{
				cout << "Je suis " << nom << ", " << ennemis.getNom() << ". Tu vas vite comprendre pourquoi je suis le Dresseur qu'il te faut affronter !" << endl;
			}
			else if (random == 1)
			{
				cout << "Ce n'est qu'un petit entraînement avant de me frotter aux vrais challenges. Prépare-toi à perdre, " << ennemis.getNom() << " !" << endl;
			}
			else
			{
				cout << "Si tu penses que ton équipe est meilleure que la mienne, " << ennemis.getNom() << ", je suis prêt à te prouver le contraire !" << endl;
			}

		}

	}

	void parler_victoireCombat(Entraineurs& ennemis) override {
		int random = rand() % 3;

		if (dynamic_cast<Leaders*>(&ennemis)) {
			switch (nbBadges) {
			case 0:
				cout << "Premier badge en poche ! Ce n’était qu’un début, " << ennemis.getNom() << ". Je vais devenir le meilleur !" << endl;
				break;
			case 1:
				cout << "Un deuxième badge ! Je sens que je prends de l’assurance. Merci pour ce combat, " << ennemis.getNom() << "." << endl;
				break;
			case 2:
				cout << "Trois badges maintenant… Ce n’est plus de la chance. Je deviens vraiment fort." << endl;
				break;
			case 3:
				cout << "Je ne suis plus un débutant. Ce badge prouve que je suis prêt à viser plus haut, " << ennemis.getNom() << "." << endl;
				break;
			case 4:
				cout << "Encore un badge… Et encore une preuve que rien ne peut m’arrêter." << endl;
				break;
			case 5:
				cout << "Cinq, six… peu importe le nombre. À chaque combat, je m’approche un peu plus de mon objectif." << endl;
				break;
			case 6:
				cout << "Ce badge est presque le dernier. Mon parcours touche à son sommet." << endl;
				break;
			default:
				cout << "Ce dernier badge marque la fin d’un chapitre, mais le vrai défi ne fait que commencer." << endl;
				break;
			}
		}
		else if (dynamic_cast<Maitres*>(&ennemis)) {
			switch (random) {
			case 0:
				cout << "C’est fait... Je t’ai vaincu, " << ennemis.getNom() << ". Je suis maintenant le nouveau Maître Pokémon." << endl;
				break;
			case 1:
				cout << "Ce combat était épique, " << ennemis.getNom() << ". Mais aujourd’hui, l’élève a surpassé le Maître." << endl;
				break;
			case 2:
				cout << "Je n’oublierai jamais ce moment. Merci pour ce combat légendaire, " << ennemis.getNom() << "." << endl;
				break;
			}
		}
		else {
			switch (random) {
			case 0:
				cout << "Bien joué, " << ennemis.getNom() << ", mais aujourd’hui la victoire m’appartient !" << endl;
				break;
			case 1:
				cout << "Un bon entraînement ! Ce genre de combat me pousse à progresser encore plus." << endl;
				break;
			case 2:
				cout << "Tu m’as donné du fil à retordre, " << ennemis.getNom() << ", mais j’ai fini par l’emporter." << endl;
				break;
			}
		}
	}

	void parler_defaiteCombat(Entraineurs& ennemis) override {
		int random = rand() % 3;

		if (dynamic_cast<Leaders*>(&ennemis)) {
			switch (nbBadges) {
			case 0:
				cout << "Ouch... Premier vrai défi, et première vraie claque. Je ne m'attendais pas à ça, " << ennemis.getNom() << "." << endl;
				break;
			case 1:
				cout << "Je croyais avoir pris de l'assurance, mais visiblement ce n'est pas encore suffisant... Bien joué, " << ennemis.getNom() << "." << endl;
				break;
			case 2:
				cout << "Aïe... Peut-être que je me suis un peu trop reposé sur mes lauriers. Ce badge attendra." << endl;
				break;
			case 3:
				cout << "Ce combat m’a ramené sur terre. Merci pour la leçon, " << ennemis.getNom() << "." << endl;
				break;
			case 4:
				cout << "Je pensais avoir tout vu... mais tu viens de me rappeler que je peux encore échouer." << endl;
				break;
			case 5:
				cout << "Encore une défaite... Juste avant la fin. Ça pique. Mais je reviendrai plus fort." << endl;
				break;
			case 6:
				cout << "Le dernier obstacle... et je tombe. Mais crois-moi, " << ennemis.getNom() << ", ce n’est que partie remise." << endl;
				break;
			default:
				cout << "Même avec tous ces badges... je peux encore perdre. C’est ça, être un dresseur." << endl;
				break;
			}
		}
		else if (dynamic_cast<Maitres*>(&ennemis)) {
			switch (random) {
			case 0:
				cout << "J’étais si près du but… Mais tu as prouvé pourquoi tu es Maître. Je reviendrai, " << ennemis.getNom() << "." << endl;
				break;
			case 1:
				cout << "Cette défaite fait mal, mais elle est aussi nécessaire. Je vais grandir grâce à ce combat." << endl;
				break;
			case 2:
				cout << "Tu m’as stoppé juste avant le sommet. Mais je gravirai cette montagne, peu importe le temps que ça prendra." << endl;
				break;
			}
		}
		else {
			switch (random) {
			case 0:
				cout << "T'as gagné cette fois, " << ennemis.getNom() << ", mais la prochaine sera différente. Compte là-dessus." << endl;
				break;
			case 1:
				cout << "Pas mon jour… Mais chaque défaite m’enseigne quelque chose. Merci pour ce combat." << endl;
				break;
			case 2:
				cout << "Tu m'as eu… Bien joué. Mais j’apprendrai de cette erreur, et la prochaine fois, je te surprendrai." << endl;
				break;
			}
		}
	}


};


