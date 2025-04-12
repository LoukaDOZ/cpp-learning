class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit)
    {
        string repeatLimitedStr = "";
        map<char, int, greater<char>> m;
        int n = s.size();

        for(char c: s)
        {
            if(m.find(c) != m.end())
                m[c]++;
            else
                m[c] = 1;
        }

        auto current = m.begin();
        auto next = std::next(current);
        
        while(current->first != m.rbegin()->first)
        {
            int take = min(current->second, repeatLimit);
            current->second -= take;
            repeatLimitedStr += string(take, current->first);

            if(current->second == 0)
            {
                m.erase(current);
                current = m.begin();
                next = std::next(current);
                continue;
            }

            repeatLimitedStr += next->first;
            next->second--;

            if(next->second == 0)
            {
                m.erase(next);
                next = std::next(current);
            }
        }

        if(current->second > 0)
            repeatLimitedStr += string(min(current->second, repeatLimit), current->first);

        return repeatLimitedStr;
    }
};