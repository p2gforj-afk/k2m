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
  } while(!ok);
    
  return a;
}

int abs(int a){
  return a - 2*a*(a<0);
}

int NY(int Xa, int Ya, int Xs, int Ys){
  return abs(Xs - Xa) + abs(Ys - Ya);
}

action victoire_ou_defaite_si_la_map_ne_convient_pas(char * * map, int mapxsize, int mapysize, snake_list s, action last_action ){
  if(mapxsize%2 == 0 && mapysize%2 == 0){
    printf("fin des reves");
    return 0;
  }
  int x_head = s->x;
  int y_head = s->y;
  if (mapxsize%2 == 1){
    if(y_head == 1 && x_head > 1){ //en haut on va a gauche
      return WEST;
    }
    if(x_head ==  mapxsize-1 && y_head == 2){ //fin du serpentin on remonte vers le couloir du haut
      return NORTH;
    }
    if(x_head%2 == 1 && y_head < mapysize-1){ //serpentin
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
    if(y_head ==  mapysize-1 && x_head == 2){//fin du serpentin on va dans le couloir de gauche
      return WEST;
    }
    if(y_head%2 == 1 && x_head < mapxsize-1){
      return EAST;
    }
    if(y_head%2 == 0 && x_head >2){
      return NORTH;
    }
    return SOUTH;
  }
}
action victoire(char * * map, int mapxsize, int mapysize, snake_list s, action last_action ){
  action a = 0;
  return a;
}

action snake(
	     char * * map, // array of chars modeling the game map
	     int mapxsize, // x size of the map
	     int mapysize, // y size of the map
	     snake_list s, // snake coded as a linked list
	     action last_action // last action made, set to -1 in the beginning 
	     ) {
  action a; // action to choose and return
  
  a = victoire_ou_defaite_si_la_map_ne_convient_pas(map,mapxsize,mapysize,s,last_action);
  // a = victoire(map,mapxsize,mapysize,s,last_action);
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

