import java.util.Random;


public class Tableau{

    public static void tri(int[] tab){
        int idmin;
        int tmp;
        for(int i = 0; i<9; i++){
            idmin = i;
            for(int j = i+1; j<10; j++){
                if(tab[j] < tab[idmin]){
                    idmin = j;
                }
            }
            tmp = tab[idmin];
            tab[idmin] = tab[i];
            tab[i] = tmp;

        }
    }
    public static void main(String[] args) {
        Random rnd = new Random();
        int[] tab = new int[10];
        for(int i = 0; i<10; i++){
            tab[i] = rnd.nextInt(100);
        }
        for(int i = 0; i<10; i++){
            System.out.print(tab[i] + ";");
        }
        System.err.println("");
        Tableau.tri(tab);

        for(int i = 0; i<10; i++){
            System.out.print(tab[i] + ";");
        }
        System.err.println("");
    }
}