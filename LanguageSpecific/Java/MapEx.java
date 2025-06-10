import java.util.*;
public class MapEx{
    public static void main(String[] args){
        /*
        a Java program that demonstrates almost all commonly used functions of Map interface, 
        using HashMap (you can replace it with TreeMap, LinkedHashMap, etc.):
        */

       // 1. Create a Map
        Map<Integer, String> map = new HashMap<>();

        // 2. put(K, V)
        map.put(1, "Apple");
        map.put(2, "Banana");
        map.put(3, "Cherry");

        System.out.println("Initial Map: " + map);

        // 3. putIfAbsent(K, V)
        map.putIfAbsent(2, "Blueberry");  // won't replace Banana
        map.putIfAbsent(4, "Date");
        System.out.println("After putIfAbsent: " + map);

        // 4. get(K)
        System.out.println("Value for key 2: " + map.get(2));

        // 5. getOrDefault(K, defaultValue)
        System.out.println("Value for key 5 (default): " + map.getOrDefault(5, "Not Found"));

        // 6. containsKey(K)
        System.out.println("Contains key 3? " + map.containsKey(3));

        // 7. containsValue(V)
        System.out.println("Contains value 'Apple'? " + map.containsValue("Apple"));

        // 8. remove(K)
        map.remove(4);
        System.out.println("After removing key 4: " + map);

        // 9. remove(K, V)
        boolean removed = map.remove(3, "Cherry");
        System.out.println("Removed key 3 with value 'Cherry'? " + removed);
        System.out.println("Map after conditional remove: " + map);

        // 10. replace(K, V)
        map.replace(2, "Blueberry");
        System.out.println("After replacing value for key 2: " + map);

        // 11. replace(K, oldV, newV)
        boolean replaced = map.replace(2, "Blueberry", "Blackberry");
        System.out.println("Replaced key 2 from Blueberry to Blackberry? " + replaced);
        System.out.println("Map after conditional replace: " + map);

        // 12. keySet()
        Set<Integer> keys = map.keySet();
        System.out.println("Keys: " + keys);

        // 13. values()
        Collection<String> values = map.values();
        System.out.println("Values: " + values);

        // 14. entrySet()
        Set<Map.Entry<Integer, String>> entries = map.entrySet();
        System.out.println("Entries: " + entries);

        // 15. size()
        System.out.println("Size of map: " + map.size());

        // 16. isEmpty()
        System.out.println("Is map empty? " + map.isEmpty());

        // 17. putAll()
        Map<Integer, String> anotherMap = new HashMap<>();
        anotherMap.put(5, "Elderberry");
        anotherMap.put(6, "Fig");
        map.putAll(anotherMap);
        System.out.println("After putAll: " + map);

        // 18. clear()
        map.clear();
        System.out.println("After clear(): " + map);

        // 19. forEach()
        map.put(7, "Grapes");
        map.put(8, "Honeydew");
        System.out.print("Using forEach: ");
        map.forEach((key, value) -> System.out.print(key + "=" + value + " "));
        System.out.println();

        // 20. compute()
        map.compute(7, (key, val) -> val + " Pie");
        System.out.println("After compute on key 7: " + map);

        // 21. computeIfAbsent()
        map.computeIfAbsent(9, key -> "Indian Fig");
        System.out.println("After computeIfAbsent for key 9: " + map);

        // 22. computeIfPresent()
        map.computeIfPresent(8, (key, val) -> val + " Juice");
        System.out.println("After computeIfPresent for key 8: " + map);

        // 23. merge()
        map.merge(7, " Jam", (oldVal, newVal) -> oldVal + newVal);
        System.out.println("After merge on key 7: " + map);
    }
}

/*
Output:
Initial Map: {1=Apple, 2=Banana, 3=Cherry}
After putIfAbsent: {1=Apple, 2=Banana, 3=Cherry, 4=Date}
Value for key 2: Banana
Value for key 5 (default): Not Found
Contains key 3? true
Contains value 'Apple'? true
After removing key 4: {1=Apple, 2=Banana, 3=Cherry}
Removed key 3 with value 'Cherry'? true
Map after conditional remove: {1=Apple, 2=Banana}
After replacing value for key 2: {1=Apple, 2=Blueberry}
Replaced key 2 from Blueberry to Blackberry? true
Map after conditional replace: {1=Apple, 2=Blackberry}
Keys: [1, 2]
Values: [Apple, Blackberry]
Entries: [1=Apple, 2=Blackberry]
Size of map: 2
Is map empty? false
After putAll: {1=Apple, 2=Blackberry, 5=Elderberry, 6=Fig}
After clear(): {}
Using forEach: 7=Grapes 8=Honeydew 
After compute on key 7: {7=Grapes Pie, 8=Honeydew}
After computeIfAbsent for key 9: {7=Grapes Pie, 8=Honeydew, 9=Indian Fig}
After computeIfPresent for key 8: {7=Grapes Pie, 8=Honeydew Juice, 9=Indian Fig}
After merge on key 7: {7=Grapes Pie Jam, 8=Honeydew Juice, 9=Indian Fig}

*/