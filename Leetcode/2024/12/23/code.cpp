/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int minimumOperations(TreeNode* root)
    {
        queue<TreeNode*> queue;
        int count = 0;

        if(root->left != nullptr)
            queue.push(root->left);

        if(root->right != nullptr)
            queue.push(root->right);

        while(!queue.empty())
        {
            int levelSize = queue.size();
            vector<int> values, sorted;
            unordered_map<int,int> positions;

            for(int i = 0; i < levelSize; i++)
            {
                TreeNode* n = queue.front();
                queue.pop();

                values.push_back(n->val);
                sorted.push_back(n->val);
                positions[n->val] = i;

                if(n->left != nullptr)
                    queue.push(n->left);

                if(n->right != nullptr)
                    queue.push(n->right);
            }

            sort(sorted.begin(), sorted.end());

            for(int i = 0; i < levelSize; i++)
            {
                if(values[i] == sorted[i])
                    continue;
                
                int vPos = positions[sorted[i]];
                positions[values[i]] = vPos;
                values[vPos] = values[i];
                values[i] = sorted[i];
                count++;
            }
        }

        return count;
    }
};