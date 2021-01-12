/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#define MAX 1000

/* Eléments à revoir :
Diminution du stock
suppression*/

typedef char string[80];
typedef struct 
{
    int reference;
    string nom_modele;
    float prix_HT;
    int quantite_en_stock;
} MODELE ;


void ajout_modele (int *ne, MODELE t[], int reference_saisie, string nom_saisi, float prix_saisi, int quantite_saisie);
int pile_pleine (int ne, int max);
int pile_vide (int ne);
void affiche_tab (int ne, MODELE t[]);
int recherche_modele (int n, MODELE t[], int reference_saisie, int *position);
void ajout_stock_supplementaire (int n, MODELE t[], int reference_saisie, int quantite_saisie);
int recherche_modele_par_nom (int n, MODELE t[], string nom_saisi, int *reference_modele, float *prix_modele, int *stock);
float calcul_net_a_payer (int n, MODELE t[], float *net_a_payer);
void tri_croissant_prix(int n, MODELE t[]);
void dimunition_stock (int n, MODELE t[], string nom_saisi, int quantite_achetee, int *stock_final);
void supprime_modele (int *ne, MODELE t[]);
void ajout_quantite_panier (int n, MODELE t[], int *reference_saisie, int quantite_saisie);
void ajout_modele_dans_panier (int *ne, MODELE t[], int *reference_saisie, string nom_saisi, float *prix_saisi, int quantite_saisie);

void ajout_modele (int *ne, MODELE t[], int reference_saisie, string nom_saisi, float prix_saisi, int quantite_saisie)
{
    t[*ne].reference = reference_saisie;
    strcpy (t[*ne].nom_modele, nom_saisi);
    t[*ne].prix_HT = prix_saisi;
    t[*ne].quantite_en_stock = quantite_saisie;
    *ne = *ne + 1;
    
    return;
}

void ajout_modele_dans_panier (int *ne, MODELE t[], int *reference_saisie, string nom_saisi, float *prix_saisi, int quantite_saisie)
{
    t[*ne].reference = *reference_saisie;
    strcpy (t[*ne].nom_modele, nom_saisi);
    t[*ne].prix_HT = *prix_saisi;
    t[*ne].quantite_en_stock = quantite_saisie;
    *ne = *ne + 1;
    
    return;
}

int recherche_modele (int n, MODELE t[], int reference_saisie, int *position)
{
    int flag;
    int i;
    
    i = 0;
    flag = 0;
    
    while (i < n && flag == 0)
    {
        if (t[i].reference == reference_saisie)
        {
            flag = 1;
            *position = i;
        }
        i = i + 1;
    }
    return flag;
}



void ajout_stock_supplementaire (int n, MODELE t[], int reference_saisie, int quantite_saisie)
{
    int flag;
    int i;
    
    i = 0;
    flag = 0;
    
    while (i < n && flag == 0)
    {
        if (t[i].reference == reference_saisie)
        {
            t[i].quantite_en_stock = t[i].quantite_en_stock + quantite_saisie ;
            flag = 1;
        }
        i = i + 1;
    }
    return;
}

void ajout_quantite_panier (int n, MODELE t[], int *reference_saisie, int quantite_saisie)
{
    int flag;
    int i;
    
    i = 0;
    flag = 0;
    
    while (i < n && flag == 0)
    {
        if (t[i].reference == *reference_saisie)
        {
            t[i].quantite_en_stock = t[i].quantite_en_stock + quantite_saisie ;
        }
        i = i + 1;
    }
    return;
}

int pile_vide (int ne)
{
    int flag;
    
    flag = 0;
    if(ne == 0)
    {
        flag = 1;
    }
    return flag;
}

int pile_pleine (int ne, int max)
{
    int flag;
    
    flag = 0;
    if(ne == max)
    {
        flag = 1;
    }
    return flag;
}

float calcul_cout_moyen (int n, MODELE t[])
{
    int i;
    float somme;
    
    i = 0;
    somme = 0;
    while (i < n)
    {
        somme = somme + t[i].prix_HT;
        i = i + 1;
    }
    return somme/n;
}

