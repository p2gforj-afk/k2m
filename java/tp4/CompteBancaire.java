import java.util.Date;

public abstract class CompteBancaire {
  private final Date dateOuverture;
  private double solde;
  private int numeroCompte;
  private Client client;

  public CompteBancaire(double solde, int numeroCompte, Date dateOuverture, Client client) {
    this.solde = solde;
    this.numeroCompte = numeroCompte;
    this.dateOuverture = dateOuverture;
    this.client = client;
  }

  // ============ Getters and Setters ============
  public double getSolde() {
    return solde;
  }
  public void setSolde(double solde) {
    this.solde = solde;
  }

  public int getNumeroCompte() {
    return numeroCompte;
  }
  public void setNumeroCompte(int numeroCompte) {
    this.numeroCompte = numeroCompte;
  }

  public Client getClient() {
    return client;
  }
  public void setClient(Client client) {
    this.client = client;
  }

  public Date getDateOuverture() {
    return dateOuverture;
  }

  // ============ Abstract Methods ============
  public abstract void credit(double creditValue);
  public abstract void debit(double debitValue);

  // ============ Override Methods ============
  @Override
  public String toString() {
    return "CompteBancaire{" +
        "solde=" + solde +
        ", numeroCompte=" + numeroCompte +
        ", dateOuverture=" + dateOuverture +
        '}';
  }

}
