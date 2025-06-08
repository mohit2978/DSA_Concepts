using namespace std;

int main() {
    //just hashmap avg tc of search insert delete  O(1) 
    // Declare a map to store key-value pairs
    unordered_map<int, string> mp;

    // 1. Insert elements
    mp[1] = "Apple";           // Using [] operator
    mp[2] = "Banana";
    mp.insert({3, "Cherry"});  // Using insert()

    // 2. Access elements
    cout << "Element at key 1: " << mp[1] << endl;  // Access using []
    cout << "Element at key 2: " << mp.at(2) << endl; // Access using at()

    // 3. Check if a key exists
    int key = 4;
    if (mp.find(key) != mp.end()) {
        cout << "Key " << key << " exists in the map." << endl;
    } else {
        cout << "Key " << key << " does not exist in the map." << endl;
    }

    // 4. Iterate through the map
    cout << "\nAll elements in the map:\n";
    for (auto it : mp) {
        cout << "Key: " << it.first << ", Value: " << it.second << endl;
    }

    // 5. Erase an element
    mp.erase(2);  // Remove key 2
    cout << "\nAfter erasing key 2:\n";
    for (auto it : mp) {
        cout << "Key: " << it.first << ", Value: " << it.second << endl;
    }

    // 6. Clear the map
    mp.clear();
    if (mp.empty()) {
        cout << "\nThe map is now empty." << endl;
    }

    return 0;
}
