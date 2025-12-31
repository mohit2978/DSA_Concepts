# Notes

![alt text](<004heap implementation _240517_174240.jpg>) ![alt text](<004heap implementation _240517_174240(2).jpg>) ![alt text](<004heap implementation _240517_174240(3).jpg>) ![alt text](<004heap implementation _240517_174240(4).jpg>) ![alt text](<004heap implementation _240517_174240(5).jpg>) ![alt text](<004heap implementation _240517_174240(6).jpg>) ![alt text](<004heap implementation _240517_174240(7).jpg>) ![alt text](<004heap implementation _240517_174240(8).jpg>) ![alt text](<004heap implementation _240517_174240(9).jpg>) ![alt text](<004heap implementation _240517_174240(10).jpg>) ![alt text](<004heap implementation _240517_174240(11).jpg>) ![alt text](<004heap implementation _240517_174240(12).jpg>) ![alt text](<004heap implementation _240517_174240(13).jpg>) ![alt text](<004heap implementation _240517_174240(14).jpg>) ![alt text](<004heap implementation _240517_174240(15).jpg>) ![alt text](<004heap implementation _240517_174240(16).jpg>) ![alt text](<004heap implementation _240517_174240(17).jpg>) ![alt text](<004heap implementation _240517_174240(18).jpg>) ![alt text](<004heap implementation _240517_174240(19).jpg>) ![alt text](<004heap implementation _240517_174240(20).jpg>) ![alt text](<004heap implementation _240517_174240(21).jpg>)

![alt text](<004heap implementation _240517_174240(22).jpg>) ![alt text](<004heap implementation _240517_174240(23).jpg>) ![alt text](<004heap implementation _240517_174240(24).jpg>) ![alt text](<004heap implementation _240517_174240(25).jpg>) ![alt text](<004heap implementation _240517_174240(26).jpg>) ![alt text](<004heap implementation _240517_174240(27).jpg>) ![alt text](<004heap implementation _240517_174240(28).jpg>) ![alt text](<004heap implementation _240517_174240(29).jpg>) ![alt text](<004heap implementation _240517_174240(30).jpg>) ![alt text](<004heap implementation _240517_174240(31).jpg>) ![alt text](<004heap implementation _240517_174240(32).jpg>) ![alt text](<004heap implementation _240517_174240(33).jpg>) 


## Heap impl
```java
import java.util.ArrayList;

public class heap {
    private ArrayList<Integer> arr;
    private int size = 0;
    private boolean isMax = true;

    private void intialize(boolean isMax) {
        this.arr = new ArrayList<>();
        this.size = 0;
        this.isMax = isMax;
    }

    public heap() {
        intialize(true);
    }

    public heap(int[] arr, boolean isMax) { // O(n)
        intialize(isMax);
        for (int ele : arr)
            this.arr.add(ele);

        for (int i = this.arr.size() - 1; i >= 0; i--) {
            downHeapify(i);
        }

        this.size = arr.length;
    }

    // General Functions.

    public int size() {
        return this.size;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public void add(int data) { // O(logN)
        this.arr.add(data);
        this.size++;
        upheapify(this.size - 1);
    }

    public int remove() { // O(logN)
        int n = this.arr.size();
        int rv = this.arr.get(0);

        swap(0, n - 1);
        this.arr.remove(n - 1);
        this.size--;

        downHeapify(0);
        return rv;
    }

    public int peek() { // O(1)
        return this.arr.get(0);
    }

    private int compareTo(int a,int b){
        if(isMax){
            return this.arr.get(a) - this.arr.get(b);
        }else{
            return this.arr.get(b) - this.arr.get(a);
        }

    }

    private void swap(int i, int j) { // O(1)
        int ei = arr.get(i);
        int ej = arr.get(j);

        arr.set(i, ej);
        arr.set(j, ei);
    }

    private void upheapify(int ci) { // O(logn)
        int pi = (ci - 1) / 2;
        if (pi >= 0 && compareTo(ci,pi) > 0) {
            swap(pi, ci);
            upheapify(pi);
        }
    }

    private void downHeapify(int pi) { // O(logn)
        int maxIdx = pi;
        int lci = 2 * pi + 1;
        int rci = 2 * pi + 2;

        if (lci < this.arr.size() && compareTo(lci,maxIdx) > 0)
            maxIdx = lci;
        if (rci < this.arr.size() && compareTo(rci,maxIdx) > 0)
            maxIdx = rci;

        if (maxIdx != pi) {
            swap(maxIdx, pi);
            downHeapify(maxIdx);
        }
    }

}

```

### Client

```java

public class client{

    public static void solve1(int[] arr){
        heap pq = new heap();
        
        for(int ele : arr) pq.add(ele);

        while(pq.size() != 0){
            System.out.print(pq.remove() + " ");
        }
    }

    public static void solve2(int[] arr){
        heap pq = new heap(arr,false);

        while(pq.size() != 0){
            System.out.print(pq.remove() + " ");
        }
    }

    public static void main(String[] args){
        int[] arr = { 10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13 };
        solve2(arr);
    }

}
```


## Heapsort

```java

public class heapSort {
    public static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static boolean compareTo(int a, int b, boolean isMax) {
        if (isMax)
            return a > b;
        else
            return a < b;

    }

    public static void heapify(int pi, int[] arr, int li, boolean isMax) {
        int maxIdx = pi;
        int lci = 2 * pi + 1;
        int rci = 2 * pi + 2;

        if (lci <= li && compareTo(arr[lci], arr[maxIdx], isMax))
            maxIdx = lci;
        if (rci <= li && compareTo(arr[rci], arr[maxIdx], isMax))
            maxIdx = rci;

        if (pi != maxIdx) {
            swap(arr, maxIdx, pi);
            heapify(maxIdx, arr, li, isMax);
        }
    }

    public static void display(int[] arr) {
        for (int ele : arr)
            System.out.print(ele + " ");
        System.out.println();
    }

    public static void main(String[] args) {
        int[] arr = { 10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13 };
        int n = arr.length;
        boolean isMax = false;
        for (int i = n - 1; i >= 0; i--)
            heapify(i, arr, n - 1, isMax);

        int li = n - 1;
        while (li >= 0) {
            swap(arr, 0, li--);
            heapify(0, arr, li, isMax);
        }

        display(arr);

    }
}
```
















