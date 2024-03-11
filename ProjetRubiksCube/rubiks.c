//
// Created by Clara on 05/05/2021.
//

#include "rubiks.h"
#include "conio.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



/*
 Dans ce fichier, vous trouverez les différentes fonctions du rubik's cube.
 */



/*Fonction pour les types énumérés*/

//Fonction qui reçoit en parapètre une couleur et qui retourne un chiffre
int select_color(T_COLOR color){
    if (color == O)
        return 0;
    if (color == W)
        return 1;
    if (color == G)
        return 2;
    if (color == Y)
        return 3;
    if (color == R)
        return 4;
    if (color == B)
        return 5;
    if (color == LG)
        return 6;

}

//Fonction qui reçoit une face et qui retourne un chiffre
int side_to_index(T_SIDE side){
    if(side == LEFT)
        return 0;
    if(side == UP)
        return 1;
    if(side == FRONT)
        return 2;
    if(side == DOWN)
        return 3;
    if(side == RIGHT)
        return 4;
    if(side == BACK)
        return 5;
}

//Fonction qui reçoit une lettre et et qui retourne la face
T_SIDE word_to_side(char c){
    if(c == 'L')
        return LEFT;
    if(c == 'U')
        return UP;
    if(c == 'F' )
        return FRONT;
    if(c == 'D')
        return DOWN;
    if(c == 'R')
        return RIGHT;
    if(c == 'B')
        return BACK;
}

//Fonction qui reçoit en paramètre un indice et qui retounre une face
T_SIDE index_to_side(int index){
    switch (index) {
        case 0:
            return LEFT;
            break;
        case 1:
            return UP;
            break;
        case 2:
            return FRONT;
            break;
        case 3:
            return DOWN;
            break;
        case 4:
            return RIGHT;
            break;
        case 5:
            return BACK;
            break;
    }
}

//Fonction qui recoit un indice et qui retourne une couleur
T_COLOR index_to_color(int index){
    switch(index){
        case 0:
            return O;
            break;
        case 1:
            return W;
            break;

        case 2:
            return G;
            break;

        case 3:
            return Y;
            break;
        case 4 :
            return R;
            break;
        case 5:
            return B;
            break;
        case 6:
            return LG;
            break;



    }
}



//Fonction qui reçoit en paramètre une couleur et qui affiche le lettre de la couleur en utilisant les couleurs de conio
void read_color(T_COLOR color){
    switch(color){
        case R:
            c_textcolor(RED);   //utilise conio, affiche le texte en couleurs
            printf("R ");
            c_textcolor(WHITE);
            break;
        case B:
            c_textcolor(BLUE);
            printf("B ");
            c_textcolor(WHITE);
            break;
        case G:
            c_textcolor(GREEN);
            printf("G ");
            c_textcolor(WHITE);
            break;
        case W:
            c_textcolor(WHITE);
            printf("W ");
            break;
        case Y:
            c_textcolor(YELLOW);
            printf("Y ");
            c_textcolor(WHITE);
            break;
        case O:
            c_textcolor(LIGHTMAGENTA);
            printf("O ");
            c_textcolor(WHITE);
            break;
        case LG:
            printf("- ");
            c_textcolor(WHITE);
            break;
    }
}

//Fonction qui reçoit en paramètre une couleur et qui retourne la couleur qui doit être sur la face opposé
T_COLOR opp_color(T_COLOR color){
    if(color == O)
        return R;
    if(color == R)
        return O;
    if(color == W)
        return Y;
    if(color == Y)
        return W;
    if(color == G)
        return B;
    if (color == B)
        return G;
}

//Fonction qui reçoit en paramètre un entier qui désigne une face et qui retourne un chiffre qui désigne la face opposé
int opp_side(int side){
    if(side== 0)
        return 4;
    if(side == 4)
        return 0;
    if(side == 2)
        return 5;
    if(side == 5)
        return 2;
    if(side == 1)
        return 3;
    if(side == 3)
        return 1;
}






/* Fonction de réprésentation du cube */



//Fonction qui créé le cube en tableau dynamique à 3 dimension et qui retourne le pointeur
rubiks* create_rubiks(){
    rubiks *p = NULL;
    int size = 6, k, i, j, nbl = 3;

    p = (rubiks*)malloc(size*sizeof(rubiks));

    for(k=0;k<size;k++) {
        (p+k)->side = (T_SIDE **) malloc(nbl * sizeof(T_SIDE *));
    }
    for(k=0;k<size;k++) {
        for (i = 0; i < nbl; i++) {
            (p+k)->side[i] = (T_SIDE *) malloc(nbl * sizeof(T_SIDE));
        }
    }
    return p;
}

//Fonction qui reçoit un pointeur rubiks et qui l'initialise avec les couleurs do,,é dans l'énoncé (sur la face UP : blanc ...)
rubiks* init_rubiks(rubiks *p){
    int size = 6, k, i, j, nbl = 3;
    T_SIDE sid;
    T_COLOR col;
    for (k = 0; k < size; k++) {
        col = index_to_color(k);
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                (p + k)->side[i][j] = col ;
            }
        }
    }

    return p;
}

//Fonction qui libère l'espace alloué du pointeur rubiks
void free_rubiks(rubiks* p){
    int k, size = 6, i, nbl = 3;
    for(k=0;k<size;k++) {
        free((p+k)->side);    //utilise la fonction free() qui libère l'espace
    }
    for(k=0;k<size;k++) {
        for (i = 0; i < nbl; i++) {
            free((p+k)->side[i]);    //il y a autant de free() que de malloc()
        }
    }
    free(p);
}

//Fonction qui reçoit le pointeur rubiks et qui le retourne, cette fonction permet de choisir
// manuellement les couleurs des faces du cube tout en respectant les règles de distributions des couleurs
rubiks* init_rubiks_manu(rubiks *p){
    int size = 6, k,k1,k2,i, j, nbl = 3;
    int color,color1,color2;
    T_SIDE sid;
    T_COLOR col,col1,col2,colop,col1opp,col2opp;
    printf("Inserez un chiffre --> LEFT = 0 ; UP = 1; FRONT = 2 ; DOWN = 3 ; RIGHT = 4 ; BACK = 5\n");
    scanf("%d",&k);
    printf("Inserez un chiffre : ORANGE = 0 ; WHITE = 1 ; GREEN = 2 ; YELLOW = 3 ; RED = 4 ; BLUE = 5 ; LG = 6\n");
    scanf("%d",&color);
    col = index_to_color(color);
    for (i = 0; i < nbl; i++) {
        for (j = 0; j < nbl; j++) {
            (p + k)->side[i][j] = col ; //affecte la couleur voulu à la face choisit
        }
    }
    colop = opp_color(col);
    for (i = 0; i < nbl; i++) {
        for (j = 0; j < nbl; j++) {
            (p + opp_side(k))->side[i][j] = colop ;   //affecte la couleur opposé à la face opposé de la couleur
        }                                             //et face choisit pour respecter les règles de distributions
    }

    do{
        printf("Inserez un chiffre non inserez auparavant -->  LEFT = 0 ; UP = 1; FRONT = 2 ; DOWN = 3 ; RIGHT = 4 ; BACK = 5  / utilse : %d , %d\n",k,side_to_index(opp_side(k)));
        scanf("%d",&k1);
    }while(k1 == k || k1 == opp_side(k));  //empeche la face et la face opposé de la 1ere face choisit par l'utilisateur, d'être choisit
    do{
        printf("Inserez un chiffre : ORANGE = 0 ; WHITE = 1 ; GREEN = 2 ; YELLOW = 3 ; RED = 4 ; BLUE = 5 ; LG = 6 / utilise : %d , %d\n",color,select_color(colop));
        scanf("%d",&color1);
    }while(color1 == color || color1 == select_color(colop));  //empêche la couleur choisit et la couleur opposé d'être affecter car elles sont déjà affectées
    col1 = index_to_color(color1);
    for (i = 0; i < nbl; i++) {
        for (j = 0; j < nbl; j++) {
            (p + k1)->side[i][j] = col1 ;
        }
    }
    col1opp = opp_color(col1);
    for (i = 0; i < nbl; i++) {
        for (j = 0; j < nbl; j++) {
            (p + opp_side(k1))->side[i][j] = col1opp ;
        }
    }

    do{
        printf("Inserez un chiffre non inserez auparavant -->  LEFT = 0 ; UP = 1; FRONT = 2 ; DOWN = 3 ; RIGHT = 4 ; BACK = 5 / utilises :  %d , %d   , %d  , %d\n ",k,side_to_index(opp_side(k)),k1,side_to_index(opp_side(k1)));
        scanf("%d",&k2);
    }while(k2 == k1 || k2 == k || k2 == opp_side(k) || k2 == opp_side(k1));
    do{
        printf("Inserez un chiffre : ORANGE = 0 ; WHITE = 1 ; GREEN = 2 ; YELLOW = 3 ; RED = 4 ; BLUE = 5 ; LG = 6 / utilises :  %d , %d   , %d  , %d\n",color,select_color(colop),color1,select_color(col1opp));
        scanf("%d",&color2);
    }while(color2 == color || color2 == color1 || color2 == select_color(colop) || color2 == select_color(col1opp));
    col2 = index_to_color(color2);
    for (i = 0; i < nbl; i++) {
        for (j = 0; j < nbl; j++) {
            (p + k2)->side[i][j] = col2 ;
        }
    }
    col2opp = opp_color(col2);
    for (i = 0; i < nbl; i++) {
        for (j = 0; j < nbl; j++) {
            (p + opp_side(k2))->side[i][j] = col2opp ;
        }
    }
    return p;
}

