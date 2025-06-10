import java.util.*;

public class StackAndQueueEx {
    public static void main(String[] args) {

        // 1️⃣ Stack example
        System.out.println("----- Stack Example -----");
        Stack<Integer> stack = new Stack<>();

        // Push elements
        stack.push(10);
        stack.push(20);
        stack.push(30);

        System.out.println("Initial Stack: " + stack);

        // Top element
        System.out.println("Top element: " + stack.peek());

        // Pop element
        System.out.println("Popped element: " + stack.pop());
        System.out.println("Stack after pop: " + stack);

        // Size of stack
        System.out.println("Stack size: " + stack.size());

        // Iterate stack
        System.out.print("Stack elements: ");
        for (int item : stack) {
            System.out.print(item + " ");
        }
        System.out.println();

        // 2️⃣ Queue example (using LinkedList)
        System.out.println("\n----- Queue Example -----");
        Queue<Integer> queue = new LinkedList<>();

        // Enqueue elements (offer / add)
        queue.add(100);
        queue.add(200);
        queue.add(300);

        System.out.println("Initial Queue: " + queue);

        // Front element
        System.out.println("Front element: " + queue.peek());

        // Dequeue element
        System.out.println("Dequeued element: " + queue.remove());
        System.out.println("Queue after dequeue: " + queue);

        // Size of queue
        System.out.println("Queue size: " + queue.size());

        // Iterate queue
        System.out.print("Queue elements: ");
        for (int item : queue) {
            System.out.print(item + " ");
        }
        System.out.println();
    }
}

/*
----- Stack Example -----
Initial Stack: [10, 20, 30]
Top element: 30
Popped element: 30
Stack after pop: [10, 20]
Stack size: 2
Stack elements: 10 20 

----- Queue Example -----
Initial Queue: [100, 200, 300]
Front element: 100
Dequeued element: 100
Queue after dequeue: [200, 300]
Queue size: 2
Queue elements: 200 300 
*/