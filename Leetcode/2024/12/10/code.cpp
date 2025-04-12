class Solution {
public:
    void add(map<string, int>& count, string k, int quantity = 1)
    {
        if(count.find(k) == count.end())
            count[k] = quantity;
        else
            count[k] += quantity;
    }

    void devide(map<string, int>& count, string str)
    {
        int n = str.size();

        for(int size = 1; size <= n; size++)
            add(count, str.substr(0, size), n - size + 1);
    }

    int maximumLength(string s)
    {
        map<string, int> count;
        string substr{s[0]};

        for(int i = 1, start = 0; i < s.size(); i++)
        {
            if(s[i] != substr[0])
            {
                devide(count, substr);
                substr.clear();
            }
            
            substr += s[i];
        }

        devide(count, substr);
        
        int res = -1;
        for(pair<string, int> c: count)
        {
            if(c.second >= 3)
                res = max(res, (int) c.first.size());
        }

        return res;
    }
};