//Fonction qui reçoit le cube et qui l'affiche
void display_rubiks(rubiks* p){
    int k, i, j, size = 6, nbl = 3;

    for (k = 1; k < 2; k++) {              //différentes boucles qui affiche la face décidé, ici on affiche d'aboird la face UP
        for (i = 0; i < nbl; i++) {
            printf("       ");
            for (j = 0; j < nbl; j++) {
                read_color((p + k)->side[i][j]);
            }
            printf("\n");
        }
    }
    printf("\n");

    for (k = 0; k < 1; k++) {                    //puis les faces left, front, right, back
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                read_color((p + k)->side[i][j]);
            }
            printf(" ");
            for (j = 0; j < nbl; j++) {
                read_color((p + k+2)->side[i][j]);
            }
            printf(" ");
            for (j = 0; j < nbl; j++) {
                read_color((p + k+4)->side[i][j]);
            }
            printf(" ");
            for (j = 0; j < nbl; j++) {
                read_color((p + k+5)->side[i][j]);
            }
            printf("\n");
        }
    }
    printf("\n");

    for (k = 3; k < 4; k++) {            //et enfin la face down
        for (i = 0; i < nbl; i++) {
            printf("       ");
            for (j = 0; j < nbl; j++) {
                read_color((p + k)->side[i][j]);
            }
            printf("\n");
        }
    }
}


//Fonction permettant de griser le cube, qui reçoit le cube et le retourne une fois griser
rubiks* blank_rubiks(rubiks *p){
    int size = 6,k,i,j, nbl = 3;
    T_COLOR col;
    T_SIDE side;
    for(k=0;k<size; k++){
        col = LG;
        side = index_to_side(k);
        for(i = 0;i<nbl;i++){
            for( j=0 ; j<nbl ; j++){
                (p+k)->side[i][j]= col;
            }
        }
    }

    return p;
}



//Foncition qui reçoit un pointeur rubiks et qui le retourne une fois que l'utilisateur a choisit le ou les cases à modifier
int fill_rubiks(rubiks *p) {
    T_SIDE side;
    T_COLOR col;
    char c;
    int k, j, cpt = 0, ligne, colonne, n, h, bol = 1, g, i;

    for (k = 0; k < 6; k++) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if ((p + k)->side[i][j] == LG) {   //boucle permettant de savoir si au moins une case est grisé
                    cpt++;
                }
            }
        }
    }
    if (cpt == 0) {  //si le cube n'est oas griser, on peut appliquer les fonction verifcentre et check
        do {            //permettant de vérifier le bon nombre de cases par couleur et qu'il y ait une couleur par centre
            printf("Nombres de cases a remplir, il faut que vous inserez un chiffre pair (0 pour retourner au menu): ");
            scanf("%d", &g);

        } while (g % 2 == 1);   //il faut rentrer un nombre pair car si l'on modifie qu'une case
        if (g == 0) {          //il y aura forcément 10 cases d'une couleur et 8 de l'autre donc ça fera une boucle infini
            printf("\n");
            return 0;
        } else {
            do {
                printf("\n");
                for (i = 0; i < g; i++) {
                    do {
                        printf("Face : LEFT = L | UP = U | FRONT = F | DOWN = D | RIGHT = R | BACK = B | (MENU PRINCIPAL = Z) : ");
                        scanf(" %c", &c);
                    } while (c != 'L' && c != 'U' && c != 'F' && c != 'D' && c != 'R' && c != 'B' && c != 'Z');

                    if (c == 'Z') {
                        printf("\n");
                        return 0;
                        break;
                    } else {
                        side = word_to_side(c);
                        k = side_to_index(side);
                        do {
                            printf("ligne : ");
                            scanf("%d", &ligne);
                        } while (ligne < 0 || ligne > 2);

                        do {
                            printf("colonne : ");
                            scanf("%d", &colonne);
                        } while (colonne < 0 || colonne > 2);

                        do {
                            printf("Couleur: 0 = O | 1 = W | 2 = G | 3 = Y | 4 = R | 5 = B | 6 = LG : ");
                            scanf("%d", &n);
                        } while (n < 0 || n > 6);

                        printf("\n");

                        col = index_to_color(n);
                        (p + k)->side[ligne][colonne] = col;

                        printf("\n");

                        display_rubiks(p);
                    }

                }
                verifcentre(p);
            } while (check(p) == 0 || verifcentre(p) == 0);
        }
        return 1;
    }
    if (cpt > 0) {   //si le cube est griser aucune condition ne s'applique puisque ce n'est pas un vrai cube, on peut rentrer ce que l'on veut
        do {
            printf("Nombres de cases a remplir, (0 pour retourner au menu): ");
            scanf("%d", &g);

        } while (g<0 || g>54);
        if (g == 0) {
            printf("\n");
            return 0;
        } else {
            printf("\n");
            for (i = 0; i < g; i++) {
                do {
                    printf("Face : LEFT = L | UP = U | FRONT = F | DOWN = D | RIGHT = R | BACK = B | (MENU PRINCIPAL = Z) : ");
                    scanf(" %c", &c);
                } while (c != 'L' && c != 'U' && c != 'F' && c != 'D' && c != 'R' && c != 'B' && c != 'Z');

                if (c == 'Z') {
                    printf("\n");
                    return 0;
                    break;
                } else {
                    side = word_to_side(c);
                    k = side_to_index(side);
                    do {
                        printf("ligne : ");
                        scanf("%d", &ligne);
                    } while (ligne < 0 || ligne > 2);

                    do {
                        printf("colonne : ");
                        scanf("%d", &colonne);
                    } while (colonne < 0 || colonne > 2);

                    do {
                        printf("Couleur: 0 = O | 1 = W | 2 = G | 3 = Y | 4 = R | 5 = B | 6 = LG : ");
                        scanf("%d", &n);
                    } while (n < 0 || n > 6);

                    printf("\n");

                    col = index_to_color(n);
                    (p + k)->side[ligne][colonne] = col;

                    printf("\n");

                    display_rubiks(p);

                }

            }
        }
        return 1;
    }
}

//Fonction qui reçoit un pointeur rubiks et qui retourne un nombre qui a pour but d'être un booléen. Cette fonction vérifie s'il y a bine des couleurs différents pas centres
int verifcentre(rubiks *p){
    int k,i,bol=1;
    int T_COLOR[6] = {0,0,0,0,0,0};
    char o[]= "orange",bla[]= "blanche",v[]= "verte",ja[]= "jaune",r[]= "rouge",ble[]= "bleue";

    for(k=0;k<6;k++){
        if((p+k)->side[1][1]== O)T_COLOR[0]++;     //compte le nombre de couleur différente par centre, il en faut 1
        if((p+k)->side[1][1]== W)T_COLOR[1]++;
        if((p+k)->side[1][1]== G)T_COLOR[2]++;
        if((p+k)->side[1][1]== Y)T_COLOR[3]++;
        if((p+k)->side[1][1]== R)T_COLOR[4]++;
        if((p+k)->side[1][1]== B)T_COLOR[5]++;
    }

    for(i=0;i<6;i++){
        if (T_COLOR[i]!=1 )
            bol = 0;
    }
    if(bol == 0) {
        printf("Rubik's cube invalide ! :\n");
        for(i=0;i<6;i++){             //cette boucle montre à l'utilisateur les différents problèmes
            if(T_COLOR[i]>1){
                if(i==0)
                    printf("Seul une case centrale d'une face du rubik's cube  doit comporter la couleur %s\n",o);
                if(i==1)
                    printf("Seul une case centrale d'une face du rubik's cube  doit comporter la couleur %s\n",bla);
                if(i==2)
                    printf("Seul une case centrale d'une face du rubik's cube  doit comporter la couleur %s\n",v);
                if(i==3)
                    printf("Seul une case centrale d'une face du rubik's cube  doit comporter la couleur %s\n",ja);
                if(i==4)
                    printf("Seul une case centrale d'une face du rubik's cube  doit comporter la couleur %s\n",r);
                if(i==5)
                    printf("Seul une case centrale d'une face du rubik's cube  doit comporter la couleur %s\n",ble);
            }
        }

    }
    printf("\n");
    return bol;
}

//Fonction qui reçoit le pointeru rubiks et qui retourne un nombre qui a pour but d'être un booléen. Cette fonction vérifie s'il y a bien 9 cases par couleurs
int check(rubiks *p) {
    int T_COLOR[6] = {0,0,0,0,0,0};
    char o[]= "orange",bla[]= "blanche",v[]= "verte",ja[]= "jaune",r[]= "rouge",ble[]= "bleue";
    int k, i,j,bol=1;


    // Verifier si il n'y a pas plus de 9 cases de la même couleur

    for (k = 0; k < 6; k++) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if((p+k)->side[i][j]== O)T_COLOR[0]++;
                if((p+k)->side[i][j]== W)T_COLOR[1]++;
                if((p+k)->side[i][j]== G)T_COLOR[2]++;
                if((p+k)->side[i][j]== Y)T_COLOR[3]++;
                if((p+k)->side[i][j]== R)T_COLOR[4]++;
                if((p+k)->side[i][j]== B)T_COLOR[5]++;

            }
        }
    }
    for(i=0;i<6;i++){
        if (T_COLOR[i] != 9)
            bol = 0;
    }
    if(bol==0) {
        printf("Rubiks's cube invalide ! : \n");
        for (i = 0; i < 6; i++) {             //indique les problèmes pour l'utilisateur
            if (T_COLOR[i] != 9) {
                if (i == 0)
                    printf("Il y a %d cases de couleur %s au lieu de 9\n", T_COLOR[i], o);
                if (i == 1)
                    printf("Il y a %d cases de couleur %s au lieu de 9\n", T_COLOR[i], bla);
                if (i == 2)
                    printf("Il y a %d cases de couleur %s au lieu de 9\n", T_COLOR[i], v);
                if (i == 3)
                    printf("Il y a %d cases de couleur %s au lieu de 9\n", T_COLOR[i], ja);
                if (i == 4)
                    printf("Il y a %d cases de couleur %s au lieu de 9\n", T_COLOR[i], r);
                if (i == 5)
                    printf("Il y a %d cases de couleur %s au lieu de 9\n", T_COLOR[i], ble);
            }
        }
    }
    printf("\n");
    return bol;
}


