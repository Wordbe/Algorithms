package co.wordbe.sort;

import java.math.BigInteger;
import java.util.Arrays;
import java.util.Comparator;

public class BiggestNumber {
    public static String solution(int[] numbers) {
        StringBuilder answer = new StringBuilder();

        String[] nums = new String[numbers.length];
        boolean allZero = true;
        for (int i=0; i<nums.length; i++) {
            nums[i] = String.valueOf(numbers[i]);
            if (numbers[i] !=0) allZero = false;
        }
        if (allZero) return "0";

        Comparator<String> stringComparator = (o1, o2) -> (o2 + o1).compareTo(o1 + o2);
        Arrays.sort(nums, stringComparator);

        for (int i=0; i<nums.length; i++) {
            answer.append(nums[i]);
        }


        return answer.toString();
    }
}
