class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        const char* source = s.c_str();
        char dest[s.length() + spaces.size() + 1];
        int lastPos = 0, spaceCount = 0;

        for(int space: spaces) {
            int size = space - lastPos;

            memcpy(&dest[lastPos + spaceCount], &source[lastPos], sizeof(char) * size);
            dest[space + spaceCount] = ' ';

            lastPos += size;
            spaceCount++;
        }

        memcpy(&dest[lastPos + spaceCount], &source[lastPos], sizeof(char) * (s.length() - lastPos));

        dest[s.length() + spaces.size()] = '\0';
        return string(dest);
    }
};