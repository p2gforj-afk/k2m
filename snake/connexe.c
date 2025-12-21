// compiler's header files
#include <stdbool.h> // bool, true, false
#include <stdlib.h> // rand, srand
#include <stdio.h> // printf
#include <time.h> // time

// main program's header file
#include "snake_def.h"
#include "snake_dec.h"

// student name goes here
char * student="Chaigne"; //c'est moi

#define ALEA 1 // entier de 1 a inf, ainversement proportionelle au nombre de neuronne du snake

struct liste_BFS { //liste chainee pour explorer la map avec un parcours en largeur
    int x; //coordonne en x de la case
    int y; //coordonne en y de la case
    action first_move; //report du premier move qui a conduit a cette case
    struct liste_BFS *next; //case suivante a explorer
};
typedef struct liste_BFS * bfs;
int trou_connexe(char **map,int mapxsize, int mapysize){
    char map_c[mapysize][mapxsize]; // Copie de la map - permet de repertorier les visites
    int nb_trou = 0;
    int nb_trou_c = 0;
    int x_trou;
    int y_trou;
    for (int y = 0; y < mapysize; y++)
        for (int x = 0; x < mapxsize; x++){
            map_c[y][x] = map[y][x];
            if(map[y][x]  == PATH || map[y][x] == BONUS){
                x_trou = x;
                y_trou = y;
                nb_trou ++;
            } 
        }
    bfs explo_trou = malloc(sizeof(*explo_trou));
    explo_trou->x = x_trou;
    explo_trou->y = y_trou;
    explo_trou->next = NULL;
    bfs fin_trou = explo_trou;
    bfs courant_trou = explo_trou;
    int dx[4] = {1,0,-1,0};
    int dy[4] = {0,-1,0,1};
    map_c[courant_trou->y][courant_trou->x] = WALL; //visite du premier trou
    nb_trou_c ++; 
    while(courant_trou != NULL){
        for(int i = 0; i<4; i++){
            int nx = courant_trou->x + dx[i];
            int ny = courant_trou->y + dy[i];
            if (map_c[ny][nx] == PATH || map_c[ny][nx] == BONUS) { //si voisin trou
                bfs new = malloc(sizeof(*new)); //nouveau maillon pour ajouter le trou a notre liste
                new->x = nx; //coordonnees du nouveau trou
                new->y = ny;
                new->next = NULL;
                fin_trou->next = new; //ajout du trou a la fin de notre liste
                fin_trou = new; //on remet la fin a la nouvelle fin
                map_c[ny][nx] = WALL; //visite du nouveau trou
                nb_trou_c ++;
            }
        }
    courant_trou = courant_trou->next; //on se place au prochain trou
    }
    while (explo_trou != NULL){
        bfs tmp = explo_trou;
        explo_trou = explo_trou->next;
        free(tmp);
    }
    return(nb_trou_c == nb_trou);
}

int abs(int a){
  return a - 2*a*(a<0);
}
int NY(int Xa, int Ya, int Xs, int Ys){
  return abs(Xs - Xa) + abs(Ys - Ya);
}

struct SHADOW{
  action move;
  struct SHADOW *next;
};
typedef struct SHADOW *shadow_list; 

