import java.util.Date;

public class CompteCourant extends CompteBancaire {
  private int decouvertAutorise;
  private boolean chequier;
  private int carte;

  // ============ Constructor ============
  public CompteCourant(double solde, int numeroCompte, Date dateOuverture, Client client, int decouvertAutorise,
      boolean chequier, int carte) {
    super(solde, numeroCompte, dateOuverture, client);
    this.decouvertAutorise = decouvertAutorise;
    this.chequier = chequier;
    this.carte = carte;
  }

  public int getDecouvertAutorise() {
    return decouvertAutorise;
  }

  public void setDecouvertAutorise(int decouvertAutorise) {
    this.decouvertAutorise = decouvertAutorise;
  }

  public boolean isChequier() {
    return chequier;
  }

  public void setChequier(boolean chequier) {
    this.chequier = chequier;
  }

  public int getCarte() {
    return carte;
  }

  public void setCarte(int carte) {
    this.carte = carte;
  }

  // ============ Override Methods ============
  @Override
  public void credit(double creditValue) {
    setSolde(getSolde() + creditValue);
  }

  @Override
  public void debit(double debitValue) {
    double NewValue = getSolde() - debitValue;
    if (-NewValue < decouvertAutorise) {
      setSolde(NewValue);
    } else {
      System.out.println("operation non valide, depassement du decouvert");
    }
  }
}
