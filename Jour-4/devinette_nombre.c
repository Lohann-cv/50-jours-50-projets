// IMPORTANT etant donné que c'est un de mes premiers projet en C, le code est sur-commanter 
//import des bibliothéque, printf/scanf, rand/srand, et pour générer des nb aléatoire (à l'aide de l'heure)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// fonction principal
int main() {
    int nombreSecret;
    int tentatives = 0;
    int proposition;
    int trouve = 0;
    int jouerEncore;
    
    //permet de générer des nb aléatoir avec l'heure actuel
    srand(time(NULL));
    
    do {
        // la variable ppour le nombre de tentative et la variable trouve qui permet le temps qu'elle n'est pas vrai (differante de 0) de continuer la bouvle de jeu
        // elles sont remise à 0 si le joueur veut recommancer
        tentatives = 0;
        trouve = 0;
        
        // rand génére un numbre aléatoir puis on prend son reste de /100 et on lui rajoute 1 pour qu"il soit bien entre 1 et 100
        nombreSecret = rand() % 100 + 1;
        
        printf("\n========================================\n");
        printf("   JEU DE DEVINETTE - Trouvez le nombre !\n");
        printf("========================================\n");
        printf("Moi le golème malicieux ai choisi un nombre entre 1 et 100.\n");
        printf("Pouvez-vous le deviner ?\n\n");
        
        //Boucle de jeux
        while (!trouve) {
            printf("Tentative #%d - Entrez votre proposition : ", tentatives + 1); // #%d montre que 'lon attend un nombre entier
            
            // vérification de la saisie (si elle n'est pas décimal) si elle est non décimal le retour sera differant de 1 (0 donc false) et il y aura un message d'erreur
            if (scanf("%d", &proposition) != 1) {    //IMPORTANT le '&' permet de '''rendre modifiable''' une variable via scanf (commande input)
                printf("Erreur : veuillez entrer un nombre valide !\n");
                while(getchar() != '\n'); // Vider le buffer, la mémoir tampon. getchar() scan et supprime des caractère tant qu'il n'arrive pas à la fin de la ligne (\n)
                continue;
            }
            
            tentatives++; //incrementation similaire à python
            
            // Autre verification d'erreur (|| veut dire or)
            if (proposition < 1 || proposition > 100) {
                printf("Le nombre doit être entre 1 et 100 !\n\n");
                continue;
            }
            if (proposition < nombreSecret) {
                int difference = nombreSecret - proposition;
                printf("Trop petit ! ");
                if (difference > 20) {
                    printf("Vous êtes loin !\n\n");
                } else {
                    printf("Vous chauffez!\n\n");
                }
            } else if (proposition > nombreSecret) {
                int difference = proposition - nombreSecret;
                printf("Trop grand ! ");
                if (difference > 20) {
                    printf("Vous êtes loin !\n\n");
                } else {
                    printf("Vous chauffez !\n\n");
                }
            } else {
                printf("\nBRAVO ! Vous avez trouvé le nombre %d !\n", nombreSecret);
                printf("Nombre de tentatives : %d\n", tentatives);
                
                // Message selon la performance
                if (tentatives <= 5) {
                    printf("Moins de 5 tentatives ! Excellent ! Vous êtes un expert !\n");
                } else if (tentatives <= 10) {
                    printf("Moins de 10 tentatives un score honorable !\n");
                } else {
                    printf("Bravo ! Il y a de la place pour de l'amélioration, vous pouvez faire encore mieux !!\n");
                }
                
                trouve = 1;
                //la boucle if / else if / else est très semlable (voir identique) à du python ou javascript donc aucune difficulté ici
            }
        }
        
        // replay ?
        printf("\nVoulez-vous rejouer ? (1 = Oui, 0 = Non) : ");
        scanf("%d", &jouerEncore);
        
    } while (jouerEncore == 1);
    
    printf("\n👋 Merci d'avoir joué ! À bientôt !\n");
    
    return 0;
}