int recherche_modele_par_nom (int n, MODELE t[], string nom_saisi, int *reference_modele, float *prix_modele, int *stock)
{
    int flag;
    int i;
    
    i = 0;
    flag = 0;
    
    while (i < n && flag == 0)
    {
        if (strcmp(t[i].nom_modele, nom_saisi) == 0)
        {
            flag = 1;
            *reference_modele = t[i].reference;
            *prix_modele = t[i].prix_HT;
            *stock = t[i].quantite_en_stock;
        }
        i = i + 1;
    }
    return flag;
}

void affiche_tab (int ne, MODELE t[])
{
    int i;
    
    i = 0;
    printf("Valeurs du tableau\n");
    while (i < ne)
    {
        printf("Modèle n° %d\n", i + 1);
        printf("          référence: %d \n", t[i].reference);
        printf("          Nom: %s \n", t[i].nom_modele);
        printf("          Prix: %.2f \n", t[i].prix_HT);
        printf("          Stock: %d \n", t[i].quantite_en_stock);
        i = i + 1;
    }
    return; 
}

float calcul_net_a_payer (int n, MODELE t[], float *net_a_payer)
{
    int i;
    float total_HT;
    float taux_TVA;
    
    
    i = 0;
    total_HT = 0;
    taux_TVA = 0.20;
    while (i < n)
    {
        total_HT = total_HT + t[i].quantite_en_stock * t[i].prix_HT;
        i = i + 1;
    }
    *net_a_payer = total_HT + total_HT * taux_TVA;
    
    return total_HT;
}

void tri_croissant_prix(int n, MODELE t[])
{
    int i; 
    int bi;
    int bs;
    MODELE tmp; 

    i = 0;
    while (i < n)
    {
        bi = 0;
        bs = n - 1;
        while (bi != bs)
        {
            if (t[i].prix_HT < t[bi].prix_HT)
            {
                tmp = t[i];
                t[i] = t[bi];
                t[bi] = tmp;
            }
            bi = bi + 1;
        }
        i = i + 1;
    }
    return;
}

void diminition_stock (int nbre_modele_total, int nbre_modele_panier, MODELE t1[], MODELE t2[])
{
    int i;
    int j;
    int flag;
    
    i = 0;
    /*
    while (i < nbre_modele_total)
    {
        // Si la référence est retrouvée dans le tableau du panier alors on diminue le stock
        if(strcmp(t1[i].nom_modele, t2[i].nom_modele) == 0) //??? Problème: la table des modèles et celle des panoers n'ont pas forcément le meme nombre d'enregistrement
        {
            t1[i].quantite_en_stock = t1[i].quantite_en_stock - t2[i].quantite_en_stock;
        }
        i = i + 1;
    }
    */
    // Je prends chaque produit de la table des modèle, si le produit est présent dans le panier alors je modifie la quantité en stock
    while (i < nbre_modele_total)
    {
        j = 0;
        while (j < nbre_modele_panier)
        {
            if (t1[i].reference == t2[j].reference) // Si les références sont identiques (si je retrouve le produit)
            {
                t1[i].quantite_en_stock = t1[i].quantite_en_stock - t2[j].quantite_en_stock;
            }
            j = j + 1;
        }
        i = i + 1;
    }
    
    return;
}

void supprime_modele (int *ne, MODELE t[])
{
    int i; 
    int bi;
    int bs;
    int j;
    MODELE tmp; 
    
    // Je commence à trier les modèles selon leur quantité. Les plus petites quantités se retrouvent en haut
    /*
    i = 0;
    while (i < *ne)
    {
        bi = 0;
        bs = *ne - 1;
        while (bi != bs)
        {
            if (t[i].quantite_en_stock < t[bi].quantite_en_stock)
            {
                tmp = t[i];
                t[i] = t[bi];
                t[bi] = tmp;
            }
            bi = bi + 1;
        }
        i = i + 1;
    }
    */
    // Je reparcours la table des modèles et si je trouve un produit dont le stock est égal à 0 alors je le supprime (en diminuant le nombre d'enregistrement)
    // File (celui qui est en première position part en premier)
    
    // En vrai, j'ai pas besoin de faire le tri.
    
    i = 0;
    while (i < *ne) // Je parcours toute la table des modèles
    {
        if (t[i].quantite_en_stock <= 0) // Si je trouve un stock = 0 (j'ai préféré prendre <= 0 au cas où)
        {
            j = i; // Je récupère le rang de cet élément
            while (j < *ne - 1) // Je décale tout les éléments suivants
            {
                t[j] = t[j+1];
                j = j + 1;
            }
            *ne = *ne - 1; // Je diminue le nombre de Modèle
        }
        
        i = i + 1;
        
    }
    
    return;
}

