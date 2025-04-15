#pragma once
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
#include <memory> //pour les unique ptr

void toLowerCase(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}
void toLowerVect(std::vector<std::string>& vect) {
    for (std::string str : vect) { toLowerCase(str); }
}

class Type {
protected: 
	std::string nom; //nom du type (eau, feu...)
	std::unordered_map<std::string, float> faiblesses;
	//c'est juste un dico, la clef est un string et la valeurs un float (type : multiplicateur)

	std::unordered_map<std::string, float> resistances;

public:
	Type(std::string n) : nom(n) {}

    ~Type() = default;

	virtual void defFaiblesses() = 0; //on va les override dans les ss classes
	virtual void defResistances() = 0;

    std::unordered_map<std::string, float> getFaiblesses() const { return faiblesses; }
    std::unordered_map<std::string, float> getResistances() const { return resistances; }


};

/*
les faiblesses et resistances sot def a partir des données du jeu trouvées 
sur internet et non sur le tableau du sujet qui est incomplet

*/

class TypeNormal : public Type {
public:
    TypeNormal() : Type("normal") {
        defFaiblesses();
        defResistances(); //on appel nos fonctions pour le constructeur

        
    }

    void defFaiblesses() override {
        faiblesses["combat"] = 2.0; // on met à jour le dico des faiblesses avec le multiplicateur
    }

    void defResistances() override {
        resistances["spectre"] = 0.0; 
        // pareil avec les résistances, ici le type Normal n'est pas affécté par le type spectre donc mult = 0
        
    }
};

class TypeFeu : public Type {
public:
    TypeFeu() : Type("feu") {
        defFaiblesses();
        defResistances(); 

        
    }

    void defFaiblesses() override {
        faiblesses["eau"] = 2.0; // on met à jour le dico des faiblesses avec le multiplicateur
        //faiblesses["roche"] = 2.0;
        faiblesses["sol"] = 2.0;
    }

    void defResistances() override {
        resistances["plante"] = 0.5; // pareil avec les résistances
        resistances["glace"] = 0.5;
        resistances["insecte"] = 0.5;
        resistances["acier"] = 0.5;
        //resistances["fee"] = 0.5;
        resistances["feu"] = 0.5;
    }
};

class TypeEau : public Type {
public:
    TypeEau() : Type("eau") {
        defFaiblesses();
        defResistances(); 
        
    }

    void defFaiblesses() override {
        faiblesses["plante"] = 2.0; // on met à jour le dico des faiblesses avec le multiplicateur
        faiblesses["electrik"] = 2.0;
    }

    void defResistances() override {
        resistances["feu"] = 0.5; // pareil avec les résistances
        resistances["eau"] = 0.5;
        resistances["glace"] = 0.5;
        //resistances["acier"] = 0.5;
    }
};

class TypePlante : public Type {
public:
    TypePlante() : Type("plante") {
        defFaiblesses();
        defResistances(); 

        
    }

    void defFaiblesses() override {
        faiblesses["feu"] = 2.0;
        faiblesses["glace"] = 2.0;
        faiblesses["poison"] = 2.0;
        faiblesses["sol"] = 2.0;
        faiblesses["insecte"] = 2.0;
    }

    void defResistances() override {
        resistances["eau"] = 0.5;
        resistances["sol"] = 0.5;
        //resistances["roche"] = 0.5;
        resistances["plante"] = 0.5;
        resistances["electrik"] = 0.5;
        resistances["acier"] = 0.5;
        resistances["fee"] = 0.5;




    }
};

class TypeElectrik : public Type {
public:
    TypeElectrik() : Type("electrik") {
        defFaiblesses();
        defResistances(); 

        
    }

    void defFaiblesses() override {
        faiblesses["sol"] = 2.0;
    }

    void defResistances() override {
        resistances["vol"] = 0.5;
        resistances["acier"] = 0.5;
        resistances["electrik"] = 0.5;
    }
};

