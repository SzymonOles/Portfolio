public class Main {

    public static void main(String[] args) {

        String a = "0101101110111100000"; //oczekiwano 0123
        String b = "10111100001010110"; // oczekiwano 03001
        DecoderInterface dec = new Decode();

        for (int i = 0; i < b.length(); i++) {
            dec.input(Character.getNumericValue(b.charAt(i)));
        }
        System.out.println(dec.output());

        dec.reset();

        System.out.println(dec.output());
    }
}
