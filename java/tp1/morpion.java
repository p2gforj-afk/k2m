import java.util.Scanner;

public class morpion{
    private int[][] grille = new int[3][3];
    public void affiche(){
        System.out.println("+---+---+---+");
        for(int i = 0; i<3; i++){
            for (int j = 0; j<3; j++){
                switch(grille[i][j]){
                    case 1:
                        System.out.print("| x ");
                        break;
                    case 2:
                        System.out.print("| o ");
                        break;
                    default:
                        System.out.print("| . ");
                }
            }
            System.out.println("|");
            System.out.println("+---+---+---+");
        }
    }
    public void saisie(int joueur, Scanner sc){
        boolean flag = true;
        while(flag){
            System.out.print("Joueur " + joueur + "(format \"ligne colonne \") : ");
            int a = sc.nextInt() - 1;
            int b = sc.nextInt() - 1;
            if(grille[a][b] == 0){
                grille[a][b] = joueur;
                flag = false;
            }
            else{
                System.out.println("Case deja occupee, rejouez!");
            }
        }
    }

    public boolean case_libre(){
        for(int i = 0; i<3; i++){
            for (int j = 0; j<3; j++){
                if (grille[i][j] == 0) return true;
            }
        }
        return false;
    }

    public boolean gagne(){
        //victoire ligne
        for (int i = 0; i<3; i++){
            if(grille[i][0] == 1 && grille[i][1] ==1 && grille[i][2] == 1) {
                System.out.println("Bravo joueur 1 (gwer aussi)");
                return true;
            }
            if(grille[i][0] == 2 && grille[i][1] ==2 && grille[i][2] == 2) {
                System.out.println("Bravo joueur 2 (gwer)");
                return true;
            }
        }
        //victoire colonne
        for (int i = 0; i<3; i++){
            if(grille[0][i] == 1 && grille[1][i] ==1 && grille[2][i] == 1) {
                System.out.println("Bravo joueur 1 (gwer aussi)");
                return true;
            }
            if(grille[0][i] == 2 && grille[1][i] ==2 && grille[2][i] == 2) {
                System.out.println("Bravo joueur 2 (gwer)");
                return true;
            }
        }
        //victoire diago
        if (grille[0][0] == 1 && grille[1][1] == 1 && grille[2][2] == 1) {
            System.out.println("Bravo joueur 1 (gwer aussi)");
            return true;
        }
        if (grille[0][0] == 2 && grille[1][1] == 2 && grille[2][2] == 2) {
            System.out.println("Bravo joueur 2 (gwer)");
            return true;
        }

        // diagonale secondaire
        if (grille[0][2] == 1 && grille[1][1] == 1 && grille[2][0] == 1) {
            System.out.println("Bravo joueur 1 (gwer aussi)");
            return true;
        }
        if (grille[0][2] == 2 && grille[1][1] == 2 && grille[2][0] == 2) {
            System.out.println("Bravo joueur 2 (gwer)");
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        morpion fdp = new morpion();
        int gwer = 2;
        fdp.affiche();
            while(fdp.case_libre() && !fdp.gagne()){
                if(gwer == 2) gwer = 1;
                else gwer = 2;
                fdp.saisie(gwer, sc);
                fdp.affiche();
            }
        if(!fdp.case_libre() && !fdp.gagne()){
            System.out.println("ya que des perdants bande de gwer");
        }
        sc.close();
    }

}