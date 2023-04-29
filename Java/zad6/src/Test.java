public class Test {
    public static void main(String[] args) {
        Compression aaa = new Compression();
        String line = "000 001 000 001 000 001 000 001 011 001 000 110 001 000 111 001 001 000 000 000 001";
        String[] split = line.split("\\s+");
        for (String s : split
        ) {
            aaa.addWord(s);
        }
        aaa.compress();
        System.out.println(aaa.getHeader());
        for (String s :
                split) {
            System.out.println(aaa.getWord());
        }
    }
}
