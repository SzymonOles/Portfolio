import java.util.*;

public class BusLine implements BusLineInterface {

    Map<String, List<Position>> mapa = new HashMap<>();
    Map<String, List<LineSegment>> segments = new HashMap<>();
    Map<String, List<Position>> simpleskrzyzowania = new HashMap<>();
    Map<String, List<String>> skrzyzowanialinie = new HashMap<>();
    Map<String, Map<String, List<Position>>> skrzyzowania = new HashMap<>();
    Map<String, Position> fp = new HashMap<>();
    Map<String, Position> lp = new HashMap<>();

    static class LinesPair implements BusLineInterface.LinesPair {
        String name1;
        String name2;

        public String getFirstLineName() {
            return name1;
        }

        public String getSecondLineName() {
            return name2;
        }

        public LinesPair(String name1, String name2) {
            this.name1 = name1;
            this.name2 = name2;
        }
    }

    public void addBusLine(String busLineName, Position firstPoint, Position lastPoint) {
        mapa.put(busLineName, new ArrayList<>());
        fp.put(busLineName, firstPoint);
        lp.put(busLineName, lastPoint);
    }

    public void addLineSegment(String busLineName, LineSegment lineSegment) {
        if (lineSegment.getFirstPosition().equals(fp.get(busLineName))) {
            mapa.get(busLineName).addAll(wypelnijliste(lineSegment.getFirstPosition(), lineSegment.getLastPosition()));
            fp.replace(busLineName, lineSegment.getLastPosition());
            if (lineSegment.getLastPosition().equals(lp.get(busLineName))) {
                mapa.get(busLineName).add(lp.get(busLineName));
            }
        } else {
            if (segments.containsKey(busLineName)) {
                segments.get(busLineName).add(lineSegment);
            } else {
                List<LineSegment> templs = new ArrayList<>();
                templs.add(lineSegment);
                segments.put(busLineName, templs);
            }
        }
        fitsegments();
    }

    public void findIntersections() {
        skrzyzowania.clear();
        simpleskrzyzowania.clear();
        skrzyzowanialinie.clear();
        int l1 = 0;
        int l2;
        int z1;
        int z2;
        for (Map.Entry<String, List<Position>> entry : mapa.entrySet())  //kazda linia
        {
            List<Position> listpos1 = entry.getValue();
            z1 = 0;
            for (Position pos1 : listpos1)  //dla kazdej zmiennej
            {
                l2 = 0;
                for (Map.Entry<String, List<Position>> entry2 : mapa.entrySet()) {
                    List<Position> listpos2 = entry2.getValue();
                    z2 = 0;
                    for (Position pos2 : listpos2)   //kazda zmienna dla kazdej zmiennej
                    {
                        if (l1 == l2 && z1 == z2) {
                            z2++;
                            continue;
                        }
                        if (pos1.equals(pos2)) { //porownanie kazdych dwoch zmiennych
                            boolean skrz = false;

                            // -- |
                            if (((listpos1.contains(newpos(pos1, -1, 0))) && (listpos1.contains(newpos(pos1, 1, 0))))
                                    && ((listpos2.contains(newpos(pos2, 0, -1))) && (listpos2.contains(newpos(pos2, 0, 1))))) {
                                skrz = true;
//                                System.out.println("1 "+ entry.getKey()+ ":" +pos1+" "+ entry2.getKey()+ ":" +pos2);
                            }
                            // \ /
                            else if (((listpos1.contains(newpos(pos1, -1, -1))) && (listpos1.contains(newpos(pos1, 1, 1))))
                                    && ((listpos2.contains(newpos(pos2, -1, 1))) && (listpos2.contains(newpos(pos2, 1, -1))))) {
                                skrz = true;
//                                System.out.println("2 "+ entry.getKey()+ ":" +pos1+" "+ entry2.getKey()+ ":" +pos2);
                            }
                            // | --
                            else if (((listpos1.contains(newpos(pos1, 0, -1))) && (listpos1.contains(newpos(pos1, 0, 1))))
                                    && ((listpos2.contains(newpos(pos2, -1, 0))) && (listpos2.contains(newpos(pos2, 1, 0))))) {
                                skrz = true;
//                                System.out.println("3 "+ entry.getKey()+ ":" +pos1+" "+ entry2.getKey()+ ":" +pos2);
                            }
                            // / \
                            else if (((listpos1.contains(newpos(pos1, -1, 1))) && (listpos1.contains(newpos(pos1, 1, -1))))
                                    && ((listpos2.contains(newpos(pos2, -1, -1))) && (listpos2.contains(newpos(pos2, 1, 1))))) {
                                skrz = true;
//                                System.out.println("4 "+ entry.getKey()+ ":" +pos1+" "+ entry2.getKey()+ ":" +pos2);
                            }

                            if (skrz) {

                                if (skrzyzowania.containsKey(entry.getKey())) { //ma klucz
                                    if (skrzyzowania.get(entry.getKey()).containsKey(entry2.getKey())) { //ma klucz klucza
                                        skrzyzowania.get(entry.getKey()).get(entry2.getKey()).add(pos1);
                                    } else {   //nie ma klucza klucza
                                        List<Position> plist = new ArrayList<>();
                                        plist.add(pos1);
                                        skrzyzowania.get(entry.getKey()).put(entry2.getKey(), plist);
                                    }
                                } else {//nie ma klucza
                                    List<Position> plist = new ArrayList<>();
                                    plist.add(pos1);
                                    Map<String, List<Position>> tempmap = new HashMap<>();
                                    tempmap.put(entry2.getKey(), plist);
                                    skrzyzowania.put(entry.getKey(), tempmap);
                                }

                                if (simpleskrzyzowania.containsKey(entry.getKey())) {
                                    simpleskrzyzowania.get(entry.getKey()).add(pos1);
                                } else {
                                    List<Position> templpos = new ArrayList<>();
                                    templpos.add(pos1);
                                    simpleskrzyzowania.put(entry.getKey(), templpos);
                                }

                                if (skrzyzowanialinie.containsKey(entry.getKey())) {
                                    skrzyzowanialinie.get(entry.getKey()).add(entry2.getKey());
                                } else {
                                    List<String> templpos = new ArrayList<>();
                                    templpos.add(entry2.getKey());
                                    skrzyzowanialinie.put(entry.getKey(), templpos);
                                }
                            }
                        }
                        z2++;
                    }
                    l2++;
                }
                z1++;
            }
            l1++;
        }
    }

