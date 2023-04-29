import java.util.HashMap;
import java.util.Map;

public class Shop implements ShopInterface {

    Map<String, Integer> supply = new HashMap<>();
    Map<String, Object> keymap = new HashMap<>();
    final Object check = new Object();

    public void delivery(Map<String, Integer> goods) {
        for (Map.Entry<String, Integer> e :
                goods.entrySet()) {
            synchronized (check){
                if (!keymap.containsKey(e.getKey())) {
                    keymap.put(e.getKey(), new Object());
                }
            }
            synchronized (keymap.get(e.getKey())) {
                if (!supply.containsKey(e.getKey())) {
                    supply.put(e.getKey(), e.getValue());
                } else {
                    supply.replace(e.getKey(), supply.get(e.getKey()) + e.getValue());
                }
                keymap.get(e.getKey()).notifyAll();
            }
        }
    }

    public boolean purchase(String productName, int quantity) {
        synchronized (check) {
            if (!keymap.containsKey(productName)) {
                keymap.put(productName, new Object());
            }
        }
        synchronized (keymap.get(productName)) {
            boolean triedtopurchase = false;

            while (true) {

                if (!supply.containsKey(productName)) {
                    try {
                        triedtopurchase = true;
                        keymap.get(productName).wait();
                    } catch (InterruptedException ignored) {
                    }

                } else {
                    if (supply.get(productName) < quantity) {

                        if (!triedtopurchase) {
                            try {
                                triedtopurchase = true;
                                keymap.get(productName).wait();
                            } catch (InterruptedException ignored) {
                            }

                        } else {
                            return false;
                        }
                    } else {
                        supply.replace(productName, supply.get(productName) - quantity);
                        return true;
                    }

                }
            }
        }
    }

    public Map<String, Integer> stock() {
        return supply;
    }
}
//md5 asdasdasdasdasd