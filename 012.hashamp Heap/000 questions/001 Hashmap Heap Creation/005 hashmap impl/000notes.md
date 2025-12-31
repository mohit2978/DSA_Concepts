# Notes


 ![alt text](<006 hashmap youtube_231018_213422.jpg>) ![alt text](<006 hashmap youtube_231018_213422(1).jpg>) ![alt text](<006 hashmap youtube_231018_213422(2).jpg>) ![alt text](<006 hashmap youtube_231018_213422(3).jpg>) ![alt text](<006 hashmap youtube_231018_213422(4).jpg>) ![alt text](<006 hashmap youtube_231018_213422(5).jpg>) ![alt text](<006 hashmap youtube_231018_213422(6).jpg>) ![alt text](<006 hashmap youtube_231018_213422(7).jpg>) ![alt text](<006 hashmap youtube_231018_213422(8).jpg>) ![alt text](<006 hashmap youtube_231018_213422(9).jpg>) ![alt text](<006 hashmap youtube_231018_213422(10).jpg>) ![alt text](<006 hashmap youtube_231018_213422(11).jpg>) ![alt text](<006 hashmap youtube_231018_213422(12).jpg>) ![alt text](<006 hashmap youtube_231018_213422(13).jpg>) ![alt text](<006 hashmap youtube_231018_213422(14).jpg>) ![alt text](<006 hashmap youtube_231018_213422(15).jpg>) ![alt text](<006 hashmap youtube_231018_213422(16).jpg>) ![alt text](<006 hashmap youtube_231018_213422(17).jpg>) ![alt text](<006 hashmap youtube_231018_213422(18).jpg>) ![alt text](<006 hashmap youtube_231018_213422(19).jpg>) ![alt text](<006 hashmap youtube_231018_213422(20).jpg>) ![alt text](<006 hashmap youtube_231018_213422(21).jpg>)

![alt text](<006 hashmap youtube_231018_213422(22).jpg>) ![alt text](<006 hashmap youtube_231018_213422(23).jpg>) ![alt text](<006 hashmap youtube_231018_213422(24).jpg>) ![alt text](<006 hashmap youtube_231018_213422(25).jpg>) ![alt text](<006 hashmap youtube_231018_213422(26).jpg>) ![alt text](<006 hashmap youtube_231018_213422(27).jpg>)

```java
import java.util.ArrayList;
import java.util.LinkedList;

public class HashMap<K, V> {

    private class Node {
        K key = null;
        V value = null;

        Node(K key, V value) {
            this.key = key;
            this.value = value;
        }

        @Override
        public String toString() {
            return key + "=" + value;
        }
    }

    private LinkedList<Node>[] buckets;
    private int NoOFElements = 0;
    private int maxSizeOfBucket = 0;

    private void intialize(int size) {
        buckets = new LinkedList[size];
        for (int i = 0; i < size; i++) {
            buckets[i] = new LinkedList<>();
        }

        this.maxSizeOfBucket = size;
        this.NoOFElements = 0;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        int sizeOfMap = this.NoOFElements;
        for (int i = 0; i < this.maxSizeOfBucket; i++) {
            LinkedList<Node> group = this.buckets[i];
            int size = group.size();
            while (size-- > 0) {
                sb.append(group.getFirst());
                if (sizeOfMap > 1)
                    sb.append(",");

                group.addLast(group.removeFirst());
                sizeOfMap--;
            }
        }

        sb.append("]");

        return sb.toString();
    }

    public HashMap() {
        intialize(10);
    }

    public Integer size() {
        return this.NoOFElements;
    }

    public boolean isEmpty() {
        return this.size() == 0;
    }

    private void rehash() {
        LinkedList<Node>[] temp = this.buckets;
        intialize(2 * this.maxSizeOfBucket);
        for (int i = 0; i < temp.length; i++) {
            LinkedList<Node> group = temp[i];
            int size = group.size();
            while (size-- > 0) {
                Node node = group.removeFirst();
                put(node.key, node.value);
            }
        }
    }

    public void put(K key, V value) {
        LinkedList<Node> group = group(key);
        boolean res = containsKey(key);
        if (res) {
            group.getFirst().value = value;
        } else {
            Node node = new Node(key, value);
            group.addLast(node);
            this.NoOFElements++;

            double lambda = (0.4 * this.maxSizeOfBucket);
            if (group.size() >= lambda)
                rehash();
        }
    }

    // if you found return value if not return null.
    public V get(K key) {
        LinkedList<Node> group = group(key);
        boolean res = containsKey(key);
        if (res)
            return group.getFirst().value;

        return null;
    }

    public V remove(K key) {
        LinkedList<Node> group = group(key);
        boolean res = containsKey(key);
        if (res) {
            this.NoOFElements--;
            return group.removeFirst().value;
        }
        return null;
    }

    public boolean containsKey(K key) {
        LinkedList<Node> group = group(key);
        int size = group.size();
        while (size-- > 0) {
            if (group.getFirst().key == key)
                return true;
            group.addLast(group.removeFirst());
        }
        return false;
    }

    private void allkeysOfGroup(LinkedList<Node> group, ArrayList<K> ans) {
        int size = group.size();
        while (size-- > 0) {
            ans.add(group.getFirst().key);
            group.addLast(group.removeFirst());
        }
    }

    public ArrayList<K> keySet() {
        ArrayList<K> ans = new ArrayList<>();
        for (int i = 0; i < this.maxSizeOfBucket; i++) {
            allkeysOfGroup(this.buckets[i], ans);
        }

        return ans;
    }

    public V getOrDefault(K key, V defaultValue) {
        V value = get(key);
        if (value == null)
            return defaultValue;
        return value;
    }

    public void putIfAbsent(K key, V value) {
        LinkedList<Node> group = group(key);
        boolean res = containsKey(key);
        if (!res)
            put(key, value);
    }

    private LinkedList<Node> group(K key) {
        int groupNo = groupNo(key);
        return this.buckets[groupNo];
    }

    private Integer groupNo(K key) {
        Integer hc = Math.abs(key.hashCode());
        return hc % maxSizeOfBucket;
    }

}

```
### Client

```java

import java.util.Scanner;
import java.util.ArrayList;

public class client {
    public static Scanner scn = new Scanner(System.in);

    public static void main(String[] args) {
        HashMap<Character, ArrayList<Integer>> map = new HashMap<>();
        String str = "asdasasaaasskacbasmcbasmcasbcjhcbsahcjhcsvhcsHVcsvhjcks";
        for (int i = 0; i < str.length(); i++) {
            char ch = str.charAt(i);
            map.putIfAbsent(ch, new ArrayList<>());
            map.get(ch).add(i);
        }

        for(Character ch : map.keySet()){
            System.out.println(ch + " -> " + map.get(ch));
        }

    }
}
```