//Fonction permettant de mélanger alétoirement le cube en utilisant les fonctions de mouvements plus bas. Elle reçoit le pointeur rubiks et le retourne
rubiks* scramble_rubiks(rubiks *p){
    int rot, val, i;
    // On commence par initialiser le générateur de nombre aléatoires.
    srand( time( NULL ) );

    for (i=0;i<40;i++) {               //on mélange le cube en faisant 40 mouvements
        rot = 1;//rand()%2+1;
        val = rand()%11;        //a chaque boucle val est une valeur aléatoire entre 0 et 11
        if (val == 0) {
            front_clockwise(p, rot);
        }
        else if (val == 1) {
            back_clockwise(p, rot);
        }
        else if (val == 2) {
            up_clockwise(p, rot);
        }

        else if (val == 3) {
            down_clockwise(p, rot);
        }
        else if (val == 4) {
            left_clockwise(p, rot);
        }
        else if (val == 5) {
            right_clockwise(p, rot);
        }
        else if (val == 6) {
            front_anticlockwise(p, rot);
        }
        else if (val == 7) {
            back_anticlockwise(p, rot);
        }
        else if (val == 8) {
            up_anticlockwise(p, rot);
        }
        else if (val == 9) {
            down_anticlockwise(p, rot);
        }
        else if (val == 10) {
            right_anticlockwise(p, rot);
        }
        else if (val == 11) {
            left_anticlockwise(p, rot);
        }

    }
    return p;
}


// Fonction qui reçoit un pointeur de rubiks et le retiourne. Cette fonction  permet de faire une rotation horizontal du cube , c'est à dire que la face back devient front(et inversement) et la face right devient left (et inversement).
rubiks* horizontal_rotation(rubiks *p){
    int k,size = 6, nbl = 3,i,j;
    T_COLOR col[6][3][3];

    // On fait une "copie" du cube
    for(k=0 ; k<6;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                col[k][i][j] = (p+k)->side[i][j];
            }
        }
    }
    // Pour ensuite bien attribuer les couleurs aux nouvelles "faces"

    // La face right prend les couleurs de la face left
    for(k=0;k<1;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                (p+4)->side[i][j] = col[k][i][j] ;
            }
        }
    }

    // La face left prend les couleurs de la face right
    for(k=4;k<5;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                (p+0)->side[i][j]=col[k][i][j]  ;
            }
        }
    }
    // La face front prend les couleurs de la face back
    for(k=5;k<6;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                (p+2)->side[i][j]=col[k][i][j];
            }
        }
    }

    // La face back orend les couleurs de la face front
    for(k=2;k<3;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                (p+5)->side[i][j]=col[k][i][j];
            }
        }
    }

    return p;
}


// Fonction qui reçoit un pointeur de rubiks et le retiourne. Cette fonction  permet de faire une rotation verticale du cube , c'est à dire que la face up devient down (et inversement) et la face front devient back(et inversement).

rubiks* vertical_rotation(rubiks *p){
    int k,size = 6, nbl = 3,i,j;
    T_COLOR col[6][3][3];


    // "Copie du cube "
    for(k=0 ; k<6;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                col[k][i][j] = (p+k)->side[i][j];
            }
        }
    }

    // face up prend les couleurs de la face down
    for(k=3;k<4;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                (p+1)->side[i][j] = col[k][i][j] ;
            }
        }
    }

    // face down prend les couleurs de la face up
    for(k=1;k<2;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                (p+3)->side[i][j]=col[k][i][j]  ;
            }
        }
    }

    // Face front prend les couleurs de la face back
    for(k=5;k<6;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                (p+2)->side[i][j]=col[k][i][j];
            }
        }
    }

    // Face back prend les couleurs de la face front
    for(k=2;k<3;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                (p+5)->side[i][j]=col[k][i][j];
            }
        }
    }
    return p;

}


// Pour les clockwise nous avons plûtot opté de faire la majortité des mouvements manuellement

// Fonction qui reçoit un entier  et un pointeur de rubiks qui va le retourner. Cette fonction permet de faire une rotation (quart de tour ou demi tour) sur face LEFT dans le sens de l'aiguille d'une montre
rubiks* left_clockwise(rubiks *p, int rot){
    int k, nbl = 3, i, j;
    T_COLOR col[6][3][3];

    // Copie du cube
    for (k = 0; k < 6; k++) {
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                col[k][i][j] = (p + k)->side[i][j];
            }
        }
    }

    // Pour un quart de tour
    if (rot == 1){
        // changement pour la face Down
        for (k = 3; k > 2; k--) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][0] = col[k-1][i][0] ;
                }
            }
        }
        // changement pour la face Front
        for (k = 2; k > 1; k--) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][0] = col[k-1][i][0] ;
                }
            }
        }
        //changement pour la face Up
        for (k = 1; k < 5; k+=4) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k+4][2][2] ;
                    (p + k)->side[1][0] = col[k+4][1][2] ;
                    (p + k)->side[2][0] = col[k+4][0][2] ;

                }
            }
        }
        //changement pour la face Back
        for (k = 5; k > 3; k-=2) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k-2][2][0] ;
                    (p + k)->side[1][2] = col[k-2][1][0] ;
                    (p + k)->side[2][2] = col[k-2][0][0] ;


                }
            }
        }
        // changement pour la face left
        p->side[0][0] = col[0][2][0];
        p->side[0][1] = col[0][1][0];
        p->side[0][2] = col[0][0][0];
        p->side[1][0] = col[0][2][1];
        p->side[1][1] = col[0][1][1];
        p->side[1][2] = col[0][0][1];
        p->side[2][0] = col[0][2][2];
        p->side[2][1] = col[0][1][2];
        p->side[2][2] = col[0][0][2];

    }

    // Pour un demi tour
    if (rot == 2){
        // changement pour la face Down
        for (k = 3; k > 2; k-=2) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][0] = col[k-2][i][0] ;
                }
            }
        }
        // changement pour la face Front
        for (k = 2; k < 5; k+=3) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k+3][2][2] ;
                    (p + k)->side[1][0] = col[k+3][1][2] ;
                    (p + k)->side[2][0] = col[k+3][0][2] ;


                }
            }
        }
        //changement pour la face Up
        for (k = 1; k < 2; k+=2) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][0] = col[k+2][i][0] ;
                }
            }
        }
        //changement pour la face Back
        for (k = 5; k > 4; k-=3) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k-3][2][0] ;
                    (p + k)->side[1][2] = col[k-3][1][0] ;
                    (p + k)->side[2][2] = col[k-3][0][0] ;


                }
            }
        }
        // changement pour la face left
        p->side[0][0] = col[0][2][2];
        p->side[0][1] = col[0][2][1];
        p->side[0][2] = col[0][2][0];
        p->side[1][0] = col[0][1][2];
        p->side[1][1] = col[0][1][1];
        p->side[1][2] = col[0][1][0];
        p->side[2][0] = col[0][0][2];
        p->side[2][1] = col[0][0][1];
        p->side[2][2] = col[0][0][0];
    }

    return p;

}


// Pour tous les autres nous avons procédés de la même manière que le précedent

// Fonction qui reçoit un entier et un pointeur rubiks  qui va le retourner. Cette fonction permet de faire une rotation (quart de tour ou demi tour) sur la face  RIGHT dans le sens de l'aiguille d'une montre
rubiks* right_clockwise(rubiks *p, int rot) {
    int k, nbl = 3, i, j;
    T_COLOR col[6][3][3];

    // copie du cube
    for (k = 0; k < 6; k++) {
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                col[k][i][j] = (p + k)->side[i][j];
            }
        }
    }

    // Pour un quart de tour
    if (rot == 1) {
        // changement pour la face Down
        for (k = 3; k < 4; k+=2) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k+2][2][0];
                    (p + k)->side[1][2] = col[k+2][1][0];
                    (p + k)->side[2][2] = col[k+2][0][0];


                }
            }
        }
        // changement pour la face Front
        for (k = 2; k < 3; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][2] = col[k+1][i][2] ;
                }
            }
        }
        // changement pour la face Up
        for (k = 1; k < 2; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][2] = col[k+1][i][2] ;
                }
            }
        }
        // changement pour la face Back
        for (k = 5; k > 4; k-=4) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k-4][2][2] ;
                    (p + k)->side[1][0] = col[k-4][1][2] ;
                    (p + k)->side[2][0] = col[k-4][0][2] ;


                }
            }
        }
        // changement pour la face right
        (p+4)->side[0][0] = col[4][2][0];
        (p+4)->side[0][1] = col[4][1][0];
        (p+4)->side[0][2] = col[4][0][0];
        (p+4)->side[1][0] = col[4][2][1];
        (p+4)->side[1][1] = col[4][1][1];
        (p+4)->side[1][2] = col[4][0][1];
        (p+4)->side[2][0] = col[4][2][2];
        (p+4)->side[2][1] = col[4][1][2];
        (p+4)->side[2][2] = col[4][0][2];
    }


    if (rot == 2){
        // changement pour la face Down
        for (k = 3; k > 2; k-=2) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][2] = col[k-2][i][2];
                }
            }
        }
        // changement pour la face Front
        for (k = 2; k < 3; k+=3) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k+3][2][0] ;
                    (p + k)->side[1][2] = col[k+3][1][0] ;
                    (p + k)->side[2][2] = col[k+3][0][0] ;


                }
            }
        }
        // changement pour la face Up
        for (k = 1; k < 2; k+=2) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][2] = col[k+2][i][2] ;
                }
            }
        }
        // changement pour la face Back
        for (k = 5; k > 4; k-=3) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k-3][2][2] ;
                    (p + k)->side[1][0] = col[k-3][1][2] ;
                    (p + k)->side[2][0] = col[k-3][0][2] ;


                }
            }
        }
        // changement pour la face right
        (p+4)->side[0][0] = col[4][2][2];
        (p+4)->side[0][1] = col[4][2][1];
        (p+4)->side[0][2] = col[4][2][0];
        (p+4)->side[1][0] = col[4][1][2];
        (p+4)->side[1][1] = col[4][1][1];
        (p+4)->side[1][2] = col[4][1][0];
        (p+4)->side[2][0] = col[4][0][2];
        (p+4)->side[2][1] = col[4][0][1];
        (p+4)->side[2][2] = col[4][0][0];

    }

    return p;
}