class TypeGlace : public Type {
public:
    TypeGlace() : Type("glace") {
        defFaiblesses();
        defResistances(); 

       
    }

    void defFaiblesses() override {
        faiblesses["feu"] = 2.0;
        faiblesses["combat"] = 2.0;
        faiblesses["roche"] = 2.0;
        faiblesses["acier"] = 2.0;
    }

    void defResistances() override {
        resistances["glace"] = 0.5;
    }
};

class TypeCombat : public Type {
public:
    TypeCombat() : Type("combat") {
        defFaiblesses();
        defResistances(); 
        
    }

    void defFaiblesses() override {
        faiblesses["vol"] = 2.0;
        faiblesses["psy"] = 2.0;
        faiblesses["fee"] = 2.0;
    }

    void defResistances() override {
        resistances["roche"] = 0.5;
        resistances["insecte"] = 0.5;
        resistances["tenebres"] = 0.5;
    }
};

class TypePoison : public Type {
public:
    TypePoison() : Type("poison") {
        defFaiblesses();
        defResistances(); 

        
    }

    void defFaiblesses() override {
        faiblesses["sol"] = 2.0;
        faiblesses["psy"] = 2.0;
    }

    void defResistances() override {
        resistances["plante"] = 0.5;
        resistances["fee"] = 0.5;
        resistances["combat"] = 0.5;
        resistances["poison"] = 0.5;
        resistances["insecte"] = 0.5;
    }
};

class TypeSol : public Type {
public:
    TypeSol() : Type("sol") {
        defFaiblesses();
        defResistances();

        
    }

    void defFaiblesses() override {
        faiblesses["eau"] = 2.0;
        faiblesses["plante"] = 2.0;
        faiblesses["glace"] = 2.0;
    }

    void defResistances() override {
        resistances["poison"] = 0.5;
        resistances["roche"] = 0.5;
        resistances["electrik"] = 0.0; //sol pas affecté par elec


    }
};

class TypeVol : public Type {
public:
    TypeVol() : Type("vol") {
        defFaiblesses();
        defResistances(); 

       
    }

    void defFaiblesses() override {
        faiblesses["electrik"] = 2.0;
        faiblesses["glace"] = 2.0;
        faiblesses["roche"] = 2.0;
    }

    void defResistances() override {
        resistances["plante"] = 0.5;
        resistances["combat"] = 0.5;
        resistances["insecte"] = 0.5;
    }
};

class TypePsy : public Type {
public:
    TypePsy() : Type("psy") {
        defFaiblesses();
        defResistances(); 
        
    }

    void defFaiblesses() override {
        faiblesses["insecte"] = 2.0;
        faiblesses["spectre"] = 2.0;
        faiblesses["tenebres"] = 2.0;
    }

    void defResistances() override {
        resistances["combat"] = 0.5;
        resistances["psy"] = 0.5;
    }
};

class TypeInsecte : public Type {
public:
    TypeInsecte() : Type("insecte") {
        defFaiblesses();
        defResistances(); 
        
    }

    void defFaiblesses() override {
        faiblesses["feu"] = 2.0;
        faiblesses["vol"] = 2.0;
        faiblesses["roche"] = 2.0;
    }

    void defResistances() override {
        resistances["plante"] = 0.5;
        resistances["combat"] = 0.5;
        resistances["sol"] = 0.5;
    }
};

class TypeRoche : public Type {
public:
    TypeRoche() : Type("roche") {
        defFaiblesses();
        defResistances(); 

        
    }

    void defFaiblesses() override {
        faiblesses["eau"] = 2.0;
        faiblesses["plante"] = 2.0;
        faiblesses["combat"] = 2.0;
        faiblesses["sol"] = 2.0;
        faiblesses["acier"] = 2.0;
    }

    void defResistances() override {
        resistances["feu"] = 0.5;
        resistances["vol"] = 0.5;
        resistances["poison"] = 0.5;
        resistances["normal"] = 0.5;
    }
};

