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
#include <unordered_map>


class Type {
public: //vu qu'on veut y avoir accès facilement
	std::string nom; //nom du type (eau, feu...)
	std::unordered_map<std::string, float> faiblesses;
	//c'est juste un dico, la clef est un string et la valeurs un double

	std::unordered_map<std::string, float> resistances;

	Type(std::string n) : nom(n) {}

	~Type() {}

	virtual void defFaiblesses() = 0; //on va les override dans les ss classes
	virtual void defResistances() = 0;

};

/*
les faiblesses et resistances sot def a partir des données du jeu trouvées 
sur internet et non sur le tableau du sujet qui est incomplet

*/

class TypeNormal : public Type {
public:
    TypeNormal() : Type("Normal") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Combat"] = 2.0; // on met à jour le dico des faiblesses avec le multiplicateur
    }

    void defResistances() override {
        resistances["Spectre"] = 0.0; 
        // pareil avec les résistances, ici le type Normal n'est pas affécté par le type spectre donc mult = 0
        
    }
};

class TypeFeu : public Type {
public:
    TypeFeu() : Type("Feu") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Eau"] = 2.0; // on met à jour le dico des faiblesses avec le multiplicateur
        //faiblesses["Roche"] = 2.0;
        faiblesses["Sol"] = 2.0;
    }

    void defResistances() override {
        resistances["Plante"] = 0.5; // pareil avec les résistances
        resistances["Glace"] = 0.5;
        resistances["Insecte"] = 0.5;
        resistances["Acier"] = 0.5;
        //resistances["Fée"] = 0.5;
        resistances["Feu"] = 0.5;
    }
};

class TypeEau : public Type {
public:
    TypeEau() : Type("Eau") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Plante"] = 2.0; // on met à jour le dico des faiblesses avec le multiplicateur
        faiblesses["Electrik"] = 2.0;
    }

    void defResistances() override {
        resistances["Feu"] = 0.5; // pareil avec les résistances
        resistances["Eau"] = 0.5;
        resistances["Glace"] = 0.5;
        //resistances["Acier"] = 0.5;
    }
};

class TypePlante : public Type {
public:
    TypePlante() : Type("Plante") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Feu"] = 2.0;
        faiblesses["Glace"] = 2.0;
        faiblesses["Poison"] = 2.0;
        faiblesses["Vol"] = 2.0;
        faiblesses["Insecte"] = 2.0;
    }

    void defResistances() override {
        resistances["Eau"] = 0.5;
        resistances["Sol"] = 0.5;
        //resistances["Roche"] = 0.5;
        resistances["Plante"] = 0.5;
        resistances["Electrik"] = 0.5;
        resistances["Acier"] = 0.5;
        resistances["Fée"] = 0.5;




    }
};

class TypeElectrik : public Type {
public:
    TypeElectrik() : Type("Électrik") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Sol"] = 2.0;
    }

    void defResistances() override {
        resistances["Vol"] = 0.5;
        resistances["Acier"] = 0.5;
        resistances["Électrik"] = 0.5;
    }
};

class TypeGlace : public Type {
public:
    TypeGlace() : Type("Glace") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Feu"] = 2.0;
        faiblesses["Combat"] = 2.0;
        faiblesses["Roche"] = 2.0;
        faiblesses["Acier"] = 2.0;
    }

    void defResistances() override {
        resistances["Glace"] = 0.5;
    }
};

class TypeCombat : public Type {
public:
    TypeCombat() : Type("Combat") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Vol"] = 2.0;
        faiblesses["Psy"] = 2.0;
        faiblesses["Fée"] = 2.0;
    }

    void defResistances() override {
        resistances["Roche"] = 0.5;
        resistances["Insecte"] = 0.5;
        resistances["Ténèbres"] = 0.5;
    }
};

class TypePoison : public Type {
public:
    TypePoison() : Type("Poison") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Sol"] = 2.0;
        faiblesses["Psy"] = 2.0;
    }

    void defResistances() override {
        resistances["Plante"] = 0.5;
        resistances["Fée"] = 0.5;
        resistances["Combat"] = 0.5;
        resistances["Poison"] = 0.5;
        resistances["Insecte"] = 0.5;
    }
};

class TypeSol : public Type {
public:
    TypeSol() : Type("Sol") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Eau"] = 2.0;
        faiblesses["Plante"] = 2.0;
        faiblesses["Glace"] = 2.0;
    }

    void defResistances() override {
        resistances["Poison"] = 0.5;
        resistances["Roche"] = 0.5;
        resistances["Electrik"] = 0.0; //sol pas affecté par elec


    }
};

class TypeVol : public Type {
public:
    TypeVol() : Type("Vol") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Electrik"] = 2.0;
        faiblesses["Glace"] = 2.0;
        faiblesses["Roche"] = 2.0;
    }

    void defResistances() override {
        resistances["Plante"] = 0.5;
        resistances["Combat"] = 0.5;
        resistances["Insecte"] = 0.5;
    }
};

