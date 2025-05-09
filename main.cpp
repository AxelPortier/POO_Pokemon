/*
Bienvenu sur le code du Projet Pokemon de Pitigliano Victor et Portier Axel 
note importante, nous avons réussis à surcharger les opérateurs tard dans le projet donc certaines fonctions sont inutiles, si elles sont encore présentes dasn le code final 
c'est un simple oublis

*/





#include "raylib.h"




#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <algorithm> // pour std::clamp

//#include <Windows.h> je tej parce que ca rentre en conflit avec raylib
#include <unordered_map>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour time()

#include "Pokemon.h"
#include "Entraineurs.h"
#include "Données.h"
#include "Combat.h"


//donner aux pokemons 4 attaques de bases et les overrides avec les dresseurs pour les adapter, comme ça je peux
//instancier des pokemons sans ecrire toutes leurs attaques a la main et en meme temps les 
//leaders et autres ont leurs attaques fetiches

//relire tout le code et verif les liens entre les fonctions, si les & et * sont bien utilisés.


//la class qui va gérer les diffs aspects du jeu, les combats, choisir adversaire et equipe pokemon, interagir, voir qui on a battu et nos badges
//faut tout faire avec raylib dès le debut et comme ça j'apprend a l'utiliser sur un truc simple et je ferais le combat apres
class Jeu {
public:

    enum class EtatJeu {
        Accueil, //ecran d'acceuil
        ChoixEquipe, 
        ChoixAdversaire,
        Combat,
        Interagire,
    };


private:
    EtatJeu etatJeu = EtatJeu::Accueil;

    std::vector< PokemonData> listePokemonDispo; //les infos sur tout les pokemons
    std::vector<std::string> nomsPokemonsChoisie;

    std::vector<Pokemon> EquipePokemon;

    bool EquipeChoisie = false;

    //pour scroller dans le choix des pokemons
    float scrollOffset = 0.0f;
    bool draggingScrollBar = false;
    float scrollStartMouseY = 0;
    float scrollStartOffset = 0;


public:

    Jeu() {
        srand(time(0)); //on initialise le random pour les dialogues 
        listePokemonDispo = ListeCompletePokemon();

        Jouer();
    }

    void Jouer() {
        const int screenWidth = 1000;
        const int screenHeight = 600;
        InitWindow(screenWidth, screenHeight, "Combat Pokémon");
        SetTargetFPS(60);
//je met tout dans le while pour l'instant mais je vais séparer en diff fonction comme ça ya que des appels de fonctions dans la bu=oucle


        while (!WindowShouldClose()) {


            BeginDrawing();
            ClearBackground(RAYWHITE);
            Rectangle boutonAccueil = { 10, 10, 100, 30 };
            Vector2 mouse = GetMousePosition(); //lon prend la position de la souris

            if (etatJeu != EtatJeu::Accueil) {
                DrawRectangleRec(boutonAccueil, LIGHTGRAY);
                DrawText("Accueil", boutonAccueil.x + 10, boutonAccueil.y + 8, 18, BLACK);

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, boutonAccueil)) {
                    etatJeu = EtatJeu::Accueil;
                }
            }

