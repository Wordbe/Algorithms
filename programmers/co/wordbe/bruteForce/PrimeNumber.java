package co.wordbe.bruteForce;

import java.util.ArrayList;
import java.util.TreeSet;

public class PrimeNumber {

    int M;
    ArrayList<Integer> nums = new ArrayList<>();
    boolean[] visited = new boolean[7];
    int[] a;
    TreeSet<Integer> set = new TreeSet<>();

    public void dfs(int depth) {
        if (depth == M) {
            StringBuilder tmp = new StringBuilder();
            for (int i=0; i<M; i++) {
                tmp.append(a[i]);
            }
            set.add(Integer.valueOf(tmp.toString()));
            return;
        }

        for (int i=0; i<nums.size(); i++) {
            if (visited[i]) continue;

            a[depth] = nums.get(i);
            visited[i] = true;
            dfs(depth + 1);
            visited[i] = false;
        }
    }

    public int solution(String numbers) {
        int N = numbers.length();
        for (int i = 0; i<N; i++) {
            nums.add(numbers.charAt(i) - '0');
        }

        for (int i=1; i<numbers.length()+1; i++) {
            M = i;
            a = new int[M];
            dfs(0);
        }

        boolean[] primes = new boolean[set.last() + 1];
        primes[0] = true;
        primes[1] = true;
        double sqrt = Math.sqrt(set.last());
        for (int i = 2; i <= sqrt; i++) {
            if (primes[i]) continue;
            for (int j=i + i; j<=set.last(); j += i) {
                primes[j] = true;
            }
        }
        int ans = 0;
        for (Integer i: set) {
            if (!primes[i]) ans++;
        }
        return ans;
    }
}
