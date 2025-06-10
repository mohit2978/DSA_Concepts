import java.util.*;

class MyClass {
    int val1;
    int val2;
    int val3;

    public MyClass(int val1, int val2, int val3) {
        this.val1 = val1;
        this.val2 = val2;
        this.val3 = val3;
    }

    @Override
    public String toString() {
        return "(" + val1 + ", " + val2 + ", " + val3 + ")";
    }
}

public class PriorityQueueEx2 {
    public static void main(String[] args) {

        // Max-Heap based on val2 using lambda comparator
        PriorityQueue<MyClass> pq = new PriorityQueue<>(
            (a, b) ->  a.val2 - b.val2 // Min-heap on val2
        );

        // Add elements
        pq.add(new MyClass(1, 50, 100));
        pq.add(new MyClass(2, 70, 200));
        pq.add(new MyClass(3, 40, 300));
        pq.add(new MyClass(4, 90, 150));
        pq.add(new MyClass(5, 60, 250));

        // Print initial size
        System.out.println("Initial size of PQ: " + pq.size());

        // Print top element
        System.out.println("Top element (peek / top()): " + pq.peek());

        // Remove elements one by one (like remove / pop)
        System.out.println("Removing elements in max-heap order (by val2):");
        while (pq.size() > 0) {
            MyClass top = pq.remove(); // remove() == poll()
            System.out.println("Removed: " + top + " | Current size: " + pq.size());
        }
    }
}

/*
in case comparator is b.val2- a.val2  max heap
Initial size of PQ: 5
Top element (peek / top()): (4, 90, 150)
Removing elements in max-heap order (by val2):
Removed: (4, 90, 150) | Current size: 4
Removed: (2, 70, 200) | Current size: 3
Removed: (5, 60, 250) | Current size: 2
Removed: (1, 50, 100) | Current size: 1
Removed: (3, 40, 300) | Current size: 0
*/

/* 
in case  a.val2 - b.val2
Initial size of PQ: 5
Top element (peek / top()): (3, 40, 300)
Removing elements in max-heap order (by val2):
Removed: (3, 40, 300) | Current size: 4
Removed: (1, 50, 100) | Current size: 3
Removed: (5, 60, 250) | Current size: 2
Removed: (2, 70, 200) | Current size: 1
Removed: (4, 90, 150) | Current size: 0

*/