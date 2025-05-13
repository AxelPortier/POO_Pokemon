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



//ya des soucis, je redef tout les adversaires a chaques fois que jveux combattre
//faut instancier les leaders et le conseil quand je choisis la region mais quand je veux combattre je dois acceder a la liste deja faite
//soultion, quand je choisis combattre, ça met le jeu en etat choix region, instancie les adversaire, ensuite on passe en choix adversaire





class Jeu {
public:

    enum class EtatJeu {

        Accueil, //ecran d'acceuil
        ChoixEquipe,
        ChoixRegion,
        ChoixAdversaireChampions,
        Ligue,
        InteragireLigue,
        Combat,
        Interagire
       
    };

    //peut etre qu'il fut plutot un etat choix region et ensuite dans combat ça choisis auto notre adversaire vu qu'on dit les combattres dans l'ordre


private:
    std::string nomJoueur;
    std::string nomDuJeu;

    EtatJeu etatJeu = EtatJeu::Accueil;

    std::vector< PokemonData> listePokemonDispo; //les infos sur tout les pokemons
    std::vector<std::string> nomsPokemonsChoisie;

    std::vector<Pokemon> EquipePokemon;  //juste pour la fonction choisir equipe graphiquement

    std::vector<Pokemon>* Equipe; //pointeur veers l'equipe du joueurs
    bool EquipeChoisie = false;

    //pour scroller dans le choix des pokemons
    float scrollOffset = 0.0f;
    bool draggingScrollBar = false;
    float scrollStartMouseY = 0;
    float scrollStartOffset = 0;

    bool quitter = false;
    bool aUneEquipe = false;
    int choixRegion = 0; //pour savoir dans quel region on va jouer

    Joueurs* Joueur;
    Entraineurs* Adversaire;
    Maitres* Maitre;

    std::vector<Leaders> listeChampions;
    std::vector<Conseil> listeConseil;
    
    std::string region;//region tu bagarre

    bool ligue = false; //true quand t'auras les 8 badges
    bool maitre = false; //true quand tu bat le co,siel des 4
    



public:

    Jeu(std::string nomDuJeu) : nomDuJeu(nomDuJeu) {
        srand(time(0)); //on initialise le random pour les dialogues 
        listePokemonDispo = ListeCompletePokemon();
        Jouer();
    }
    
    ~Jeu() { //on delete les pointeurs dynamique
        delete Joueur;
        //delete Adversaire;
        delete Maitre;
    }
    
    void ListeAdversaires_Region(std::string region) {
        std::cout << "Chargement des adversaires..." << std::endl;
        listeChampions = ListeChampions(region); //met a jours la liste des leaders
        //std::cout << "on a finis les leaders" << std::endl;
        listeConseil = ListeConseil(region); //la liste du conseil
        //std::cout << "on tente le maitre" << std::endl;

        Maitre = new Maitres( ListeMaitre(region)); //renvoie juste le maitre 'est pas un vector
        std::cout << "Chargement terminée." << std::endl;
    }

