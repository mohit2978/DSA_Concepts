import java.util.*;

public class ArrayListEx{
    public static void main(String[] args){
        
        // 1. Create an ArrayList
        ArrayList<String> list = new ArrayList<>();

        // 2. Add elements
        list.add("Apple");
        list.add("Banana");
        list.add("Cherry");
        list.add("Date");

        System.out.println("Initial List: " + list);

        // 3. Add element at index
        list.add(2, "Blueberry");
        System.out.println("After adding at index 2: " + list);

        // 4. Get element at index
        System.out.println("Element at index 1: " + list.get(1));

        // 5. Set element at index
        list.set(3, "Dragonfruit");
        System.out.println("After setting index 3: " + list);

        // 6. Remove element by index
        list.remove(1);
        System.out.println("After removing index 1: " + list);

        // 7. Remove element by value
        list.remove("Date");
        System.out.println("After removing 'Date': " + list);

        // 8. Contains element
        System.out.println("Contains 'Apple'? " + list.contains("Apple"));

        // 9. IndexOf
        System.out.println("Index of 'Cherry': " + list.indexOf("Cherry"));

        // 10. LastIndexOf (works when list has duplicates)
        list.add("Apple");
        System.out.println("List with duplicate Apple: " + list);
        System.out.println("Last index of 'Apple': " + list.lastIndexOf("Apple"));

        // 11. Size
        System.out.println("Size of list: " + list.size());

        // 12. IsEmpty
        System.out.println("Is list empty? " + list.isEmpty());

        // 13. ToArray
        Object[] array = list.toArray();
        System.out.println("Array: " + Arrays.toString(array));

        // 14. Clone
        ArrayList<String> clonedList = (ArrayList<String>) list.clone();
        System.out.println("Cloned list: " + clonedList);

        // 15. SubList
        List<String> subList = list.subList(1, 3);  // index 1 to 2
        System.out.println("Sublist (1 to 3): " + subList);

        // 16. AddAll
        ArrayList<String> newList = new ArrayList<>();
        newList.add("Elderberry");
        newList.add("Fig");
        list.addAll(newList);
        System.out.println("After addAll: " + list);

        // 17. ContainsAll
        System.out.println("Contains all from newList? " + list.containsAll(newList));

        // 18. RemoveAll
        list.removeAll(newList);
        System.out.println("After removeAll: " + list);

        // 19. RetainAll
        ArrayList<String> retainList = new ArrayList<>();
        retainList.add("Apple");
        retainList.add("Cherry");
        list.retainAll(retainList);
        System.out.println("After retainAll: " + list);

        // 20. Clear
        list.clear();
        System.out.println("After clear(): " + list);

        // 21. EnsureCapacity (no visible output, used to optimize capacity internally)
        list.ensureCapacity(100);

        // 22. TrimToSize (no visible output, used to optimize memory internally)
        list.trimToSize();

        // 23. ForEach
        list.add("Grapes");
        list.add("Honeydew");
        System.out.print("ForEach: ");
        list.forEach(item -> System.out.print(item + " "));
        System.out.println();

        // 24. Iterator
        Iterator<String> iterator = list.iterator();
        System.out.print("Using Iterator: ");
        while (iterator.hasNext()) {
            System.out.print(iterator.next() + " ");
        }
        System.out.println();

        // 25. ListIterator
        ListIterator<String> listIterator = list.listIterator();
        System.out.print("Using ListIterator (forward): ");
        while (listIterator.hasNext()) {
            System.out.print(listIterator.next() + " ");
        }
        System.out.println();

        // 26. ListIterator backward
        System.out.print("Using ListIterator (backward): ");
        while (listIterator.hasPrevious()) {
            System.out.print(listIterator.previous() + " ");
        }
        System.out.println();
    }
}

/**
 * Output :
 * 
 * Initial List: [Apple, Banana, Cherry, Date]
After adding at index 2: [Apple, Banana, Blueberry, Cherry, Date]
Element at index 1: Banana
After setting index 3: [Apple, Banana, Blueberry, Dragonfruit, Date]
After removing index 1: [Apple, Blueberry, Dragonfruit, Date]
After removing 'Date': [Apple, Blueberry, Dragonfruit]
Contains 'Apple'? true
Index of 'Cherry': -1
List with duplicate Apple: [Apple, Blueberry, Dragonfruit, Apple]
Last index of 'Apple': 3
Size of list: 4
Is list empty? false
Array: [Apple, Blueberry, Dragonfruit, Apple]
Cloned list: [Apple, Blueberry, Dragonfruit, Apple]
Sublist (1 to 3): [Blueberry, Dragonfruit]
After addAll: [Apple, Blueberry, Dragonfruit, Apple, Elderberry, Fig]
Contains all from newList? true
After removeAll: [Apple, Blueberry, Dragonfruit, Apple]
After retainAll: [Apple, Apple]
After clear(): []
ForEach: Grapes Honeydew 
Using Iterator: Grapes Honeydew 
Using ListIterator (forward): Grapes Honeydew 
Using ListIterator (backward): Honeydew Grapes 
 * 
 */