void diminition_stock2 (int n, MODELE t[], int reference_panier, int stock_panier)
{
    int i;
    int flag;
    
    while (i < n)
    {
        if (t[i].reference == reference_panier)
        {
            t[i].quantite_en_stock = t[i].quantite_en_stock - stock_panier;
            // Vérifier le stock
            if (t[i].quantite_en_stock == 0)
            {
                //lancer le programme de suppression
                
            }
        }
        i = i + 1;
    }
    
    return;
    
}

void vide_panier (int *ne, MODELE t[])
{
    *ne = 0;
    return;
}
int verifie_stock (int quantite_voulue, int *stock)
{
    int flag;
    
    flag = 0;
    if (quantite_voulue <= *stock)
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }
    
    return flag;
}

int verifie_stock_2 (int quantite_voulue, int *quantity_deja_reserve, int *stock)
{
    int flag;
    int total_voulue;
    
    flag = 0;
    total_voulue = quantite_voulue + *quantity_deja_reserve;
    if (total_voulue <= *stock)
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }
    
    return flag;
}



int main()
{
    int user_choice;
    int n;
    int ref;
    string name_model;
    float price;
    int quantity;
    int flag;
    MODELE tab[MAX];
    MODELE panier[MAX];
    int number;
    float cout_moyen;
    int choix;
    int quantity_storage;
    int nombre_produit_panier;
    float valeur_panier_HT;
    float valeur_panier_TTC;
    int stock_restant;
    int quantite_stock;
    int drapeau;
    int quantity_panier;
    int temp;
    int ref_produit_achete;
    int quantite_commandee;
    
    // On initialise le nombre de modèle à zéro
    n = 0;
    nombre_produit_panier = 0; // Nombre de produit contenu dans le panier
    // Menu 
    do
    {
        printf("\n**************Menu**************\n");
        printf("1: Ajout d'un modèle dans le stock\n");
        printf("2: Ajout d'unités dans un modèle qui existe déjà\n");
        printf("3: Calcul du cout moyen des outils \n");
        printf("4: Commande: remplir un panier \n");
        printf("5: Commande: trier le panier \n");
        printf("6: Commande: afficher le panier \n");
        printf("7: Afficher les modèles \n");
        printf("0: Quitter le programme \n");
        
        printf("Quel est votre choix?\n");
        scanf("%d", &user_choice);
        
        // Si l'utilisateur choisit 1
        if (user_choice == 1)
        {
            // On vérifie l'état de la pile
            flag = pile_pleine (n, MAX);
            if (flag == 1)
            {
                // Si la pile est pleine cela signifie qu'on ne peut plus faire aucun enregistrement
                printf ("Vous avez déjà enregistré 1000 modèles\n");
            }
            else // Si la pile n'est pas pleine alors on peut ajouter des modèles
            {
                printf("Ajout d'un modèle \n");
                printf("Entrez la référence\n");
                scanf ("%d", &ref);
                printf("Entrez le nom du modèle\n");
                scanf ("%s", name_model);
                /*
                fgets(name_model, 200, stdin);
                name_model[strlen(name_model) - 1] = '\0'; */
                printf("Entrez le prix hors taxe\n");
                scanf("%f", &price);
                printf("Entrez la quantité disponible\n");
                scanf("%d", &quantity);
                
                ajout_modele (&n, tab, ref, name_model, price, quantity );
            }
            
        }
        else
        { 
            if (user_choice == 2) // choix 2
            {
                printf("Entrez la référence du modèle\n");
                scanf ("%d", &ref);
                
                flag = recherche_modele (n, tab, ref, &number); // On recherche le modèle à l'aide de sa référence. Non indispensable
                if (flag == 0)
                {
                    printf ("Ce modèle n'existe pas dans notre base \n");
                }
                else
                {
                    printf("Entrez le nombre de modèles que vous souhaitez ajouter au stock\n");
                    scanf("%d", &quantity);
                    //tab[&number].quantite_en_stock = tab[&number].quantite_en_stock + quantity;
                    ajout_stock_supplementaire (n, tab, ref, quantity);
                }
            }
            else
            {
                if (user_choice == 3)
                {
                    flag = pile_vide(n);
                    if (flag == 1) // aucune donnée dans la base
                    {
                        printf("Aucun modèle n'a été enregistré\n");
                    }
                    else
                    {
                        cout_moyen = calcul_cout_moyen (n, tab);
                        printf ("Le cout moyen est de %.2f\n", cout_moyen);
                    }
                    
                }
                else
                {
                    if (user_choice == 4)
                    {
                        flag = pile_vide(n);
                        if (flag == 1)
                        {
                            printf("Aucun modèle n'a été enregistré\n");
                        }
                        else
                        {
                            // On demande à l'utilisateur s'il veut enregister un produit dans le panier
                            printf("Souhaitez-vous ajouter un produit à votre panier ?\n");
                            printf ("Tapez 1 pour oui\n");
                            printf ("Tapez 2 pour non\n");
                            scanf("%d", &choix);
                            while (choix == 1) // Tant qu'il répondra oui, on lancera le programme d'enregistrement
                            {
                                printf("Entrez le nom du modèle\n");
                                scanf ("%s", name_model);
                                // On recherche le modèle grace au nom saisi par l'utilisateur (recherche dans la table des modèles)
                                flag = recherche_modele_par_nom (n, tab, name_model, &ref, &price, &quantity_storage);
                                if (flag == 0) // Produit non trouvé
                                {
                                    printf ("Ce modèle n'existe pas dans notre base \n");
                                }
                                else
                                {
                                    // Produit trouvé
                                    
                                    // Vérifier si le produit est déjà dans le panier (recherche dans le panier)
                                    // Si le produit est présent dans le panier, on récupère les données
                                    flag = recherche_modele_par_nom (nombre_produit_panier, panier, name_model, &ref, &price, &quantity_panier);
                                    if (flag == 0) // Si le produit n'est pas encore dans le panier
                                    {
                                        // On demande quel quantité l'utilisateur veut acheter
                                        printf("Entrez le nombre de modèles que vous souhaitez acheter\n");
                                        scanf("%d", &quantity);
                                        
                                        // On vérifie si la quantité que le client souhaite acheter est disponible
                                        drapeau = verifie_stock (quantity, &quantity_storage);
                                        if (drapeau == 0)
                                        { // Si on n'a pas assez de stock, on affiche un message
                                            printf ("Nous n'avons pas assez de stock pour satisfaire votre demande\n");
                                        }
                                        else
                                        {
                                            // Lancer le programme d'enregistrement ???
                                            // Ce que j'ai fait: j'ai créé un second tableau qui contient uniquement les commandes
                                            ajout_modele_dans_panier (&nombre_produit_panier, panier, &ref, name_model, &price, quantity );
                                        }
                                        /*
                                        
                                        //On compare la quantité saisie avec la quantité en stock
                                        quantite_stock = &quantity_storage;
                                        if (quantite_stock < quantity)
                                        {
                                            printf ("Nous n'avons pas assez de stock pour satisfaire votre demande\n");
                                        }
                                        else
                                        {
                                            // Lancer le programme d'enregistrement ???
                                            // Ce que j'ai fait: j'ai créé un second tableau qui contient uniquement les commandes
                                            ajout_modele_dans_panier (&nombre_produit_panier, panier, &ref, name_model, &price, quantity );
                                            
                                        } 
                                        */
                                    }
                                    else // Si le produit est déjà dans le panier
                                    {
                                        // On demande quel quantité l'utilisateur veut acheter
                                        printf("Entrez le nombre de modèles que vous souhaitez acheter\n");
                                        scanf("%d", &quantity);
                                        // Il faut récupérer l'ancienne quantité et l'ajouter à la nouvelle et si la somme est inférieure au stock, on pourra faire l'enregistrement
                                    
                                        drapeau = verifie_stock_2 (quantity, &quantity_panier, &quantity_storage);
                                        if (drapeau == 0)
                                        { // Si on n'a pas assez de stock, on affiche un message
                                            printf ("Nous n'avons pas assez de stock pour satisfaire votre demande\n");
                                        }
                                        else
                                        {
                                            // Ajoute la nouvelle quantité à l'ancienne
                                            ajout_quantite_panier (nombre_produit_panier, panier, &ref, quantity);
                                        }
                                        
                                    }
                                   
                                }
                                
                                printf("Souhaitez-vous ajouter un produit à votre panier ?\n");
                                printf ("Tapez 1 pour oui\n");
                                printf ("Tapez 2 pour non\n");
                                scanf("%d", &choix);
                            }
                            /*
                            do 
                            {
                                printf("Souhaitez-vous ajouter un produit à votre panier ?\n");
                                printf ("Tapez 1 pour oui\n");
                                printf ("Tapez 2 pour non\n");
                                scanf("%d", &choix);
                            } while (choix != 2)
                            */
                            
                            // Dès qu'il a fini de remplir son panier
                            
                            printf("Souhaitez-vous valider votre panier? \n");
                            printf("Entrez 1 pour oui et 2 pour non\n");
                            scanf("%d", &choix);
                            if (choix == 2)// il ne souhaite pas valider son panier 
                            {
                                printf("Vous ne souhaitez pas valider votre panier. A bientot\n");
                            }
                            else
                            {
                                if (choix == 1)
                                {
                                    // S'il souhaite valider son panier, diminuer le stock
                                    // Dans un premier temps récupérer le stock initial (lancer la recherche dans la table des produits)
                                    // Il y a un problème, sur quel critère lancer la recherche. 
                                    //Une solution consiste à valider le panier à chaque fois qu'on choisit un produit. Comme ca récupére le nom du produit, lance la recherche et diminue le stock
    
                                    /* solution 1
                                    // Ensuite récupérer la quantité total acheté
                                    
                                    // Enfin diminuer le stock
                                    diminition_stock (n, nombre_produit_panier, tab, panier);
                                    //Lancer le programme de suppression
                                    supprime_modele (&n, tab);
                                    */
                                    // Solution 2: passer la référence en paramètre
                                    while (i < nombre_produit_panier)
                                    {
                                        ref_produit_achete = panier[i].reference;
                                        quantite_commandee = panier[i].quantite_en_stock;
                                        diminition_stock2 (n, tab, ref_produit_achete, quantite_commandee);
                                        
                                    }
                                    
                                    // Calculer la valeur du panier
                                    valeur_panier_HT = calcul_net_a_payer (nombre_produit_panier, panier, &valeur_panier_TTC);
                                    printf("Le total HT est de %.2f", valeur_panier_HT);
                                    printf("Vous devez payer %.2f \n", valeur_panier_TTC);
                                }
                                else // Dans le cas où l'utilisateur entre un chiffre différent de 1 ou de 2
                                {
                                   printf("Réésayer. Vous devez saisir 1 pour oui et 2 pour non\n"); 
                                   scanf("%d", &choix);
                                }
                            }
                            
                            
                        }
                        
                    }
                  
                    else
                    {
                        if (user_choice == 5)
                        {
                           tri_croissant_prix(nombre_produit_panier, panier);
                        }
                        else
                        {
                            if (user_choice == 6)
                            {
                                flag = pile_vide(nombre_produit_panier);
                                if (flag == 1) // aucune donnée dans la base
                                {
                                    printf("Panier vide\n");
                                }
                                else
                                {
                                    affiche_tab(nombre_produit_panier, panier);
                                }   
                                
                            }
                            else
                            {
                                if (user_choice == 7)
                                {
                                    flag = pile_vide(n);
                                    if (flag == 1) // aucune donnée dans la base
                                    {
                                        printf("Aucun modèle n'a été enregistré\n");
                                    }
                                    else
                                    {
                                        affiche_tab (n, tab);
                                    }  
                                    
                                    
                                }
                                else
                                {
                                    printf("Commande non pris en charge\n");
                                }
                            }
                        }
                   }
                }
                
                
            }
            
        }
        
        
    } while (user_choice != 0);
    
    printf("\n\n**************Fin. Merci d'avoir utiliser notre logiciel :) **************\n\n");
    
    return 0;
}