    void Jouer() {
        std::cout << nomDuJeu << std::endl;
        std::cout << "Comment vous appelez-vous ?" << std::endl;
        std::cin >> nomJoueur;
       

        std::cout << "Bienvenue " << nomJoueur << std::endl;
        Joueur =  new Joueurs(defJoueur(nomJoueur)); //on le def avec une equipe vide pour commencer, Joueur pointe vers un joueur du coup
        
        Equipe = &Joueur->getEquipePokemon(); //on pointe vers l'equipe (vide pour l'instant)

        while (!quitter) {
            if (Joueur->getBadges().size() == 8 && choixRegion != 0) { //si on a les 8 badges et qu'on a choisis une region
                ligue = true;
                std::cout << "Vous avez obtenu les 8 badges de la region. Vous pouvez désormais affronter la Ligue des Dresseurs de " << region << "." << std::endl;;
            }
            switch (etatJeu) {

                
           

            case EtatJeu::Accueil: {
                SpaceScreen();
                std::cout << *Joueur;
                std::cout << "Selectioner une action : " << std::endl;
                std::cout << "1) Choisir vos Pokemon  |  2) Combattre  |  3) Intéragire avec vos Pokemons  |  4) Quitter" << std::endl;
                int choix;
                std::cin >> choix;
                if (choix == 1) {
                    etatJeu = EtatJeu::ChoixEquipe; //ça fonctionne
                    break;
                }

                else if (choix == 2) {
                    if (aUneEquipe && std::all_of(Joueur->getEquipePokemon().begin(), Joueur->getEquipePokemon().end(), [](const Pokemon& poke) {return poke.getKO();}))
                    {
                        std::cout << "Tes Pokemon ont besoin de soins d'urgence !" << std::endl;
                        continue;
                    }
                    if (aUneEquipe){ 
                        if (!ligue) {
                            etatJeu = EtatJeu::ChoixAdversaireChampions;
                            break;
                        }
                        else {
                            etatJeu = EtatJeu::Ligue;
                            break;

                        }
                        
                    }
                    else {
                        std::cout << "Vous avez besoin d'une Equipe !" << std::endl;
                        continue;
                    }
                  

                }
                else if (choix == 3) {
                    etatJeu = EtatJeu::Interagire;
                    break;

                }
                else if (choix == 4) {
                    std::cout << "Merci d'avoir jouée !" << std::endl;
                    quitter = true;
                    break;
                }
                else { std::cout << "Entrée invalide." << std::endl; continue; }
                break;
            }

            case EtatJeu::ChoixEquipe: {
                ChoisirEquipeGraphiquement();
                Joueur->setEquipe(EquipePokemon); //on met l'equipe temporaire de choix poke graphe dans l'equipe du joueur
                aUneEquipe = true;
                ClearScreen();
                etatJeu = EtatJeu::Accueil;
                break;
            }

                                     //pour charger les adversaires
            case EtatJeu::ChoixRegion: { 
                switch (choixRegion) {
                case 0: {
                    std::cout << "Quelle region voulez-vous conquérire ?" << std::endl;
                    std::cout << "1) Kanto | 2) Johto | 3) Hoenn | 4) Sinnoh " << std::endl;
                    std::cin >> choixRegion;
                    break;
                }
                case 1: {
                    region = "Kanto";
                    ListeAdversaires_Region("Kanto"); //instancie les adversaire de kanto
                    etatJeu = EtatJeu::ChoixAdversaireChampions;

                    break;
                }
                case 2: {
                    region = "Johto";
                    ListeAdversaires_Region("Johto");
                    etatJeu = EtatJeu::ChoixAdversaireChampions;

                    break;

                }
                case 3: {
                    region = "Hoenn";
                    ListeAdversaires_Region("Hoenn");
                    etatJeu = EtatJeu::ChoixAdversaireChampions;

                    break;

                }
                case 4: {
                    region = "Sinnoh";
                    ListeAdversaires_Region("Sinnoh");
                    etatJeu = EtatJeu::ChoixAdversaireChampions;

                    break;

                }
             
                break;//sors du switch choix region
                }
                break;//sors du switch choix region
            }
            case EtatJeu::ChoixAdversaireChampions:
            {
                if (choixRegion == 0) {

                    etatJeu = EtatJeu::ChoixRegion; //on a pas encore choisis la region donc on part vers ChoixRegion
                }
                
                else {
                    if (nomJoueur == "moi") { //cheat code pour aller a la ligue direct
                        ligue = true;
                        //maitre = true;
                        etatJeu = EtatJeu::Ligue;
                    }
                    //affiche les adversaires qui sont deja instancié normalement
                    while (etatJeu == EtatJeu::ChoixAdversaireChampions) {
                        SpaceScreen();
;                        std::cout << "0) Retour au Menu \n" << std::endl;

                        std::cout << "Qui voulez-vous affronter ? \n" << std::endl;

                        int i = 1;
                        for (const auto& champ : listeChampions) {
                            std::cout << i << ") " << champ << std::endl;
                            ++i;
                        }


                        int choixAdv = 10;
                        std::cin >> choixAdv;
                        if (choixAdv > 0 && choixAdv <= listeChampions.size()) {
                            ClearScreen();
                            
                            std::cout << "Vous entrez dans l'arène de " << listeChampions[choixAdv - 1].getGymnase() << " du champion " << listeChampions[choixAdv - 1].getNom() << std::endl;
                            Adversaire = &listeChampions[choixAdv - 1]; //on fait pointer adversaire vers celui qu'on affronte
                            if (Adversaire->getVaincu()) { Adversaire->setVaincu(false); }
                            etatJeu = EtatJeu::Combat;

                            break;
                        }
                        else if (choixAdv == 0) {
                            etatJeu = EtatJeu::Accueil;
                            break;
                        }


                        else {
                            std::cout << "Entrée invalide." << std::endl;
                            continue;
                        }

                    }
                }

           
                break;//sors de choixAdversaire
            }
            case EtatJeu::Ligue: {
                SpaceScreen();
                std::cout << "Vous entrez dans la Ligue de " << region << std::endl;
                while (etatJeu == EtatJeu::Ligue) {
                    

                    std::cout << "Vous sentez vous près à relever le défis du Conseil ? \n" << std::endl;
                    std::cout << "1) Oui  |  2) Non" << std::endl;
                    int choix;
                    std::cin >> choix;
                    if (choix == 2) {
                        etatJeu = EtatJeu::Accueil;
                        break;

                    }
                    else if (choix != 1) { std::cout << "Entrée Invalide." << std::endl; continue; }
                    else if (choix == 1) {
                        std::vector<bool> Porte = { true , true , true , true }; //si les portes sont ouvertes

                        
                        //affronter le conseil
                        while ((!maitre) && (etatJeu == EtatJeu::Ligue)) {
                            if (!Porte[0] && !Porte[1] && !Porte[2] && !Porte[3]) {
                                maitre = true;
                                break;
                            }
                            std::cout << "Vous avez devant vous 4 portes \n" << std::endl;
                            int porte;
                            
                            
                            std::cout << "|   Porte 1   |   Porte 2   |   Porte 3   |   Porte 4   |" << std::endl;
                            std::cout << "Emprunter la porte : ";
                            std::cin >> porte;

                            if (porte < 1 || porte > 4) { std::cout << "Entrée Invalide." << std::endl; SpaceScreen(); continue; }
                            else if (!Porte[porte - 1]) { std::cout << "La porte est fermé, on dirait que " << listeConseil[porte - 1].getNom() << " ne veux pas vous revoir" << std::endl; continue; }
                            else if ((porte >= 1 || porte <=4 ) && Porte[porte-1] == true) {
                                std::cout << "Vous passez la porte " << porte <<". \n" << listeConseil[porte - 1].getNom() << " vous attend." << std::endl;
                               
                                std::cout << "Que voulez-vous faire ?" << std::endl;
                                std::cout << "1) Interagire avec vos Pokemon  |  2) Combattre" << std::endl;

                                int action;
                                std::cin >> action;
                                switch(action) //si 1 on soigen d'abord puis combat si 2 on combat direct
                                {
                                case 1: {
                                        while (true) {
                                            SpaceScreen();

                                            std::cout << "Votre Equipe \n" << std::endl;

                                            int i = 1;

                                            for (const auto& poke : *Equipe) { //bah oui on boucle sur l'equipe donc ce que pointe Equipe pas sur Equipe c'est un pointeur gros beta
                                                std::cout << i << ") " << poke << std::endl;
                                                ++i;
                                            }

                                            SpaceScreen();

                                            std::cout << "Que voulez-vous faire ?" << std::endl;
                                            std::cout << "0) Retour " << std::endl;
                                            std::cout << "1) Soigner l'équipe" << std::endl;

                                            int choix;
                                            std::cin >> choix;
                                            if (choix == 1) {
                                                for (auto& poke : *Equipe) {
                                                    poke.setHP(poke.getHPmax()); //on soigne le poke

                                                    poke.setKO(false);
                                                }
                                                std::cout << "Vos Pokemon sont en pleine forme !" << std::endl;
                                                SpaceScreen();

                                                continue;
                                            }
                                            else if (choix == 0) { break; }

                                            else { std::cout << "Entrée invalide." << std::endl; continue; }


                                        }
                                    }
                                case 2:
                                    {
                                        Adversaire = &listeConseil[porte - 1];
                                        std::cout << *Adversaire << std::endl;

                                        Combat combat(*Joueur, *Adversaire);
                                        if (Adversaire->getVaincu()) {
                                            std::cout << "Vous sortez de la chambre de " << listeConseil[porte - 1].getNom() << ". La porte se ferme derriere vous." << std::endl;
                                            Porte[porte - 1] = false; //on ferme la porte
                                            continue;
                                        }
                                        else {
                                            std::cout << "Vous avez échoué. Revenez quand vous serez à la hauteur." << std::endl;
                                            for (auto& conseil : listeConseil) {

                                                for (auto& poke : conseil.getEquipePokemon()) {
                                                    poke.setHP(poke.getHPmax()); //on soigne les poke du conseil
                                                    poke.setKO(false);

                                                }
                                                conseil.setVaincu(false);
                                            }
                                            etatJeu = EtatJeu::Accueil;
                                            break;
                                        }
                                    }
                                }


                            }
                            else { std::cout << "Entrée Invalide." << std::endl; continue; }
                        }
                        if (maitre)
                        {
                            std::cout << "Vous avez réussi l'épreuve du conseil, un escalier apparait devant vous, un sentiment d'effroi vous traverse. \n Voulez-vous emprunter cet escalier ? \n 1) Oui  |  2) Non" << std::endl;
                            int esc;
                            std::cin >> esc;
                            if (esc == 2) {
                                std::cout << Maitre->getNom() << " : Ne t'inquiete pas ça vas bien se passer, viens" << std::endl;
                            }
                            std::cout << "Vous prenez l'escalier et entrez dans une salle obscure et vide" << std::endl;
                            std::cout << Maitre->getNom() << " : Je t'attendais " << Joueur->getNom() << "." << std::endl;
                            SpaceScreen();
                            std::cout << "Que voulez-vous faire ?" << std::endl;
                            std::cout << "1) Interagire avec vos Pokemon  |  2) Combattre" << std::endl;
                            int action;
                            std::cin >> action;
                            switch(action)
                            {
                            case 1: {
                                    while (true) {
                                        SpaceScreen();

                                        std::cout << "Votre Equipe \n" << std::endl;

                                        int i = 1;

                                        for (const auto& poke : *Equipe) { //bah oui on boucle sur l'equipe donc ce que pointe Equipe pas sur Equipe c'est un pointeur gros beta
                                            std::cout << i << ") " << poke << std::endl;
                                            ++i;
                                        }

                                        SpaceScreen();

                                        std::cout << "Que voulez-vous faire ?" << std::endl;
                                        std::cout << "0) Retour " << std::endl;
                                        std::cout << "1) Soigner l'équipe" << std::endl;

                                        int choix;
                                        std::cin >> choix;
                                        if (choix == 1) {
                                            for (auto& poke : *Equipe) {
                                                poke.setHP(poke.getHPmax()); //on soigne le poke

                                                poke.setKO(false);
                                            }
                                            std::cout << "Vos Pokemon sont en pleine forme !" << std::endl;
                                            SpaceScreen();

                                            continue;
                                        }
                                        else if (choix == 0) { break; }

                                        else { std::cout << "Entrée invalide." << std::endl; continue; }


                                    }
                                }
                            case 2:
                                {
                                std::cout << "Vous approchez du Maitre" << std::endl;
                                    
                                    std::cout << *Maitre << std::endl;
                                    Combat combat(*Joueur, *Maitre);
                                    if (!Maitre->getVaincu()) {
                                        std::cout << "Vous avez échoué. Revenez quand vous serez à la hauteur." << std::endl;
                                        for (auto& conseil : listeConseil) {

                                            for (auto& poke : conseil.getEquipePokemon()) {
                                                poke.setHP(poke.getHPmax()); //on soigne les poke du conseil
                                                poke.setKO(false);

                                            }
                                            conseil.setVaincu(false);
                                        }
                                        for (auto& poke : Maitre->getEquipePokemon()) {
                                            poke.setHP(poke.getHPmax()); //on soigne les poke du conseil
                                            poke.setKO(false);

                                        }
                                        Maitre->setVaincu(false); //sers a rien mais jle laisse quand meme

                                        etatJeu = EtatJeu::Accueil;
                                        break;
                                    }
                                    else {
                                        std::cout << Maitre->getNom() << " : suis moi " << Joueur->getNom() << ". Tu fais desormais partis de l'elite des dresseurs de " << region << ".\nC'est avec un immense honneur que je t'acompagne pour inscrire ton nom au Pantheon des Dresseurs !" << std::endl;
                                        std::cout << "Veuillez entrer le nom que vous souhaitez graver dans l'histoire." << std::endl;
                                        std::string pantheon;
                                        std::cin >> pantheon;
                                        std::cout << "Pantheon des Dresseurs \nMaitre Dresseurs de " << region << " : " << pantheon << std::endl;
                                        std::cout << "Equipe Pokemon :\n";
                                        for (auto& poke : Joueur->getEquipePokemon()) { std::cout << poke.getNom() << "\n"; }
                                        while (true)
                                        {
                                            std::cout << "Appuyez sur 0 pour revenir au Menu" << std::endl;
                                            int menu;
                                            std::cin >> menu;
                                            if (menu == 0) { choixRegion = 0;Joueur->clearBadge() ;ligue = false; maitre = false; etatJeu = EtatJeu::Accueil; break; } //choix region 0 pour pouvoir recommencer le jeu avec la region qu'on veut
                                            else { std::cout << "Entrée invalide." << std::endl; continue; }
                                        }
                                    }
                                }
                            }
                        }


                    }
                    else std::cout << "Entrée Invalide." << std::endl; continue;
                   
                   


                }
                break;//sors de ligue
            }

            case EtatJeu::Combat:
            {

                Combat combat(*Joueur, *Adversaire);
                etatJeu = EtatJeu::Accueil;
                SpaceScreen();
                break; //sors de combat
            }

            case EtatJeu::Interagire: {
                if (!aUneEquipe) {
                    std::cout << "Vous n'avez pas encore de Pokemon !" << std::endl;
                    etatJeu = EtatJeu::Accueil;
                    break;
                }
                while (etatJeu == EtatJeu::Interagire) {
                    SpaceScreen();

                    std::cout << "Votre Equipe \n" << std::endl;

                    int i = 1;

                    for (const auto& poke : *Equipe) { //bah oui on boucle sur l'equipe donc ce que pointe Equipe pas sur Equipe c'est un pointeur gros beta
                        std::cout << i << ") " << poke << std::endl;
                        ++i;
                    }

                    SpaceScreen();

                    std::cout << "Que voulez-vous faire ?" << std::endl;
                    std::cout << "0) Menu" << std::endl;
                    std::cout << "1) Soigner l'équipe" << std::endl;
                    for (int j = 0; j < Joueur->getEquipePokemon().size(); ++j) {
                        std::cout << j+2 << ") Sortir " << Joueur->getEquipePokemon()[j].getNom() << " de sa pokeball" << std::endl;
                    }
                    int choix;
                    std::cin >> choix;
                    if (choix == 1) {
                        for (auto& poke : *Equipe) {
                            poke.setHP(poke.getHPmax()); //on soigne le poke

                            poke.setKO(false);
                        }
                        std::cout << "Vos Pokemon sont en pleine forme !" << std::endl;
                        SpaceScreen();

                        continue;
                    }
                    else if (choix == 0) {
                        etatJeu = EtatJeu::Accueil;
                        break;
                    }
                    else if (choix > 1 || choix < Joueur->getEquipePokemon().size()+1) {
                        std::cout << "vous sortez " << Joueur->getEquipePokemon()[choix - 2].getNom() << " de sa pokeball, il gambade à vos cotés puis retourne dans sa boite." << std::endl;
                        SpaceScreen();

                        continue;
                    }
                    else { std::cout << "Entrée invalide." << std::endl; continue; }

                
                    }
                    etatJeu = EtatJeu::Accueil;
                    break; //sors de Interagire
                }
            

                break; //break final du switch etat jeu

            }//fin du switch etatjeu
                
        }//fin de while !quitter


        

    }//fin de joueur()


  


    
    //affiche l'équipe et te demande si tu veux leurs parler ou les soigner ou changer l'ordre