// Fonction qui reçoit un entier et un pointeur rubiks  qui va le retourner. Cette fonction permet de faire une rotation (quart de tour ou demi tour) sur la face  DOWN dans le sens de l'aiguille d'une montre
rubiks* down_clockwise(rubiks *p, int rot){
    int k, nbl = 3, i, j;
    T_COLOR col[6][3][3];

    // Copie du cube

    for (k = 0; k < 6; k++) {
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                col[k][i][j] = (p + k)->side[i][j];
            }
        }
    }

    // Pour quart de tour
    if (rot == 1){
        //changement pour la face Left
        for (k=0;k<5;k+=5){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k+5][2][j];
                }
            }
        }
        //changement pour la face Right
        for (k=4;k>3;k-=2){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k-2][2][j];
                }
            }
        }
        //changement pour la face back
        for (k=5;k>4;k-=1){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k-1][2][j];
                }
            }
        }
        //changement pour la face front
        for (k=2;k>0;k-=2){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k-2][2][j];
                }
            }
        }
        //changement pour la face down
        (p+3)->side[0][0] = col[3][2][0];
        (p+3)->side[0][1] = col[3][1][0];
        (p+3)->side[0][2] = col[3][0][0];
        (p+3)->side[1][0] = col[3][2][1];
        (p+3)->side[1][1] = col[3][1][1];
        (p+3)->side[1][2] = col[3][0][1];
        (p+3)->side[2][0] = col[3][2][2];
        (p+3)->side[2][1] = col[3][1][2];
        (p+3)->side[2][2] = col[3][0][2];

    }
    // Pour demi-tour
    if (rot == 2){
        //changement pour la face Left
        for (k=0;k<4;k+=4){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k+4][2][j];
                }
            }
        }
        //changement pour la face Right
        for (k=4;k>0;k-=4){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k-4][2][j];
                }
            }
        }
        //changement pour la face Back
        for (k=5;k>3;k-=3){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k-3][2][j];
                }
            }
        }
        //changement pour la face Front
        for (k=2;k<5;k+=3){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k+3][2][j];
                }
            }
        }
        //changement pour la face Down
        (p+3)->side[0][0] = col[3][2][2];
        (p+3)->side[0][1] = col[3][2][1];
        (p+3)->side[0][2] = col[3][2][0];
        (p+3)->side[1][0] = col[3][1][2];
        (p+3)->side[1][1] = col[3][1][1];
        (p+3)->side[1][2] = col[3][1][0];
        (p+3)->side[2][0] = col[3][0][2];
        (p+3)->side[2][1] = col[3][0][1];
        (p+3)->side[2][2] = col[3][0][0];


    }

    return p;
}


// Fonction qui reçoit un entier et un pointeur rubiks  qui va le retourner. Cette fonction permet de faire une rotation (quart de tour ou demi tour) sur la face  BACK dans le sens de l'aiguille d'une montre
rubiks* back_clockwise(rubiks *p, int rot){
    int k, nbl = 3, i, j;
    T_COLOR col[6][3][3];

    // Copie du cube
    for (k = 0; k < 6; k++) {
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                col[k][i][j] = (p + k)->side[i][j];
            }
        }
    }
    // Rotation quart de tour
    if (rot == 1){

        // changement pour la face Down
        for (k = 3; k < 4; k+=2) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][0] = col[k-3][0][0];
                    (p + k)->side[2][1] = col[k-3][1][0];
                    (p + k)->side[2][2] = col[k-3][2][0];
                }
            }
        }

        // changement pour la face Up
        for (k = 1; k < 2; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][0] = col[k+3][0][2] ;
                    (p + k)->side[0][1] = col[k+3][1][2] ;
                    (p + k)->side[0][2] = col[k+3][2][2] ;
                }
            }
        }

        // changement pour la face Left
        for (k = 0; k < 1; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl ; j++) {
                    (p + k)->side[0][0] = col[k+1][0][2] ;
                    (p + k)->side[1][0] = col[k+1][0][1] ;
                    (p + k)->side[2][0] = col[k+1][0][0] ;
                }
            }
        }


        // changement pour la face Right
        for (k = 4; k < 5; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][2] = col[k-1][2][2] ;
                    (p + k)->side[1][2] = col[k-1][2][1] ;
                    (p + k)->side[2][2] = col[k-1][2][0] ;
                }
            }
        }


        // changement pour la face Back
        (p+5)->side[0][0] = col[5][2][0];
        (p+5)->side[0][1] = col[5][1][0];
        (p+5)->side[0][2] = col[5][0][0];
        (p+5)->side[1][0] = col[5][2][1];
        (p+5)->side[1][1] = col[5][1][1];
        (p+5)->side[1][2] = col[5][0][1];
        (p+5)->side[2][0] = col[5][2][2];
        (p+5)->side[2][1] = col[5][1][2];
        (p+5)->side[2][2] = col[5][0][2];


    }

    // Rotation demi tour
    if (rot == 2){

        // changement pour la face Down
        for (k = 3; k < 4; k+=2) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[2][0] = col[k-2][0][2];
                    (p + k)->side[2][1] = col[k-2][0][1];
                    (p + k)->side[2][2] = col[k-2][0][0];
                }
            }
        }

        // changement pour la face Up
        for (k = 1; k < 2; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k+2][2][2] ;
                    (p + k)->side[0][1] = col[k+2][2][1] ;
                    (p + k)->side[0][2] = col[k+2][2][0] ;
                }
            }
        }

        // changement pour la face Left
        for (k = 0; k < 1; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k+4][2][2] ;
                    (p + k)->side[1][0] = col[k+4][1][2] ;
                    (p + k)->side[2][0] = col[k+4][0][2] ;
                }
            }
        }


        // changement pour la face Right
        for (k = 4; k < 5; k++) {
            for (i = 0; i <1; i++) {
                for (j = 0; j <1; j++) {
                    (p + k)->side[0][2] = col[k-4][2][0] ;
                    (p + k)->side[1][2] = col[k-4][1][0] ;
                    (p + k)->side[2][2] = col[k-4][0][0] ;
                }
            }
        }


        // changement pour la face Back
        (p+5)->side[0][0] = col[5][2][2];
        (p+5)->side[0][1] = col[5][2][1];
        (p+5)->side[0][2] = col[5][2][0];
        (p+5)->side[1][0] = col[5][1][2];
        (p+5)->side[1][1] = col[5][1][1];
        (p+5)->side[1][2] = col[5][1][0];
        (p+5)->side[2][0] = col[5][0][2];
        (p+5)->side[2][1] = col[5][0][1];
        (p+5)->side[2][2] = col[5][0][0];

    }
    return p;
}

// Fonction qui reçoit un entier et un pointeur rubiks  qui va le retourner. Cette fonction permet de faire une rotation (quart de tour ou demi tour) sur la face  FRONT dans le sens de l'aiguille d'une montre
rubiks* front_clockwise(rubiks *p, int rot){

    int k, nbl = 3, i, j;
    T_COLOR col[6][3][3];

    // Copie du cube

    for (k = 0; k < 6; k++) {
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                col[k][i][j] = (p + k)->side[i][j];
            }
        }
    }

    // Rotation quart de tour
    if (rot == 1) {

        // changement pour la face Down
        for (k = 3; k < 4; k += 2) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k + 1][2][0];
                    (p + k)->side[0][1] = col[k + 1][1][0];
                    (p + k)->side[0][2] = col[k + 1][0][0];
                }
            }
        }

        // changement pour la face Up
        for (k = 1; k < 2; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[2][0] = col[k - 1][2][2];
                    (p + k)->side[2][1] = col[k - 1][1][2];
                    (p + k)->side[2][2] = col[k - 1][0][2];
                }
            }
        }

        // changement pour la face Left
        for (k = 0; k < 1; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k + 3][0][0];
                    (p + k)->side[1][2] = col[k + 3][0][1];
                    (p + k)->side[2][2] = col[k + 3][0][2];
                }
            }
        }


        // changement pour la face Right
        for (k = 4; k < 5; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][0] = col[k - 3][2][0];
                    (p + k)->side[1][0] = col[k - 3][2][1];
                    (p + k)->side[2][0] = col[k - 3][2][2];
                }
            }
        }


        // changement pour la face Front
        (p + 2)->side[0][0] = col[2][2][0];
        (p + 2)->side[0][1] = col[2][1][0];
        (p + 2)->side[0][2] = col[2][0][0];
        (p + 2)->side[1][0] = col[2][2][1];
        (p + 2)->side[1][1] = col[2][1][1];
        (p + 2)->side[1][2] = col[2][0][1];
        (p + 2)->side[2][0] = col[2][2][2];
        (p + 2)->side[2][1] = col[2][1][2];
        (p + 2)->side[2][2] = col[2][0][2];

    }

    // Rotation demi-tour
    if(rot == 2){


        // changement pour la face Down
        for (k = 3; k < 4; k += 2) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k -2][2][2];
                    (p + k)->side[0][1] = col[k -2][2][1];
                    (p + k)->side[0][2] = col[k -2][2][0];
                }
            }
        }

        // changement pour la face Up
        for (k = 1; k < 2; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][0] = col[k + 2][0][2];
                    (p + k)->side[2][1] = col[k + 2][0][1];
                    (p + k)->side[2][2] = col[k + 2][0][0];
                }
            }
        }

        // changement pour la face Left
        for (k = 0; k < 1; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k + 4][2][0];
                    (p + k)->side[1][2] = col[k + 4][1][0];
                    (p + k)->side[2][2] = col[k + 4][0][0];
                }
            }
        }


        // changement pour la face Right
        for (k = 4; k < 5; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k - 4][2][2];
                    (p + k)->side[1][0] = col[k - 4][1][2];
                    (p + k)->side[2][0] = col[k - 4][0][2];
                }
            }
        }


        // changement pour la face Front
        (p+2)->side[0][0] = col[2][2][2];
        (p+2)->side[0][1] = col[2][2][1];
        (p+2)->side[0][2] = col[2][2][0];
        (p+2)->side[1][0] = col[2][1][2];
        (p+2)->side[1][1] = col[2][1][1];
        (p+2)->side[1][2] = col[2][1][0];
        (p+2)->side[2][0] = col[2][0][2];
        (p+2)->side[2][1] = col[2][0][1];
        (p+2)->side[2][2] = col[2][0][0];


    }
    return p;
}


