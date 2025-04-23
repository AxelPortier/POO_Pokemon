#pragma once
#include "Pokemon.h"
#include "Entraineurs.h"
#include "json.hpp" 
#include <fstream>
//fichier telechargé sur github pour pouvoir manipuler des json, j'ai glissé le fichier json.hpp dans le doss où ya les hearders et le .cpp

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


Leaders defLeaders(const std::string& nomLeader) {
	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Leaders_Kanto.json";
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

Pokemon defPokemon(const std::string& nomPokemon, std::string attaque, std::string type_attaque, int degats) {
	std::string chemin_fichier = "C:/Users/pitig/Desktop/Cours/ESILV/A3/S6/Langage C - C++/Projet Pokemon/Pokemon.json";
	std::ifstream fichier(chemin_fichier); //on ouvre le fichier

	if (!fichier.is_open()) {
		throw std::runtime_error("Impossible d'ouvrir le fichier Pokemon.json.");

	}
	nlohmann::json data; //creation objet json nommé data
	fichier >> data;
	std::vector<std::string> types; //initalise le vecteur des types du poke
	int HP = 0;
	int vitesse = 0;
	for (const auto& poke : data) {
		int HP;
		int vitesse;
		if (poke.contains("nom") && poke["nom"] == nomPokemon) { //si on trouve celui qu'on veut

			types.push_back(poke["type1"]); //on met le premier type
			if (poke["type2"] != "") {
				types.push_back(poke["type2"]); //si y'en a un 2e on le met aussi
			}

			HP = poke["pv"];
			vitesse = poke["vitesse"];

		}
	}

	return Pokemon(nomPokemon, types, HP, attaque, type_attaque, degats, vitesse);
}

