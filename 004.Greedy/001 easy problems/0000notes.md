# Notes

## Q1 Assign cookies

Input : Student = [1, 2, 3] , Cookie = [1, 1]

Output :1

Explanation : You have 3 students and 2 cookies.

The minimum size of cookies required for students are 1 , 2 ,3.

You have 2 cookies both of size 1, So you can assign the cookie only to student having minimum cookie size 1.

So your answer is 1.

Input : Student = [1, 2] , Cookie = [1, 2, 3]

Output : 2

Explanation : You have 2 students and 3 cookies.

The minimum size of cookies required for students are 1 , 2.

You have 3 cookies and their sizes are big enough to assign cookies to all students.

So your answer is 2.

Mysolution

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution{    
    public:
    int findMaximumCookieStudents(vector<int>& Student, vector<int>& Cookie){
        sort(Student.begin(),Student.end());
        sort(Cookie.begin(),Cookie.end());
        //if min student >max of cookies then no student will get cookie
        if(Student[0]>Cookie[Cookie.size()-1]) return 0;
        int res=0;
        int j=0;
        for(int i=0;i<Student.size();i++){
            int val=Student[i];
            while(j<Cookie.size() && Cookie[j]<val) j++;
            if(j==Cookie.size()) return res;
            res++;
            j++;
        }
        return res;
    }
};

int main() {
    // Example input
    vector<int> Student = {1, 2};
    vector<int> Cookie = {1, 2, 3};

    // Create a Solution object
    Solution solution;

    // Call the findMaximumCookieStudents function
    int result = solution.findMaximumCookieStudents(Student, Cookie);

    // Output the result
    cout << "Number of students satisfied: " << result << endl;

    return 0;
}
```

Given solution
```cpp

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    
    int findMaximumCookieStudents(vector<int>& Student, vector<int>& Cookie) {
        int n = Student.size();
        int m = Cookie.size();
        // Pointers
        int l = 0, r = 0;
        // Sorting of vectors
        sort(Student.begin(), Student.end());
        sort(Cookie.begin(), Cookie.end());

        // Traverse through both arrays
        while (l < n && r < m) {
            /*If the current cookie can satisfy 
            the current student, move to the 
            next student*/
            if (Cookie[r] >= Student[l]) {
                l++;
            }
            // Move to next cookie
            r++;
        }
        // Return the number of students who got cookies
        return l; 
    }
};
int main() {
    // Example input
    vector<int> Student = {1, 2};
    vector<int> Cookie = {1, 2, 3};

    // Create a Solution object
    Solution solution;

    // Call the findMaximumCookieStudents function
    int result = solution.findMaximumCookieStudents(Student, Cookie);

    // Output the result
    cout << "Number of students satisfied: " << result << endl;

    return 0;
}

```