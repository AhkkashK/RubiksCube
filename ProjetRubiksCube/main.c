#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"
#include "conio.h"


/*
 Ce fichier contient le programme principal.
 */

//Dans la fonction main, nous avons en premier tamps l'affichage du menu et l'afficheage du rubiks initialisé.
int main() {          //Puis en fonction de ce que rentre l'utilisateur, une fonction est appliqué sur le cube
    rubiks *p;
    int c;
    int bol = 1,i;
    p = create_rubiks();
    init_rubiks(p);
    c_textcolor(WHITE);
    printf(" ---------------------------------------------------------------------------------------------\n");
    printf(" 1: Scramble   2: Reset    3: Blank   4: PLay   5: Fill   6: Solve   7: InitAllFaces   8: Quit\n");
    printf(" ---------------------------------------------------------------------------------------------\n");
    printf("\n");
    display_rubiks(p);
    printf("\n");
    do{
        i=menu(p);         //permet d'afficher le menu principal après le premier affichage du menu
        switch (i) {

            case 1:              //les différents cas correspondent aux différentes options applicable, et énoncé dans le menu
                display_rubiks(scramble_rubiks(p));
                break;
            case 2:
                display_rubiks(init_rubiks(p));
                break;
            case 3:
                display_rubiks(blank_rubiks(p));
                break;
            case 4:
                display_rubiks(move_rubiks(p));
                break;
            case 5:
                fill_rubiks(p);
                break;
            case 6:
                display_rubiks(perfectCross(p));
                do {
                    printf("Voulez vous passez a l'etape suivante ?\n1 : oui 2 : non \n");
                    scanf("%d", &c);
                }while(c != 1 && c != 2);
                if (c == 1)
                    display_rubiks(whitecones(p));
                else
                    display_rubiks(perfectCross(p));
                break;
            case 7:
                display_rubiks(init_rubiks_manu(p));
                break;
            case 8:
                bol = 2;
                break;
        }

    } while (bol == 1);
    free_rubiks(p);      //libère le rubiks à la fin
    printf("\nAu revoir !\n");
    return 0;

}


