
public class Main {
  public static void main(String[] args) {
    /*
     * HEURESUP MAX
     *
     * EnseignantChercheur : inf
     * Ater : 45
     * Doctorants : 64
     * Vacataores : 45
     *
     *
     */

    EnseignantChercheur e1 = new EnseignantChercheur("pierre", "gwer", "evreux", 0670772503, 127, 10);
    Ater e2 = new Ater("pierre", "gwer", "evreux", 0670772503, 127, 10);
    Doctorants e3 = new Doctorants("pierre", "gwer", "evreux", 0670772503, 127, 10);
    Vacataires e4 = new Vacataires("pierre", "gwer", "evreux", 0670772503, 127, 10, "gwerCorp");

    String cout = String.format("%.2f", Enseignant.coutGlobal());
    System.out.println(cout);
  }
}
