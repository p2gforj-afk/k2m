

public class MonPremierCodeJava{
    public static void HelloWorld(){
        System.out.println("Hello World !");
    }

    public static void main(String[] args) {
        MonPremierCodeJava.HelloWorld();
        for (int i = 0; i<args.length; i++){
            System.out.println(args[i]);
        }
    }
}