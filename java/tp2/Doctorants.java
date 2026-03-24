public class Doctorants extends Enseignant{
    private static int PRIXSUP = 30;
    private int heureSup;

    public void setHeureSup(int heureSup){
        if (heureSup <= 64 && heureSup >= 0) this.heureSup = heureSup;
        else System.err.println("nb d'heures invalide");
    }

    public int getHeureSup(){
        return heureSup;
    }

    public int getPRIXSUP(){
        return PRIXSUP;
    }

    public Doctorants(String namae, 
                      String prenom, 
                      String adresse, 
                      int numero, 
                      int nbCour, 
                      int heureSup ) {
                        
        super(namae, prenom, adresse, numero, nbCour);
        this.setHeureSup(heureSup);
    }

    @Override
    public double coutEnseignant(){
    return (double) this.getHeureSup()*PRIXSUP;
}
}