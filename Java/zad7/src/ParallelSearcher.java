import java.util.ArrayList;

public class ParallelSearcher implements ParallelSearcherInterface {

    HidingPlaceSupplier sup;

    class Value {
        double PrevVal = 0;

        public synchronized void Increment(HidingPlaceSupplier.HidingPlace HP) {
            PrevVal += HP.openAndGetValue();
        }

        public synchronized void setPrevVal(double prevVal) {
            PrevVal = prevVal;
        }

        public synchronized double getPrevVal() {
            return PrevVal;
        }

    }

    Value v = new Value();

    public class Opener extends Thread {

        public void run() {

            while (true) {
                HidingPlaceSupplier.HidingPlace HP = sup.get();
                if (HP == null) {
                    return;
                } else if (HP.isPresent()) {
                    v.Increment(HP);
                }
            }

        }
    }

    public void set(HidingPlaceSupplierSupplier supplier) {
        ArrayList<Opener> arrThreads = new ArrayList();

        while (true) {
            sup = supplier.get(v.getPrevVal());
            v.setPrevVal(0);

            if (sup == null) {
                return;
            }

            arrThreads.clear();
            for (int i = 0; i < sup.threads(); i++) {
                Opener obj = new Opener();
                obj.start();
                arrThreads.add(obj);
            }

            for (int i = 0; i < arrThreads.size(); i++) {
                try {
                    arrThreads.get(i).join();
                } catch (InterruptedException ignored) {
                }
            }
        }
    }

}
