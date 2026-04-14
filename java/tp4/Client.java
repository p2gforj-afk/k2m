public class Client{
  private int numero;
  private String nom;
  private String prenom;
  private int numeroDePorte;
  private int codePostalClient;
  private String rueClient;
  private String villeClient;

  // ============ Constructor ============
  public Client(int numero, String nom, String prenom, int numeroDePorte,
                int codePostalClient, String rueClient, String villeClient) {
    this.numero = numero;
    this.nom = nom;
    this.prenom = prenom;
    this.numeroDePorte = numeroDePorte;
    this.codePostalClient = codePostalClient;
    this.rueClient = rueClient;
    this.villeClient = villeClient;
  }

  // ============ Getters and setters ============
  // Default getters and setters
  public int getNumero() {return numero;}
  public void setNumero(int numero) {this.numero = numero;}

  public String getNom() {return nom;}
  public void setNom(String nom) {this.nom = nom;}

  public String getPrenom() {return prenom;}
  public void setPrenom(String prenom) {this.prenom = prenom;}

  public int getNumeroDePorte() {return numeroDePorte;}
  public void setNumeroDePorte(int numeroDePorte) {this.numeroDePorte = numeroDePorte;}

  public int getCodePostalClient() {
    return codePostalClient;
  }
  public void setCodePostalClient(int codePostalClient) {
    this.codePostalClient = codePostalClient;
  }

  public String getRueClient() {
    return rueClient;
  }
  public void setRueClient(String rueClient) {
    this.rueClient = rueClient;
  }

  public String getVilleClient() {
    return villeClient;
  }
  public void setVilleClient(String villeClient) {
    this.villeClient = villeClient;
  }

  // ============ Custom Setter ============
  public void setAdresseClient(int numeroDePorte, int codePostalClient, String rueClient, String villeClient) {
    this.numeroDePorte = numeroDePorte;
    this.codePostalClient = codePostalClient;
    this.rueClient = rueClient;
    this.villeClient = villeClient;
  }

  // ============ Override Methods ============
  @Override
  public String toString() {
    return "Client{" +
        "numero=" + numero +
        ", nom='" + nom + '\'' +
        ", prenom='" + prenom + '\'' +
        ", numeroDePorte=" + numeroDePorte +
        ", codePostalClient=" + codePostalClient +
        ", rueClient='" + rueClient + '\'' +
        ", villeClient='" + villeClient + '\'' +
        '}';
  }
}
