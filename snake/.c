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


// Compte toutes les cases libres dans la map
int count_free_cells(char **map, int mapxsize, int mapysize) {
    int count = 0;
    for (int y = 0; y < mapysize; y++) {
        for (int x = 0; x < mapxsize; x++) {
            if (map[y][x] != WALL && map[y][x] != SNAKE_BODY && map[y][x] != SNAKE_HEAD) {
                count++;
            }
        }
    }
    return count;
}

// Compte les cases accessibles depuis (start_x, start_y) avec flood fill
int count_reachable(char **map, int mapxsize, int mapysize, int start_x, int start_y) {
    char temp_map[mapysize][mapxsize];
    for (int i = 0; i < mapysize; i++)
        for (int j = 0; j < mapxsize; j++)
            temp_map[i][j] = map[i][j];
    
    int count = 0;
    int stack_x[mapxsize * mapysize];
    int stack_y[mapxsize * mapysize];
    int top = 0;
    
    stack_x[top] = start_x;
    stack_y[top] = start_y;
    top++;
    temp_map[start_y][start_x] = WALL;
    
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {-1, 1, 0, 0};
    
    while (top > 0) {
        top--;
        int cx = stack_x[top];
        int cy = stack_y[top];
        count++;
        
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (temp_map[ny][nx] != WALL && 
                temp_map[ny][nx] != SNAKE_BODY && 
                temp_map[ny][nx] != SNAKE_HEAD) {
                temp_map[ny][nx] = WALL;
                stack_x[top] = nx;
                stack_y[top] = ny;
                top++;
            }
        }
    }
    return count;
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
    if(sh_map[y_debut][x_debut] == BONUS){ //GOALLLLLLAsOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
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
      if ((parcours_largeur(sh_map,mapxsize,mapysize,x_debut,y_debut,SNAKE_TAIL) == -1) && (snake_size < mapsize)){ 
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

// Remplace le bloc de choix de voisin dans a_shadow_star
// De "int min = -1;" jusqu'à "else flag = false;"

    int dx_local[4] = { 0,  0,  1, -1};
    int dy_local[4] = {-1,  1,  0,  0};
    
    // Évalue TOUS les voisins
    int best_id = -1;
    int best_dist = -1;
    
    for (int i = 0; i < 4; i++) {
      int nx = x_debut + dx_local[rd[i]];
      int ny = y_debut + dy_local[rd[i]];
      
      // Vérifie que c'est safe de base
      if (sh_map[ny][nx] == WALL || sh_map[ny][nx] == SNAKE_BODY || sh_map[ny][nx] == SNAKE_HEAD)
        continue;
      
      int dist = NY(nx, ny, x_apple, y_apple);
      
      // ===== VÉRIFICATION TOPOLOGIQUE GLOBALE =====
      // Simule le move complet sur une copie de la map
      char **test_map = malloc(sizeof(char*) * mapysize);
      for (int y = 0; y < mapysize; y++) {
        test_map[y] = malloc(sizeof(char) * mapxsize);
        for (int x = 0; x < mapxsize; x++)
          test_map[y][x] = sh_map[y][x];
      }
      
      // Simule le déplacement du snake
      test_map[ny][nx] = SNAKE_HEAD;
      test_map[y_debut][x_debut] = SNAKE_BODY;
      
      // Si on n'a pas mangé, la queue avance (libère une case)
      if (sh_map[ny][nx] != BONUS && sh_snake_fin != NULL) {
        test_map[sh_snake_fin->y][sh_snake_fin->x] = PATH;
      }
      
      // Compte le nombre total de cases libres
      int total_free = count_free_cells(test_map, mapxsize, mapysize);
      
      // Compte les cases accessibles depuis la nouvelle position
      int reachable = count_reachable(test_map, mapxsize, mapysize, nx, ny);
      
      // Free la test_map
      for (int y = 0; y < mapysize; y++)
        free(test_map[y]);
      free(test_map);
      
      // Si on ne peut pas atteindre toutes les cases libres = on crée un trou !
      bool creates_hole = (reachable < total_free);
      
      // Garde ce voisin s'il est meilleur et ne crée pas de trou
      if (!creates_hole && (dist < best_dist || best_dist == -1)) {
        best_dist = dist;
        best_id = i;
      }
    }
    
    if (best_id != -1) {
      int next_x = x_debut + dx_local[rd[best_id]]; 
      int next_y = y_debut + dy_local[rd[best_id]];
      
      x_debut = next_x; 
      y_debut = next_y;
      
      shadow_list new = malloc(sizeof(*new));
      new->move = dirs[rd[best_id]];
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
    else {
      flag = false;
    }
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
  while (*sh != NULL){
    action a = (*sh)->move;
    shadow_list tmp = (*sh);
    (*sh) = (*sh)->next;
    free(tmp);
    return a;
  }
  int x = s->x;
  int y = s->y;
  // action b = -1;
  if (a_shadow_star(map, mapxsize, mapysize,x, y, s,&(*sh)) == -1){
    /* b = parcours_largeur(map, mapxsize, mapysize,x, y, PATH);
    if (b != -1) {
      switch (b){
      case NORTH:
        if(parcours_largeur(map, mapxsize, mapysize, x, y-1, SNAKE_TAIL) != -1)
          return NORTH;
        break;
      case SOUTH:
        if(parcours_largeur(map, mapxsize, mapysize, x, y+1, SNAKE_TAIL) != -1 )
          return SOUTH;
        break;
      case EAST:
        if(parcours_largeur(map, mapxsize, mapysize, x+1, y, SNAKE_TAIL) != -1)
          return EAST;
        break;
      case WEST:
        if(parcours_largeur(map, mapxsize, mapysize, x-1, y, SNAKE_TAIL) != -1)
          return WEST;
        break;
      }
    }
    */
    return parcours_largeur(map, mapxsize, mapysize,x, y, SNAKE_TAIL);
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