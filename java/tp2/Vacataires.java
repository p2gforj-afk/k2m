public class Vacataires extends Enseignant{
    private String nomEntreprise;
    private static final int PRIXSUP = 30;
    private int heureSup;

    public void setHeureSup(int heureSup){
        if (heureSup <= 45 && heureSup >= 0) this.heureSup = heureSup;
        else System.err.println("nb d'heures invalide");
    }

    public void setNomEntreprise(String nomEntreprise){
        this.nomEntreprise = nomEntreprise;
    }

    public int getHeureSup(){
        return heureSup;
    }

    public String getNomEntreprise(){
        return nomEntreprise;
    }

    public int getPRIXSUP(){
        return PRIXSUP;
    }

    public Vacataires(String namae, 
                      String prenom, 
                      String adresse, 
                      int numero, 
                      int nbCour, 
                      int heureSup, 
                      String nomEntreprise) {

        super(namae, prenom, adresse, numero, nbCour);
        this.setHeureSup(heureSup);
        this.setNomEntreprise(nomEntreprise);
    }

    @Override
    public double coutEnseignant(){
        return (double) this.getHeureSup()*PRIXSUP;
    }
}