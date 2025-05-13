

#pragma once

#include "json.hpp" 
#include <fstream>

//fichier telechargé sur github pour pouvoir manipuler des json, j'ai glissé le fichier json.hpp dans le doss où ya les hearders et le .cpp

#include "Pokemon.h"
#include "Entraineurs.h"

/*
chargement des données

Pokemons j'ai tout sauf leurs attaques

donc jpense que ce que je vais faire c'est faire la liste des leaders et maitres avec leurs pokemons parce
que j'ai acces aux attaques de ses pokemons

reste a savoir si je dois tout taper a la main ou pas
et comment organiser les attaques des autres pokemons

en vrai c'est tellement mieux de taffer avec des json que en csv, csv c'est tellement dla d

OK je viens enfin de trouver d'ou viennes les gros soucis d'instance, les fichier Pokemon.json et regions autre que kanto.json *
appelles les pokemon "nom"
alors que Kanto les appels "Pokemon" donc ça fou le zbeul
solution, mettre des verification genre pokedata.value("nom" , poke.value("pokemon", "Inconnu"))
*/

using json = nlohmann::json;

//la finction defPokemon a besoin des infos sur les attaques pare que c'est dispo que dans le json des dresseurs


Pokemon defPokemon(const std::string& nomPokemon, std::string attaque, std::string type_attaque, int degats) { //fonction pour instancier les pokemons adverses (on a certaines infos depuis le json des dresseurs
	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Jsons/Pokemon_sans_accents.json";
	std::ifstream fichier(chemin_fichier); //on ouvre le fichier

	if (!fichier.is_open()) {
		throw std::runtime_error("Impossible d'ouvrir le fichier Pokemon.json. ");

	}

	nlohmann::json data; //creation objet json nommé data
	fichier >> data;
	std::vector<std::string> types; //initalise le vecteur des types du poke
	int HP = 0;
	int vitesse = 0;
	for (const auto& poke : data) {
		if (poke.value("nom", poke.value("pokemon", "Inconnu")) == nomPokemon){ //si on trouve celui qu'on veut
			//std::cout << "on a trouvé " << nomPokemon;

			types.push_back(poke["type1"]); //on met le premier type
			if (poke["type2"] != "") {
				types.push_back(poke["type2"]); //si y'en a un 2e on le met aussi
			}

			HP = poke["pv"];
			vitesse = poke["vitesse"];

			
			//std::cout << " | HP : " << HP << " | vitesse : " << vitesse << std::endl;

		}
	}

	//std::cout << "defPokemon , création de " << nomPokemon << std::endl;


	return 	Pokemon(nomPokemon, types, HP, attaque, type_attaque, degats, vitesse);
}






Leaders defLeaders(const std::string& nomLeader, std::string region) {

	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Jsons/Dresseurs_" + region + ".json";
	//changer ele fichier source quand j'aurais tout les dresseurs

	std::ifstream fichier(chemin_fichier); //on ouvre le fichier

	if (!fichier.is_open()) {
		throw std::runtime_error("Impossible d'ouvrir le fichier dresseurs.json.");
	}

	nlohmann::json data; //creation objet json nommé data
	fichier >> data; //la surcharge de >> est fournis dans json.hpp donc on met le fichier dans data



	for (const auto& champion : data["champions"]) { //a changer en fonction de la structure du json !!
		//on boucle sur les leaders du json
		if (champion.value("nom" , "Inconnu") == nomLeader) {//verif si le leader a bien un nom et si c'ets celui qu'on cherche

			std::string badge = champion.value("badge", "");
			std::string gymnase = champion.value("gymnase", "");

			std::vector<Pokemon> equipe;

			for (const auto& pokeData : champion["equipe"]) {
				std::string nomPoke = pokeData.value("nom", pokeData.value("pokemon", "")); //faut def une fonction def pokemon qui prend le nom et recup les types et tout, là on obtient les attaques deja 

				//je prend que la 1er attaque pour l'instant j'ai pas encore codé les attaques multiples lol
				std::string attaque = pokeData["attaques"][0]["nom"];
				std::string type_attaque = pokeData["attaques"][0]["type"];

				int degats = pokeData["attaques"][0]["puissance"];

				Pokemon Poke = defPokemon(nomPoke, attaque, type_attaque, degats);
				equipe.push_back(Poke);  //je sens que ça va pas marcher, apparement si lol

			}

			return Leaders(nomLeader, equipe, badge, gymnase);

		}

	}
	throw std::runtime_error("Leader '" + nomLeader + "' introuvable dans le fichier.");//si on trouve pas le leader

}

