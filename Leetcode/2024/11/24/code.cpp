class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix)
    {
        int minAbs = 100001;
        pair<int, int> minAbsIndex = {0, 0};

        // Move all negative number to the left (auto merging pairs)
        for(int i = 0; i < matrix.size(); i++)
        {
            vector<int>& row = matrix[i];

            for(int j = 0; j < row.size(); j++)
            {
                if(abs(row[j]) < minAbs)
                {
                    minAbs = abs(row[j]);
                    minAbsIndex = {i, j};
                }

                if(row[j] < 0)
                {
                    for(int k = j; k > 0; k--)
                    {
                        row[k - 1] *= -1;
                        row[k] *= -1;
                    }
                }
            }
        }
        
        // Move all negative number to the top (auto merging pairs)
        for(int i = 1; i < matrix.size(); i++)
        {
            if(matrix[i][0] < 0)
            {
                for(int j = i; j > 0; j--)
                {
                    matrix[j - 1][0] *= -1;
                    matrix[j][0] *= -1;
                }
            }
        }

        // If a negative number remains, transfer it to the smallest number
        if(matrix[0][0] < 0)
        {
            int x = 1;

            for(; x <= minAbsIndex.first; x++)
            {
                matrix[x - 1][0] *= -1;
                matrix[x][0] *= -1;
            }

            x--;
            for(int y = 1; y <= minAbsIndex.second; y++)
            {
                matrix[x][y - 1] *= -1;
                matrix[x][y] *= -1;
            }
        }

        long long sum = 0;
        for(vector<int> row: matrix)
        {
            for(int cell: row)
                sum += cell;
        }

        return sum;
    }
};