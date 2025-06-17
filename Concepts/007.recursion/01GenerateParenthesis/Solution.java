import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<String> generateParenthesis(int n) {
        List<String> result = new ArrayList<>();

        generate(0, 0, n, "", result);
        return result;
    }

    private void generate(int open, int close, int n, String current, List<String> result) {
   
        if (open == close && open + close == 2 * n) {
            result.add(current);
            return;
        }

        if (open < n) {
            generate(open + 1, close, n, current + '(', result);
        }

    
        if (close < open) {
            generate(open, close + 1, n, current + ')', result);
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int n = 3; // Example input
        List<String> result = sol.generateParenthesis(n);

        System.out.println("All combinations of balanced parentheses for n = " + n + " are:");
        for (String combination : result) {
            System.out.println(combination);
        }
    }
}

/*
Output:
All combinations of balanced parentheses for n = 3 are:
((()))
(()())
(())()
()(())
()()()
*/