            switch (etatJeu) {
                
            case EtatJeu::Accueil:{
                DrawText("Pokemon - Le Retour de Axel le maudis", 120, 50, 30, BLACK);

                //on def les boutons

                Rectangle boutonEquipe = { 50, 150, 200, 50 };  
                Rectangle boutonCombat = { 50, 230, 200, 50 };
                Rectangle boutonQuitter = { 50, 310, 200, 50 };

                //on les dessines


                DrawRectangleRec(boutonEquipe, LIGHTGRAY);
                DrawRectangleRec(boutonCombat, LIGHTGRAY);
                DrawRectangleRec(boutonQuitter, LIGHTGRAY);

                DrawText("Choisir équipe", boutonEquipe.x + 20, boutonEquipe.y + 15, 20, BLACK);
                DrawText("Combattre", boutonCombat.x + 40, boutonCombat.y + 15, 20, BLACK);
                DrawText("Quitter", boutonQuitter.x + 60, boutonQuitter.y + 15, 20, BLACK);

                // Position et dimensions
                int equipeX = 500; // Position X à droite
                int equipeY = 150; // Position Y du premier Pokémon
                int pokemonHeight = 50; // Hauteur de chaque case
                int caseWidth = 200;
                int caseHeight = 40;

                // Titre "Equipe Pokémon"
                DrawText("Equipe Pokémon :", equipeX, equipeY - 40, 20, BLACK);

                // Affiche toujours 6 cases, même si certaines sont vides
                for (int i = 0; i < 6; i++) {
                    Rectangle zonePokemon = { equipeX, equipeY + i * pokemonHeight, (float)caseWidth, (float)caseHeight };

                    if (i < nomsPokemonsChoisie.size()) {
                        // Case remplie : Pokémon sélectionné
                        DrawRectangleRec(zonePokemon, GREEN);
                        DrawText(nomsPokemonsChoisie[i].c_str(), equipeX + 10, equipeY + i * pokemonHeight + 10, 20, BLACK);
                    }
                    else {
                        // Case vide : rectangle gris clair
                        DrawRectangleRec(zonePokemon, LIGHTGRAY);
                    }
                }


                //on regarde où la souris pointe quand on clique et on attribut un etat a ce clique
                
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (CheckCollisionPointRec(mouse, boutonEquipe)) {
                        etatJeu = EtatJeu::ChoixEquipe;
                    }
                    else if (CheckCollisionPointRec(mouse, boutonCombat)) {
                        etatJeu = EtatJeu::Combat;
                    }
                    else if (CheckCollisionPointRec(mouse, boutonQuitter)) {
                        CloseWindow();
                        return;
                    }
                }

                break;
                }

          

