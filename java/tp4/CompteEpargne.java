import java.util.Date;

public class CompteEpargne extends CompteBancaire implements ParametreCompteEpargne {
  private double renumeration;
  private boolean fiscalite;

  // ============ Constructor ============
  public CompteEpargne(double solde, int numeroCompte, Date dateOuverture, Client client, double renumeration, boolean fiscalite) {
    super(solde+VERSEMENT_INITIAL, numeroCompte, dateOuverture, client);
    this.renumeration = renumeration;
    this.fiscalite = fiscalite;
  }

  // ============ Getters and Setters ============
  public double getRenumeration() {return renumeration;}
  public void setRenumeration(double renumeration) {this.renumeration = renumeration;}

  public boolean isFiscalite() {return fiscalite;}
  public void setFiscalite(boolean fiscalite) {this.fiscalite = fiscalite;}

  // ============ Methods ============
  public double calculInteret(double taux, double duree){
    if (fiscalite)
      return getSolde()*(taux-0.186)*duree;
    else
      return getSolde()*taux*duree;
  }

  // ============ Override Methods ============
  @Override
  public void credit(double creditValue) {
    double value = getSolde()+creditValue;
    if (value>PLAFOND)
      setSolde(value);
  }

  @Override
  public void debit(double debitValue) {
    double newValue=getSolde() - debitValue;
    if (newValue < MINIMUM_SUR_LE_COMPTE)
      setSolde(newValue);
  }


}
