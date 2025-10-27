// import biblio I/O et manipulation de caractère 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
// Déclaration de constante (celon moi c'est un peut comme les variable const de javascript, elle ne sont pas iterable)
#define MAX_CONTACTS 100
#define MAX_NOM 50
#define MAX_TELEPHONE 20
#define MAX_EMAIL 50

//Une structure resemble un peu à une classe en python, on crée un type avec des caractèristique donné
// La structure d'un contacte donc avec un nom tel et email (par exemple le nom ne peut pas faire plus de 100 caractère)
struct Contact {
    char nom[MAX_NOM];
    char telephone[MAX_TELEPHONE];
    char email[MAX_EMAIL];
};

//fonction pour mettre les caractère en minuscule (comme .lower en python sauf qu'ici on doit lui donné la logique)
//la fonction scan chaque caractère et lui applique la fonction toLower puis l'incremente dans le tableau result
//on utilise void car c'est une fonction procedure (elle ne se renvois rien à elle meme)
void toLower(char *str, char *result) {
    int i = 0;
    while (str[i]) {
        result[i] = tolower(str[i]);
        i++;
    }
    result[i] = '\0';
}

// Fonction pour nettoyer le buffer d'entré
void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); //EOF : endOfFile
}

void ajouterContact(struct Contact contacts[], int *nombreContacts) {
    if (*nombreContacts >= MAX_CONTACTS) {
        printf("Erreur : La liste de contacts est pleine !\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("     AJOUTER UN NOUVEAU CONTACT\n");
    printf("========================================\n");
    
    viderBuffer();
    
    printf("Nom complet : ");
    fgets(contacts[*nombreContacts].nom, MAX_NOM, stdin);
    contacts[*nombreContacts].nom[strcspn(contacts[*nombreContacts].nom, "\n")] = 0;
    
    // Vérifier que le nom n'est pas vide
    if (strlen(contacts[*nombreContacts].nom) == 0) {
        printf("Le nom ne peut pas être vide...\n");
        return;
    }
    
    printf("Téléphone : ");
    fgets(contacts[*nombreContacts].telephone, MAX_TELEPHONE, stdin); //comme scanf mais pour une ligne entière (c'est mieux dans ce cas présant)
    contacts[*nombreContacts].telephone[strcspn(contacts[*nombreContacts].telephone, "\n")] = 0;
    
    printf("Email : ");
    fgets(contacts[*nombreContacts].email, MAX_EMAIL, stdin);
    contacts[*nombreContacts].email[strcspn(contacts[*nombreContacts].email, "\n")] = 0;
    
    (*nombreContacts)++;
    
    printf("\nContact ajouté avec succès ! Vive les contacts !\n");
    printf("Total de contacts : %d/%d\n", *nombreContacts, MAX_CONTACTS);
}

void afficherContacts(struct Contact contacts[], int nombreContacts) {
    if (nombreContacts == 0) {
        printf("\nAucun contact enregistré.\n");
        printf("Utilisez l'option 1 pour ajouter votre premier contact.\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("      LISTE DES CONTACTS (%d)\n", nombreContacts);
    printf("========================================\n");
    
    for (int i = 0; i < nombreContacts; i++) {
        printf("\nContact #%d\n", i + 1);
        printf("┌────────────────────────────────────┐\n");
        printf("│ Nom       : %-22s │\n", contacts[i].nom);
        printf("│ Téléphone : %-22s │\n", contacts[i].telephone);
        printf("│ Email     : %-22s │\n", contacts[i].email);
        printf("└────────────────────────────────────┘\n");
    }
    
    printf("\nTotal : %d contact(s)\n", nombreContacts);
}

void rechercherContact(struct Contact contacts[], int nombreContacts) {
    if (nombreContacts == 0) {
        printf("\nAucun contact à rechercher.\n");
        return;
    }
    
    char recherche[MAX_NOM];
    char rechercheLower[MAX_NOM];
    char nomLower[MAX_NOM];
    int trouve = 0;
    
    printf("\n========================================\n");
    printf("        RECHERCHER UN CONTACT\n");
    printf("========================================\n");
    printf("Entrez le nom à rechercher : ");
    
    viderBuffer();
    fgets(recherche, MAX_NOM, stdin);
    recherche[strcspn(recherche, "\n")] = 0;
    
    // Convertir la recherche en minuscules
    toLower(recherche, rechercheLower);
    
    printf("\n  Résultat pour \"%s\" :\n", recherche);
    printf("========================================\n");
    
    for (int i = 0; i < nombreContacts; i++) {
        // Convertir le nom du contact en minuscules
        toLower(contacts[i].nom, nomLower);
        
        // Recherche insensible à la casse car le & n'etait pas mis dans les paramzttre
        if (strstr(nomLower, rechercheLower) != NULL) {
            printf("\nContact #%d\n", i + 1);
            printf("┌────────────────────────────────────┐\n");
            printf("│ Nom       : %-22s │\n", contacts[i].nom);
            printf("│ Téléphone : %-22s │\n", contacts[i].telephone);
            printf("│ Email     : %-22s │\n", contacts[i].email);
            printf("└────────────────────────────────────┘\n");
            trouve = 1;
        }
    }
    
    if (!trouve) {
        printf("\nAucun contact trouver avec \"%s\".\n", recherche);
        printf("Astuce : La recherche fonctionne avec des noms partiel.\n");
    } else {
        printf("\nRecherche terminer.\n");
    }
}

void supprimerContact(struct Contact contacts[], int *nombreContacts) {
    if (*nombreContacts == 0) {
        printf("\nAucun contact à suprimer.\n");
        return;
    }
    
    int numero;
    char confirmation;
    
    printf("\n========================================\n");
    printf("        SUPPRIMER UN CONTACT\n");
    printf("========================================\n");
    
    // Afficher la liste pour aider l'utilisateur
    printf("Liste des contacts :\n");
    for (int i = 0; i < *nombreContacts; i++) {
        printf("  %d. %s\n", i + 1, contacts[i].nom);
    }
    
    printf("\nEntrez le numéro du contact à supprimer (1 à %d) : ", *nombreContacts);
    scanf("%d", &numero);
    
    if (numero < 1 || numero > *nombreContacts) {
        printf("Numéro de contact invalide !\n");
        return;
    }
    
    // Afficher le contact à supprime
    printf("\nVous allez supprimer :\n");
    printf("┌────────────────────────────────────┐\n");
    printf("│ Nom       : %-22s │\n", contacts[numero - 1].nom);
    printf("│ Téléphone : %-22s │\n", contacts[numero - 1].telephone);
    printf("│ Email     : %-22s │\n", contacts[numero - 1].email);
    printf("└────────────────────────────────────┘\n");
    
    printf("\nConfirmer la supression ? (o/n) : ");
    viderBuffer();
    scanf("%c", &confirmation);
    
    if (confirmation != 'o' && confirmation != 'O') {
        printf("Suppression annulé.\n");
        return;
    }
    
    // Décaler tous les contacts suivants
    for (int i = numero - 1; i < *nombreContacts - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    
    (*nombreContacts)--;
    
    printf("\nContact supprimé avec succès !\n");
    printf("Total de contacts : %d/%d\n", *nombreContacts, MAX_CONTACTS);
}
// elle est en void car c'est main() qui prendre l'input afficherMenu() n'a qu'un role visuel
void afficherMenu() {
    printf("\n╔════════════════════════════════════╗\n");
    printf("║   GESTIONNAIRE DE CONTACT          ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║ 1.    Ajouter un contact           ║\n");
    printf("║ 2.    Afficher tous les contacts   ║\n");
    printf("║ 3.    Rechercher un contact        ║\n");
    printf("║ 4.    Supprime un  contact         ║\n");
    printf("║ 5.    Quitter                      ║\n");
    printf("╚════════════════════════════════════╝\n");
    printf("Votre choix : ");
}

void afficherStatistiques(int nombreContacts) {
    printf("\nSTATISTIQUE\n");
    printf("────────────────────────────────────\n");
    printf("Contacts enregistrés : %d/%d\n", nombreContacts, MAX_CONTACTS);
    printf("Places disponibles   : %d\n", MAX_CONTACTS - nombreContacts);
    
    if (nombreContacts > 0) {
        float pourcentage = (float)nombreContacts / MAX_CONTACTS * 100;
        printf("Taux de remplissage  : %.1f%%\n", pourcentage);
    }
}
// la fonction principale qui appel toutes les autres
int main() {
    struct Contact contacts[MAX_CONTACTS];
    int nombreContacts = 0;
    int choix;
    
    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║                                            ║\n");
    printf("║     BIENVENUE DANS VOTRE GESTIONNAIRE      ║\n");
    printf("║            DE CONTACTS                     ║\n");
    printf("║                                            ║\n");
    printf("╚════════════════════════════════════════════╝\n");
     
    do {
        afficherMenu();
        // fonction de securité qui vide le cache si l'user ne rentre pas un nombre entier 
        if (scanf("%d", &choix) != 1) {
            printf("\nEntrée invalide ! Veuillez entrer un nombre.\n");
            viderBuffer();
            continue;
        }
        // la fonction main appel les fonctions plus haut lorsqu'elles sont choisie (elle est à la fin car comme en python si les fonction ne sont pas deja déclarer a l'ordi ca marche pas)
        switch(choix) {
            case 1:
                ajouterContact(contacts, &nombreContacts);
                break;
            case 2:
                afficherContacts(contacts, nombreContacts);
                break;
            case 3:
                rechercherContact(contacts, nombreContacts);
                break;
            case 4:
                supprimerContact(contacts, &nombreContacts);
                break;
            case 5:
                printf("\n");
                afficherStatistiques(nombreContacts);
                printf("\n╔════════════════════════════════════╗\n");
                printf("║   Merci d'avoir utilisé           ║\n");
                printf("║   le gestionnaire de contacts !   ║\n");
                printf("║   À bientôt ! Bobye !              ║\n");
                printf("╚════════════════════════════════════╝\n\n");
                break;
            default:
                printf("\nChoix invalide ! Veuillez entrer un nombre entre 1 et 5, selon l'opptions que vous choisissez\n");//ausii une secu contre les nb non dit
        }
        
    } while (choix != 5); //la boucle while s'execute au moins une fois tant que 5 n'est pas choisi
    
    return 0;
}