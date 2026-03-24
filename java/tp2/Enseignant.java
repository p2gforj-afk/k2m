import java.util.ArrayList;
import java.util.List;

abstract class Enseignant {
    private String namae;
    private String prenom;
    private String adresse;
    private int numero;
    private int nbCour;
    private static final List<Enseignant> listEnseignant = new ArrayList<>();


    public static double coutGlobal(){
        double cout = 0;
        for (Enseignant e : listEnseignant){
            cout += e.coutEnseignant();
        }
        return cout;
    }

    
    public String getNamae() {
        return namae;
    }
    public String getPrenom() {
        return prenom;
    }
    public String getAdresse() {
        return adresse;
    }
    public int getNumero() {
        return numero;
    }
    public int getNbCour() {
        return nbCour;
    }
    
    public Enseignant(String namae, String prenom, String adresse, int numero, int nbCour) {
        listEnseignant.add(this);
        this.namae = namae;
        this.prenom = prenom;
        this.adresse = adresse;
        this.numero = numero;
        this.nbCour = nbCour;
    }
    
    public void setNamae(String namae) {
        this.namae = namae;
    }
    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }
    public void setAdresse(String adresse) {
        this.adresse = adresse;
    }
    public void setNumero(int numero) {
        this.numero = numero;
    }
    public void setNbCour(int nbCour) {
        this.nbCour = nbCour;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Enseignant{");
        sb.append("namae=").append(namae);
        sb.append(", prenom=").append(prenom);
        sb.append(", adresse=").append(adresse);
        sb.append(", numero=").append(numero);
        sb.append(", nbCour=").append(nbCour);
        sb.append('}');
        return sb.toString();
    }

    public abstract double coutEnseignant();
}
