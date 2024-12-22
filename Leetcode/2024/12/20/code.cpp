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
    TreeNode* reverseOddLevels(TreeNode* root) {
        if(root->left == nullptr)
            return root;

        queue<pair<TreeNode*, int>> left;
        queue<pair<TreeNode*, int>> right;
        left.push({root->left, 1});
        right.push({root->right, 1});

        while(!left.empty())
        {
            pair<TreeNode*, int> l = left.front();
            pair<TreeNode*, int> r = right.front();
            left.pop();
            right.pop();

            if(l.second % 2 != 0)
            {
                int tmp = r.first->val;
                r.first->val = l.first->val;
                l.first->val = tmp;
            }

            if(l.first->left != nullptr)
            {
                left.push({l.first->left, ++l.second});
                left.push({l.first->right, l.second});
                right.push({r.first->right, l.second});
                right.push({r.first->left, l.second});
            }
        }

        return root;
    }
};