    public Map<String, List<Position>> getLines() {
        fitsegments();
        findIntersections();
        Map<String, List<Position>> tmap = new HashMap<>(mapa);
        Set<Map.Entry<String, List<Position>>> entrySet = mapa.entrySet();
        for (Map.Entry<String, List<Position>> entry : entrySet) {
            String key = entry.getKey();
            if (!simpleskrzyzowania.containsKey(key)) {
                tmap.remove(key);
            }
        }
        System.out.println(tmap);
        return tmap;
    }

    public Map<String, List<Position>> getIntersectionPositions() {
        return simpleskrzyzowania;
    }

    public Map<String, List<String>> getIntersectionsWithLines() {
        return skrzyzowanialinie;
    }

    public Map<BusLineInterface.LinesPair, Set<Position>> getIntersectionOfLinesPair() {
        Map<BusLineInterface.LinesPair, Set<Position>> slp = new HashMap<>();
        Set<String> linie = mapa.keySet();
        for (String linia1 : linie) {
            for (String linia2 : linie) {
                slp.put(new LinesPair(linia1, linia2), new HashSet<>());
            }
        }
        for (Map.Entry<BusLineInterface.LinesPair, Set<Position>> para : slp.entrySet()) {
            for (Map.Entry<String, Map<String, List<Position>>> pierwsza : skrzyzowania.entrySet()) {
                for (Map.Entry<String, List<Position>> druga : pierwsza.getValue().entrySet()) {
                    if (para.getKey().getFirstLineName().equals(pierwsza.getKey()) && para.getKey().getSecondLineName().equals(druga.getKey())) {
                        para.getValue().addAll(druga.getValue());
                    }
                }
            }
        }

        return slp;
    }

    void fitsegments() {
        for (Map.Entry<String, List<LineSegment>> entry : segments.entrySet()) {
            for (LineSegment segment : entry.getValue()) {
                if (segment.getFirstPosition().equals(fp.get(entry.getKey()))) {
                    mapa.get(entry.getKey()).addAll(wypelnijliste(segment.getFirstPosition(), segment.getLastPosition()));
                    entry.getValue().remove(segment);
                    fp.replace(entry.getKey(), segment.getLastPosition());
                    if (segment.getLastPosition().equals(lp.get(entry.getKey()))) {
                        mapa.get(entry.getKey()).add(lp.get(entry.getKey()));
                    }
                    fitsegments();
                    return;
                }
            }
        }
    }

    Position newpos(Position pos, int col, int row) {
        return new Position2D(pos.getCol() + col, pos.getRow() + row);
    }

    List<Position> wypelnijliste(Position fp, Position lp) {
        List<Position> lis = new ArrayList<>();

        //pionowa
        if (fp.getCol() == lp.getCol()) {
            //w dol
            if (fp.getRow() < lp.getRow()) {
                for (int i = 0; i < (lp.getRow() - fp.getRow()); i++) {
                    lis.add(new Position2D(fp.getCol(), fp.getRow() + i));
                }
            }
            //w gore
            else {
                for (int i = 0; i < (fp.getRow() - lp.getRow()); i++) {
                    lis.add(new Position2D(fp.getCol(), fp.getRow() - i));
                }
            }
        }
        //pozioma
        else if (fp.getRow() == lp.getRow()) {
            //w prawo
            if (fp.getCol() < lp.getCol()) {
                for (int i = 0; i < (lp.getCol() - fp.getCol()); i++) {
                    lis.add(new Position2D(fp.getCol() + i, fp.getRow()));
                }
            }
            //w lewo
            else {
                for (int i = 0; i < (fp.getCol() - lp.getCol()); i++) {
                    lis.add(new Position2D(fp.getCol() - i, fp.getRow()));
                }
            }
        }
        //ukosna \ w dol
        else if ((fp.getRow() < lp.getRow() && fp.getCol() < lp.getCol())) {
            for (int i = 0; i < (lp.getRow() - fp.getRow()); i++) {
                lis.add(new Position2D(fp.getCol() + i, fp.getRow() + i));
            }
        }
        //ukosna \ w gore
        else if ((fp.getRow() > lp.getRow() && fp.getCol() > lp.getCol())) {
            for (int i = 0; i < (fp.getRow() - lp.getRow()); i++) {
                lis.add(new Position2D(fp.getCol() - i, fp.getRow() - i));
            }
        }
        //ukosna /
        else {
            //w dol
            if (fp.getRow() < lp.getRow()) {
                for (int i = 0; i < (lp.getRow() - fp.getRow()); i++) {
                    lis.add(new Position2D(fp.getCol() - i, fp.getRow() + i));
                }
            }
            //w gore
            else {
                for (int i = 0; i < (fp.getRow() - lp.getRow()); i++) {
                    lis.add(new Position2D(fp.getCol() + i, fp.getRow() - i));
                }
            }
        }
        return lis;
    }

}
//md5 asdasdasdsa