

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

public:
	Pokemon(std::string nom,
		std::vector<std::string> t,
		int HP,
		std::string attaque,
		std::string TypeAttaque,
		int degats,
		int vitesse) : nom(nom), types(t), HP(HP), attaque(attaque),
		TypeAttaque(TypeAttaque) , degats(degats) , vitesse(vitesse)

*/

using json = nlohmann::json;

//la finction defPokemon a besoin des infos sur les attaques pare que c'est dispo que dans le json des dresseurs


Pokemon defPokemon(const std::string& nomPokemon, std::string attaque, std::string type_attaque, int degats) {
	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Pokemon.json";
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
		if ( poke["nom"] == nomPokemon) { //si on trouve celui qu'on veut
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

	//std::cout << "création de " << nomPokemon << std::endl;
	return Pokemon(nomPokemon, types, HP, attaque, type_attaque, degats, vitesse);
}






Leaders defLeaders(const std::string& nomLeader) {

	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Fusion_Kanto.json";
	//changer ele fichier source quand j'aurais tout les dresseurs

	std::ifstream fichier(chemin_fichier); //on ouvre le fichier

	if (!fichier.is_open()) {
		throw std::runtime_error("Impossible d'ouvrir le fichier dresseurs.json.");
	}

	nlohmann::json data; //creation objet json nommé data
	fichier >> data; //la surcharge de >> est fournis dans json.hpp donc on met le fichier dans data



	for (const auto& leader : data["champions"]) { //a changer en fonction de la structure du json !!
		//on boucle sur les leaders du json
		if (leader.contains("nom") && leader["nom"] == nomLeader) {//verif si le leader a bien un nom et si c'ets celui qu'on cherche

			std::string badge = leader.value("badge", "");
			std::string gymnase = leader.value("gymnase", "");

			std::vector<Pokemon> equipe;
			for (const auto& pokeData : leader["equipe"]) {
				std::string nomPoke = pokeData.value("pokemon", "Inconnu"); //faut def une fonction def pokemon qui prend le nom et recup les types et tout, là on obtient les attaques deja 

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


Maitres defMaitres(const std::string& nomMaitre) {

	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Fusion_Kanto.json";
	//changer ele fichier source quand j'aurais tout les dresseurs

	std::ifstream fichier(chemin_fichier); //on ouvre le fichier

	if (!fichier.is_open()) {
		throw std::runtime_error("Impossible d'ouvrir le fichier dresseurs.json.");
	}

	nlohmann::json data; //creation objet json nommé data
	fichier >> data; //la surcharge de >> est fournis dans json.hpp donc on met le fichier dans data



	for (const auto& maitre : data["maitre"]) { //a changer en fonction de la structure du json !!
		//on boucle sur les leaders du json
		if (maitre["nom"] == nomMaitre) {//verif si le leader a bien un nom et si c'ets celui qu'on cherche

			

			std::vector<Pokemon> equipe;
			for (const auto& pokeData : maitre["equipe"]) {

				std::string nomPoke = pokeData.value("nom", "Inconnu"); //faut def une fonction def pokemon qui prend le nom et recup les types et tout, là on obtient les attaques deja 
				std::cout << nomPoke << std::endl;
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
	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Pokemon.json";
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
		if (poke["nom"] == nomPokemon) { //si on trouve celui qu'on veut
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

Joueurs defJoueur(std::string nomJoueur, std::vector<std::string> equipe = {"Pikachu"}, int nbBadges = 0, int nbVictoires = 0, int nbDefaites = 0) {
	
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
};

std::vector<PokemonData> ListeCompletePokemon() {
	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Pokemon.json";

	std::ifstream fichier(chemin_fichier);
	json data;
	fichier >> data;

	std::vector<PokemonData> pokemons;

	for (const auto& poke : data) {


		pokemons.push_back({
			poke["nom"],
			poke["type1"],
			poke["type2"],
			poke["pv"]
			});

	}
	return pokemons;

}