class TypeSpectre : public Type {
public:
    TypeSpectre() : Type("spectre") {
        defFaiblesses();
        defResistances();

        
    }

    void defFaiblesses() override {
        faiblesses["spectre"] = 2.0;
        faiblesses["tenebres"] = 2.0;
    }

    void defResistances() override {
        resistances["poison"] = 0.5;
        resistances["insecte"] = 0.5;
        resistances["normal"] = 0.0; //spectre pas affecté par normal
        resistances["combat"] = 0.0; //spectre pas affecté par combat


    }
};

class TypeDragon : public Type {
public:
    TypeDragon() : Type("dragon") {
        defFaiblesses();
        defResistances(); 

        
    }

    void defFaiblesses() override {
        faiblesses["glace"] = 2.0;
        faiblesses["dragon"] = 2.0;
        faiblesses["fee"] = 2.0;
    }

    void defResistances() override {
        resistances["feu"] = 0.5;
        resistances["eau"] = 0.5;
        resistances["electrik"] = 0.5;
        resistances["plante"] = 0.5;
    }
};

class TypeTenebres : public Type {
public:
    TypeTenebres() : Type("tenebres") {
        defFaiblesses();
        defResistances();

    }

    void defFaiblesses() override {
        faiblesses["combat"] = 2.0;
        faiblesses["insecte"] = 2.0;
        faiblesses["fee"] = 2.0;
    }

    void defResistances() override {
        resistances["spectre"] = 0.5;
        resistances["psy"] = 0.0; //tenebre pas affecté par psy
        resistances["tenebres"] = 0.5;
    }
};

class TypeAcier : public Type {
public:
    TypeAcier() : Type("acier") {
        defFaiblesses();
        defResistances(); 

        
    }

    void defFaiblesses() override {
        faiblesses["feu"] = 2.0;
        faiblesses["combat"] = 2.0;
        faiblesses["sol"] = 2.0;
    }

    void defResistances() override {
        resistances["normal"] = 0.5;
        resistances["plante"] = 0.5;
        resistances["glace"] = 0.5;
        resistances["vol"] = 0.5;
        resistances["psy"] = 0.5;
        resistances["insecte"] = 0.5;
        resistances["roche"] = 0.5;
        resistances["dragon"] = 0.5;
        resistances["acier"] = 0.5;
        resistances["fee"] = 0.5;
        resistances["poison"] = 0.0;

    }
};

class TypeFee : public Type {
public:
    TypeFee() : Type("fee") {
        defFaiblesses();
        defResistances(); 

        
    }

    void defFaiblesses() override {
        faiblesses["poison"] = 2.0;
        faiblesses["acier"] = 2.0;
    }

    void defResistances() override {
        resistances["combat"] = 0.5;
        resistances["insecte"] = 0.5;
        resistances["tenebres"] = 0.5;
        resistances["dragon"] = 0.0; //fée pas affecté par dragon
    }
};



class Pokemon {
private:
    
    std::string nom;

    std::vector<std::string> types; //vecteur qui prend 1 ou 2 noms de types

    std::unordered_map<std::string, float> faiblesses_Pokemon;
    std::unordered_map<std::string, float> resistances_Pokemon;

    int HP;
    std::string attaque; //pour l'instant que une attaque (on verra si on en fait plus apres)
    std::string TypeAttaque;
    int degats;
    int HPmax; //juste pour faire HP/HPmax sur l'interface (les pv restants quoi)

    int vitesse; //la vitesse du pokemon decide lequel attaque en premier
    bool KO;


public:  
    Pokemon(std::string nom,
        std::vector<std::string> t,
        int HP,
        std::string attaque,
        std::string TypeAttaque,
        int degats,
        int vitesse) : nom(nom), types(t), HP(HP), attaque(attaque),
        TypeAttaque(TypeAttaque) , degats(degats) , vitesse(vitesse) { //debut constructeur

        HPmax = HP;
        KO = false;
        toLowerVect(t);
        toLowerCase(TypeAttaque);
        

        instanceType(t); //on predn le vecteur de string des types et on met les faiblesses du pokemon a jours
        leRoiKai();//ptite fonction qui s'active si on créer kaiminus

    } //fin du constructeur

