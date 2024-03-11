//
// Created by Clara on 05/05/2021.
//

/*
  Ce fichier contient la structure rubiks et toutes les entêtes des foncitons dans rubiks.c
 */

#ifndef PROJETRUBIKSCUBE_RUBIKS_H
#define PROJETRUBIKSCUBE_RUBIKS_H

typedef enum { R, B, G, W, Y, O, LG } T_COLOR ;
typedef enum { FRONT, BACK, UP, DOWN, RIGHT, LEFT } T_SIDE ;

typedef struct {
    T_SIDE **side;   // double pointeur de type T_SIDE qui sera une tableau 2D dynamique, représentant les lignes/colonnes d'une face
    T_COLOR color;   // Variable de type T_COLOR qui représente une couleur
}rubiks;

/*Fonction pour les types énumérés*/


int select_color(T_COLOR color);
int side_to_index(T_SIDE side);
void read_color(T_COLOR color);
T_SIDE index_to_side(int index);
T_COLOR index_to_color(int index);
T_SIDE word_to_side(char c);
T_COLOR opp_color(T_COLOR color);
int opp_side(int side);





/*Fonctions de réprésentation du cube */

rubiks* create_rubiks();
rubiks* init_rubiks(rubiks *p);
void free_rubiks(rubiks* p);
rubiks* init_rubiks_manu(rubiks *p);
rubiks* blank_rubiks(rubiks *p);
void display_rubiks(rubiks *p);
int fill_rubiks(rubiks *p);
int verifcentre(rubiks *p);
int check(rubiks *p);
rubiks* scramble_rubiks(rubiks *p);


/*Fonctions de mouvement*/

rubiks* left_clockwise(rubiks *p, int rot);
rubiks* right_clockwise(rubiks *p, int rot);
rubiks* down_clockwise(rubiks *p, int rot);
rubiks* up_clockwise(rubiks *p, int rot);
rubiks* back_clockwise(rubiks *p, int rot);
rubiks* front_clockwise(rubiks *p, int rot);
rubiks* front_anticlockwise(rubiks *p, int rot);
rubiks* back_anticlockwise(rubiks *p, int rot);
rubiks* up_anticlockwise(rubiks *p, int rot);
rubiks* down_anticlockwise(rubiks *p, int rot);
rubiks* left_anticlockwise(rubiks *p, int rot);
rubiks* right_anticlockwise(rubiks *p, int rot);
rubiks* horizontal_rotation(rubiks *p);
rubiks* vertical_rotation(rubiks *p);
rubiks* move_rubiks(rubiks * p);
int menu(rubiks *p);
rubiks* horizontalq_rotation(rubiks* p);


/*Fonctions de résolutions du Rubiks*/

rubiks* perfectCross(rubiks *p);
rubiks* whitecones(rubiks *p);





#endif //PROJETRUBIKSCUBE_RUBIKS_H

