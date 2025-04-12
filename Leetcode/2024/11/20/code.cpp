#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCount(int* count)
    {
        return min(count[0], min(count[1], count[2]));
    }

    int cToI(char c)
    {
        return c - 97;
    }

    int takeCharacters(string s, int k)
    {
        int count[3] = {0, 0, 0};

        for(int i = 0; i < s.length(); i++)
            count[cToI(s.at(i))]++;

        if(minCount(count) < k)
            return -1;
        
        int res = s.length() + 1;
        int end = 0;

        for(int i = 0; i < s.length(); i++)
        {
            count[cToI(s.at(i))]--;

            while(minCount(count) < k)
            {
                count[cToI(s.at(end))]++;
                end++;
            }

            res = min(res, (int) (s.length() - (i - end + 1)));
        }

        return res;
    }
};