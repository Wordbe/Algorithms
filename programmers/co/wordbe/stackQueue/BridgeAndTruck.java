package co.wordbe.stackQueue;

import java.util.LinkedList;
import java.util.Queue;

public class BridgeAndTruck {
    public int solution(int bridge_length, int weight, int[] truck_weights) {
        int answer = 0;
        Queue<Integer> bridge = new LinkedList<>();

        int current_weight = 0;
        for(int truck : truck_weights)
        {
            while(true){
                if(bridge.isEmpty()){
                    bridge.offer(truck);
                    answer++;
                    current_weight+=truck;
                    break;
                }else if(bridge.size() == bridge_length){
                    current_weight-=bridge.poll();
                }else if(current_weight + truck <= weight){
                    bridge.offer(truck);
                    answer++;
                    current_weight+=truck;
                    break;
                }else{
                    bridge.offer(0);
                    answer++;
                }
            }
        }

        return answer + bridge_length;
    }



    // 정확성 21% 실패
    public class Truck {
        final int weight;
        int remainTime;

        public Truck(int weight, int remainTime) {
            this.weight = weight;
            this.remainTime = remainTime;
        }
    }

    public int solution1(int bridgeLength, int weight, int[] truckWeights) {
        int ans = bridgeLength + truckWeights.length;

        Queue<Truck> queue = new LinkedList<>();
        int sum = 0;
        for (int truckWeight: truckWeights) {

            if (weight >= sum + truckWeight) {
                queue.offer(new Truck(truckWeight, bridgeLength));
                for (Truck q: queue) {
                    q.remainTime -= 1;
                }
                sum += truckWeight;
            } else {
                Truck arrivedTruck = queue.poll();
                for (Truck q: queue) {
                    q.remainTime -= arrivedTruck.remainTime;
                }
                sum -= arrivedTruck.weight;
                ans += arrivedTruck.remainTime;
            }
        }

        return ans;
    }
}
