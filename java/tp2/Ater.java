public class Ater extends Enseignant{
    private static final int SALAIRENET = 2500;
    private static final int PRIXSUP = 40;
    private int heureSup;

    public void setHeureSup(int heureSup){
        if (heureSup <= 45 && heureSup >= 0) this.heureSup = heureSup;
        else System.err.println("nb d'heures invalide");
    }

    public int getHeureSup(){
        return heureSup;
    }

    public int getSALAIRENET(){
        return SALAIRENET;
    }

    public int getPRIXSUP(){
        return PRIXSUP;
    }

    public Ater(String namae, String prenom, String adresse, int numero, int nbCour, int heureSup) {
        super(namae, prenom, adresse, numero, nbCour);
        this.setHeureSup(heureSup);
    }

    @Override
    public double coutEnseignant(){
        return (double) SALAIRENET/0.35 + this.getHeureSup()*PRIXSUP/0.95;
    }
    }