    void instanceType(std::vector<std::string> t) {
        std::vector<Type*> typePokemon;
        /*
       vecteur de Type qu'on va remplir d'instances des classes TypeTruc
       en fonction des string qu'on a mis en entrée

       on va donc créer des instances de Type en parcourant le vecteur de string
        */



        for (std::string& typeNom : t) {
            toLowerCase(typeNom); //pour eviter de causer des prblms si on oublis les majuscules (pour les accents c'est trop chiant on fait sans)

            if (typeNom == "feu") { typePokemon.push_back(new TypeFeu()); }
            else if (typeNom == "eau") { typePokemon.push_back(new TypeEau()); }
            else if (typeNom == "plante") { typePokemon.push_back(new TypePlante()); }
            else if (typeNom == "electrik") { typePokemon.push_back(new TypeElectrik()); }
            else if (typeNom == "glace") { typePokemon.push_back(new TypeGlace()); }
            else if (typeNom == "combat") { typePokemon.push_back(new TypeCombat()); }
            else if (typeNom == "poison") { typePokemon.push_back(new TypePoison()); }
            else if (typeNom == "sol") { typePokemon.push_back(new TypeSol()); }
            else if (typeNom == "vol") { typePokemon.push_back(new TypeVol()); }
            else if (typeNom == "psy") { typePokemon.push_back(new TypePsy()); }
            else if (typeNom == "insecte") { typePokemon.push_back(new TypeInsecte()); }
            else if (typeNom == "roche") { typePokemon.push_back(new TypeRoche()); }
            else if (typeNom == "spectre") { typePokemon.push_back(new TypeSpectre()); }
            else if (typeNom == "dragon") { typePokemon.push_back(new TypeDragon()); }
            else if (typeNom == "tenebres") { typePokemon.push_back(new TypeTenebres()); }
            else if (typeNom == "acier") { typePokemon.push_back(new TypeAcier()); }
            else if (typeNom == "fee") { typePokemon.push_back(new TypeFee()); }
            else if (typeNom == "normal") { typePokemon.push_back(new TypeNormal()); }

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

      //faut mettre ça dans un setter bordel et mettre les faiblesses en lowercase!! et aussi ya un prblm de range jsp ou
      //les mult sont pas bien mis a jours là ya un soucis de logique

        for (const auto& type : typePokemon) { //on parcours le ou les Types du pokemon
            for (const auto& f : type->getFaiblesses()) {
                if (this->faiblesses_Pokemon.find(f.first) == this->faiblesses_Pokemon.end()) {
                    this->faiblesses_Pokemon[f.first] = 1.0; //on initialise la valeurs du mult
                }
                this->faiblesses_Pokemon[f.first] *= f.second; //mise a jours des faiblesses
            }

            for (const auto& r : type->getResistances()) {
                if (this->resistances_Pokemon.find(r.first) == this->resistances_Pokemon.end()) {
                    this->resistances_Pokemon[r.first] = 1.0; //on initialise la valeurs du mult
                }
                this->resistances_Pokemon[r.first] *= r.second;//mise a j des res
            }
        }

        //on degage les pointeurs

        for (auto instance : typePokemon) {
            delete instance;
        }
        
    }
    
    //les getters

     std::string getNom() const { return nom; }

     int getHP() const { return HP; }
     int getHPmax() const { return HPmax; }
     int getDegats() const { return degats; }
     int getVitesse() { return vitesse; }


     std::unordered_map<std::string, float> getFaiblesses_Pokemon() const {  //on a faillis avoir un gros soucis olalalala, je renomme les fcts pour les diff des methodes de la class type
        return faiblesses_Pokemon;
    }

     std::unordered_map<std::string, float> getResistances_Pokemon() const {
        return resistances_Pokemon;
    }

     bool getKO() { return KO; }

    //les setters
   

     void setDegats(float newDegats) {
        degats = static_cast<int>(std::round(newDegats)); //pour garder les degats en int j'arrondie et je met en int (le mult du maitre est un float ça m'a bien cassé la tete)
    } //c'est pour set les degats infligé par l'attaque c'est pas la methode degats reçus !!

     void setHP(int newHP) {
        HP = newHP;
    }
     void setHPmax(int newHPmax) {
         HPmax = newHPmax;
     }

     void setVitesse(int newVitesse) {
         vitesse = newVitesse;
     }

     void setKO(bool ko) {
         KO = ko;
     }

     void leRoiKai() { //si on a kaiminus
         if (nom == "Kaiminus") {
             int KaiBonus = 5; //bonus de puissance pour le roi Kaiminus

           
             std::cout << "Le roi entre en scène" << std::endl;

             std::cout << nom << " active sa capacité 'Aura du roi'" << std::endl;

             setDegats(degats * KaiBonus);
             setHP(HP * KaiBonus);
             setVitesse(vitesse * KaiBonus);
             setHPmax(HPmax * KaiBonus);
         }
        
    }
    

     void attaquer(Pokemon& cible) { 
        float multiplicateur = 1.0;
        //on regarde les faiblesses et res de la cible
        
        
        if (cible.faiblesses_Pokemon.find(TypeAttaque) != cible.faiblesses_Pokemon.end()) {
                /*faiblesse.find() = faiblesse.end() ça veut dire que find n'a rien trouvé */

                multiplicateur *= cible.faiblesses_Pokemon[TypeAttaque];

            }
        if (cible.resistances_Pokemon.find(TypeAttaque) != cible.resistances_Pokemon.end()) {

                multiplicateur *= cible.resistances_Pokemon[TypeAttaque];

            }

            int degatsFinal = static_cast<int>(degats * multiplicateur); //statit_cast pour mettre en int

            cible.recevoireDegats(degatsFinal); //la cible prend un pied bouche

            if (multiplicateur == 1) {
                std::cout << nom << " attaque " << cible.nom << " avec " << attaque <<"."<< std::endl;

            }
            else if (multiplicateur > 1) {
                std::cout << nom << " attaque " << cible.nom << " avec " << attaque <<". C'est super efficace !" << std::endl;

            }
            else if ((0 < multiplicateur) and (multiplicateur < 1)) {
                std::cout << nom << " attaque " << cible.nom << " avec " << attaque << ". Ce n'est pas très efficace." << std::endl;

            }
            else if (multiplicateur == 0) {
                std::cout << nom << " attaque " << cible.nom << " avec " << attaque << ". L'attaque n'a aucun effet ! (noob)" << std::endl;

            }

            cible.afficherDegats(degatsFinal);
            cible.estKO(); //on verif si la cible est ko et ça met a jours son statut

    
    }


     void recevoireDegats(int degatsReçus) {
        HP -= degatsReçus;
        if (HP < 0) { HP = 0; }
    }

     void afficherDegats(int degatsFinal) {
    std::cout << nom << " reçoit " << degatsFinal << " dégats. Il lui reste " << HP << "/"<<HPmax<<" HP." << std::endl;

    }

     void afficherFaiblesses() {
        std::cout << "Faiblesses de " << nom << " : "<<std::endl;
        for (const auto& f : faiblesses_Pokemon) {
            std::cout << f.first << " : "  << f.second << std::endl;
        }
    }

     void afficherResistances() {
        std::cout << "Resistances de " << nom << " : " << std::endl;

        for (const auto& r : resistances_Pokemon) {
            std::cout << r.first << std::endl;
        }
    }

     bool estKO() { //verif si le Pokemon est KO

         if (getKO()) { return true; } //si il est deja KO
         else if (HP == 0) { //s'il vient d'etre mis KO
             
            setKO(true);
             return true;
         }
         return false;
        
     }
    
     

};

