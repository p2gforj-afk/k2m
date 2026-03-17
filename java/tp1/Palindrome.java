public class Palindrome{
    public static void main(String[] args) {
        boolean flag = true;
        String mot = args[0];
        for(int i = 1; i<args.length; i++){
        mot = mot.concat(args[i]);
        }
        mot = mot.toLowerCase();
        int len = mot.length();
        for (int i = 0; i<len/2; i++){
            if(!(mot.substring(i,i+1).equals(mot.substring(len-i-1, len-i)))){
                flag = false;
            }
        }
        System.out.println(flag);
    }
}