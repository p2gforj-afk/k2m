#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "snake_def.h"
#include "snake_dec.h"

char * student="Chaigne";

// ================= Parcours largeur (BFS) =================
struct liste_BFS {
    int x, y;
    action first_move;
    struct liste_BFS *next;
};
typedef struct liste_BFS * bfs;

action parcours_largeur(char **map,int mapxsize,int mapysize,int x_debut,int y_debut,char GOAL) {
    char ma_map[mapysize][mapxsize];
    for(int y=0;y<mapysize;y++)
        for(int x=0;x<mapxsize;x++)
            ma_map[y][x]=map[y][x];

    bfs debut=malloc(sizeof(*debut));
    bfs fin=debut;
    debut->x=x_debut; debut->y=y_debut; debut->first_move=-1; debut->next=NULL;
    ma_map[y_debut][x_debut]=WALL;

    int dx[4]={0,0,1,-1}, dy[4]={-1,1,0,0};
    action dirs[4]={NORTH,SOUTH,EAST,WEST};
    bfs courant=debut;

    while(courant!=NULL){
        if(map[courant->y][courant->x]==GOAL){
            action res=courant->first_move;
            while(debut!=NULL){ bfs tmp=debut; debut=debut->next; free(tmp);}
            return res;
        }

        int rd[4]={-1,-1,-1,-1};
        for(int k=0;k<4;k++){
            int j=rand()%4;
            while(rd[0]==j||rd[1]==j||rd[2]==j||rd[3]==j) j=rand()%4;
            rd[k]=j;
        }

        for(int i=0;i<4;i++){
            int nx=courant->x+dx[rd[i]];
            int ny=courant->y+dy[rd[i]];
            if(ma_map[ny][nx]!=WALL && ma_map[ny][nx]!=SNAKE_BODY && ma_map[ny][nx]!=SNAKE_HEAD){
                bfs new=malloc(sizeof(*new));
                new->x=nx; new->y=ny;
                new->first_move=(courant->first_move==-1)?dirs[rd[i]]:courant->first_move;
                new->next=NULL;
                fin->next=new; fin=new;
                ma_map[ny][nx]=WALL;
            }
        }
        courant=courant->next;
    }

    while(debut!=NULL){ bfs tmp=debut; debut=debut->next; free(tmp);}
    return -1;
}

// ================= Flood fill =================
typedef struct { int x,y; } Point;

void flood_fill(char **map,int mapxsize,int mapysize,int sx,int sy,bool *visited,int *size,bool *has_tail){
    Point stack[mapxsize*mapysize];
    int top=0;
    stack[top++] = (Point){sx,sy};
    visited[sy*mapxsize+sx]=true;
    *size=0; *has_tail=false;

    int dx[4]={0,0,1,-1}, dy[4]={-1,1,0,0};

    while(top>0){
        Point p=stack[--top];
        (*size)++;
        if(map[p.y][p.x]==SNAKE_TAIL) *has_tail=true;

        for(int d=0;d<4;d++){
            int nx=p.x+dx[d], ny=p.y+dy[d];
            if(nx<0||nx>=mapxsize||ny<0||ny>=mapysize) continue;
            if(visited[ny*mapxsize+nx]) continue;
            if(map[ny][nx]!=PATH) continue;
            stack[top++] = (Point){nx,ny};
            visited[ny*mapxsize+nx]=true;
        }
    }
}

bool creates_bad_region(char **map,int mapxsize,int mapysize){
    bool visited[mapxsize*mapysize];
    for(int i=0;i<mapxsize*mapysize;i++) visited[i]=false;

    for(int y=0;y<mapysize;y++){
        for(int x=0;x<mapxsize;x++){
            if(!visited[y*mapxsize+x] && map[y][x]==PATH){
                int region_size=0;
                bool has_tail=false;
                flood_fill(map,mapxsize,mapysize,x,y,visited,&region_size,&has_tail);
                if(!has_tail && region_size>2 && (region_size%2==1)) return true;
            }
        }
    }
    return false;
}

// ================= Utilitaires =================
int abs(int a){ return a-2*a*(a<0); }
int NY(int Xa,int Ya,int Xs,int Ys){ return abs(Xs-Xa)+abs(Ys-Ya); }

struct SHADOW{ action move; struct SHADOW *next; };
typedef struct SHADOW *shadow_list;

// ================= Shadow simulation =================
snake_list copy_snake(snake_list s){
    if(!s) return NULL;
    snake_list head=malloc(sizeof(*head));
    head->c=s->c; head->x=s->x; head->y=s->y;
    snake_list cur=head, src=s->next;
    while(src){
        cur->next=malloc(sizeof(*cur));
        cur=cur->next;
        cur->c=src->c; cur->x=src->x; cur->y=src->y;
        src=src->next;
    }
    cur->next=NULL;
    return head;
}

void free_snake(snake_list s){
    while(s){
        snake_list tmp=s;
        s=s->next;
        free(tmp);
    }
}

