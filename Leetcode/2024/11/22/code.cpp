class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix)
    {
        map<string, int> rowCount;
        int best = 0;

        for(vector<int> row: matrix)
        {
            stringstream s;
            string key;

            if(row[0] == 0)
            {
                for(int col: row)
                    s << col;
            } else {
                for(int col: row)
                    s << ((col + 1) % 2);
            }

            key = s.str();
            if(rowCount.find(key) == rowCount.end())
                rowCount.insert({key, 1});
            else
                rowCount[key] += 1;
            
            if(rowCount[key] > best)
                best = rowCount[key];
        }

        return best;
    }
};