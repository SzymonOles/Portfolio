import java.util.ArrayList;
import java.util.List;

public class Loops implements GeneralLoops {

    List<Integer> lower = new ArrayList<>();
    List<Integer> upper = new ArrayList<>();
    List<List<Integer>> out = new ArrayList<List<Integer>>();
    int listsize = 1;
    boolean changedlower = false;
    boolean changedupper = false;
    boolean changedvar = false;
    List<Integer> var = new ArrayList<>();

    //ustaw limit dolny
    public void setLowerLimits(List<Integer> limits) {
        lower = limits;
        listsize = lower.size();
        changedlower = true;
    }

    //ustaw limit gorny
    public void setUpperLimits(List<Integer> limits) {
        upper = limits;
        listsize = upper.size();
        changedupper = true;
    }

    //wynik
    public List<List<Integer>> getResult() {
        out.clear();                                //wyszysc out dla wiekszej ilosci powtorzen
        if (!changedupper && !changedlower) {       //testy dla pustych danych wejsciowych
            upper.add(0);
            lower.add(0);
            changedlower = true;
            changedupper = true;
        } else if (!changedupper) {
            for (int i = 0; i < lower.size(); i++) {
                upper.add(0);
                changedupper = true;
            }
        } else if (!changedlower) {
            for (int i = 0; i < upper.size(); i++) {
                lower.add(0);
                changedlower = true;
            }
        }
        else if (lower.size()<upper.size()){
            for (int i = 0; i < upper.size()-lower.size(); i++) {
                lower.add(0);
            }
        }
        else if (lower.size()>upper.size()){
            for (int i = 0; i < lower.size()-upper.size(); i++) {
                lower.add(0);
            }
        }
        if (!changedvar) {                              //testy rozmiaru dla tabeli w tabeli tabel
            for (int i = 0; i < listsize; i++) {
                var.add(0);
            }
            changedvar = true;
        }
        else if(var.size()<listsize){
            for (int i = 0; i < listsize-var.size(); i++) {
                var.add(0);
            }
        }
        Loop(0);                                        //wywolaj glowny program
        return out;
    }

    private void Loop(int i) {
        for (int licznik = lower.get(i); licznik <= upper.get(i); licznik++) {  //petla dla danych wejsciowych
            var.set(i, licznik);                                                //ustawianie zmiennej w arrayu na licznik
            if (i + 1 < listsize) {                                             //wywoylwanie podpetli
                Loop(i + 1);
            } else {                                                            //dla ostatniej podpetli skopiuj wynik z arraya i wpisz do tabeli tabel wynikow
                List<Integer> tmp = new ArrayList<>();
                for (int j = 0; j < var.size(); j++) {
                    tmp.add(var.get(j));
                }
                out.add(tmp);
            }
        }
    }
}