int a_shadow_star(char **map,int mapxsize,int mapysize,int x_debut,int y_debut,snake_list ssh,shadow_list *sh){
  shadow_list last_move = *sh;
  snake_list sshc = ssh;
  int y_apple = 1; // position de la pomme
  int x_apple = 1;
  while(map[y_apple][x_apple] != BONUS){ 
    y_apple++;
    if (y_apple == mapysize){
      y_apple = 1;
      x_apple++;
    }
  }
  char **sh_map = malloc(sizeof(char*) * mapysize); // shadow_map 
    for (int y = 0; y < mapysize; y++){
      sh_map[y] = malloc(sizeof(char) * mapxsize);
      for (int x = 0; x < mapxsize; x++)
        sh_map[y][x] = map[y][x];
    }
  snake_list sh_snake = malloc(sizeof(*sh_snake)); //shadow_snake
  sh_snake->c = ssh->c;
  sh_snake->x = ssh->x;
  sh_snake->y = ssh->y;
  snake_list sh_snake_fin = sh_snake;
  while(ssh->next != NULL){
    snake_list new = malloc(sizeof(*new));
    new->c = ssh->next->c;
    new->x = ssh->next->x;
    new->y = ssh->next->y;
    sh_snake_fin->next = new;
    sh_snake_fin = sh_snake_fin->next;
    ssh = ssh->next;
  }
  sh_snake_fin->next = NULL;

  int dx[4] = { 0,  0,  1, -1};
  int dy[4] = {-1,  1,  0,  0};
  action dirs[4] = {NORTH, SOUTH, EAST, WEST};
  bool flag = true;

  while(flag){
    if(sh_map[y_debut][x_debut] == BONUS){ //GOALLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
      sh_map[y_debut][x_debut] = SNAKE_HEAD;
      while (sh_snake != NULL) {   //free shadow_snake
      snake_list tmp = sh_snake;
      sh_snake = sh_snake->next;
      free(tmp);
      }
      if (sshc->next == NULL){        
        for(int y = 0; y < mapysize; y++)
          free(sh_map[y]);
        free(sh_map);
        return 0;
      }
      int mapsize = -1;
      for (int y = 0; y < mapysize; y++)
        for (int x = 0; x < mapxsize; x++)
          if (map[y][x] !=WALL)
            mapsize ++;
      int snake_size = 1; //on calcule la taille de snake - sur certaines maps la fin de partie est impossible donc on va la forcer -
      while(sshc->next != NULL){
        snake_size ++;
        sshc = sshc->next;
      }
      if ((trou_connexe(sh_map, mapxsize, mapysize) == 0) && (snake_size < mapsize)){ 
        while (*sh != NULL){ //clear de la shadow list car chemin guezz
          shadow_list tmp = (*sh);
          (*sh) = (*sh)->next;
          free(tmp);
        }
        for(int y = 0; y < mapysize; y++)
          free(sh_map[y]);
        free(sh_map);
        return -1;
      }
      for(int y = 0; y < mapysize; y++)
        free(sh_map[y]);
      free(sh_map);
      int nb_action = 0;
      shadow_list action = *sh;
      while(action->next != NULL){
        nb_action++;
        action = action->next;
      }    
      int n = 10 + rand()%(mapxsize - 13);
      printf("\033[33m"); 
      for (int i = 0; i < n; i++)
        printf("*");
      printf("\033[0m"); 

      printf("\033[95m%d\033[0m\n",nb_action);

      return 0; 
    }
    sh_map[y_debut][x_debut] = SNAKE_HEAD;
    int rd[4] = {-1,-1,-1,-1};
    for(int k = 0; k<4; k++){ 
      int j = rand()%4;
      while (rd[0] == j || rd[1] == j ||rd[2] == j || rd[3] == j)
        j = rand()%4;
      rd[k] = j; 
    }
    int min = -1;
    int shadow_id = -1;
    for (int i = 0; i < 4; i++) { //exploration des voisins
      int nx = x_debut + dx[rd[i]];
      int ny = y_debut + dy[rd[i]];
      if (sh_map[ny][nx] != WALL && sh_map[ny][nx] != SNAKE_BODY && sh_map[ny][nx] != SNAKE_HEAD) { //si voisin safe
        // va falloir conserver le meilleur i voila
        if(NY(nx,ny,x_apple,y_apple) < min || min == -1){
          if(rand()%ALEA == 0) //vous vous en doutez on fait des choses etranges ici
            min = NY(nx,ny,x_apple,y_apple);
          shadow_id = i;
        }
      } 
    }
    if(shadow_id != -1){
      x_debut = x_debut + dx[rd[shadow_id]]; //update de la position dans le a*
      y_debut = y_debut + dy[rd[shadow_id]];
      shadow_list new = malloc(sizeof(*new)); //ajout du move a shadow_move
      new->move = dirs[rd[shadow_id]];
      new->next = NULL;
      if (*sh == NULL){
        *sh = new;
        last_move = new;
      }
      else {
        last_move->next = new;
        last_move = last_move->next;
      }

      snake_list new_head = malloc(sizeof(*new_head));//update shadow snake et se souvenir de l'ancienne position de la queue ie tempo
      new_head->c = SNAKE_HEAD;
      new_head->x = x_debut;
      new_head->y = y_debut;
      new_head->next = sh_snake;
      sh_snake = new_head;

      snake_list sh_snake_new_fin = sh_snake;
      while(sh_snake_new_fin->next != sh_snake_fin){
        sh_snake_new_fin = sh_snake_new_fin->next;
      }
      sh_snake_new_fin->c = SNAKE_HEAD;
      snake_list tempo = sh_snake_fin;
      if(sh_snake_new_fin != sh_snake)
        sh_snake_new_fin->c = SNAKE_TAIL;
      sh_snake_fin = sh_snake_new_fin;
      sh_snake_fin->next = NULL;
      //update de la map mmt trivial
      if(sh_map[sh_snake->y][sh_snake->x] != BONUS)
        sh_map[tempo->y][tempo->x] = PATH;
      free(tempo);
      if (sh_snake->next != NULL){
        if(sh_map[sh_snake->y][sh_snake->x] != BONUS)
          sh_map[sh_snake_fin->y][sh_snake_fin->x] = sh_snake_fin->c;
        sh_map[sh_snake->next->y][sh_snake->next->x] = sh_snake->next->c;
      }
    }
    else flag = false;
  }
  while (sh_snake != NULL) {   //free shadow_snake
  snake_list tmp = sh_snake;
  sh_snake = sh_snake->next;
  free(tmp);
  }
  for(int y = 0; y < mapysize; y++)
    free(sh_map[y]);
  free(sh_map);
  while (*sh != NULL){ //clear de la shadow list car chemin guezz
    shadow_list tmp = (*sh);
    (*sh) = (*sh)->next;
    free(tmp);
  }
  return -1;
}

