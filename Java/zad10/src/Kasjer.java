import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.function.Supplier;

public class Kasjer implements KasjerInterface {
    List<Pieniadz> kasa = new ArrayList<>();
    RozmieniaczInterface rozmieniacz;

    public List<Pieniadz> rozlicz(int cena, List<Pieniadz> pieniadze) {
        List<Pieniadz> reszta = new ArrayList<>();
        List<Pieniadz> nrozm = new ArrayList<>();
        List<Pieniadz> rozm = new ArrayList<>();
        int nsuma = 0;
        int rsuma = 0;

        for (Pieniadz p :
                pieniadze) {
            if (!p.czyMozeBycRozmieniony()) {
                nrozm.add(p);
                nsuma += p.wartosc();
            } else {
                rozm.add(p);
                rsuma += p.wartosc();
            }
        }

        rozmienkase();

        if (rsuma + nsuma <= cena) {
            if (rozm.size() != 0) {
                kasa.addAll(rozm);
            }
            if (nrozm.size() != 0) {
                kasa.addAll(nrozm);
            }
            return reszta;
        }
        if (nsuma < cena) {
            int dowydania;
            cena -= nsuma;
            dowydania = rsuma - cena;

            if (rozm.size() != 0) {
                kasa.addAll(rozm);
            }

            rozmienkase();

            while (dowydania > 0) {
                if (kasa.get(0).czyMozeBycRozmieniony()) {
                    dowydania -= kasa.get(0).wartosc();
                    reszta.add(kasa.remove(0));
                } else {
                    kasa.add(kasa.remove(0));
                }
            }

            if (nrozm.size() != 0) {
                kasa.addAll(nrozm);
            }

        }
        //nsuma > cena // brak rozmienialnych z zalozenia
        else {

            //min
            int min = 501;
            int minid = 0;
            for (int i = 0; i < nrozm.size(); i++) {
                if (nrozm.get(i).wartosc() < min) {
                    min = nrozm.get(i).wartosc();
                    minid = i;
                }
            }
            int dowydania;
            dowydania = nsuma - cena;

            rozmienkase();


            //wydaj reszte
            if (!kasa.isEmpty()) {
                while (dowydania > 0) {
                    int kasaRsum = 0;
                    for (Pieniadz pieniadz : kasa) {
                        if (pieniadz.czyMozeBycRozmieniony())
                            kasaRsum += pieniadz.wartosc();
                    }
                    if (kasaRsum >= dowydania) {
                        for (int i = 0; i < kasa.size(); i++) {
                            if (kasa.get(i).czyMozeBycRozmieniony()) {
                                dowydania -= kasa.get(i).wartosc();
                                reszta.add(kasa.remove(i));
                                if (dowydania <= 0)
                                    break;
                                i--;
                            }
                        }
                    } else {
                        int maxim = 0;
                        int maximid = -1;
                        for (int i = 0; i < kasa.size(); i++) {
                            if (kasa.get(i).wartosc() >= maxim && kasa.get(i).wartosc() <= dowydania) {
                                maximid = i;
                                maxim = kasa.get(i).wartosc();
                            }
                        }
                        if (maximid == -1) {
                            for (int i = 0; i < kasa.size(); i++) {
                                if (kasa.get(i).wartosc() >= maxim) {
                                    maximid = i;
                                    maxim = kasa.get(i).wartosc();
                                }
                            }
                        }
                        dowydania -= kasa.get(maximid).wartosc();
                        reszta.add(kasa.remove(maximid));
                    }
                }
                //brute force
                if (dowydania != 0) {
                    Random generator = new Random();
                    kasa.addAll(reszta);
                    reszta.clear();
                    int dowyd = -1;
                    List<Pieniadz> tempreszta = new ArrayList<>();
                    List<Pieniadz> NRkasa = new ArrayList<>();
                    while (dowyd != 0) {
                        dowyd = nsuma - cena;
                        tempreszta.clear();
                        NRkasa.clear();
                        for (Pieniadz pieniadz : kasa) {
                            if (!pieniadz.czyMozeBycRozmieniony()) {
                                NRkasa.add(pieniadz);
                            }
                        }
                        while (dowyd > 0) {
                            int size = NRkasa.size();
                            int numer = generator.nextInt(size);
                            dowyd-=NRkasa.get(numer).wartosc();
                            tempreszta.add(NRkasa.remove(numer));
                        }
                    }
                    reszta.addAll(tempreszta);
                    for (int i = 0; i < reszta.size(); i++) {
                        for (int j = 0; j < kasa.size(); j++) {
                            if (reszta.get(i).numerSeryjny() == kasa.get(j).numerSeryjny()){
                                kasa.remove(j);
                                break;
                            }
                        }
                    }
                }
            }

            //oddaj nierozmienialny
            if (nrozm.size() != 0) {
                for (int i = 0; i < nrozm.size(); i++) {
                    if (i != minid) {
                        kasa.add(nrozm.get(i));
                    }
                }
                reszta.add(nrozm.get(minid));
            }


        }
        return reszta;
    }

    public List<Pieniadz> stanKasy() {
        return kasa;
    }

    public void dostępDoRozmieniacza(RozmieniaczInterface rozm) {
        rozmieniacz = rozm;
    }

    public void dostępDoPoczątkowegoStanuKasy(Supplier<Pieniadz> dostawca) {
        kasa.clear();
        Pieniadz temp = dostawca.get();

        while (temp != null) {
            kasa.add(temp);
            temp = dostawca.get();
        }
    }

    private void rozmienkase() {
        if (kasa != null) {
            if (!kasa.isEmpty()) {
                List<Pieniadz> temp;
                boolean rozmieniono = true;
                while (rozmieniono) {
                    rozmieniono = false;
                    for (int i = 0; i < kasa.size(); i++) {
                        if (kasa.get(i).wartosc() != 1 && kasa.get(i).czyMozeBycRozmieniony()) {
                            temp = rozmieniacz.rozmien(kasa.remove(i));
                            i--;
                            kasa.addAll(temp);
                            rozmieniono = true;
                        }
                    }
                }
            }
        }
    }
}