// Fonction qui reçoit un entier et un pointeur rubiks  qui va le retourner. Cette fonction permet de faire une rotation (quart de tour ou demi tour) sur la face  UP dans le sens de l'aiguille d'une montre

rubiks* up_clockwise(rubiks *p, int rot){
    int k, nbl = 3, i, j;
    T_COLOR col[6][3][3];


    // Copie du cube
    for (k = 0; k < 6; k++) {
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                col[k][i][j] = (p + k)->side[i][j];
            }
        }
    }


    // Rotation quart de tour
    if (rot == 1) {
        // changement pour la face Left
        for (k = 0; k < 1; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k + 2][0][j];
                }
            }
        }

        // changement pour la face Right
        for (k = 4; k < 5; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k+1][0][j];
                }
            }
        }

        // changement pour la face Front
        for (k = 2; k < 3; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k+2][0][j];
                }
            }
        }

        // changement pour la face Back
        for (k = 5; k < 6; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k-5][0][j];
                }
            }
        }

        // changement pour la face UP
        (p + 1)->side[0][0] = col[1][2][0];
        (p + 1)->side[0][1] = col[1][1][0];
        (p + 1)->side[0][2] = col[1][0][0];
        (p + 1)->side[1][0] = col[1][2][1];
        (p + 1)->side[1][1] = col[1][1][1];
        (p + 1)->side[1][2] = col[1][0][1];
        (p + 1)->side[2][0] = col[1][2][2];
        (p + 1)->side[2][1] = col[1][1][2];
        (p + 1)->side[2][2] = col[1][0][2];
    }

    // Rotation demi tour
    if(rot == 2){
        // changement pour la face Left
        for (k = 0; k < 1; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k + 4][0][j];
                }
            }
        }

        // changement pour la face Right
        for (k = 4; k < 5; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k-4][0][j];
                }
            }
        }

        // changement pour la face Front
        for (k = 2; k < 3; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k+3][0][j];
                }
            }
        }

        // changement pour la face Back
        for (k = 5; k < 6; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k-3][0][j];
                }
            }
        }

        // changement pour la face UP
        (p+1)->side[0][0] = col[1][2][2];
        (p+1)->side[0][1] = col[1][2][1];
        (p+1)->side[0][2] = col[1][2][0];
        (p+1)->side[1][0] = col[1][1][2];
        (p+1)->side[1][1] = col[1][1][1];
        (p+1)->side[1][2] = col[1][1][0];
        (p+1)->side[2][0] = col[1][0][2];
        (p+1)->side[2][1] = col[1][0][1];
        (p+1)->side[2][2] = col[1][0][0];

    }
    return p;
}

// Fonction qui reçoit un entier et un pointeur rubiks  qui va le retourner. Cette fonction permet de faire une rotation (quart de tour ou demi tour) sur la face  FRONT dans le sens contraire de l'aiguille d'une montre
rubiks* front_anticlockwise(rubiks *p, int rot){
    int k, nbl = 3, i, j;
    T_COLOR col[6][3][3];

    // Copie du cube
    for (k = 0; k < 6; k++) {
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                col[k][i][j] = (p + k)->side[i][j];
            }
        }
    }

    // Rotation quart de tour
    if (rot == 1) {

        // changement pour la face Down
        for (k = 3; k < 4; k += 2) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k - 3][0][2];
                    (p + k)->side[0][1] = col[k - 3][1][2];
                    (p + k)->side[0][2] = col[k - 3][2][2];
                }
            }
        }

        // changement pour la face Up
        for (k = 1; k < 2; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[2][0] = col[k + 3][0][0];
                    (p + k)->side[2][1] = col[k + 3][1][0];
                    (p + k)->side[2][2] = col[k + 3][2][0];
                }
            }
        }

        // changement pour la face Left
        for (k = 0; k < 1; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k + 1][2][2];
                    (p + k)->side[1][2] = col[k + 1][2][1];
                    (p + k)->side[2][2] = col[k + 1][2][0];
                }
            }
        }


        // changement pour la face Right
        for (k = 4; k < 5; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k - 1][0][2];
                    (p + k)->side[1][0] = col[k - 1][0][1];
                    (p + k)->side[2][0] = col[k - 1][0][0];
                }
            }
        }


        // changement pour la face Front
        (p + 2)->side[0][0] = col[2][0][2];
        (p + 2)->side[0][1] = col[2][1][2];
        (p + 2)->side[0][2] = col[2][2][2];
        (p + 2)->side[1][0] = col[2][0][1];
        (p + 2)->side[1][1] = col[2][1][1];
        (p + 2)->side[1][2] = col[2][2][1];
        (p + 2)->side[2][0] = col[2][0][0];
        (p + 2)->side[2][1] = col[2][1][0];
        (p + 2)->side[2][2] = col[2][2][0];

    }

    // Rotation demi-tour

    if(rot == 2){


        // changement pour la face Down
        for (k = 3; k < 4; k += 2) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k -2][2][2];
                    (p + k)->side[0][1] = col[k -2][2][1];
                    (p + k)->side[0][2] = col[k -2][2][0];
                }
            }
        }

        // changement pour la face Up
        for (k = 1; k < 2; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[2][0] = col[k + 2][0][2];
                    (p + k)->side[2][1] = col[k + 2][0][1];
                    (p + k)->side[2][2] = col[k + 2][0][0];
                }
            }
        }

        // changement pour la face Left
        for (k = 0; k < 1; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k + 4][2][0];
                    (p + k)->side[1][2] = col[k + 4][1][0];
                    (p + k)->side[2][2] = col[k + 4][0][0];
                }
            }
        }


        // changement pour la face Right
        for (k = 4; k < 5; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k - 4][2][2];
                    (p + k)->side[1][0] = col[k - 4][1][2];
                    (p + k)->side[2][0] = col[k - 4][0][2];
                }
            }
        }


        // changement pour la face Front

        (p+2)->side[0][0] = col[2][2][2];
        (p+2)->side[0][1] = col[2][2][1];
        (p+2)->side[0][2] = col[2][2][0];
        (p+2)->side[1][0] = col[2][1][2];
        (p+2)->side[1][1] = col[2][1][1];
        (p+2)->side[1][2] = col[2][1][0];
        (p+2)->side[2][0] = col[2][0][2];
        (p+2)->side[2][1] = col[2][0][1];
        (p+2)->side[2][2] = col[2][0][0];





    }
    return p;
}

// Fonction qui reçoit un entier et un pointeur rubiks  qui va le retourner. Cette fonction permet de faire une rotation (quart de tour ou demi tour) sur la face  BACK dans le sens contraire de l'aiguille d'une montre

rubiks* back_anticlockwise(rubiks *p, int rot){
    int k, nbl = 3, i, j;
    T_COLOR col[6][3][3];

    // Copie du cube

    for (k = 0; k < 6; k++) {
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                col[k][i][j] = (p + k)->side[i][j];
            }
        }
    }

    // Rotation quart de tour
    if (rot == 1){

        // changement pour la face Down
        for (k = 3; k < 4; k+=2) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[2][0] = col[k+1][2][2];
                    (p + k)->side[2][1] = col[k+1][1][2];
                    (p + k)->side[2][2] = col[k+1][0][2];
                }
            }
        }

        // changement pour la face Up
        for (k = 1; k < 2; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k-1][2][0] ;
                    (p + k)->side[0][1] = col[k-1][1][0] ;
                    (p + k)->side[0][2] = col[k-1][0][0] ;
                }
            }
        }

        // changement pour la face Left
        for (k = 0; k < 1; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][0] = col[k+3][2][0] ;
                    (p + k)->side[1][0] = col[k+3][2][1] ;
                    (p + k)->side[2][0] = col[k+3][2][2] ;
                }
            }
        }


        // changement pour la face Right
        for (k = 4; k < 5; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][2] = col[k-3][0][0] ;
                    (p + k)->side[1][2] = col[k-3][0][1] ;
                    (p + k)->side[2][2] = col[k-3][0][2] ;
                }
            }
        }


        // changement pour la face Back
        (p + 5)->side[0][0] = col[5][0][2];
        (p + 5)->side[0][1] = col[5][1][2];
        (p + 5)->side[0][2] = col[5][2][2];
        (p + 5)->side[1][0] = col[5][0][1];
        (p + 5)->side[1][1] = col[5][1][1];
        (p + 5)->side[1][2] = col[5][2][1];
        (p + 5)->side[2][0] = col[5][0][0];
        (p + 5)->side[2][1] = col[5][1][0];
        (p + 5)->side[2][2] = col[5][2][0];


    }

    // Rotation demi tour

    if (rot == 2){

        // changement pour la face Down
        for (k = 3; k < 4; k+=2) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[2][0] = col[k-2][0][2];
                    (p + k)->side[2][1] = col[k-2][0][1];
                    (p + k)->side[2][2] = col[k-2][0][0];
                }
            }
        }

        // changement pour la face Up
        for (k = 1; k < 2; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k+2][2][2] ;
                    (p + k)->side[0][1] = col[k+2][2][1] ;
                    (p + k)->side[0][2] = col[k+2][2][0] ;
                }
            }
        }

        // changement pour la face Left
        for (k = 0; k < 1; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k+4][2][2] ;
                    (p + k)->side[1][0] = col[k+4][1][2] ;
                    (p + k)->side[2][0] = col[k+4][0][2] ;
                }
            }
        }


        // changement pour la face Right
        for (k = 4; k < 5; k++) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k-4][2][0] ;
                    (p + k)->side[1][2] = col[k-4][1][0] ;
                    (p + k)->side[2][2] = col[k-4][0][0] ;
                }
            }
        }


        // changement pour la face Back
        (p+5)->side[0][0] = col[5][2][2];
        (p+5)->side[0][1] = col[5][2][1];
        (p+5)->side[0][2] = col[5][2][0];
        (p+5)->side[1][0] = col[5][1][2];
        (p+5)->side[1][1] = col[5][1][1];
        (p+5)->side[1][2] = col[5][1][0];
        (p+5)->side[2][0] = col[5][0][2];
        (p+5)->side[2][1] = col[5][0][1];
        (p+5)->side[2][2] = col[5][0][0];

    }
    return p;

}


