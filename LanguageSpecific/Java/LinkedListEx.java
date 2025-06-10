import java.util.*;
//never use LL by this use only to make stack and queue
public class LinkedListEx{
    public static void main(String[] args) {

        // 1️⃣ Create LinkedList
        LinkedList<String> list = new LinkedList<>();

        // 2️⃣ Add elements
        list.add("Apple");
        list.add("Banana");
        list.add("Cherry");
        System.out.println("Initial LinkedList: " + list);

        // 3️⃣ Add element at first and last
        list.addFirst("Start");
        list.addLast("End");
        System.out.println("After addFirst and addLast: " + list);

        // 4️⃣ Get first and last element
        System.out.println("First element: " + list.getFirst());
        System.out.println("Last element: " + list.getLast());

        // 5️⃣ Remove first and last element
        list.removeFirst();
        list.removeLast();
        System.out.println("After removeFirst and removeLast: " + list);

        // 6️⃣ Get element by index
        System.out.println("Element at index 1: " + list.get(1));

        // 7️⃣ Remove element by index and by value
        list.remove(0);
        System.out.println("After removing index 0: " + list);

        list.remove("Cherry");
        System.out.println("After removing 'Cherry': " + list);

        // 8️⃣ Contains
        System.out.println("Contains 'Banana'? " + list.contains("Banana"));

        // 9️⃣ Size and isEmpty
        System.out.println("Size of list: " + list.size());
        System.out.println("Is list empty? " + list.isEmpty());

        // 10️⃣ Iterate with for-each
        System.out.print("Iterating with for-each: ");
        for (String item : list) {
            System.out.print(item + " ");
        }
        System.out.println();

        // 11️⃣ Iterate with Iterator
        System.out.print("Iterating with Iterator: ");
        Iterator<String> iterator = list.iterator();
        while (iterator.hasNext()) {
            System.out.print(iterator.next() + " ");
        }
        System.out.println();

        // 12️⃣ Clear list
        list.clear();
        System.out.println("After clear(): " + list);
    }
}

/* Output :

Initial LinkedList: [Apple, Banana, Cherry]
After addFirst and addLast: [Start, Apple, Banana, Cherry, End]
First element: Start
Last element: End
After removeFirst and removeLast: [Apple, Banana, Cherry]
Element at index 1: Banana
After removing index 0: [Banana, Cherry]
After removing 'Cherry': [Banana]
Contains 'Banana'? true
Size of list: 1
Is list empty? false
Iterating with for-each: Banana 
Iterating with Iterator: Banana 
After clear(): []

*/