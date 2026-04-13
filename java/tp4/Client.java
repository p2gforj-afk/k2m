public class Client{
    private int numero;
    private String nom;
    private String prenom;
    private int numeroDePorte;
    private int codePostalClient;
    private String rueClient;
    private String villeClient;

    public String getNom() {
        return nom;
    }
    public String getPrenom() {
        return prenom;
    }
    public String getAdresseClient() {
        return numeroDePorte + rueClient + codePostalClient + villeClient;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }
    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public void setAdresseClient(int numeroDePorte, String rueClient, int codePostalClient, String villeClient) {
        this.numeroDePorte = numeroDePorte;
        this.codePostalClient = codePostalClient;
        this.rueClient = rueClient;
        this.villeClient = villeClient;
    }

    @Override
    public String toString() {
        return "Client [numero=" + numero + ", nom=" + nom + ", prenom=" + prenom + ", numeroDePorte=" + numeroDePorte
                + ", codePostalClient=" + codePostalClient + ", rueClient=" + rueClient + ", villeClient=" + villeClient
                + "]";
    }

    
}