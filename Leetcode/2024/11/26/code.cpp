class Solution {
public:
    int findChampion(int n, vector<vector<int>>& edges) {
        bitset<100> successors;
        int winner = -1;

        for(vector<int> edge: edges)
            successors.set(edge[1]);
        
        for(int team = 0; team < n; team++) {
            if(!successors[team]) {
                if(winner != -1)
                    return -1;

                winner = team;
            }
        }

        return winner;
    }
};