class Solution {
public:
    char nextC(char c) {
        if(c == 'z')
            return 'a';
        
        return c + 1;
    }

    bool canMakeSubsequence(string str1, string str2) {
        int m = str1.length();
        int n = str2.length();

        if(m < n)
            return false;

        int str2Pos = 0;

        for(int i = 0; i < m; i++) {
            if(str1[i] == str2[str2Pos] || nextC(str1[i]) == str2[str2Pos])
                str2Pos++;
        }

        return str2Pos == n;
    }
};