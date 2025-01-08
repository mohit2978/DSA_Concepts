class Solution {
    findMaximumCookieStudents(Student, Cookie) {
        let n = Student.length;
        let m = Cookie.length;
        // Pointers
        let l = 0, r = 0;
        // Sorting of arrays
        Student.sort((a, b) => a - b);
        Cookie.sort((a, b) => a - b);

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
        // Return number of students
        return l; 
    }
}

// Example input
const Student = [1, 2];
const Cookie = [1, 2, 3];

// Create a Solution object
const solution = new Solution();

// Call the findMaximumCookieStudents function
const result = solution.findMaximumCookieStudents(Student, Cookie);

// Output the result
console.log("Number of students satisfied:", result);