// Fonction qui reçoit un entier et un pointeur rubiks  qui va le retourner. Cette fonction permet de faire une rotation (quart de tour ou demi tour) sur la face  UP dans le sens contraire de l'aiguille d'une montre

rubiks* up_anticlockwise(rubiks *p, int rot){
    int k, nbl = 3, i, j;
    T_COLOR col[6][3][3];

    // Copie du cube
    for (k = 0; k < 6; k++) {
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                col[k][i][j] = (p + k)->side[i][j];
            }
        }
    }

    // Rotation quart de tour
    if (rot == 1) {
        // changement pour la face Left
        for (k = 0; k < 1; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k + 5][0][j];
                }
            }
        }

        // changement pour la face Right
        for (k = 4; k < 5; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k-2][0][j];
                }
            }
        }

        // changement pour la face Front
        for (k = 2; k < 3; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k-2][0][j];
                }
            }
        }

        // changement pour la face Back
        for (k = 5; k < 6; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k-1][0][j];
                }
            }
        }

        // changement pour la face UP
        (p + 1)->side[0][0] = col[1][0][2];
        (p + 1)->side[0][1] = col[1][1][2];
        (p + 1)->side[0][2] = col[1][2][2];
        (p + 1)->side[1][0] = col[1][0][1];
        (p + 1)->side[1][1] = col[1][1][1];
        (p + 1)->side[1][2] = col[1][2][1];
        (p + 1)->side[2][0] = col[1][0][0];
        (p + 1)->side[2][1] = col[1][1][0];
        (p + 1)->side[2][2] = col[1][2][0];
    }

    // Rotation demi-tour
    if(rot == 2){
        // changement pour la face Left
        for (k = 0; k < 1; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k + 4][0][j];
                }
            }
        }

        // changement pour la face Right
        for (k = 4; k < 5; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k-4][0][j];
                }
            }
        }

        // changement pour la face Front
        for (k = 2; k < 3; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k+3][0][j];
                }
            }
        }

        // changement pour la face Back
        for (k = 5; k < 6; k++) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[0][j] = col[k-3][0][j];
                }
            }
        }

        // changement pour la face UP
        (p+1)->side[0][0] = col[1][2][2];
        (p+1)->side[0][1] = col[1][2][1];
        (p+1)->side[0][2] = col[1][2][0];
        (p+1)->side[1][0] = col[1][1][2];
        (p+1)->side[1][1] = col[1][1][1];
        (p+1)->side[1][2] = col[1][1][0];
        (p+1)->side[2][0] = col[1][0][2];
        (p+1)->side[2][1] = col[1][0][1];
        (p+1)->side[2][2] = col[1][0][0];
    }
    return p;
}

// Fonction qui reçoit un entier et un pointeur rubiks  qui va le retourner. Cette fonction permet de faire une rotation (quart de tour ou demi tour) sur la face  DOWN dans le sens contraire de l'aiguille d'une montre
rubiks* down_anticlockwise(rubiks *p, int rot){
    int k, nbl = 3, i, j;
    T_COLOR col[6][3][3];

    // Copie du cube

    for (k = 0; k < 6; k++) {
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                col[k][i][j] = (p + k)->side[i][j];
            }
        }
    }


    // Rotation quart de tour
    if (rot == 1) {
        // changement pour la face Left
        for (k = 0; k < 2; k+=2) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k + 2][2][j];
                }
            }
        }
        //changement pour la face Right
        for (k = 4; k < 5; k+=1) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k + 1][2][j];
                }
            }
        }
        //changement pour la face Back
        for (k = 5; k > 0; k-=5) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k - 5][2][j];
                }
            }
        }
        //changement pour la face Front
        for (k = 2; k < 4; k+=2) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k + 2][2][j];
                }
            }
        }
        //changement pour la face down
        (p+3)->side[0][0] = col[3][0][2];
        (p+3)->side[0][1] = col[3][1][2];
        (p+3)->side[0][2] = col[3][2][2];
        (p+3)->side[1][0] = col[3][0][1];
        (p+3)->side[1][1] = col[3][1][1];
        (p+3)->side[1][2] = col[3][2][1];
        (p+3)->side[2][0] = col[3][0][0];
        (p+3)->side[2][1] = col[3][1][0];
        (p+3)->side[2][2] = col[3][2][0];


    }

    // rotation demi-tour
    if (rot == 2){
        // changement pour la face Left
        for (k=0;k<4;k+=4){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k+4][2][j];
                }
            }
        }
        //changement pour la face Right
        for (k=4;k>0;k-=4){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k-4][2][j];
                }
            }
        }
        //changement pour la face Back
        for (k=5;k>3;k-=3){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k-3][2][j];
                }
            }
        }
        //changement pour la face Front
        for (k=2;k<5;k+=3){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[2][j] = col[k+3][2][j];
                }
            }
        }
        //changement pour la face Down
        (p+3)->side[0][0] = col[3][2][2];
        (p+3)->side[0][1] = col[3][2][1];
        (p+3)->side[0][2] = col[3][2][0];
        (p+3)->side[1][0] = col[3][1][2];
        (p+3)->side[1][1] = col[3][1][1];
        (p+3)->side[1][2] = col[3][1][0];
        (p+3)->side[2][0] = col[3][0][2];
        (p+3)->side[2][1] = col[3][0][1];
        (p+3)->side[2][2] = col[3][0][0];

    }
    return p;
}

// Fonction qui reçoit un entier et un pointeur rubiks  qui va le retourner. Cette fonction permet de faire une rotation (quart de tour ou demi tour) sur la face  LEFT dans le sens contraire de l'aiguille d'une montre

rubiks* left_anticlockwise(rubiks *p, int rot){
    int k, nbl = 3, i, j;
    T_COLOR col[6][3][3];

    // Copie du cube
    for (k = 0; k < 6; k++) {
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                col[k][i][j] = (p + k)->side[i][j];
            }
        }
    }

    // Rotation quart de tour
    if (rot == 1){
        //changement pour la face Back
        for (k=5;k>1;k-=4){
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k-4][2][0];
                    (p + k)->side[1][2] = col[k-4][1][0];
                    (p + k)->side[2][2] = col[k-4][0][0];


                }
            }
        }
        //changement pour la face Front
        for (k=2;k<3;k+=1){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][0] = col[k+1][i][0];
                }
            }
        }
        //changement pour la face Down
        for (k=3;k<5;k+=2){
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k+2][2][2];
                    (p + k)->side[1][0] = col[k+2][1][2];
                    (p + k)->side[2][0] = col[k+2][0][2];

                }
            }
        }
        //changement pour la face Up
        for (k=1;k<2;k+=1){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][0] = col[k+1][i][0];
                }
            }
        }
        //changement pour la face Left
        (p+0)->side[0][0] = col[0][0][2];
        (p+0)->side[0][1] = col[0][1][2];
        (p+0)->side[0][2] = col[0][2][2];
        (p+0)->side[1][0] = col[0][0][1];
        (p+0)->side[1][1] = col[0][1][1];
        (p+0)->side[1][2] = col[0][2][1];
        (p+0)->side[2][0] = col[0][0][0];
        (p+0)->side[2][1] = col[0][1][0];
        (p+0)->side[2][2] = col[0][2][0];

    }

    // Rotation demi-tour
    if (rot == 2){
        //changement pour la face Back
        for (k=5;k>2;k-=3){
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k-3][2][0];
                    (p + k)->side[1][2] = col[k-3][1][0];
                    (p + k)->side[2][2] = col[k-3][0][0];


                }
            }
        }
        //changement pour la face Front
        for (k=2;k<5;k+=3){
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k+3][2][2];
                    (p + k)->side[1][0] = col[k+3][1][2];
                    (p + k)->side[2][0] = col[k+3][0][2];
                }
            }
        }
        //changement pour la face Down
        for (k=3;k>1;k-=2){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][0] = col[k-2][i][0];

                }
            }
        }
        //changement pour la face Up
        for (k=1;k<3;k+=2){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][0] = col[k+2][i][0];
                }
            }
        }
        //changement pour la face Left
        (p+0)->side[0][0] = col[0][2][2];
        (p+0)->side[0][1] = col[0][2][1];
        (p+0)->side[0][2] = col[0][2][0];
        (p+0)->side[1][0] = col[0][1][2];
        (p+0)->side[1][1] = col[0][1][1];
        (p+0)->side[1][2] = col[0][1][0];
        (p+0)->side[2][0] = col[0][0][2];
        (p+0)->side[2][1] = col[0][0][1];
        (p+0)->side[2][2] = col[0][0][0];
    }
    return p;
}


// Fonction qui reçoit un entier et un pointeur rubiks  qui va le retourner. Cette fonction permet de faire une rotation (quart de tour ou demi tour) sur la face RIGHT dans le sens contraire de l'aiguille d'une montre


