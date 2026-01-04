# Notes

![alt text](<007 LIS_231121_163402.jpg>)
![alt text](<007 LIS_231121_163402(1).jpg>) ![alt text](<007 LIS_231121_163402(2).jpg>) ![alt text](<007 LIS_231121_163402(3).jpg>) ![alt text](<007 LIS_231121_163402(4).jpg>) ![alt text](<007 LIS_231121_163402(5).jpg>) ![alt text](<007 LIS_231121_163402(6).jpg>)

![alt text](<007 LIS_231121_163402(7).jpg>) ![alt text](<007 LIS_231121_163402(8).jpg>) ![alt text](<007 LIS_231121_163402(9).jpg>) ![alt text](<007 LIS_231121_163402(10).jpg>) ![alt text](<007 LIS_231121_163402(11).jpg>) ![alt text](<007 LIS_231121_163402(12).jpg>) ![alt text](<007 LIS_231121_163402(13).jpg>) ![alt text](<007 LIS_231121_163402(14).jpg>) ![alt text](<007 LIS_231121_163402(15).jpg>)


# C++ Binary Search Functions: `lower_bound` and `upper_bound`

Both functions are found in the `<algorithm>` header. They use binary search to find specific positions in a **sorted** range.

---

##  Core Logic Comparison

| Function | Condition | Description |
| :--- | :--- | :--- |
| **`std::lower_bound`** | `*it >= value` | Returns an iterator to the **first** element that is **not less** than the given value. |
| **`std::upper_bound`** | `*it > value` | Returns an iterator to the **first** element that is **strictly greater** than the given value. |


By mistake in upper notes we said upper bound is gretaer than or equal to but it is not ,it is lower bound