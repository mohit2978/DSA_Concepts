class Solution:
    def findMaximumCookieStudents(self, Student, Cookie):
        n = len(Student)
        m = len(Cookie)
        # Pointers
        l, r = 0, 0
        # Sorting of lists
        Student.sort()
        Cookie.sort()

        # Traverse through both lists
        while l < n and r < m:
            """If the current cookie can satisfy 
            the current student, move to the 
            next student"""
            if Cookie[r] >= Student[l]:
                l += 1
            # Move to next cookie
            r += 1
        # Return number of students
        return l
