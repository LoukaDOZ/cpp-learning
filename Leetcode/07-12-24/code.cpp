class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int start = 1, end = *max_element(nums.begin(), nums.end());

        while(true) {
            int mid = start + (end - start) / 2;
            int nbOps = 0;
            bool ok = true;

            for(int num: nums) {
                nbOps += ceil((double) num / mid) - 1;

                if(nbOps > maxOperations) {
                    ok = false;
                    break;
                }
            }

            if(ok)
                end = mid;
            else
                start = mid + 1;
            
            if(start == end)
                break;
        }

        return start;
    }
};