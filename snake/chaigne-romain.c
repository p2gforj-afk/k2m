// compiler's header files
#include <stdbool.h> // bool, true, false
#include <stdlib.h> // rand
#include <stdio.h> // printf

// main program's header file
#include "snake_def.h"
#include "snake_dec.h"

// student name goes here
char * student="Chaigne"; 

// prototypes of the local/private functions
static void printAction(action);
static void printBoolean(bool);

/*
  snake function called from the main program
  This function randomly selects a valid move for Snake based on its current position on the game map
*/

action aleatoire(char * * map, int mapxsize, int mapysize, snake_list s, action last_action ){
  bool ok=false;  // ok will be set to true as soon as a randomly selected action is valid
  action a;
  do {
    a=rand()%4; // ramdomly select one of the 4 possible actions: 0=NORTH, 1=EAST, 2=SOUTH, 3=WEST

    if(DEBUG) { // print the randomly selected action, only in DEBUG mode
      printf("Candidate action is: ");
      printAction(a);
      printf("\n");
    }

    switch(a) { // check whether the randomly selected action is valid, i.e., if its preconditions are satisfied 
    case NORTH: // going toward this direction does not put snake's head into
      if(map[s->y-1][s->x]!=WALL // a wall
	      && map[s->y-1][s->x]!=SNAKE_BODY // snake's body
	      && map[s->y-1][s->x]!=SNAKE_TAIL) // snake's tail
	      ok=true; // this direction is safe, hence valid!
      break;
    case EAST: // going toward this direction does not put snake's head into
      if(map[s->y][s->x+1]!=WALL // a wall
	      && map[s->y][s->x+1]!=SNAKE_BODY // snake's body
	      && map[s->y][s->x+1]!=SNAKE_TAIL) // snake's tail
	      ok=true; // this direction is safe, hence valid!
      break;
    case SOUTH: // going toward this direction does not put snake's head into
      if(map[s->y+1][s->x]!=WALL // a wall
	      && map[s->y+1][s->x]!=SNAKE_BODY // snake's body
	      && map[s->y+1][s->x]!=SNAKE_TAIL) // snake's tail
	    ok=true; // this direction is safe, hence valid!
      break;
    case WEST: // going toward this direction does not put snake's head into
      if(map[s->y][s->x-1]!=WALL // a wall
	      && map[s->y][s->x-1]!=SNAKE_BODY // snake's body
	      && map[s->y][s->x-1]!=SNAKE_TAIL) // snake's tail
	      ok=true; // this direction is safe, hence valid!
      break;
    }

    if(DEBUG) { // print whether the randomly selected action is valid, only in DEBUG mode
      printf("Is this candidate action valid? ");
      printBoolean(ok);
      printf("\n");
    }
  // while the selected action is not valid and there exists a valide move
  } while(!ok && (map[s->y-1][s->x]==PATH || map[s->y-1][s->x]==BONUS  
		  || map[s->y][s->x+1]==PATH || map[s->y][s->x+1]==BONUS
		  || map[s->y+1][s->x]==PATH || map[s->y+1][s->x]==BONUS
		  || map[s->y][s->x-1]==PATH || map[s->y][s->x-1]==BONUS));
    
  return a;
}

action victoire_ou_defaite_si_la_map_ne_convient_pas(char * * map, int mapxsize, int mapysize, snake_list s, action last_action ){
// on suit un chemin assurant la victoire - peut echouer si la map est impaire x impaire ou mur
  if(mapxsize%2 == 1 && mapysize%2 == 1){
    printf("fin des reves");
    return 0;
  }
  int x_head = s->x;
  int y_head = s->y;
  if (mapxsize%2 == 0){
    if(y_head == 1 && x_head > 1){ //en haut on va a gauche
      return WEST;
    }
    if(x_head ==  mapxsize-2 && y_head == 2){ //fin du serpentin on remonte vers le couloir du haut
      return NORTH;
    }
    if(x_head%2 == 1 && y_head < mapysize-2){ //serpentin
      return SOUTH;
    }
    if(x_head%2 == 0 && y_head >2){
      return NORTH;
    }
    return EAST;
  }
  else{
    if(x_head == 1 && y_head > 1){ //a gauche on va en haut
      return NORTH;
    }
    if(y_head ==  mapysize-2 && x_head == 2){//fin du serpentin on va dans le couloir de gauche
      return WEST;
    }
    if(y_head%2 == 1 && x_head < mapxsize-2){
      return EAST;
    }
    if(y_head%2 == 0 && x_head >2){
      return NORTH;
    }
    return SOUTH;
  }
}

struct liste_BFS {
                int x; 
                int y; 
                struct liste_BFS * next;};
typedef struct liste_BFS * bfs;

