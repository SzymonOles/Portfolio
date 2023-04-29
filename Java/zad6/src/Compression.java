import java.util.*;
import java.util.stream.Collectors;

public class Compression implements CompressionInterface {
    LinkedList<String> wordlist = new LinkedList<>();
    LinkedList<String> wordlist2 = new LinkedList<>();
    Map<String, String> header = new HashMap<>();
    Map<Integer, Integer> wyniki = new HashMap<>();
    Map<String, Integer> wordcount = new HashMap<>();
    List<String> repeatlist = new ArrayList<>();
    int bitow;
    int wordlen;

    public void addWord(String word) {
        wordlist.add(word);
        wordlen=word.length();
    }

    public void compress() {
        //policz wystapienia slow
        for (String word :
                wordlist) {
            if (!wordcount.containsKey(word)) {
                wordcount.put(word, 1);
            } else {
                wordcount.replace(word, wordcount.get(word) + 1);
            }
        }
        //sortuj po ilosci wystapien
        final Map<String, Integer> wcount = wordcount.entrySet()
                .stream()
                .sorted((Map.Entry.<String, Integer>comparingByValue().reversed()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (e1, e2) -> e1, LinkedHashMap::new));

        //dlugosc kodu dla przypadkow
        for (int i = 0; i < wcount.size(); i++) {
            bitow = 0;
            if (i != 0) {
                bitow = (int)(Math.log(i) /
                        Math.log(2) + 1);
            }
            int zdjetebity = 0;
            int dodanebity = 0;
            int j = 0;
            for (Map.Entry<String, Integer> entry :
                    wcount.entrySet()) {
                if (j <= i) {
                    zdjetebity += (entry.getKey().length() - (bitow + 1)) * entry.getValue();
                } else {
                    dodanebity += entry.getValue();
                }
                j++;
            }
            //todo
//            System.out.println("slow: "+(i+1));
//            System.out.println(bitow);
//            System.out.println(zdjetebity);
//            System.out.println(dodanebity);

            wyniki.put(i, (dodanebity - zdjetebity)+((i+1)*wordlen)+((i+1)*(bitow+1)));
        }
        //sortuj po wyniku
        final Map<Integer, Integer> minwynik = wyniki.entrySet()
                .stream()
                .sorted((Map.Entry.comparingByValue()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (e1, e2) -> e1, LinkedHashMap::new));

        //co sie najbardziej oplaca
        Map.Entry<Integer, Integer> entr = minwynik.entrySet().iterator().next();
        int minval = entr.getKey();
        if (entr.getValue() >= 0) {
            minval = -1;
        }

        if (minval != -1) {

            bitow = 0;
            if (minval + 1 != 1) {
                if ((minval + 1) % 2 == 1)
                    bitow += 1;
                bitow += (minval + 1) / 2;
            }

            int j = 0;
            for (Map.Entry<String, Integer> entry :
                    wcount.entrySet()) {
                if (j <= minval) {
                    repeatlist.add(entry.getKey());
                } else {
                    break;
                }
                j++;
            }

            //kodowanie do headera
            if (repeatlist.size() == 1) {
                header.put(repeatlist.get(0), "0");
            } else {
                for (int i = 0; i < repeatlist.size(); i++) {
                    header.put(repeatlist.get(i), fillwith(bitow, i));
                }
            }
            //zamiana w wordliscie
            for (String wrd :
                    wordlist) {
                if (header.containsKey(wrd)) {
                    wordlist2.add(header.get(wrd));
                } else {
                    wordlist2.add("1" + wrd);
                }
            }
        } else {
            header.clear();
        }
        //test todo
//        System.out.println(wcount);
//        System.out.println(wyniki);
//        System.out.println(repeatlist);
//        System.out.println(wordlist2);
    }

    public Map<String, String> getHeader() {

        Map<String, String> invheader = new HashMap<>();

        for (Map.Entry<String, String> entry : header.entrySet())
            invheader.put(entry.getValue(), entry.getKey());

        return invheader;
    }

    public String getWord() {
        if (!wordlist2.isEmpty())
            return wordlist2.removeFirst();
        else
            return wordlist.removeFirst();
    }

    private String fillwith(int bit, int i) {
        String s = "0";
        String ival = Integer.toBinaryString(i);
        if (ival.length() < bit) {
            for (int j = 0; j < bit - ival.length(); j++) {
                ival = "0" + ival;
            }
        }
        s = s + ival;
        return s;
    }
}
