class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values)
    {
        int n = values.size();
        int best = 0;
        int maxScore = values[0];

        for(int i = 1; i < n; i++)
        {
            best = max(best, maxScore + values[i] - i);
            maxScore = max(maxScore, values[i] + i);
        }

        return best;
    }
};