rubiks* right_anticlockwise(rubiks *p, int rot){
    int k, nbl = 3, i, j;
    T_COLOR col[6][3][3];

    // Copie du cube

    for (k = 0; k < 6; k++) {
        for (i = 0; i < nbl; i++) {
            for (j = 0; j < nbl; j++) {
                col[k][i][j] = (p + k)->side[i][j];
            }
        }
    }

    // Rotation quart de tour
    if (rot == 1){
        //changement pour la face Back
        for (k=5;k>3;k-=2){
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k-2][2][2];
                    (p + k)->side[1][0] = col[k-2][1][2];
                    (p + k)->side[2][0] = col[k-2][0][2];
                }
            }
        }
        //changement pour la face Front
        for (k=2;k>1;k-=1){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][2] = col[k-1][i][2];
                }
            }
        }
        //changement pour la face Down
        for (k=3;k>2;k-=1){
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][2] = col[k-1][i][2];
                }
            }
        }
        //changement pour la face Up
        for (k=1;k<5;k+=4){
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k+4][2][0];
                    (p + k)->side[1][2] = col[k+4][1][0];
                    (p + k)->side[2][2] = col[k+4][0][0];
                }
            }
        }
        //changement pour la face Right
        (p+4)->side[0][0] = col[4][0][2];
        (p+4)->side[0][1] = col[4][1][2];
        (p+4)->side[0][2] = col[4][2][2];
        (p+4)->side[1][0] = col[4][0][1];
        (p+4)->side[1][1] = col[4][1][1];
        (p+4)->side[1][2] = col[4][2][1];
        (p+4)->side[2][0] = col[4][0][0];
        (p+4)->side[2][1] = col[4][1][0];
        (p+4)->side[2][2] = col[4][2][0];
    }
    // rotation demi-tour
    if (rot == 2){
        //changement pour la face Back
        for (k=5;k>2;k-=3){
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k-3][2][0];
                    (p + k)->side[1][0] = col[k-3][1][0];
                    (p + k)->side[2][0] = col[k-3][0][0];


                }
            }
        }
        //changement pour la face Front
        // changement pour la face Down
        for (k = 3; k > 2; k-=2) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][2] = col[k-2][i][2];
                }
            }
        }
        // changement pour la face Front
        for (k = 2; k < 3; k+=3) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][2] = col[k+3][2][0] ;
                    (p + k)->side[1][2] = col[k+3][1][0] ;
                    (p + k)->side[2][2] = col[k+3][0][0] ;


                }
            }
        }
        // changement pour la face Up
        for (k = 1; k < 2; k+=2) {
            for (i = 0; i < nbl; i++) {
                for (j = 0; j < nbl; j++) {
                    (p + k)->side[i][2] = col[k+2][i][2] ;
                }
            }
        }
        // changement pour la face Back
        for (k = 5; k > 4; k-=3) {
            for (i = 0; i < 1; i++) {
                for (j = 0; j < 1; j++) {
                    (p + k)->side[0][0] = col[k-3][2][2] ;
                    (p + k)->side[1][0] = col[k-3][1][2] ;
                    (p + k)->side[2][0] = col[k-3][0][2] ;


                }
            }
        }
        // changement pour la face right
        (p+4)->side[0][0] = col[4][2][2];
        (p+4)->side[0][1] = col[4][2][1];
        (p+4)->side[0][2] = col[4][2][0];
        (p+4)->side[1][0] = col[4][1][2];
        (p+4)->side[1][1] = col[4][1][1];
        (p+4)->side[1][2] = col[4][1][0];
        (p+4)->side[2][0] = col[4][0][2];
        (p+4)->side[2][1] = col[4][0][1];
        (p+4)->side[2][2] = col[4][0][0];

    }
    return p;
}


// Fonction qui reçoit un pointeur de rubiks et qui le retourne.  Cette fonction permet d'avoir un "menu" dans lequel l'utilisateur peut appliquer des mouvements en insérant un numéro
rubiks* move_rubiks(rubiks *p) {
    int r,t;

    do{
        do {
            printf("-------------------------------------------------\n");
            printf(" L : 0 | U : 1 | F : 2 | D : 3 | R : 4  | B : 5\n");
            printf(" L': 6 | U': 7 | F': 8 | D': 9 | R': 10 | B': 11\n");
            printf(" VERTICAL ROTATION: 12 | HORIZONTAL ROTATION :13\n ");
            printf("Quit 14\n");
            printf("-------------------------------------------------");
            printf("\nAction: ");
            scanf("%d", &r);
        }while(r<0 || r>14);
        //printf("\n");
        if(r<12){
            do{
                printf("Quart de Tour: 1 | Demi-tour: 2 :");
                scanf("%d",&t);
            }while(t!=1 && t!=2);
            printf("\n");
            switch (r) {
                case 0:
                    display_rubiks(left_clockwise(p,t));
                    break;
                case 1:
                    display_rubiks(up_clockwise(p,t));
                    break;
                case 2:
                    display_rubiks(front_clockwise(p,t));
                    break;
                case 3:
                    display_rubiks(down_clockwise(p,t));
                    break;
                case 4:
                    display_rubiks(right_clockwise(p,t));
                    break;
                case 5:
                    display_rubiks(back_clockwise(p,t));
                    break;
                case 6:
                    display_rubiks(left_anticlockwise(p,t));
                    break;
                case 7:
                    display_rubiks(up_anticlockwise(p,t));
                    break;
                case 8:
                    display_rubiks(front_anticlockwise(p,t));
                    break;
                case 9:
                    display_rubiks(down_anticlockwise(p,t));
                    break;
                case 10:
                    display_rubiks(right_anticlockwise(p,t));
                    break;
                case 11:
                    display_rubiks(back_anticlockwise(p,t));
                    break;

            }
        }
        if(r == 12)
            display_rubiks(vertical_rotation(p));

        if(r == 13)
            display_rubiks(horizontal_rotation(p));
        if (r==14)
            printf("\nMENU PRINCIPAL\n");

    }while(r!=14);  // Dès que l'utilisateur insérera le numéro 14 celui-ci sera renvoyé au menu principal

    return p;
}


// Fonction qui reçoit un pointeur de rubiks et qui retourne un entier. Même principe que le code précédent: l'utilisateur insérer un des numéros valide pour faire une action.
int menu(rubiks *p){
    int n;
    printf(" ---------------------------------------------------------------------------------------------\n");
    printf(" 1: Scramble   2: Reset    3: Blank   4: PLay   5: Fill   6: Solve   7: InitAllFaces   8: Quit\n");
    printf(" ---------------------------------------------------------------------------------------------\n");
    do{
        printf("Action: ");
        scanf("%d",&n);
    }while(n<1 || n>8);
    switch (n) {
        case 1 :
            return 1;
        case 2 :
            return 2;
        case 3 :
            return 3;
        case 4 :
            return 4;
        case 5 :
            return 5;
        case 6 :
            return 6;
        case 7 :
            return 7;
        case 8 :
            return 8;

    }
}

//Fonction qui reçoit un pointeur rubiks et le retourne qui fait une rotation horizontal q'un quart de tour
rubiks* horizontalq_rotation(rubiks *p){
    int k,size = 6, nbl = 3,i,j;
    T_COLOR col[6][3][3];

    // Copie du cube

    for(k=0 ; k<6;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                col[k][i][j] = (p+k)->side[i][j];
            }
        }
    }

    // FRONT prend les couleurs de LEFT
    for(k=0 ; k<1;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                (p+2)->side[i][j]=col[k][i][j];
            }
        }
    }

    // RIGHT prend les couleurs de FRONT
    for(k=2 ; k<3;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                (p+4)->side[i][j]=col[k][i][j];
            }
        }
    }

    // BACK prend les couleurs de RIGHT
    for(k=4 ; k<5;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                (p+5)->side[i][j]=col[k][i][j];
            }
        }
    }

    // LEFT prend les couleurs de BACK
    for(k=5 ; k<6;k++){
        for(i=0;i<nbl;i++){
            for(j=0;j<nbl;j++){
                (p+0)->side[i][j]=col[k][i][j];
            }
        }
    }

    return p;


}

//Fonctions de résolutions du Rubiks


//Fonction permettant de faire une croix parfaite sur la face UP dans certains cas. ELle reçoit le pointeur rubiks et le retourne
rubiks* perfectCross(rubiks *p){
    int k,i,j, b = 3;
    for(i=0;i<4;i++) {   // On fait 4 boucles pour faire sur toutes les faces horizontal
        do {            //Les if sont les différents cas donné dans l'énoncé où l'on peut appliquer l'algorithme proposé
            if ((p + 1)->side[0][1] == (p + 1)->side[1][0] && (p + 1)->side[1][1] == (p + 1)->side[0][1] &&
                (p + 2)->side[0][1] == (p + 1)->side[0][1] && (p + 1)->side[2][1] == (p + 2)->side[1][1] &&
                (p + 4)->side[0][1] == (p + 4)->side[1][1]) {
                printf("Pour realiser une croix blanche parfaite, il faut faire les mouvements suivants : F U' R U\n");
                front_clockwise(p, 1);
                up_anticlockwise(p, 1);
                right_clockwise(p, 1);
                up_clockwise(p, 1);
                display_rubiks(p);
                b = 2;
            }
            if ((p + 1)->side[0][1] == (p + 1)->side[1][0] && (p + 1)->side[1][1] == (p + 1)->side[0][1] &&
                (p + 1)->side[1][2] == (p + 1)->side[0][1] && (p + 2)->side[2][1] == (p + 1)->side[0][1] &&
                (p + 2)->side[1][1] != (p + 1)->side[0][1] && (p + 2)->side[1][1] != (p + 4)->side[0][1] &&
                (p + 4)->side[0][1] == R && (p + 4)->side[1][1] == R) {
                printf("Pour realiser une croix blanche parfaite, il faut faire les mouvements suivants : F' R' D' R F2'\n");
                front_anticlockwise(p, 1);
                right_anticlockwise(p, 1);
                down_anticlockwise(p, 1);
                right_clockwise(p, 1);
                front_anticlockwise(p, 2);
                display_rubiks(p);
                b = 2;
            }

            if ((p + 1)->side[0][1] == (p + 1)->side[1][0] && (p + 1)->side[1][1] == (p + 1)->side[0][1] &&
                (p + 1)->side[1][2] == (p + 1)->side[0][1] && (p + 2)->side[1][1] == (p + 4)->side[1][0] &&
                (p + 2)->side[1][2] == (p + 1)->side[0][1] && (p + 4)->side[0][1] == (p + 4)->side[1][1]) {
                printf("\nPour realiser une croix blanche parfaite, il faut faire les mouvements suivants : R' D' R F2'\n");
                right_anticlockwise(p, 1);
                down_anticlockwise(p, 1);
                right_clockwise(p, 1);
                front_anticlockwise(p, 2);
                display_rubiks(p);
                b = 2;
            }
            if ((p + 1)->side[1][1] == (p + 2)->side[0][1] && (p + 1)->side[2][1] == (p + 4)->side[1][1] &&
                (p + 2)->side[1][1] != (p + 1)->side[1][1] && (p + 2)->side[1][1] != (p + 1)->side[2][1]) {
                printf("\nPour realiser une croix blanche parfaite, il faut faire les mouvements suivants : F R\n");
                front_clockwise(p, 1);
                right_clockwise(p, 1);
                display_rubiks(p);
                b = 2;
            }
            if ((p + 1)->side[1][1] == (p + 4)->side[0][1] && (p + 1)->side[1][2] != (p + 4)->side[0][1] &&
                (p + 1)->side[1][2] != (p + 2)->side[1][1] && (p + 1)->side[1][2] != (p + 4)->side[1][1] &&
                (p + 2)->side[1][1] != (p + 4)->side[0][1] && (p + 2)->side[1][1] != (p + 1)->side[1][2] &&
                (p + 2)->side[1][1] != (p + 4)->side[1][1] && (p + 4)->side[1][1] != (p + 4)->side[0][1] &&
                (p + 4)->side[1][1] != (p + 2)->side[1][1] && (p + 4)->side[1][1] != (p + 1)->side[1][2]) {
                printf("\nPour realiser une croix blanche parfaite, il faut faire les mouvements suivants : R' F' U\n");
                right_anticlockwise(p, 1);
                front_anticlockwise(p, 1);
                up_clockwise(p, 1);
                display_rubiks(p);
                b = 2;
            }
            else
                b = 3;

        }while(b == 2);
        horizontalq_rotation(p);   // a chaque fin de boucle on tourne le cube horizontalement d'un quart
    }
    horizontalq_rotation(p);

    if (b == 3 ){
        printf("\nVous pouvez completer manuellement si il n'y a pas de croix parfaite\n\n");
    }

    return p;
}


