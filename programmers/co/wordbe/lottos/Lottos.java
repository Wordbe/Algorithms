package co.wordbe.lottos;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Lottos {
    public int[] solution(int[] lottos, int[] win_nums) {

        List<Integer> matched = new ArrayList<>();
        for (int lotto : lottos) {
            for (int win_num : win_nums) {
                if (lotto == win_num) {
                    matched.add(lotto);
                }
            }
        }
        long zeroCount = Arrays.stream(lottos).filter(lotto -> lotto == 0).count();
        int minMatched = matched.size();
        int maxMatched = matched.size() + (int)zeroCount;

        int[] answer = {rank(maxMatched), rank(minMatched)};
        return answer;
    }

    private int rank(int number) {
        return switch (number) {
            case 6 -> 1;
            case 5 -> 2;
            case 4 -> 3;
            case 3 -> 4;
            case 2 -> 5;
            default -> 6;
        };
    }
}

//    public static void main(String[] args) {
//        Lottos lottos = new Lottos();
//        int[] solution = lottos.solution(new int[]{44, 1, 0, 0, 31, 25}, new int[]{31, 10, 45, 1, 6, 19});
//        System.out.println("solution = " + solution[0] + " " + solution[1]);
//    }