            case EtatJeu::ChoixEquipe:{

                DrawText("Choisissez votre équipe (1 à 6 Pokémon)", 100, 20, 20, BLACK);

                Vector2 mouse = GetMousePosition();
                const int visibleHeight = 440; // Espace visible entre 60 et 500
                const int totalHeight = listePokemonDispo.size() * 50;
                const int yMin = 60;

                // Scrollbar dimensions
                Rectangle scrollBarArea = { 720, yMin, 20, (float)visibleHeight };
                float scrollThumbHeight = std::max((float)visibleHeight * visibleHeight / totalHeight, 30.0f);
                float maxScrollOffset = std::max(0.0f, static_cast<float>(totalHeight - visibleHeight));
                float scrollThumbY = yMin;
                if (maxScrollOffset > 0.0f) {
                    scrollThumbY = yMin + (scrollOffset / maxScrollOffset) * (visibleHeight - scrollThumbHeight);
                }
                Rectangle scrollThumb = { scrollBarArea.x, scrollThumbY, scrollBarArea.width, scrollThumbHeight };

                // Gestion du glisser de la barre
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, scrollThumb)) {
                    draggingScrollBar = true;
                    scrollStartMouseY = mouse.y;
                    scrollStartOffset = scrollOffset;
                }

                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && draggingScrollBar) {
                    float delta = mouse.y - scrollStartMouseY;

                    if (maxScrollOffset > 0.0f && (visibleHeight - scrollThumbHeight) > 0.0f) {
                        float ratio = delta / (visibleHeight - scrollThumbHeight);
                        scrollOffset = scrollStartOffset + ratio * maxScrollOffset;

                        // Remplace std::clamp par un contrôle manuel
                        if (scrollOffset < 0.0f) {
                            scrollOffset = 0.0f;
                        }
                        else if (scrollOffset > maxScrollOffset) {
                            scrollOffset = maxScrollOffset;
                        }
                    }
                }


                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                    draggingScrollBar = false;
                }

                // Affichage de la liste avec scroll
                int y = yMin - (int)scrollOffset;
                for (int i = 0; i < listePokemonDispo.size(); i++) {
                    const PokemonData& p = listePokemonDispo[i];
                    Rectangle zone = { 100, static_cast<float>(y), 600, 40 };

                    if (zone.y + zone.height > yMin && zone.y < 500) {
                        DrawRectangleRec(zone, LIGHTGRAY);

                        std::string ligne = p.nom + " - " + p.type1 +
                            (p.type2 != "" ? "/" + p.type2 : "") +
                            " - PV: " + std::to_string(p.pv);
                        DrawText(ligne.c_str(), 110, y + 10, 20, BLACK);

                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, zone)) {
                            if (nomsPokemonsChoisie.size() < 6 ) {
                                nomsPokemonsChoisie.push_back(p.nom);
                            }
                        }
                    }

                    y += 50;
                }
                // Affichage des Pokémon sélectionnés à droite
                const int xEquipe = 780;  // Position des Pokémon sélectionnés à droite
                DrawText("Équipe choisie:", xEquipe, 20, 20, BLACK);
                int yEquipe = 60;

                for (int i = 0; i < nomsPokemonsChoisie.size(); i++) {
                    const std::string& nom = nomsPokemonsChoisie[i];
                    Rectangle zoneEquipe = { xEquipe, (float)yEquipe, 200, 40 };
                    DrawRectangleRec(zoneEquipe, LIME);  // Utilise LIME ou autre couleur
                    DrawText(nom.c_str(), xEquipe + 10, yEquipe + 10, 20, BLACK);

                    // Ajouter bouton de suppression
                    Rectangle boutonSupprimer = { xEquipe + 160, (float)yEquipe + 10, 30, 30 };
                    DrawRectangleRec(boutonSupprimer, RED);
                    DrawText("X", boutonSupprimer.x + 10, boutonSupprimer.y + 5, 20, WHITE);

                    // Supprimer un Pokémon de l'équipe
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, boutonSupprimer)) {
                        nomsPokemonsChoisie.erase(nomsPokemonsChoisie.begin() + i);
                    }

                    yEquipe += 50;
                }

                DrawText(("Sélectionnés : " + std::to_string(nomsPokemonsChoisie.size()) + " / 6").c_str(), 100, 510, 20, DARKGREEN);

                // Bouton de validation
                Rectangle boutonSuivant = { 600, 540, 150, 40 };
                DrawRectangleRec(boutonSuivant, SKYBLUE);
                DrawText("Valider équipe", boutonSuivant.x + 10, boutonSuivant.y + 10, 20, BLACK);

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, boutonSuivant)
                    && nomsPokemonsChoisie.size() > 0) {

                    EquipePokemon.clear();
                    for (const auto& nom : nomsPokemonsChoisie) {
                        EquipePokemon.push_back(InstancePokemon(nom));
                    }

                    etatJeu = EtatJeu::Accueil;
                }

                // Affiche la scrollbar
                DrawRectangleRec(scrollBarArea, GRAY);
                DrawRectangleRec(scrollThumb, DARKGRAY);

                break;


               
            }

            case EtatJeu::Combat:
            {
                DrawText("Écran de combat (à coder)", 100, 100, 20, DARKGRAY);
                break;
            }

            default:
                break;
            }


            


            EndDrawing();
        } // fin du whilde

        CloseWindow();
    }//fin de joueur()

    void CreationEquipe() {

    }

    void ChoixAdversaire() {

    }

    void Bagarre() {
    
    }

    void InteragirePokemon() {

    }

    void InteragireDresseur() {

    }





};









//Leaders Ondine = defLeaders("Ondine");

//on est ibkigé de faire la boucle whilde de raylib parce qu'on est censé pouoir faire plusieurs combat
//suffis juste de renvoyer les infos de la boucle de combat a raylib!!!!! pas besoin de se casser les couilles, raylib affiche juste les infos de la logique
// 
// 
// Pokemon Strassie = InstancePokemon("Strassie");

//on est censé 

int main() {

    

   

    Joueurs Victor = defJoueur("Victor", { "Mia" , "Marius" , "Kaiminus" }); 
    Leaders Pierre = defLeaders("Pierre");

    //std::cout << Victor << std::endl;

    //Combat combat(Victor, Pierre);

    Jeu zepartis;

 
    return 0;

    

}


