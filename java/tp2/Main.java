

public class Main {
    public static void main(String[] args) {
        EnseignantChercheur e1 = new EnseignantChercheur("pierre", "gwer","evreux", 0670772503, 127, 53);
        Ater e2 = new Ater("pierre", "gwer", "evreux", 0670772503, 127, 53);
        Doctorants e3 = new Doctorants("pierre", "gwer", "evreux", 0670772503, 127, 53);
        Vacataires e4 = new Vacataires("pierre", "gwer", "evreux", 0670772503, 127, 53, "gwerCorp");

        double cout = Enseignant.coutGlobal();
        System.out.println(cout);
    }   
}