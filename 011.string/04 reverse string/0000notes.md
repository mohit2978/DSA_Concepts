# Reverse string

## Reverse every word in a string


Given an input string, containing upper-case and lower-case letters, digits, and spaces( ' ' ). A word is defined as a sequence of non-space characters. The words in s are separated by at least one space.



Return a string with the words in reverse order, concatenated by a single space.


Examples:
Input: s = "welcome to the jungle"



Output: "jungle the to welcome"



Explanation: The words in the input string are "welcome", "to", "the", and "jungle". Reversing the order of these words gives "jungle", "the", "to", and "welcome". The output string should have exactly one space between each word.

Input: s = " amazing coding skills "



Output: "skills coding amazing"



Explanation: The input string has leading and trailing spaces, as well as multiple spaces between the words "amazing", "coding", and "skills". After trimming the leading and trailing spaces and reducing the multiple spaces between words to a single space, the words are "amazing", "coding", and "skills". Reversing the order of these words gives "skills", "coding", and "amazing". The output string should not have any leading or trailing spaces and should have exactly one space between each word.

### Mycode

```cpp
class Solution {
public:
    string reverseWords(string s) {
       int n=s.size();
       int i=0;
       vector<string>strVec;
       while(i<n){
          while(i<n && s[i]==' ') i++;
          string str;
          while(i<n && s[i]!=' '){
              str.push_back(s[i++]);
          }
          if(str.size()>0) strVec.push_back(str);
          //if you do not put this then last vala empty space 
          //aaega as empty string and after reversal it will 
          //become first mai empty space for eg 2 if ke bina 
          //run krna
       }
      i=0;
      int j=strVec.size()-1;
      while(i<j){
        swap(strVec[i++],strVec[j--]);
      }
      string res;
      i=0;
      while(i<strVec.size()){
        res.append(strVec[i]);
        if(i!=strVec.size()-1) res.append(" ");
        i++;
      }
      return res;
    } 
};
```

## Very very imporatnt
see string methods 

| Method | Syntax | Description |
| :--- | :--- | :--- |
| **`append()`** | `str1.append(str2);` | Appends a whole string, a substring, a C-style string, or a specified number of characters to the end of `str1`. |
| **`+=` operator** | `str1 += str2;` | The simplest way to append a string, a single character, or a C-style string. |
| **`push_back()`** | `str1.push_back(ch);` | Appends a **single character** (`char`) to the end of the string. |
| **`+` operator** | `result = str1 + str2;` | Creates and returns a **new string** that is the concatenation of `str1` and `str2`. |