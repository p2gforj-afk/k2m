import java.util.Scanner;

public class kino {
    public void menu(){
        System.out.println("Veuillez choisir");
        System.out.println("1. creer liste");
        System.out.println("2. supprimer la liste");
        System.out.println("3. ajouter element a la liste");
        System.out.println("4. supprimer element de la liste");
        System.out.println("0. Exit");
    }
    public static void main(String[] args) {
        kino kn = new kino();
        kn.menu();
        Scanner sc = new Scanner(System.in);
        int i = -1;
        while (i != 0){
            i = sc.nextInt();
            switch(i){
                case 1:
                    System.out.println("create");
                    break;
                case 2:
                    System.out.println("delete");
                    break;
                case 3:
                    System.out.println("add");
                    break;
                case 4:
                    System.out.println("delete element");
                    break;
                case 0:
                    System.out.println("au revoir");
                    break;                
                default:
                    System.out.println("choix non permis !");
            }
        }
        
        sc.close();
    }
}
