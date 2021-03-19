package co.wordbe.hash;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class BestAlbum {

    public static class Pair {
        public int id;
        public int playNum;

        public Pair(int id, int playNum) {
            this.id = id;
            this.playNum = playNum;
        }


    }

    public static int[] solution(String[] genres, int[] plays) {
        HashMap<String, Integer> genreSum = new HashMap<>();

        HashMap<String, ArrayList<Pair>> playOrder = new HashMap<>();
        for (int i=0; i<genres.length; i++) {
            String genre = genres[i];
            Integer play = plays[i];

            Integer ret = genreSum.get(genre);
            if (ret == null) {
                genreSum.put(genre, play);

                ArrayList<Pair> pairs = new ArrayList<>();
                pairs.add(new Pair(i, play));
                playOrder.put(genre, pairs);
            } else {
                genreSum.put(genre, ret + play);

                ArrayList<Pair> pairs = playOrder.get(genre);
                pairs.add(new Pair(i, play));
                playOrder.put(genre, pairs);
            }
        }

        ArrayList<Integer> ans = new ArrayList<>();
        List<Map.Entry<String, Integer>> entries = genreSum.entrySet()
                .stream()
                .sorted(Map.Entry.comparingByValue(Collections.reverseOrder()))
                .collect(Collectors.toList());

        Comparator<Pair> comparator = (o1, o2) -> {
            if (o1.playNum < o2.playNum) return 1;
            else if (o1.playNum == o2.playNum) {
                if (o1.id > o2.id) return 1;
                else return -1;
            } else return -1;
        };

        for (var entry : entries) {
            String key = entry.getKey();
            ArrayList<Pair> pairsResult = playOrder.get(key);
            pairsResult.sort(comparator);
            int cnt = 0;
            for (Pair pair: pairsResult) {
                cnt++;
                if (cnt > 2) break;
                ans.add(pair.id);
            }
        }

        int[] answer = new int[ans.size()];
        for (int i=0; i<ans.size(); i++) {
            answer[i] = ans.get(i);
        }
        return answer;
    }
}
