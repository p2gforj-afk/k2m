import java.util.Date;
import java.util.HashSet;


public class GestionCompte implements ParametreCompteEpargne {
  private HashSet<CompteBancaire> listeCompte;

  // ============ Constructor ============
  public GestionCompte(HashSet<CompteBancaire> listeCompte) {
    this.listeCompte = listeCompte;
  }

  // ============ Getters and Setters ============
  public HashSet<CompteBancaire> getListeCompte() {
    return listeCompte;
  }
  public void setListeCompte(HashSet<CompteBancaire> listeCompte) {
    this.listeCompte = listeCompte;
  }

  // ============ Methods ============
  public void creerCompteCourant(int decouvertAutorise, boolean chequier,
                                 int carte, int numeroCompte, double solde,
                                 double credit, Client client, Date dateOuverture){
    listeCompte.add(new CompteCourant(solde, numeroCompte, dateOuverture, client, decouvertAutorise, chequier, carte));
  }

  public void creerCompteEpargne(double solde, boolean fiscalite,
                                 double renumeration, Date dateOuverture,
                                 int numeroCompte, Client client){
    listeCompte.add(new CompteEpargne(solde, numeroCompte, dateOuverture, client, renumeration, fiscalite));
  }
  public void supprimerCompte(CompteBancaire compte){
    listeCompte.remove(compte);
  }

  // ============ Override Methods ============
  @Override
  public String toString() {
    return "GestionCompte{" +
        "listeCompte=" + listeCompte +
        '}';
  }
}