Conseil defConseil(const std::string& nomConseil, std::string region) {
	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Jsons/Dresseurs_" + region + ".json";
	//changer ele fichier source quand j'aurais tout les dresseurs

	std::ifstream fichier(chemin_fichier); //on ouvre le fichier

	if (!fichier.is_open()) {
		throw std::runtime_error("Impossible d'ouvrir le fichier dresseurs.json.");
	}

	nlohmann::json data; //creation objet json nommé data
	fichier >> data; //la surcharge de >> est fournis dans json.hpp donc on met le fichier dans data



	for (const auto& conseil : data["conseil"]) { //a changer en fonction de la structure du json !!
		//on boucle sur les leaders du json
		
		if (conseil.value("nom", "Inconnu") == nomConseil) {//verif si le leader a bien un nom et si c'ets celui qu'on cherche

			std::string specialite = conseil.value("specialite", "");

			std::vector<Pokemon> equipe;
			//std::cout << "dans conseil on regarde l'equipe de " << nomConseil << std::endl;
			for (const auto& pokeData : conseil["equipe"]) {

				std::string nomPoke = pokeData.value("nom", pokeData.value("pokemon", "Inconnu")); //faut def une fonction def pokemon qui prend le nom et recup les types et tout, là on obtient les attaques deja 
				//std::cout << nomPoke << std::endl;
				//je prend que la 1er attaque pour l'instant j'ai pas encore codé les attaques multiples lol
				std::string attaque = pokeData["attaques"][0]["nom"];
				std::string type_attaque = pokeData["attaques"][0]["type"];

				int degats = pokeData["attaques"][0]["puissance"];

				Pokemon Poke = defPokemon(nomPoke, attaque, type_attaque, degats);
				//std::cout << "on vient de fabriquer " << nomPoke << std::endl;
				equipe.push_back(Poke);  //je sens que ça va pas marcher, apparement si lol

			}

			return Conseil(nomConseil, equipe, specialite);

		}

	}
	throw std::runtime_error("Maitre '" + nomConseil + "' introuvable dans le fichier."); //si on trouve pas le leader
}


Maitres defMaitres(const std::string& nomMaitre , std::string region) {

	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Jsons/Dresseurs_" + region + ".json";
	//changer ele fichier source quand j'aurais tout les dresseurs

	std::ifstream fichier(chemin_fichier); //on ouvre le fichier

	if (!fichier.is_open()) {
		throw std::runtime_error("Impossible d'ouvrir le fichier dresseurs.json.");
	}

	nlohmann::json data; //creation objet json nommé data
	fichier >> data; //la surcharge de >> est fournis dans json.hpp donc on met le fichier dans data



	for (const auto& maitre : data["maitre"]) { //a changer en fonction de la structure du json !!
		//on boucle sur les leaders du json
		//std::cout << "on parcours data maitre";
		if (maitre.value("nom" , "Inconnu") == nomMaitre) {//verif si le leader a bien un nom et si c'ets celui qu'on cherche

			

			std::vector<Pokemon> equipe;
			for (const auto& pokeData : maitre["equipe"]) {

				std::string nomPoke = pokeData.value("nom", pokeData.value("pokemon" , "Inconnu")); //faut def une fonction def pokemon qui prend le nom et recup les types et tout, là on obtient les attaques deja 
				//std::cout << nomPoke << std::endl;
				//je prend que la 1er attaque pour l'instant j'ai pas encore codé les attaques multiples lol
				std::string attaque = pokeData["attaques"][0]["nom"];
				std::string type_attaque = pokeData["attaques"][0]["type"];

				int degats = pokeData["attaques"][0]["puissance"];

				Pokemon Poke = defPokemon(nomPoke, attaque, type_attaque, degats);
				equipe.push_back(Poke);  //je sens que ça va pas marcher, apparement si lol
				
			}

			return Maitres(nomMaitre, equipe);

		}

	}
	throw std::runtime_error("Maitre '" + nomMaitre + "' introuvable dans le fichier.");//si on trouve pas le leader

}


