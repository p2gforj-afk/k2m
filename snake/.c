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

struct liste_BFS { //liste chainee pour explorer la map avec un parcours en largeur
    int x; //coordonne en x de la case
    int y; //coordonne en y de la case
    action first_move; //report du premier move qui a conduit a cette case
    struct liste_BFS *next; //case suivante a explorer
};
typedef struct liste_BFS * bfs;
action parcours_largeur(char **map,int mapxsize,int mapysize,int x_debut,int y_debut,char GOAL) {
  char ma_map[mapysize][mapxsize]; // Copie de la map - permet de repertorier les visites
    for (int y = 0; y < mapysize; y++)
      for (int x = 0; x < mapxsize; x++)
        ma_map[y][x] = map[y][x];
  bfs debut = malloc(sizeof(*debut)); //premier maillon, permettra de free plus tard
  bfs fin = debut; //premet d'ajouter les nouveaux maillons a la fin
  debut->x = x_debut; //initialisation a la position x_debut
  debut->y = y_debut; //initialisation a la position y_debut
  debut->first_move = -1; //pas encore de first_move
  debut->next = NULL;
  ma_map[y_debut][x_debut] = WALL; // visite par default de la position initiale
  int dx[4] = { 0,  0,  1, -1}; //intialisation d'un vecteur pour chacune des direction, permet un truc cool juste apres
  int dy[4] = {-1,  1,  0,  0};
  action dirs[4] = {NORTH, SOUTH, EAST, WEST};
  bfs courant = debut; //designe le maillon dont on va explorer les voisins
  while (courant != NULL) { //il existe encore des cases a visiter
    if (map[courant->y][courant->x] == GOAL){ //GOALLLLLLLLLLLLLLLLLLLLLLLLLL
      action res = courant->first_move; //on note la direction initiale ayant menee a cette trouvaille
      while (debut != NULL) { //on free la liste
      bfs tmp = debut;
      debut = debut->next;
      free(tmp);
      }
      return res; //on renvoie la direction
    }
    int rd[4] = {-1,-1,-1,-1}; //ordre d'exploration des voisins qu'on rend aleatoire juste ici (truc cool)
    for(int k = 0; k<4; k++){ 
      int j = rand()%4;
      while (rd[0] == j || rd[1] == j ||rd[2] == j || rd[3] == j)
        j = rand()%4;
      rd[k] = j; //prend une valeur aleatoire entre 0 et 3, pas encore associee a un rd[k] precedent
    }
    for (int i = 0; i < 4; i++) { //exploration des voisins
      int nx = courant->x + dx[rd[i]];
      int ny = courant->y + dy[rd[i]];
      if (ma_map[ny][nx] != WALL && ma_map[ny][nx] != SNAKE_BODY && ma_map[ny][nx] != SNAKE_HEAD) { //si voisin safe
        bfs new = malloc(sizeof(*new)); //nouveau maillon pour ajouter la case a notre liste
        new->x = nx; //coordonnees de la nouvelle case
        new->y = ny;
        new->first_move = (courant->first_move == -1) //test pour soit reporter first_move, soit l'initialiser
                        ? dirs[rd[i]]
                        : courant->first_move;
        new->next = NULL;
        fin->next = new; //ajout du nouveau maillon a la fin de notre liste
        fin = new; //on remet la fin a la nouvelle fin
        ma_map[ny][nx] = WALL; //on marque la case comme visitee en y mettant un mur
      }
    }
    courant = courant->next; //on se place au prochain maillon pour continuer notre exploration
  }
  while (debut != NULL) { //il n'existe plus de case a visite, on free
    bfs tmp = debut;
    debut = debut->next;
    free(tmp);
  }
  return -1; //on renvoie -1, aucun chemin n'existe
}

typedef struct { int x, y; } Point;

void flood_fill(char **map, int mapxsize, int mapysize, int sx, int sy, bool *visited, int *size, bool *has_tail) {
    Point stack[mapxsize * mapysize];
    int top = 0;
    stack[top++] = (Point){sx, sy};
    visited[sy * mapxsize + sx] = true;
    *size = 0;
    *has_tail = false;

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {-1, 1, 0, 0};

    while(top > 0) {
        Point p = stack[--top];
        (*size)++;

        if(map[p.y][p.x] == SNAKE_TAIL) *has_tail = true;

        for(int d=0; d<4; d++) {
            int nx = p.x + dx[d];
            int ny = p.y + dy[d];
            if(nx < 0 || nx >= mapxsize || ny < 0 || ny >= mapysize) continue;
            if(visited[ny*mapxsize + nx]) continue;
            if(map[ny][nx] != PATH) continue;
            stack[top++] = (Point){nx, ny};
            visited[ny*mapxsize + nx] = true;
        }
    }
}