// Fonction qui reçoit un pointeur de rubiks qui le retourne. Fonction qui permet de faire les coins blancs  si il y a une configuration précise est reconnue
rubiks* whitecones(rubiks *p) {
    int k, cpt = 0, nbl = 3, i, j, bol, boll = 3;

    for (i = 0; i < 4; i++) {  // On fait 4 boucles pour faire sur toutes les faces horizontal
        do {

            if (((((p + 2)->side[2][0]) == (p + 1)->side[1][1]) && ((((p + 0)->side[1][1]) == ((p + 0)->side[2][2])) &&(((p + 2)->side[1][1]) ==((p + 3)->side[0][0])))) ||((((p + 0)->side[2][2]) == (p + 1)->side[1][1]) && ((((p + 0)->side[1][1]) == ((p + 3)->side[0][0])) &&(((p + 2)->side[1][1]) ==((p + 2)->side[2][0])))) ||((((p + 3)->side[0][0]) == (p + 1)->side[1][1]) && ((((p + 0)->side[1][1]) == ((p + 2)->side[2][0])) &&(((p + 0)->side[2][2]) ==((p + 2)->side[1][1]))))) {
                cpt = 0;
                do {
                    right_anticlockwise(p, 1);
                    down_anticlockwise(p, 1);
                    right_clockwise(p, 1);
                    down_clockwise(p, 1);
                    cpt++;
                } while ((p + 1)->side[2][0] == (p + 1)->side[1][1]);
                printf("Les mouvements suivant %d fois sont effectues : R' D' R D\n",cpt);
                display_rubiks(p);
                boll = 2;
            }
            else {
                boll=3;
            }
        } while (boll == 2);
        horizontalq_rotation(p);
    }
    if(boll==3){
        printf("Si tous les coins ne sont pas faits, essayez de tourner la face down puis reessayez \n");
    }
    return p;
}

/*

 // Fonction whitecones mais verifie les cas et fait un algo spécifique (sans rotation du cube )

rubiks* whitecones(rubiks *p) {
    int k, cpt = 0, nbl = 3, i, j, bol, boll = 3;

    for (i = 0; i < 4; i++) {
        do {
            // Bleu/Orange
            if (((((p + 0)->side[2][0]) == (p + 1)->side[1][1]) && ((((p + 0)->side[1][1]) == ((p + 3)->side[2][0])) &&
                                                                    (((p + 5)->side[2][2]) ==
                                                                     ((p + 5)->side[1][1])))) ||
                ((((p + 5)->side[2][2]) == (p + 1)->side[1][1]) && ((((p + 0)->side[1][1]) == ((p + 0)->side[2][0])) &&
                                                                    (((p + 5)->side[1][1]) ==
                                                                     ((p + 3)->side[2][0])))) ||
                ((((p + 3)->side[2][0]) == (p + 1)->side[1][1]) && ((((p + 0)->side[1][1]) == ((p + 5)->side[2][2])) &&
                                                                    (((p + 5)->side[1][1]) ==
                                                                     ((p + 0)->side[2][0]))))) {
                do {
                    left_anticlockwise(p, 1);
                    down_anticlockwise(p, 1);
                    left_clockwise(p, 1);
                    down_clockwise(p, 1);
                    cpt++;
                } while ((p + 1)->side[0][0] == (p + 1)->side[1][1]);
                printf("Les mouvements suivant %d fois pour avoir un coin bien place (ORANGE/BLEUE): L' D' L D\n",
                       cpt);

                display_rubiks(p);
                boll = 2;
            }


            // Orange/Vert

            if (((((p + 2)->side[2][0]) == (p + 1)->side[1][1]) && ((((p + 0)->side[1][1]) == ((p + 0)->side[2][2])) &&
                                                                    (((p + 2)->side[1][1]) ==
                                                                     ((p + 3)->side[0][0])))) ||
                ((((p + 0)->side[2][2]) == (p + 1)->side[1][1]) && ((((p + 0)->side[1][1]) == ((p + 3)->side[0][0])) &&
                                                                    (((p + 2)->side[1][1]) ==
                                                                     ((p + 2)->side[2][0])))) ||
                ((((p + 3)->side[0][0]) == (p + 1)->side[1][1]) && ((((p + 0)->side[1][1]) == ((p + 2)->side[2][0])) &&
                                                                    (((p + 0)->side[2][2]) ==
                                                                     ((p + 2)->side[1][1]))))) {
                cpt = 0;
                do {
                    front_anticlockwise(p, 1);
                    down_anticlockwise(p, 1);
                    front_clockwise(p, 1);
                    down_clockwise(p, 1);
                    cpt++;
                } while ((p + 1)->side[2][0] == (p + 1)->side[1][1]);
                printf("Les mouvements suivant %d fois pour avoir un coin bien place (ORANGE/VERT): F' D' F D\n",
                       cpt);

                display_rubiks(p);
                boll = 2;


            }
            // Vert/Rouge
            if (((((p + 2)->side[2][2]) == (p + 1)->side[1][1]) && ((((p + 2)->side[1][1]) == ((p + 3)->side[0][2])) &&
                                                                    (((p + 4)->side[2][0]) ==
                                                                     ((p + 4)->side[1][1])))) ||
                ((((p + 4)->side[2][0]) == (p + 1)->side[1][1]) && ((((p + 2)->side[1][1]) == ((p + 2)->side[2][2])) &&
                                                                    (((p + 4)->side[1][1]) ==
                                                                     ((p + 3)->side[2][0])))) ||
                ((((p + 3)->side[0][2]) == (p + 1)->side[1][1]) && ((((p + 2)->side[1][1]) == ((p + 4)->side[2][0])) &&
                                                                    (((p + 4)->side[1][1]) ==
                                                                     ((p + 2)->side[2][2]))))) {
                cpt = 0;
                do {
                    right_anticlockwise(p, 1);
                    down_anticlockwise(p, 1);
                    right_clockwise(p, 1);
                    down_clockwise(p, 1);
                    cpt++;
                } while ((p + 1)->side[2][2] == (p + 1)->side[1][1]);
                printf("Les mouvements suivant %d fois pour avoir un coin bien place (VERT/ROUGE): R' D' R D\n",
                       cpt);

                display_rubiks(p);
                boll = 2;

            }


            if (((((p + 5)->side[2][0]) == (p + 1)->side[1][1]) && ((((p + 4)->side[1][1]) == ((p + 4)->side[2][2])) &&
                                                                    (((p + 5)->side[1][1]) ==
                                                                     ((p + 3)->side[2][2])))) ||
                ((((p + 4)->side[2][2]) == (p + 1)->side[1][1]) && ((((p + 4)->side[1][1]) == ((p + 3)->side[2][2])) &&
                                                                    (((p + 5)->side[1][1]) ==
                                                                     ((p + 5)->side[2][0])))) ||
                ((((p + 3)->side[2][2]) == (p + 1)->side[1][1]) && ((((p + 4)->side[1][1]) == ((p + 5)->side[2][0])) &&
                                                                    (((p + 5)->side[1][1]) ==
                                                                     ((p + 4)->side[2][2]))))) {
                cpt = 0;
                do {
                    back_anticlockwise(p, 1);
                    down_anticlockwise(p, 1);
                    back_clockwise(p, 1);
                    down_clockwise(p, 1);
                    cpt++;
                } while ((p + 1)->side[0][2] == (p + 1)->side[1][1]);
                printf("Les mouvements suivant %d fois pour avoir un coin bien place (ROUGE/BLEUE): B' D' B D\n",
                       cpt);

                display_rubiks(p);
                boll = 2;

            }
            else {
                boll=3;
            }
        } while (boll == 2);

    }
    if(boll==3){
        printf("Si tous les coins ne sont pas faits, essayez de tourner la face down puis réessayez \n");
    }
    return p;
}
*/

