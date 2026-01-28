## Sliding window template 

```cpp
long long slidingWindow(vector<int>& arr, int k) {
    long long currentSum = 0;
    long long maxSum = 0;

    // 1. "Build the Base" (Like pre-calculating base primes)
    for(int i = 0; i < k; i++) {
        currentSum += arr[i];
    }
    maxSum = currentSum;

    // 2. "The Slide" (Like moving the segment from [L, R] to the next block)
    for(int i = k; i < arr.size(); i++) {
        // Add the "Entering" element (Right side of window)
        // Subtract the "Exiting" element (Left side of window)
        currentSum += arr[i] - arr[i - k];
        
        // 3. Update the Result
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}
```

![alt text](<012 ptr sliding window_250711_223007_1.jpg>) 
![alt text](<012 ptr sliding window_250711_223007_2.jpg>) 
![alt text](<012 ptr sliding window_250711_223007_3.jpg>)
 ![alt text](<012 ptr sliding window_250711_223007_4.jpg>) 
 ![alt text](<012 ptr sliding window_250711_223007_5.jpg>)
  ![alt text](<012 ptr sliding window_250711_223007_6.jpg>) 
  ![alt text](<012 ptr sliding window_250711_223007_7.jpg>) 
  ![alt text](<012 ptr sliding window_250711_223007_8.jpg>)