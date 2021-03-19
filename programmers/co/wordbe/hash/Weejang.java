package co.wordbe.hash;

import java.util.HashMap;
import java.util.Iterator;

public class Weejang {
    public static int solution(String[][] clothes) {
        int answer = 1;

        HashMap<String, Integer> types = new HashMap<>();
        for (int i=0; i<clothes.length; i++) {
            String type = clothes[i][1];

            Integer value = types.get(type);
            if (value == null) {
                types.put(type, 1);
            } else {
                types.put(type, value + 1);
            }
        }

        Iterator<String> keys = types.keySet().iterator();
        while (keys.hasNext()) {
            String key = keys.next();
            Integer val = types.get(key);
            answer = answer * (val + 1);
        }

        return answer - 1;
    }
}