action shadow_victoire(char **map,int mapxsize,int mapysize,snake_list s,action last_action,shadow_list *sh) {
  if(trou_connexe(map, mapxsize, mapysize) == 0){
    printf("PUE LA MERDE\n");
  }
  while (*sh != NULL){
    action a = (*sh)->move;
    shadow_list tmp = (*sh);
    (*sh) = (*sh)->next;
    free(tmp);
    return a;
  }
  int x = s->x;
  int y = s->y;
  if (a_shadow_star(map, mapxsize, mapysize,x, y, s,&(*sh)) == -1){
    int dx[4] = { 0,  0,  1, -1};
    int dy[4] = {-1,  1,  0,  0};
    action dirs[4] = {NORTH, SOUTH, EAST, WEST};
    int rd[4] = {-1,-1,-1,-1};
    for(int k = 0; k<4; k++){ 
      int j = rand()%4;
      while (rd[0] == j || rd[1] == j ||rd[2] == j || rd[3] == j)
        j = rand()%4;
      rd[k] = j; 
    }
    for (int i = 0; i < 4; i++) { //exploration des voisins
      int nx = x + dx[rd[i]];
      int ny = y + dy[rd[i]];
      if (map[ny][nx] != WALL && map[ny][nx] != SNAKE_BODY && map[ny][nx] != SNAKE_HEAD) { //si voisin safe
        char **tigre = malloc(sizeof(char*) * mapysize); //faire tigre, en considerant que ce chient peut bouffer une pomme
        for (int y = 0; y < mapysize; y++){
            tigre[y] = malloc(sizeof(char) * mapxsize);
            for (int x = 0; x < mapxsize; x++)
                tigre[y][x] = map[y][x];
        }
        if (tigre[ny][nx] != BONUS){
            snake_list ss = s;
            while (ss->next != NULL){
                ss = ss->next;
            }
            tigre[ss->y][ss->x] = WALL;
        }
        tigre[ny][nx] = WALL;
        action b = -1;
        if(trou_connexe(tigre,mapxsize,mapysize) == 1)
            b = dirs[i];
        for(int y = 0; y < mapysize; y++)
            free(tigre[y]);
        free(tigre);
        if (b != -1)
            return b;
      } 
    }   
  } 
  action a = (*sh)->move;
  shadow_list tmp = (*sh);
  (*sh) = (*sh)->next;
  free(tmp);
  return a;
}
/*
  snake fonction de base
*/
action snake(
	     char * * map, // array of chars modeling the game map
	     int mapxsize, // x size of the map
	     int mapysize, // y size of the map
	     snake_list s, // snake coded as a linked list
	     action last_action // last action made, set to -1 in the beginning
	     ) {
  static shadow_list shadow_move = NULL;
  if(last_action == - 1){
    srand(time(NULL)); //on initialise la seed de l'execution
    shadow_move = NULL;
  }
  return shadow_victoire(map,mapxsize,mapysize,s,last_action,&shadow_move);
}