class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k) {
        priority_queue<int> queue(gifts.begin(), gifts.end());
        long long sum = 0;

        for(int i = 0; i < k; i++) {
            int e = queue.top();
            queue.pop();
            queue.push(floor(sqrt(e)));
        }

        while(!queue.empty()) {
            sum += queue.top();
            queue.pop();
        }

        return sum;
    }
};