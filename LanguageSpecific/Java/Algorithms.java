import java.util.*;

public class Algorithms {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(10, 20, 30, 40, 50);
        int index = Collections.binarySearch(list, 30);
        System.out.println(index);  // Output: 2

         index = Collections.binarySearch(list, 5);
        System.out.println(index); 

        /*
        *The list must be sorted in ascending order before using binarySearch, otherwise the result is undefined.

        Returns:

        Index (≥0) if the element is found.

        Negative value (< 0) if the element is not found. The return value is -(insertion point) - 1.

        so to get value where it is inserted we index=-(index+1)

         temp.set(index, val);

         List<Integer> list = Arrays.asList(10, 20, 30, 40, 50);
            int index = Collections.binarySearch(list, 35);
            System.out.println(index);  // Output: -4
             Means: insertion point is at index 3 → -(-4)+1

             say x=-(insertion Point)-1
             so x+1=-(insertion Point)
             so insertion Point=-(x+1)
        */

    }
}