int a_shadow_star(char **map,int mapxsize,int mapysize,int x_debut,int y_debut,snake_list ssh,shadow_list *sh){
    shadow_list last_move=*sh;
    snake_list sshc=ssh;

    int x_apple=1, y_apple=1;
    while(map[y_apple][x_apple]!=BONUS){
        y_apple++; if(y_apple>=mapysize){ y_apple=0; x_apple++; }
    }

    // copie map
    char **sh_map=malloc(sizeof(char*)*mapysize);
    for(int y=0;y<mapysize;y++){
        sh_map[y]=malloc(sizeof(char)*mapxsize);
        for(int x=0;x<mapxsize;x++) sh_map[y][x]=map[y][x];
    }

    // copie snake
    snake_list sh_snake=copy_snake(ssh);
    snake_list sh_snake_fin=sh_snake;
    while(sh_snake_fin->next) sh_snake_fin=sh_snake_fin->next;

    int dx[4]={0,0,1,-1}, dy[4]={-1,1,0,0};
    action dirs[4]={NORTH,SOUTH,EAST,WEST};
    bool flag=true;

    while(flag){
        if(sh_map[y_debut][x_debut]==BONUS){
            // Vérifier sécurité avant de manger
            sh_map[y_debut][x_debut]=PATH; // ne pas poser tête encore
            bool bad_region=creates_bad_region(sh_map,mapxsize,mapysize);
            int bfs_tail=parcours_largeur(sh_map,mapxsize,mapysize,x_debut,y_debut,SNAKE_TAIL);

            if(bad_region || bfs_tail==-1){
                // impossible de manger
                for(int y=0;y<mapysize;y++) free(sh_map[y]); free(sh_map);
                free_snake(sh_snake);
                while(*sh){ shadow_list tmp=*sh; *sh=(*sh)->next; free(tmp);}
                return -1;
            }

            // ok, sécurité validée
            sh_map[y_debut][x_debut]=SNAKE_HEAD;
            for(int y=0;y<mapysize;y++) free(sh_map[y]); free(sh_map);
            free_snake(sh_snake);
            return 0;
        }

        int rd[4]={-1,-1,-1,-1};
        for(int k=0;k<4;k++){
            int j=rand()%4;
            while(rd[0]==j||rd[1]==j||rd[2]==j||rd[3]==j) j=rand()%4;
            rd[k]=j;
        }

        int min=-1, shadow_id=-1;
        for(int i=0;i<4;i++){
            int nx=x_debut+dx[rd[i]], ny=y_debut+dy[rd[i]];
            if(sh_map[ny][nx]!=WALL && sh_map[ny][nx]!=SNAKE_BODY && sh_map[ny][nx]!=SNAKE_HEAD){
                if(NY(nx,ny,x_apple,y_apple)<min||min==-1){ min=NY(nx,ny,x_apple,y_apple); shadow_id=i; }
            }
        }

        if(shadow_id!=-1){
            x_debut+=dx[rd[shadow_id]]; y_debut+=dy[rd[shadow_id]];
            shadow_list new=malloc(sizeof(*new));
            new->move=dirs[rd[shadow_id]]; new->next=NULL;
            if(!*sh){ *sh=new; last_move=new; }
            else{ last_move->next=new; last_move=new; }

            // avancer snake shadow
            snake_list new_head=malloc(sizeof(*new_head));
            new_head->c=SNAKE_HEAD; new_head->x=x_debut; new_head->y=y_debut; new_head->next=sh_snake;
            sh_snake=new_head;

            // déplacer queue
            snake_list cur=sh_snake;
            while(cur->next!=sh_snake_fin) cur=cur->next;
            cur->c=SNAKE_TAIL;
            sh_snake_fin=cur;
            sh_snake_fin->next=NULL;
        } else flag=false;
    }

    for(int y=0;y<mapysize;y++) free(sh_map[y]); free(sh_map);
    free_snake(sh_snake);
    while(*sh){ shadow_list tmp=*sh; *sh=(*sh)->next; free(tmp);}
    return -1;
}

// ================= Action finale =================
action shadow_victoire(char **map,int mapxsize,int mapysize,snake_list s,action last_action,shadow_list *sh){
    if(*sh){
        action a=(*sh)->move;
        shadow_list tmp=*sh; *sh=(*sh)->next; free(tmp);
        return a;
    }
    int x=s->x, y=s->y;
    if(a_shadow_star(map,mapxsize,mapysize,x,y,s,sh)==-1)
        return parcours_largeur(map,mapxsize,mapysize,x,y,SNAKE_TAIL);
    action a=(*sh)->move;
    shadow_list tmp=*sh; *sh=(*sh)->next; free(tmp);
    return a;
}

// ================= Snake entry =================
action snake(char **map,int mapxsize,int mapysize,snake_list s,action last_action){
    static shadow_list shadow_move=NULL;
    if(last_action==-1){ srand(time(NULL)); shadow_move=NULL;}
    return shadow_victoire(map,mapxsize,mapysize,s,last_action,&shadow_move);
}
