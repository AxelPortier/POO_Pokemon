#pragma once
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




class Pokemon {

protected:
	std::string nom;
	std::vector<std::string> types;
	int HP; //on dit PV normalement, noob
	std::string attaque;
	int degats;
	//faiblesse ??
	

public:
	Pokemon(std::string nom,
		//std::vector<std::string> types,
		int HP,
		std::string attaque,
		int degats);

};

class PokemonSimple : public Pokemon {
private : 
	std::string type;

public : 
	PokemonSimple(std::string nom ,
		int HP ,
		std::string attaque ,
		int degats) : Pokemon(nom , HP , attaque , degats) , type(type) {}

};

class PokemonDouble : public Pokemon {
private:
	std::string type1;
	std::string type2;

public:
	PokemonDouble(std::string nom,
		int HP,
		std::string attaque,
		int degats) : Pokemon(nom, HP, attaque, degats),
		type1(type1) , type2(type2) {}


};


