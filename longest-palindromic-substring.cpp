// longest-palindromic-substring.cpp:
// Original question: https://leetcode.com/problems/longest-palindromic-substring/submissions/1251435750/
// 
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//solution one: Dynamic programming:
//O(n^2) time complexity.
//O(n^2) space complexity.

string longestPalindrome(string s) {
    int n = s.size();
    
    //base case:
    if (n < 2) {
        return s;
    }

    //induction cases:
    //initializing maximum range of longest palindrome and start.
    int maxlens = 1;
    int begin = 0;

    //initializing dp[i][j] as the determination of whether s[i..j] is the longest palindrome.
    vector<vector<int>> dp(n, vector<int>(n));

    //initialization of dp: all palidrome are at length of 1.
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }

    //start of traversal:
    for (int L = 2; L <= n; L++) {
        for (int i = 0; i < n; i++) {
            int j = L + i - 1;

            //check if j has reached to the right boundary.
            if (j >= n) {
                break;
            }

            if (s[i] != s[j]) {
                dp[i][j] = false;
            }
            else
            {
                if (j - i < 3) {
                    dp[i][j] = true;
                }
                else {
                    dp[i][j] = dp[i + 1][j - 1];
                }
            }
            
            //if dp[i][L] is true, that means s[i..L] is a palidrome, we should record the length and the start of the palidrome.
            if (dp[i][j] && j - i + 1 > maxlens) {
                maxlens = j - i + 1;
                begin = i;
            }
        }
    }
    return s.substr(begin, maxlens);
}

//solution two: expand from middle:
//O(n^2) time complexity
//O(1) space complexity

string expand(int i, int j, string s) {
    int left = i;
    int right = j;

    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        left--;
        right++;
    }
    return s.substr(left + 1, right - left - 1);
}

string longestPalindromeExpandFromMiddle(string s) {
    string ans;

    for (int i = 0; i < s.size(); i++) {
        string odd = expand(i, i, s);
        if (odd.size() > ans.size()) {
            ans = odd;
        }
    }

    for (int i = 0; i < s.size() - 1; i++) {
        string even = expand(i, i + 1, s);
        if (even.size() > ans.size()) {
            ans = even;
        }
    }

    return ans;

}

