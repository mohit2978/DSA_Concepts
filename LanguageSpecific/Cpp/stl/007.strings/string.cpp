#include <iostream>
#include <string>
#include <algorithm> // for reverse

using namespace std;

int main() {
    // 1. Initialization
    string s1 = "Hello";
    string s2 = "World";
    string s3 = s1 + " " + s2; // Concatenation

    // 2. Access and modify
    cout << "Original string: " << s3 << endl;
    cout << "Character at index 1: " << s3[1] << endl;

    // Modify character
    s3[1] = 'a';
    cout << "Modified string: " << s3 << endl;

    // 3. Size and substrings
    cout << "Length of string: " << s3.size() << endl;
    cout << "Substring (2, 3): " << s3.substr(2, 3) << endl; //from index 2 3 length substring
    //output:Substring (2, 3): llo

    // 4. Find and replace
    size_t pos = s3.find("World");
    if (pos != string::npos) {
        s3.replace(pos, 5, "Everyone");
    }
    cout << "Replaced string: " << s3 << endl;

    // 5. Reverse string
    reverse(s3.begin(), s3.end());
    cout << "Reversed string: " << s3 << endl;

    // 6. Check if empty
    string emptyString;
    if (emptyString.empty()) {
        cout << "String is empty!" << endl;
    }

    return 0;
}
