import java.util.*;

public class SetEx{
    public static void main(String[] args){

        // 1️⃣ Create a Set
        Set<String> set = new HashSet<>();

        // 2️⃣ Add elements
        set.add("Apple");
        set.add("Banana");
        set.add("Cherry");
        set.add("Date");

        System.out.println("Initial Set: " + set);

        // 3️⃣ Add duplicate (won't be added)
        set.add("Apple");
        System.out.println("After adding duplicate 'Apple': " + set);

        // 4️⃣ Remove element
        set.remove("Banana");
        System.out.println("After removing 'Banana': " + set);

        // 5️⃣ Contains element
        System.out.println("Contains 'Cherry'? " + set.contains("Cherry"));

        // 6️⃣ Size of set
        System.out.println("Size of set: " + set.size());

        // 7️⃣ IsEmpty
        System.out.println("Is set empty? " + set.isEmpty());

        // 8️⃣ Iterating using for-each loop
        System.out.print("Iterating using for-each: ");
        for (String item : set) {
            System.out.print(item + " ");
        }
        System.out.println();

        // 9️⃣ Iterating using Iterator
        System.out.print("Iterating using Iterator: ");
        Iterator<String> iterator = set.iterator();
        while (iterator.hasNext()) {
            System.out.print(iterator.next() + " ");
        }
        System.out.println();

        // 10️⃣ Clear the set
        set.clear();
        System.out.println("After clear(): " + set);
        System.out.println("Is set empty now? " + set.isEmpty());
    }
}

/*
Output:
Initial Set: [Apple, Cherry, Date, Banana]
After adding duplicate 'Apple': [Apple, Cherry, Date, Banana]
After removing 'Banana': [Apple, Cherry, Date]
Contains 'Cherry'? true
Size of set: 3
Is set empty? false
Iterating using for-each: Apple Cherry Date 
Iterating using Iterator: Apple Cherry Date 
After clear(): []
Is set empty now? true
*/