    void InteragireDresseur() {

    }

    void ChoisirEquipeGraphiquement() {
        InitWindow(1000, 600, "Choix de l'équipe");
        SetTargetFPS(60);

        std::string recherche = "";
        bool searchBoxActive = false;
        Rectangle searchBox = { 100, 60, 400, 30 };

        

        while (!WindowShouldClose() && etatJeu == EtatJeu::ChoixEquipe) {
            BeginDrawing();
            ClearBackground(RAYWHITE);


            //barre de recherche
            DrawRectangleRec(searchBox, LIGHTGRAY);
            DrawText(("Recherche : " + recherche).c_str(), searchBox.x + 5, searchBox.y + 5, 20, BLACK);

            // Clic dans la zone de recherche
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                searchBoxActive = CheckCollisionPointRec(GetMousePosition(), searchBox);
            }

            // Saisie clavier dans la barre de recherche
            if (searchBoxActive) {
                int key = GetCharPressed();
                while (key > 0) {
                    if (key >= 32 && key <= 125) {  // caractères imprimables
                        recherche += (char)key;
                    }
                    key = GetCharPressed();
                }

                if (IsKeyPressed(KEY_BACKSPACE) && !recherche.empty()) {
                    recherche.pop_back();
                }
            }


         

                DrawText("Choisissez votre équipe (1 à 6 Pokémon)", 100, 20, 20, BLACK);

                Vector2 mouse = GetMousePosition();
                const int visibleHeight = 440; // Espace visible entre 60 et 500
                const int totalHeight = listePokemonDispo.size() * 50;
                const int yMin = 100;

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
                // Filtrage en fonction de la recherche
                std::vector<PokemonData> pokemonsFiltres;
                for (const auto& p : listePokemonDispo) {
                    if (recherche.empty() || p.nom.find(recherche) != std::string::npos) {
                        pokemonsFiltres.push_back(p);
                    }
                }

                int y = yMin - (int)scrollOffset;
                for (int i = 0; i < pokemonsFiltres.size(); i++) {
                    const PokemonData& p = pokemonsFiltres[i];

                    Rectangle zone = { 100, static_cast<float>(y), 600, 40 };

                    if (zone.y + zone.height > yMin && zone.y < 500) {
                        DrawRectangleRec(zone, LIGHTGRAY);

                        std::string ligne = p.nom + " - " + p.type1 +
                            (p.type2 != "" ? "/" + p.type2 : "") +
                            " - PV: " + std::to_string(p.pv);
                        DrawText(ligne.c_str(), 110, y + 10, 20, BLACK);

                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, zone)) {
                            if (nomsPokemonsChoisie.size() < 6) {
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

            

            EndDrawing();
        }

        CloseWindow();
    }






};


int main() {

    Jeu zepartis("Pokemon - Le Retour de Axel le Maudit");
    //Joueurs vico = defJoueur("vico", { "Kaiminus" });
    //Maitres Cynthia = defMaitres("Cynthia", "Sinnoh");
  //  Combat combat(vico, Cynthia);

    return 0;



}


