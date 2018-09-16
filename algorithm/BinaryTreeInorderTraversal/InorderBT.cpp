/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<pair<TreeNode*,bool>> s;
        s.push(pair<TreeNode*,bool>(root,false));
        while(!s.empty()) {
            pair<TreeNode*,bool> use = s.top();
            s.pop();
            if(use.first == NULL) continue;
            if(!use.second){
                s.push(pair<TreeNode*,bool>(use.first->right,false));
                s.push(pair<TreeNode*,bool>(use.first,true));
                s.push(pair<TreeNode*,bool>(use.first->left,false));
            }else ans.push_back(use.first->val);
            
        }
        return ans;
    }
    
};