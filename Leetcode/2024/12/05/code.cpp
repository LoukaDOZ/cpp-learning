class Solution {
public:
    bool canChange(string start, string target)
    {
        int current = 0;
        int n = start.length();
        int m = target.length();

        for(; current < m; current++)
        {
            if(target[current] != '_')
                break;
        }

        for(int i = 0; i < n; i++)
        {
            char si = start[i];

            if(si == '_')
                continue;

            if(si != target[current] || (si == 'L' && i < current) || (si == 'R' && i > current))
                return false;

            for(current++; current < m; current++)
            {
                if(target[current] != '_')
                    break;
            }
        }

        return current == target.length();
    }
};