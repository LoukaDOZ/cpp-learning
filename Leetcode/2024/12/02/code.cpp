class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord)
    {
        istringstream iss(sentence);
        string s;
        int index = 1;
        
        while (getline(iss, s, ' '))
        {
            if (s.find(searchWord) == 0)
            {
                return index;
            }

            index++;
        }
        
        return -1;
    }
};