class TypePsy : public Type {
public:
    TypePsy() : Type("Psy") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Insecte"] = 2.0;
        faiblesses["Spectre"] = 2.0;
        faiblesses["Ténèbres"] = 2.0;
    }

    void defResistances() override {
        resistances["Combat"] = 0.5;
        resistances["Psy"] = 0.5;
    }
};

class TypeInsecte : public Type {
public:
    TypeInsecte() : Type("Insecte") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Feu"] = 2.0;
        faiblesses["Vol"] = 2.0;
        faiblesses["Roche"] = 2.0;
    }

    void defResistances() override {
        resistances["Plante"] = 0.5;
        resistances["Combat"] = 0.5;
        resistances["Sol"] = 0.5;
    }
};

class TypeRoche : public Type {
public:
    TypeRoche() : Type("Roche") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Eau"] = 2.0;
        faiblesses["Plante"] = 2.0;
        faiblesses["Combat"] = 2.0;
        faiblesses["Sol"] = 2.0;
        faiblesses["Acier"] = 2.0;
    }

    void defResistances() override {
        resistances["Feu"] = 0.5;
        resistances["Vol"] = 0.5;
        resistances["Poison"] = 0.5;
        resistances["Normal"] = 0.5;
    }
};

class TypeSpectre : public Type {
public:
    TypeSpectre() : Type("Spectre") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Spectre"] = 2.0;
        faiblesses["Ténèbres"] = 2.0;
    }

    void defResistances() override {
        resistances["Poison"] = 0.5;
        resistances["Insecte"] = 0.5;
        resistances["Normal"] = 0.0; //spectre pas affecté par normal
        resistances["Combat"] = 0.0; //spectre pas affecté par combat


    }
};

class TypeDragon : public Type {
public:
    TypeDragon() : Type("Dragon") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Glace"] = 2.0;
        faiblesses["Dragon"] = 2.0;
        faiblesses["Fée"] = 2.0;
    }

    void defResistances() override {
        resistances["Feu"] = 0.5;
        resistances["Eau"] = 0.5;
        resistances["Électrik"] = 0.5;
        resistances["Plante"] = 0.5;
    }
};

class TypeTenebres : public Type {
public:
    TypeTenebres() : Type("Ténèbres") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Combat"] = 2.0;
        faiblesses["Insecte"] = 2.0;
        faiblesses["Fée"] = 2.0;
    }

    void defResistances() override {
        resistances["Spectre"] = 0.5;
        resistances["Psy"] = 0.0; //tenebre pas affecté par psy
        resistances["Ténèbres"] = 0.5;
    }
};

class TypeAcier : public Type {
public:
    TypeAcier() : Type("Acier") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Feu"] = 2.0;
        faiblesses["Combat"] = 2.0;
        faiblesses["Sol"] = 2.0;
    }

    void defResistances() override {
        resistances["Normal"] = 0.5;
        resistances["Plante"] = 0.5;
        resistances["Glace"] = 0.5;
        resistances["Vol"] = 0.5;
        resistances["Psy"] = 0.5;
        resistances["Insecte"] = 0.5;
        resistances["Roche"] = 0.5;
        resistances["Dragon"] = 0.5;
        resistances["Acier"] = 0.5;
        resistances["Fée"] = 0.5;
        resistances["Poison"] = 0.0;

    }
};

class TypeFee : public Type {
public:
    TypeFee() : Type("Fée") {
        defFaiblesses();
        defResistances(); // on appelle nos fonctions
    }

    void defFaiblesses() override {
        faiblesses["Poison"] = 2.0;
        faiblesses["Acier"] = 2.0;
    }

    void defResistances() override {
        resistances["Combat"] = 0.5;
        resistances["Insecte"] = 0.5;
        resistances["Ténèbres"] = 0.5;
        resistances["Dragon"] = 0.0; //fée pas affecté par dragon
    }
};



class Pokemon {
public:
    std::string nom;

    std::vector<std::string> types; //vecteur qui prend 1 ou 2 noms de types

    std::unordered_map<std::string, float> faiblesses;
    std::unordered_map<std::string, float> resistances;