// Correction : soft-lock check qui prend en compte la taille du snake
bool creates_bad_region(char **map, int mapxsize, int mapysize, int snake_size) {
    bool visited[mapysize * mapxsize];
    for(int i=0; i<mapxsize*mapysize; i++) visited[i]=false;

    for(int y=0; y<mapysize; y++){
        for(int x=0; x<mapxsize; x++){
            if(!visited[y*mapxsize + x] && map[y][x] == PATH){
                int region_size = 0;
                bool has_tail = false;
                flood_fill(map, mapxsize, mapysize, x, y, visited, &region_size, &has_tail);

                // On ignore les petites régions <= snake_size
                if(!has_tail && region_size > snake_size && (region_size % 2 == 1)){
                    return true; // soft-lock possible
                }
            }
        }
    }
    return false;
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
    if(sh_map[y_debut][x_debut] == BONUS){
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
      int snake_size = 1;
      while(sshc->next != NULL){
        snake_size ++;
        sshc = sshc->next;
      }
      if ((parcours_largeur(sh_map,mapxsize,mapysize,x_debut,y_debut,SNAKE_TAIL) == -1) && (snake_size < mapsize)){ 
        while (*sh != NULL){
          shadow_list tmp = (*sh);
          (*sh) = (*sh)->next;
          free(tmp);
        }
        for(int y = 0; y < mapysize; y++)
          free(sh_map[y]);
        free(sh_map);
        return -1;
      }
      if (creates_bad_region(sh_map, mapxsize, mapysize, snake_size)) {
        while (*sh != NULL){
          shadow_list tmp = (*sh);
          *sh = (*sh)->next;
          free(tmp);
        }
        for(int y=0;y<mapysize;y++) 
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
    for (int i = 0; i < 4; i++) {
      int nx = x_debut + dx[rd[i]];
      int ny = y_debut + dy[rd[i]];
      if (sh_map[ny][nx] != WALL && sh_map[ny][nx] != SNAKE_BODY && sh_map[ny][nx] != SNAKE_HEAD) {
        if(NY(nx,ny,x_apple,y_apple) < min || min == -1){
            min = NY(nx,ny,x_apple,y_apple);
            shadow_id = i;
        }
      } 
    }
    if(shadow_id != -1){
      x_debut = x_debut + dx[rd[shadow_id]];
      y_debut = y_debut + dy[rd[shadow_id]];
      shadow_list new = malloc(sizeof(*new));
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

      snake_list new_head = malloc(sizeof(*new_head));
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
  while (sh_snake != NULL) {
    snake_list tmp = sh_snake;
    sh_snake = sh_snake->next;
    free(tmp);
  }
  for(int y = 0; y < mapysize; y++)
    free(sh_map[y]);
  free(sh_map);
  while (*sh != NULL){
    shadow_list tmp = (*sh);
    (*sh) = (*sh)->next;
    free(tmp);
  }
  return -1;
}

action shadow_victoire(char **map,int mapxsize,int mapysize,snake_list s,action last_action,shadow_list *sh) {
  while (*sh != NULL){
    action a = (*sh)->move;
    shadow_list tmp = (*sh);
    (*sh) = (*sh)->next;
    free(tmp);
    return a;
  }
  int x = s->x;
  int y = s->y;
  if (a_shadow_star(map, mapxsize, mapysize,x, y, s,&(*sh)) == -1)
    return parcours_largeur(map, mapxsize, mapysize,x, y, SNAKE_TAIL);
  action a = (*sh)->move;
  shadow_list tmp = (*sh);
  (*sh) = (*sh)->next;
  free(tmp);
  return a;
}

action snake(
	     char * * map,
	     int mapxsize,
	     int mapysize,
	     snake_list s,
	     action last_action
	     ) {
  static shadow_list shadow_move = NULL;
  if(last_action == - 1){
    srand(time(NULL));
    shadow_move = NULL;
  }
  return shadow_victoire(map,mapxsize,mapysize,s,last_action,&shadow_move);
}
