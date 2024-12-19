class Solution {
public: 
    int maxChunksToSorted(vector<int>& arr) {
        int maxChunks = 0, expectedSum = 0, currentSum = 0;
        int n = arr.size();

        for(int i = 0; i < n; i++)
        {
            expectedSum += i;
            currentSum += arr[i];
            
            if(expectedSum == currentSum)
                maxChunks++;
        }

        return maxChunks;
    }
};