public class CompteCourant extends CompteBancaire{
    private int decouvertAutorise;
    private boolean chequier;
    private CB carte;

    public double credit(double sommeCredit){
        return solde + sommeCredit;
    }

    public double debit(double sommeDebit){
        return solde - sommeDebit;
    }

    
}