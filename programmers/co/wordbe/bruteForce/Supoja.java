package co.wordbe.bruteForce;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

public class Supoja {

    public static class Rank {
        public int num;
        public int cnt;

        public Rank(int num, int cnt) {
            this.num = num;
            this.cnt = cnt;
        }
    }

    public static int[] solution(int[] answers) {

        int[] supoja1 = new int[]{1, 2, 3, 4, 5};
        int[] supoja2 = new int[]{2, 1, 2, 3, 2, 4, 2, 5};
        int[] supoja3 = new int[]{3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
        ArrayList<Rank> ranks = new ArrayList<>(3);
        ranks.add(new Rank(1, 0));
        ranks.add(new Rank(2, 0));
        ranks.add(new Rank(3, 0));

        for (int i=0; i<answers.length; i++) {
            if (answers[i] == supoja1[i % 5]) ranks.get(0).cnt++;
            if (answers[i] == supoja2[i % 8]) ranks.get(1).cnt++;
            if (answers[i] == supoja3[i % 10]) ranks.get(2).cnt++;
        }
        Comparator<Rank> comparator = (o1, o2) -> {
            if (o2.cnt >= o1.cnt) {
                return 1;
            }
            return -1;
        };
        ranks.sort(comparator);

        ArrayList<Integer> ans = new ArrayList<>();
        ans.add(ranks.get(0).num);
        if (ranks.get(0).cnt == ranks.get(1).cnt) {
            ans.add(ranks.get(1).num);
            if (ranks.get(1).cnt == ranks.get(2).cnt) {
                ans.add(ranks.get(2).num);
            }
        }

        int[] finalAns = new int[ans.size()];
        for (int i=0; i<ans.size(); i++) {
            finalAns[i] = ans.get(i);
        }

        return finalAns;
    }
}