int parcours_largeur(char **map, int mapxsize, int mapysize,int x_debut, int y_debut,char GOAL, action premiere_action){
  char ma_map[mapysize][mapxsize]; //copie local de la map
  for (int i=0; i<mapysize; i++){
    for (int j=0; j<mapxsize; j++){
      ma_map[i][j] = map[i][j];
    }
  }
  bfs debut = malloc(sizeof(struct liste_BFS));
  bfs fin = debut;
  //intialisation de debut
  switch (premiere_action) {
    case NORTH: 
      debut->x = x_debut;     
      debut->y = y_debut - 1; 
      break;
    case SOUTH: 
      debut->x = x_debut;     
      debut->y = y_debut + 1; break;
    case EAST:  
      debut->x = x_debut + 1; 
      debut->y = y_debut;     
      break;
    case WEST:  
      debut->x = x_debut - 1; 
      debut->y = y_debut;     
      break;
    }
    debut->next = NULL;

  //si on peut rien faire
  if (ma_map[debut->y][debut->x] == WALL ||
      ma_map[debut->y][debut->x] == SNAKE_BODY ||
      ma_map[debut->y][debut->x] == SNAKE_HEAD) {
    free(debut);
    return -1;
  }

  ma_map[debut->y][debut->x] = WALL; //vu
  bfs courant = debut;
  while (courant != NULL) {
    if (ma_map[courant->y][courant->x] == GOAL) {
      // free
      while (debut != NULL) {
      bfs tmp = debut;
      debut = debut->next;
      free(tmp);
      }
      return 0; //le chemin existe
    }
    int dx[4] = {-1, 0, 0, 1};
    int dy[4] = {0, -1, 1, 0};

    for (int i = 0; i < 4; i++) {
      int nx = courant->x + dx[i];
      int ny = courant->y + dy[i];
      if (ma_map[ny][nx] != WALL &&
          ma_map[ny][nx] != SNAKE_BODY &&
          ma_map[ny][nx] != SNAKE_HEAD){
        bfs new = malloc(sizeof(struct liste_BFS));
        new->x = nx;
        new->y = ny;
        new->next = NULL;
        fin->next = new;
        fin = new;
        ma_map[ny][nx] = WALL; //vu
      }
    }
    courant = courant->next;
    }
    //pas d'issue
    while (debut != NULL) {
        bfs tmp = debut;
        debut = debut->next;
        free(tmp);
    }
    return -1;
}

action victoire(char * * map, int mapxsize, int mapysize, snake_list s, action last_action){
//BFS entre tete et pomme 
//si un chemin existe
  //regarde si prochaine position de la tete peut rejoindre la queue
  //si oui, move valide on le fait
//si pas de chemin ou prochaine postition non valide, on suit notre queue (avec BFS)
// si ya pas aleatoire - normalement ya mais bon -
  int y_serpent = s->y;
  int x_serpent = s->x;
  if(parcours_largeur(map,mapxsize,mapysize,x_serpent,y_serpent,BONUS, NORTH) != -1 
  && (parcours_largeur(map,mapxsize,mapysize,x_serpent,y_serpent,SNAKE_TAIL, NORTH) != -1 || s->next == NULL)){
        return NORTH;
      }
  if(parcours_largeur(map,mapxsize,mapysize,x_serpent,y_serpent,BONUS, SOUTH) != -1 
  && (parcours_largeur(map,mapxsize,mapysize,x_serpent,y_serpent,SNAKE_TAIL, SOUTH) != -1 || s->next == NULL)){
        return SOUTH;
      }
  if(parcours_largeur(map,mapxsize,mapysize,x_serpent,y_serpent,BONUS, EAST) != -1 
  && (parcours_largeur(map,mapxsize,mapysize,x_serpent,y_serpent,SNAKE_TAIL, EAST) != -1 || s->next == NULL)){
        return EAST;
      }
  if(parcours_largeur(map,mapxsize,mapysize,x_serpent,y_serpent,BONUS, WEST) != -1 
  && (parcours_largeur(map,mapxsize,mapysize,x_serpent,y_serpent,SNAKE_TAIL, WEST) != -1 || s->next == NULL)){
        return WEST;
      }
  printf("DEBUG 1 \n");
  if(parcours_largeur(map,mapxsize,mapysize,x_serpent,y_serpent,SNAKE_TAIL, NORTH) != -1){
        return NORTH;
      }
  if(parcours_largeur(map,mapxsize,mapysize,x_serpent,y_serpent,SNAKE_TAIL, SOUTH) != -1){
        return SOUTH;
      }
  if(parcours_largeur(map,mapxsize,mapysize,x_serpent,y_serpent,SNAKE_TAIL, EAST) != -1){
        return EAST;
      }
  if(parcours_largeur(map,mapxsize,mapysize,x_serpent,y_serpent,SNAKE_TAIL, WEST) != -1){
        return WEST;
      }
  printf("DEBUG 2 \n");
  return aleatoire(map,mapxsize,mapysize,s,last_action);
}

action snake(
	     char * * map, // array of chars modeling the game map
	     int mapxsize, // x size of the map
	     int mapysize, // y size of the map
	     snake_list s, // snake coded as a linked list
	     action last_action // last action made, set to -1 in the beginning 
	     ) {
  action a; // action to choose and return
  
  // a = victoire_ou_defaite_si_la_map_ne_convient_pas(map,mapxsize,mapysize,s,last_action);
  a = victoire(map,mapxsize,mapysize,s,last_action);
  // a = aleatoire(map,mapxsize,mapysize,s,last_action);
  
  return a; // answer to the game engine
}

/*
  printAction function:
  This function prints the input action name on screen.
*/
static void printAction(action a) {
  switch(a) {
  case NORTH:
    printf("NORTH");
    break;
  case EAST:
    printf("EAST");
    break;
  case SOUTH:
    printf("SOUTH");
    break;
  case WEST:
    printf("WEST");
    break;
  }
}

/*
  printBoolean funtion:
  This function prints the input boolan value on screen.
*/
static void printBoolean(bool b) {
  if(b) {
    printf("true");
  }
  else {
    printf("false");
  }
}

