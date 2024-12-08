bool comparator(vector<int> a, vector<int> b) {
    return a[0] < b[0];
}

class Solution {
public:
    int findFirstStartAfter(vector<vector<int>>& events, int n, int endTime) {
        int start = 0, end = n - 1, mid, startTime;

        while(start != end) {
            mid = start + (end - start) / 2;
            startTime = events[mid][0]; 

            if(startTime > endTime)
                end = mid;
            else
                start = mid + 1;
        }

        return events[start][0] > endTime ? start : -1;
    }

    int maxTwoEvents(vector<vector<int>>& events) {
        int n = events.size();
        unordered_map<int,int> maximums;

        sort(events.begin(), events.end(), comparator);

        int maxi = 0;
        maximums[-1] = 0;
        for(int i = n - 1; i >= 0; i--) {
            maxi = max(maxi, events[i][2]);
            maximums[i] = maxi;
        }

        int maxSum = 0;
        for(int i = 0; i < n; i++)
            maxSum = max(maxSum, events[i][2] + maximums[findFirstStartAfter(events, n, events[i][1])]);

        return maxSum;
    }
};