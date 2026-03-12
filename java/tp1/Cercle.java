public class Cercle{
    public static void main(String[] args) {
        if (args.length != 1){
            System.err.println("vous devez indiquer en parametre le rayon du cercle");
        }
        else{
            float rayon = Float.valueOf(args[0]);
            double aire = rayon * Math.PI * rayon;
            double perimetre = rayon * Math.PI * 2;
            System.out.println("L'aire du cercle de rayon " + rayon + " est : " + aire);
            System.out.println("Le perimetre du cercle de rayon " + rayon + " est : " + perimetre);

        }

    }
}