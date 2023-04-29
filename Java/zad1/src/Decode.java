class Decode extends DecoderInterface {

    String wejscie = "";
    String wynik = "";

    public void input(int bit) {
        wejscie += bit;
    }

    public String output() {

        int x = 0;
        boolean pomijaczera = true;

        for (int i = 0; i < wejscie.length(); i++) {    //szukam x
            if (wejscie.charAt(i) == '0' && pomijaczera) {
                continue;
            } else if (wejscie.charAt(i) == '1') {
                x++;
                pomijaczera = false;
            } else {
                break;
            }
        }

        for (int i = 0; i < wejscie.length(); i++) {    //dla kazdej liczby
            int var = 0;
            if (wejscie.charAt(i) == '0') {
                continue;
            }
            else if (wejscie.charAt(i) == '1'){
                for (int j = i; j < wejscie.length(); j++) {    //dla jedynki
                    if (wejscie.charAt(j) == '1'){
                    var++;
                    i++;
                    }
                    else if (wejscie.charAt(j) == '0'){
                        wynik+= ((var/x)-1);
                        break;
                    }
                }
            }
        }
        return wynik;
    }

    public void reset() {
        wejscie = "";
        wynik = "";
    }
}

