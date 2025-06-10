import java.util.*;

public class PriorityQueueEx{
    public static void main(String[] args){
        // 1️⃣ Min-Heap (default behavior)
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        minHeap.add(5);
        minHeap.add(2);
        minHeap.add(8);
        minHeap.add(1);
        minHeap.add(10);

        System.out.println("Min-Heap elements (poll in order):");
        while (!minHeap.isEmpty()) { //can use .size()>0
            System.out.print(minHeap.poll() + " ");
        }
        System.out.println();

        // 2️⃣ Max-Heap (using custom comparator)
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());

        maxHeap.add(5);
        maxHeap.add(2);
        maxHeap.add(8);
        maxHeap.add(1);
        maxHeap.add(10);

        System.out.println("Max-Heap elements (poll in order):");
        while (!maxHeap.isEmpty()) {
            System.out.print(maxHeap.poll() + " ");
        }
        System.out.println();
    }
}