import java.util.Date;

abstract class CompteBancaire{
    public double solde;
    private int numeroCompte;
    private Date dateOuverture;
    private Client client;

    
    public void setNumeroCompte(int numeroCompte) {
        this.numeroCompte = numeroCompte;
    }


    public int getNumeroCompte() {
        return numeroCompte;
    }


    public Date getDateOuverture() {
        return dateOuverture;
    }

    public Client getClient(){
        return client;
    }


    @Override
    public String toString() {
        return "CompteBancaire [solde=" + solde + ", numeroCompte=" + numeroCompte + ", dateOuverture=" + dateOuverture
                + ", client=" + client + "]";
    }
    
    abstract double credit(double sommeCredit);
    abstract double debit(double sommeDebit);
}