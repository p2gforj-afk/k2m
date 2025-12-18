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

// prototypes of the local/private functions
static void printAction(action);
static void printBoolean(bool);

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

struct liste_BFS {
    int x;
    int y;
    action first_move;
    struct liste_BFS *next;
};
typedef struct liste_BFS * bfs;

action parcours_largeur(char **map,int mapxsize,int mapysize,int x_debut,int y_debut,char GOAL) {
  char ma_map[mapysize][mapxsize]; // Copie de la map
    for (int y = 0; y < mapysize; y++)
      for (int x = 0; x < mapxsize; x++)
        ma_map[y][x] = map[y][x];
  bfs debut = malloc(sizeof(*debut));
  bfs fin = debut;
  debut->x = x_debut;
  debut->y = y_debut;
  debut->first_move = -1;
  debut->next = NULL;
  int dx[4] = { 0,  0,  1, -1};
  int dy[4] = {-1,  1,  0,  0};
  action dirs[4] = {NORTH, SOUTH, EAST, WEST};
  bfs courant = debut;
  while (courant != NULL) {
    if (map[courant->y][courant->x] == GOAL){ //GOALLLLLLLLLLLLL
      action res = courant->first_move;
      while (debut != NULL) {
      bfs tmp = debut;
      debut = debut->next;
      free(tmp);
      }
      return res;
    }
    int rd[4] = {-1,-1,-1,-1}; // cinema incoming soon
    for(int k = 0; k<4; k++){
      int j = rand()%4;
      while (rd[0] == j || rd[1] == j ||rd[2] == j || rd[3] == j)
        j = rand()%4;
      rd[k] = j;
    }
    for (int i = 0; i < 4; i++) {
      int nx = courant->x + dx[rd[i]];
      int ny = courant->y + dy[rd[i]];
      if (ma_map[ny][nx] != WALL && ma_map[ny][nx] != SNAKE_BODY && ma_map[ny][nx] != SNAKE_HEAD) {
        bfs new = malloc(sizeof(*new));
        new->x = nx;
        new->y = ny;
        new->first_move = (courant->first_move == -1) 
                        ? dirs[rd[i]] 
                        : courant->first_move;
        new->next = NULL;
        fin->next = new;
        fin = new;
        ma_map[ny][nx] = WALL; // visité
      }
    }
    courant = courant->next;
  }
  while (debut != NULL) { //goal non atteint
    bfs tmp = debut;
    debut = debut->next;
    free(tmp);
  }
  return -1;
}

action presque_victoire(char **map,int mapxsize,int mapysize,snake_list s,action last_action) {
  int x = s->x;
  int y = s->y;
  action a = parcours_largeur(map, mapxsize, mapysize,x, y, BONUS); 
  if (a != -1) { //ETAPE 1 : aller vers la pomme si possible et si c'est safe
    switch (a){
    case NORTH:
      if((parcours_largeur(map, mapxsize, mapysize, x, y-1, SNAKE_TAIL) != -1) || s->next == NULL)
        return NORTH;
      break;
    case SOUTH:
      if((parcours_largeur(map, mapxsize, mapysize, x, y+1, SNAKE_TAIL) != -1 )|| s->next == NULL)
        return SOUTH;
      break;
    case EAST:
      if((parcours_largeur(map, mapxsize, mapysize, x+1, y, SNAKE_TAIL) != -1) || s->next == NULL)
        return EAST;
      break;
    case WEST:
      if((parcours_largeur(map, mapxsize, mapysize, x-1, y, SNAKE_TAIL) != -1) || s->next == NULL)
        return WEST;
      break;
    }
  }
  if (rand()%2 == 1){ //ETAPE 2 s'en remettre a l'aleatoire pour eviter de se bloquer
    a = parcours_largeur(map, mapxsize, mapysize,x, y, PATH);
    if (a != -1) { 
      switch (a){
      case NORTH:
        if((parcours_largeur(map, mapxsize, mapysize, x, y-1, SNAKE_TAIL) != -1) || s->next == NULL)
          return NORTH;
        break;
      case SOUTH:
        if((parcours_largeur(map, mapxsize, mapysize, x, y+1, SNAKE_TAIL) != -1 )|| s->next == NULL)
          return SOUTH;
        break;
      case EAST:
        if((parcours_largeur(map, mapxsize, mapysize, x+1, y, SNAKE_TAIL) != -1) || s->next == NULL)
          return EAST;
        break;
      case WEST:
        if((parcours_largeur(map, mapxsize, mapysize, x-1, y, SNAKE_TAIL) != -1) || s->next == NULL)
          return WEST;
        break;
      }
    }
  }
  else{
    if ((map[s->y-1][s->x]==SNAKE_TAIL || map[s->y][s->x+1]==SNAKE_TAIL || map[s->y+1][s->x]==SNAKE_TAIL || map[s->y][s->x-1]==SNAKE_TAIL) 
        && map[s->y-1][s->x]!=BONUS && map[s->y][s->x+1]!=BONUS && map[s->y+1][s->x]!=BONUS && map[s->y][s->x-1]!=BONUS){
      snake_list ptail = s;
      while(ptail->next->c != SNAKE_TAIL){
        ptail = ptail->next;
      }
      int clef1 = 0;
      int clef2 = 0;
      if(map[s->y-1][s->x]==PATH){
        clef1 ++;
        if(((s->y-2 == ptail->y) && (s->x == ptail->x))   ||
          ((s->y-1 == ptail->y) && (s->x+1 == ptail->x)) ||
          ((s->y-1 == ptail->y) && (s->x-1 == ptail->x)) )
          clef2 ++;
      }
      if(map[s->y][s->x+1]==PATH){
        clef1 ++;
        if(((s->y-1 == ptail->y) && (s->x+1 == ptail->x)) ||
          ((s->y == ptail->y)   && (s->x+2 == ptail->x)) ||
          ((s->y+1 == ptail->y) && (s->x+1 == ptail->x)) )
          clef2 ++;
      }
      if(map[s->y+1][s->x]==PATH){
        clef1 ++;
        if(((s->y+1 == ptail->y) && (s->x+1 == ptail->x)) ||
          ((s->y+2 == ptail->y)   && (s->x == ptail->x)) ||
          ((s->y+1 == ptail->y) && (s->x-1 == ptail->x)) )
          clef2 ++;
      }
      if(map[s->y][s->x-1]==PATH){
        clef1 ++;
        if(((s->y-1 == ptail->y) && (s->x-1 == ptail->x))  ||
          ((s->y+1 == ptail->y)   && (s->x-1 == ptail->x))||
          ((s->y == ptail->y) && (s->x-2 == ptail->x))    )
          clef2 ++;
      }
      if (clef1==1 && clef2==1)
        return aleatoire(map,mapxsize,mapysize,s,last_action);
    }
  }//ETAPE 3 : suivre sa queue, si ce n'est pas possible - cas tres rare - aleatoire
  a = parcours_largeur(map, mapxsize, mapysize,x, y, SNAKE_TAIL); 
  if (a != -1)
    return a;
  return aleatoire(map,mapxsize,mapysize,s,last_action);
}
/*
  snake function called from the main program
  call presque_victoire because why not
*/
action snake(
	     char * * map, // array of chars modeling the game map
	     int mapxsize, // x size of the map
	     int mapysize, // y size of the map
	     snake_list s, // snake coded as a linked list
	     action last_action // last action made, set to -1 in the beginning 
	     ) {
  if(last_action == - 1)
    srand(time(NULL)); //on initialise la seed de l'execution
  return presque_victoire(map,mapxsize,mapysize,s,last_action);
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