import java.util.*;

public class Decrypter implements DecrypterInterface {

    boolean strnull = true;
    String str;
    Map<Character, Character> kod = new TreeMap<>();
    Map<Character, Character> dekod = new TreeMap<>();

    int[] siz = {7, 7, 10, 1, 11, 10};
    String base = "Wydział Fizyki, Astronomii i Informatyki Stosowanej";
    List<String> lista;
    List<String> templatka;

    public void setInputText(String encryptedDocument) {
        strnull = true;
        kod.clear();
        dekod.clear();
        if (encryptedDocument == null) {
            return;
        }
        str = encryptedDocument;
        strnull = false;
        lista = Arrays.asList(str.split("\\s+"));
        templatka = Arrays.asList(base.split("\\s+"));
    }

    public Map<Character, Character> getCode() {
        if (!strnull) {
            //szukanie odpowiednich dlugosci - found = indeks pierwszego el. inaczej -1
            int found = find(0);

            //mapowanie
            if (found != -1) {
                wsadz(found);
            }

        }
        return kod;
    }

    public Map<Character, Character> getDecode() {
        if (!strnull) {
            for (Map.Entry<Character, Character> entry : kod.entrySet()) {
                dekod.put(entry.getValue(), entry.getKey());
            }

        }
        return dekod;
    }

    private int find(int x) {
        int found = -1;
        for (int i = x; i < lista.size(); i++) {
            if (found == -1) {
                for (int j = 0; j < siz.length; j++) {
                    if (i + j > lista.size()) {
                        found = -1;
                        break;
                    } else if (lista.get(i + j).length() != siz[j]) {
                        found = -1;
                        break;
                    } else {
                        found = i;
                    }
                }
            }
        }
        return found;
    }

    private void wsadz(int found) {
        kod.clear();
        for (int i = 0; i < siz.length; i++) {  //dla slowa
            for (int j = 0; j < siz[i]; j++) {  //dla litery
                //case'y

                if (templatka.get(i).charAt(j) == ',' && lista.get(i + found).charAt(j) != ',') {
                    if (find(found + 1) != -1) {
                        wsadz(find(found + 1));
                    }
                    return;
                } else if (templatka.get(i).charAt(j) == ',') {
                    continue;
                }


                //jesli zawiera klucz
                if (kod.containsKey(templatka.get(i).charAt(j))) {
                    //jesli wartosc nie pasuje
                    if (kod.get(templatka.get(i).charAt(j)) != lista.get(i + found).charAt(j)) {
                        kod.clear();
                        if (find(found + 1) != -1) {
                            wsadz(find(found + 1));
                        }
                        return;
                    }
                }
                //jesli nie ma tego klucza
                else {
                    //jesli ma wartosc
                    if (kod.containsValue(lista.get(i + found).charAt(j))) {
                        kod.clear();
                        if (find(found + 1) != -1) {
                            wsadz(find(found + 1));
                        }
                        return;
                    }
                    //jesli nie ma wartosci
                    else {
                        //wsadzanie
                        if (lista.get(i + found).charAt(j) == ',') {
                            if (find(found + 1) != -1) {
                                wsadz(find(found + 1));
                            }
                            return;
                        }
                        kod.put(templatka.get(i).charAt(j), lista.get(i + found).charAt(j));
                    }
                }
            }
        }
    }
}
//zmiana md5 123123213asd
