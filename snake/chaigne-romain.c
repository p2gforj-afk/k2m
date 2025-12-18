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

/*
  called by presque_victoire for some weird situation
  chose a random direction trying no yo kill our dear Snake
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

struct liste_BFS { //liste chainee pour explorer la map avec un parcours en largeur
    int x; //coordonne en x de la case
    int y; //coordonne en y de la case
    action first_move; //report du premier move qui a conduit a cette case
    struct liste_BFS *next; //case suivante a explorer
};
typedef struct liste_BFS * bfs;
/*
  parcours_largeur called from the preque_victoire fonction
  return a move that will bring u closer to the goal if a path exist, else return -1
*/
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
/*
  presque_vicoire fonction bring u close to the win, sometimes reach it, sometimes not...
  do lot of weird stuff but it will be explained in the fonction, in french.
  basically the main rule is to still have a path between the head and the tail bc that way Snake nv die
*/
action presque_victoire(char **map,int mapxsize,int mapysize,snake_list s,action last_action) {
  int x = s->x; //on note la position de la tete du serpent dans
  int y = s->y;
  action a = parcours_largeur(map, mapxsize, mapysize,x, y, BONUS); //on chercher un chemin entre la tete et la pomme
  if (a != -1) { //si le chemin existe
    int snake_size = 1; //on calcule la taille de snake - sur certaines maps la fin de partie est impossible donc on va la forcer -
    int mapsize = ((mapxsize-2)*(mapysize-2)-1);
    snake_list size = s;
    while(size->next != NULL){
      snake_size ++;
      size = size->next;
    }
    switch (a){ //on regarde quelle est ce chemin puis 
    case NORTH: 
      if((parcours_largeur(map, mapxsize, mapysize, x, y-1, SNAKE_TAIL) != -1) || s->next == NULL || snake_size == mapsize)
        //on verifie qu'il existe un chemin entre la position suivante et la queue, si oui on renvoie la direction
        return NORTH;
      break;
    case SOUTH:
      if((parcours_largeur(map, mapxsize, mapysize, x, y+1, SNAKE_TAIL) != -1 )|| s->next == NULL || snake_size == mapsize)
        return SOUTH;
      break;
    case EAST:
      if((parcours_largeur(map, mapxsize, mapysize, x+1, y, SNAKE_TAIL) != -1) || s->next == NULL || snake_size == mapsize)
        return EAST;
      break;
    case WEST:
      if((parcours_largeur(map, mapxsize, mapysize, x-1, y, SNAKE_TAIL) != -1) || s->next == NULL || snake_size == mapsize)
        return WEST;
      break;
    }
  }
  if(rand()%2 == 1){//pas de chemin safe vers la tete donc on mouline severe pour esperer avoir un chemin plus tard
    a = parcours_largeur(map, mapxsize, mapysize,x, y, PATH);// on cherche une case adjacente safe
    if (a != -1) {//si cette case existe
      switch (a){// on regarde dans quelle direction est celle case
      case NORTH:
        if(parcours_largeur(map, mapxsize, mapysize, x, y-1, SNAKE_TAIL) != -1)
            //on verifie que une fois sur cette case on pourra toujours rejoindre notre queue,
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
  }
  else if(rand()%2 == 1){
    if (map[s->y-1][s->x]!=BONUS && map[s->y][s->x+1]!=BONUS && map[s->y+1][s->x]!=BONUS && map[s->y][s->x-1]!=BONUS){
        // cas tres specifique au late game, le but etant de bouger les trous restants
        // en effet le test precedent ira tres rarement dans un trou d'une seule case en late game 
        // car snake suit sa queue et pour la simple et bonne raison que je n'update pas la postion du snake lors du BFS...
        // on verifie ici que la pomme n'est pas adjacente a la tete sinon l'aleatoire qui va arriver peut faire de la dingz
      snake_list ptail = s; //va correspondre a l'avant dernier maillon du snake
      while(ptail->next->c != SNAKE_TAIL){
        ptail = ptail->next;
      }
      int clef1 = 0; //premier verrou, car on veut pas vrmt que l'appel a aleatoire soit aleatoire
      int clef2 = 0; //second verrou, pour s'assurer que l'on pourra rejoindre notre queue apres
      if(map[s->y-1][s->x]==PATH){ //determine si un trou est la
        clef1 ++;
        if(((s->y-2 == ptail->y) && (s->x == ptail->x))  ||
          ((s->y-1 == ptail->y) && (s->x+1 == ptail->x)) ||
          ((s->y-1 == ptail->y) && (s->x-1 == ptail->x)) )
          //assure que l'on pourra rejoindre notre queue apres
          clef2 ++;
      }
      if(map[s->y][s->x+1]==PATH){
        clef1 ++;
        if(((s->y-1 == ptail->y) && (s->x+1 == ptail->x))||
          ((s->y == ptail->y) && (s->x+2 == ptail->x))   ||
          ((s->y+1 == ptail->y) && (s->x+1 == ptail->x)) )
          clef2 ++;
      }
      if(map[s->y+1][s->x]==PATH){
        clef1 ++;
        if(((s->y+1 == ptail->y) && (s->x+1 == ptail->x))||
          ((s->y+2 == ptail->y) && (s->x == ptail->x))   ||
          ((s->y+1 == ptail->y) && (s->x-1 == ptail->x)) )
          clef2 ++;
      }
      if(map[s->y][s->x-1]==PATH){
        clef1 ++;
        if(((s->y-1 == ptail->y) && (s->x-1 == ptail->x))||
          ((s->y+1 == ptail->y) && (s->x-1 == ptail->x)) ||
          ((s->y == ptail->y) && (s->x-2 == ptail->x))   )
          clef2 ++;
      }
      if (clef1==1 && clef2==1) // si on a bien une seule case dispo et que cette derniere est safe on y go
        return aleatoire(map,mapxsize,mapysize,s,last_action);
    }
  }
  //enfin si tout cela est impossible on suit notre queue
  return parcours_largeur(map, mapxsize, mapysize,x, y, SNAKE_TAIL);
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