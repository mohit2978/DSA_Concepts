public class Bits {

    // Convert decimal to binary string
    public static String decimalToBinary(int n) {
        StringBuilder result = new StringBuilder();
        while (n > 0) {
            result.append(n % 2 == 1 ? '1' : '0');
            n = n / 2;
        }
        result.reverse();
        System.out.println(result.toString());
        return result.toString();
    }

    // Check if ith bit is set
    public static boolean isBitSet(int n, int i) {
        return (n & (1 << i)) != 0;
    }

    // Set the ith bit
    public static int setBit(int n, int i) {
        return n | (1 << i);
    }

    // Clear the ith bit
    public static int clearBit(int n, int i) {
        return n & ~(1 << i);
    }

    // Toggle the ith bit
    public static int toggleBit(int n, int i) {
        return n ^ (1 << i);
    }

    // Remove the last set bit
    public static int removeLastSetBit(int n) {
        return n & (n - 1);
    }

    // Check if number is a power of 2
    public static boolean isPowerOfTwo(int n) {
        return (n > 0) && ((n & (n - 1)) == 0);
    }

    // Count set bits using basic approach (O(no. of bits))
    public static int countSetBitsBasic(int n) {
        int count = 0;
        while (n > 0) {
            count += (n & 1);
            n >>= 1;
        }
        return count;
    }

    // Count set bits using Brian Kernighan's algorithm (O(no. of set bits))
    public static int countSetBitsFast(int n) {
        int count = 0;
        while (n != 0) {
            n &= (n - 1);
            count++;
        }
        return count;
    }

    // Swap two integers without a temp variable
    public static void swap(int[] pair) {
        // assuming pair has exactly two elements: [x, y]
        pair[0] = pair[0] ^ pair[1];
        pair[1] = pair[0] ^ pair[1];
        pair[0] = pair[0] ^ pair[1];
    }

    public static void main(String[] args) {
        decimalToBinary(12);                    // 1100
        System.out.println(isBitSet(12, 3));    // true
        System.out.println(setBit(12, 0));      // 13
        System.out.println(clearBit(13, 0));    // 12
        System.out.println(toggleBit(12, 0));   // 13
        System.out.println(removeLastSetBit(12)); // 8

        // Demonstrating swap
        int[] pair = {5, 9};
        System.out.println("Before swap: " + pair[0] + ", " + pair[1]);
        swap(pair);
        System.out.println("After swap: " + pair[0] + ", " + pair[1]);
    }
}
