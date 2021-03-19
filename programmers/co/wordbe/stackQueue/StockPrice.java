package co.wordbe.stackQueue;


import java.util.Arrays;
import java.util.Stack;

public class StockPrice {
    public static int[] solution(int[] prices) {
        int N = prices.length;
        int[] ans = new int[N];
        Stack<Integer> stack = new Stack<>();

        for (int i = 0; i<N; i++) {
            while (!stack.isEmpty() && prices[stack.peek()] > prices[i]) {
                Integer top = stack.pop();
                ans[top] = i - top;
            }
            stack.push(i);
        }

        while (!stack.isEmpty()) {
            Integer top = stack.pop();
            ans[top] = N - 1 - top;
        }

        return ans;
    }
//    public static int[] solution(int[] prices) {
//        int[] ans = new int[prices.length];
//
//        Stack<Integer> stack = new Stack<>();
//        stack.push(0); // 스택에 시간을 넣는다.
//        for (int i=1; i<prices.length; i++) {
//            if (prices[stack.peek()] > prices[i]) {
//                ans[i-1] = i - stack.pop();
//            }
//            stack.push(i);
//        }
//        for (int i=0; i<ans.length - 1; i++) {
//            if (ans[i] == 0) {
//                ans[i] = stack.pop();
//            }
//        }
//        ans[ans.length - 1] = 0;
//
//        return ans;
//    }
}
