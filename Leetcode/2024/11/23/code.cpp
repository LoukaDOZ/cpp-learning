class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box)
    {
        vector<vector<char>> rotatedBox(box[0].size(), vector<char>(box.size(), '.'));

        for(int row = 0; row < box.size(); row++)
        {
            int bottom = rotatedBox.size() - 1;
            int destRow = box.size() - 1 - row;

            for(int col = bottom; col >= 0; col--)
            {
                if(box[row][col] == '.')
                    continue;
                
                if(box[row][col] == '#')
                {
                    rotatedBox[bottom][destRow] = '#';
                    bottom--;
                } else {
                    rotatedBox[col][destRow] = '*';
                    bottom = col - 1;
                }
            }
        }

        return rotatedBox;
    }
};