    int HP;
    std::string attaque; //pour l'instant que une attaque (on verra si on en fait plus apres)
    std::string TypeAttaque;
    int degats;
    
     
    Pokemon(std::string nom,
        std::vector<std::string> t,
        int HP,
        std::string attaque,
        std::string TypeAttaque,
        int degats) : nom(nom), types(t), HP(HP), attaque(attaque),
        TypeAttaque(TypeAttaque) , degats(degats) { //debut constructeur


        std::vector<Type*> instances;
        /*
       vecteur de Type qu'on va remplir d'instances des classes TypeTruc
       en fonction des string qu'on a mis en entrée

       on va donc créer des instances de Type en parcourant le vecteur de string
        */

        for (const std::string& typeNom : t) {
            if (typeNom == "Feu") { instances.push_back(new TypeFeu()); }
            else if (typeNom == "Eau") { instances.push_back(new TypeEau()); }
            else if (typeNom == "Plante") { instances.push_back(new TypePlante()); }
            else if (typeNom == "Électrik") { instances.push_back(new TypeElectrik()); }
            else if (typeNom == "Glace") { instances.push_back(new TypeGlace()); }
            else if (typeNom == "Combat") { instances.push_back(new TypeCombat()); }
            else if (typeNom == "Poison") { instances.push_back(new TypePoison()); }
            else if (typeNom == "Sol") { instances.push_back(new TypeSol()); }
            else if (typeNom == "Vol") { instances.push_back(new TypeVol()); }
            else if (typeNom == "Psy") { instances.push_back(new TypePsy()); }
            else if (typeNom == "Insecte") { instances.push_back(new TypeInsecte()); }
            else if (typeNom == "Roche") { instances.push_back(new TypeRoche()); }
            else if (typeNom == "Spectre") { instances.push_back(new TypeSpectre()); }
            else if (typeNom == "Dragon") { instances.push_back(new TypeDragon()); }
            else if (typeNom == "Ténèbres") { instances.push_back(new TypeTenebres()); }
            else if (typeNom == "Acier") { instances.push_back(new TypeAcier()); }
            else if (typeNom == "Fée") { instances.push_back(new TypeFee()); }
            else if (typeNom == "Normal") { instances.push_back(new TypeNormal()); }

        }

        /*
        ensuite on met a jour les faiblesses et res du pokemon en fusionnant ceux de
        chaques types ( si y'en a plusieurs)

        auto& type parce que faut que ça s'adapte a la class en question

        type-> faiblesses c'est les faiblesses du type et this->faiblesses c'est les faiblesses du pokemon

    this->faiblesses[f.first] += f.second;
    f.first c'est le nom du type auquel on est faible et f.second c'est le mult (2 ici)
    si la faiblesse du type est pas deja dans les faiblesses du pok on l'ajoute
    et si elle y est déja on met juste a jour sa valeurs


        */

        for (const auto& type : instances) { //on parcours le ou les Types de instances
            for (const auto& f : type->faiblesses) {
                this->faiblesses[f.first] += f.second; //mise a jours des faiblesses
            }

            for (const auto& r : type->resistances) {
                this->resistances[r.first] += r.second;//mise a j des res
            }
        }

        //on degage les pointeurs

        for (auto instance : instances){
            delete instance;
    }
       
     if (nom == "Kaiminus") { 
         int KaiBonus = 20; //bonus de puissance pour le roi Kaiminus
         HP = HP * KaiBonus;
         degats = degats * KaiBonus; }

    } //fin du constructeur

    virtual std::unordered_map<std::string, float> getFaiblesses() {
        return faiblesses;
    }

    virtual std::unordered_map<std::string, float> getResistances() {
        return resistances;
    }

    virtual void attaquer(Pokemon& cible) {
        float multiplicateur = 1.0;
        //on regarde les faiblesses et res de la cible

        
            if (cible.faiblesses.find(TypeAttaque) != cible.faiblesses.end()) {
                /*faiblesse.find() = faiblesse.end() ça veut dire que find n'a rien trouvé */

                multiplicateur *= cible.faiblesses[TypeAttaque];

            }
            if (cible.resistances.find(TypeAttaque) != cible.resistances.end()) {

                multiplicateur *= cible.resistances[TypeAttaque];

            }

            int degatsFinal = static_cast<int>(degats * multiplicateur); //statit_cast pour mettre en int
            
            cible.recevoireDegats(degatsFinal); //la cible prend un pied bouche
            if (multiplicateur == 1) {
                std::cout << nom << " attaque " << cible.nom << " avec " << attaque <<"."<< std::endl;

            }
            else if (multiplicateur > 1) {
                std::cout << nom << " attaque " << cible.nom << " avec " << attaque <<". C'est super efficace !" << std::endl;

            }
            else if (0 < multiplicateur < 1) {
                std::cout << nom << " attaque " << cible.nom << " avec " << attaque << ". Ce n'est pas très efficace." << std::endl;

            }
            else if (multiplicateur == 0) {
                std::cout << nom << " attaque " << cible.nom << " avec " << attaque << ". L'attaque n'a aucun effet !" << std::endl;

            }

    
    }


    virtual void recevoireDegats(int degatsReçus) {
        HP -= degatsReçus;
        if (HP < 0) { HP = 0; }
        std::cout << nom << " reçoit " << degatsReçus << " dégats. Il lui reste " << HP << " HP." << std::endl;
    }

    

};
