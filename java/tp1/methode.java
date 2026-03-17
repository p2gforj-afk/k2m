import java.util.Scanner;

class outils {

    public String lireChaine(Scanner scanner) {
        System.out.println("Saisir une chaine de caractere :");
        return scanner.nextLine();
    }

    public int lireEntier(Scanner scanner) {
        System.out.println("Saisir un entier :");
        return scanner.nextInt();
    }

    public int multiplier(int a, int b) {
        return a * b;
    }

    public float diviser(int a, int b) {
        if (b == 0) {
            System.out.println("div par 0");
            return -1;
        }
        return (float) a / b;
    }
}

public class methode{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        outils o = new outils();

        String car = o.lireChaine(sc);
        System.out.println(car);

        int a = o.lireEntier(sc);
        int b = o.lireEntier(sc);

        int mult = o.multiplier(a, b);
        float div = o.diviser(a, b);

        System.out.println(a + " * " + b + " = " + mult);
        System.out.println(a + " / " + b + " = " + div);

        sc.close();
    }
}