Pokemon InstancePokemon(const std::string nomPokemon) {
	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Jsons/Pokemon_sans_accents.json";
	std::ifstream fichier(chemin_fichier); //on ouvre le fichier

	if (!fichier.is_open()) {
		throw std::runtime_error("Impossible d'ouvrir le fichier Pokemon.json. ");

	}

	nlohmann::json data; //creation objet json nommé data
	fichier >> data;
	std::vector<std::string> types; //initalise le vecteur des types du poke
	int HP = 0;
	int vitesse = 0;
	std::string attaque;
	std::string type_attaque;
	int degats = 0;
	for (const auto& poke : data) {
		if (poke.value("nom" , poke.value("pokemon" , "Inconnu")) == nomPokemon) { //si on trouve celui qu'on veut
			//std::cout << "on a trouvé " << nomPokemon;

			types.push_back(poke["type1"]); //on met le premier type
			if (poke["type2"] != "") {
				types.push_back(poke["type2"]); //si y'en a un 2e on le met aussi
			}

			HP = poke["pv"];
			vitesse = poke["vitesse"];

			attaque = poke["attaques"][0]["nom"]; //on prend que 1er attaque pour l'instant
			type_attaque = poke["attaques"][0]["type"];
			degats = poke["attaques"][0]["puissance"];


			//std::cout << " | HP : " << HP << " | vitesse : " << vitesse << std::endl;

		}
	}


	return Pokemon(nomPokemon, types, HP, attaque, type_attaque, degats, vitesse);

}

Joueurs defJoueur(std::string nomJoueur, std::vector<std::string> equipe = {}, int nbBadges = 0, int nbVictoires = 0, int nbDefaites = 0) {
	
	std::vector<Pokemon> EquipePokemon;
	for (const std::string& nom : equipe) {
		EquipePokemon.push_back(InstancePokemon(nom));
	}

	Joueurs joueur(nomJoueur, EquipePokemon, nbBadges, nbVictoires, nbDefaites);
	
	return joueur;
} 


//structure pour afficher les poke sans les instancier pour economiser de la memoire

struct PokemonData {
	std::string nom;
	std::string type1;
	std::string type2;
	int pv;

	PokemonData(const std::string& n, const std::string& t1, const std::string& t2, int p)
		: nom(n), type1(t1), type2(t2), pv(p) {}
};

std::vector<PokemonData> ListeCompletePokemon() {
	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Jsons/Pokemon_sans_accents.json";

	std::ifstream fichier(chemin_fichier);
	if (!fichier.is_open()) {
		throw std::runtime_error("Impossible d'ouvrir le fichier " + chemin_fichier);
	}
	json data;
	fichier >> data;

	std::vector<PokemonData> pokemons;

	for (const auto& poke : data) {


		pokemons.push_back({
			poke.value("nom" , poke.value("pokemon" , "Inconnu")),
			poke["type1"],
			poke["type2"],
			poke["pv"]
			});

	}
	return pokemons;

}


std::vector<Leaders> ListeChampions(std::string region) {
	std::vector<Leaders> ListeChampions;
	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Jsons/Dresseurs_" + region + ".json";
	std::ifstream fichier(chemin_fichier);

	if (!fichier.is_open()) {
		std::cerr << "Erreur : impossible d'ouvrir le fichier JSON pour la région " << region << std::endl;
		return ListeChampions;
	}
	json data;
	fichier >> data;
	

	for (const auto& champion : data["champions"]) {
		//std::cout << champion["nom"] << std::endl;
		std::string nom_champion = champion["nom"];
		ListeChampions.push_back(defLeaders(nom_champion , region));

	}
	
	return ListeChampions;
}//renvoie une liste des leaders de la region, faut ajouter une verif que t'as battu les leaders avant d'atteindre le conseil puis le maitre






std::vector<Conseil> ListeConseil(std::string region) {
	std::vector<Conseil> ListeConseil;
	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Jsons/Dresseurs_" + region + ".json";

	std::ifstream fichier(chemin_fichier);
	if (!fichier.is_open()) {
		std::cerr << "Erreur : impossible d'ouvrir le fichier JSON pour la région " << region << std::endl;
		return ListeConseil;
	}
	json data;
	fichier >> data;
	


	for (const auto& conseil : data["conseil"]) {
		std::string nom_conseil = conseil["nom"];
		//std::cout << nom_conseil << std::endl;

		ListeConseil.push_back(defConseil(nom_conseil, region));
	}
	
	return ListeConseil;
}//renvoie une liste du conseil et du maitre

Maitres ListeMaitre(std::string region) {
	
	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Jsons/Dresseurs_" + region + ".json";

	std::ifstream fichier(chemin_fichier);
	
	json data;
	fichier >> data;
	//d::cout << "ListeMaitre on va créer le maitre";
	Maitres maitre = defMaitres(data["maitre"][0]["nom"], region);

	return maitre;
}
