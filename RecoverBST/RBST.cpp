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
    void recoverTree(TreeNode* root) {
        TreeNode* nul = NULL;
        stack<pair<TreeNode*,pair<TreeNode*,TreeNode*>>> s;
        s.push(make_pair(root,make_pair(nul,nul)));
        pair<TreeNode*,pair<TreeNode*,TreeNode*>> use;
        TreeNode *swap1 = NULL,*swap2 = NULL;
        while(!s.empty()){
            use = s.top();
            s.pop();
            if(use.second.first != NULL && use.second.first->val > use.first->val){
                if(swap1 == NULL) {
                swap1 = use.second.first;
                swap2 = use.first;
                } else {
                    swap1 = use.first;
                }
                continue;
            } 
            if(use.second.second != NULL && use.second.second->val < use.first->val){
                if(swap1 == NULL){
                    swap1 = use.second.second;
                    swap2 = use.first;
                } else {
                    swap1 = use.first;
                }
                continue;
            } 
            if(use.first->right != NULL) s.push(make_pair(use.first->right,make_pair(use.first,use.second.second)));
            if(use.first->left != NULL) s.push(make_pair(use.first->left,make_pair(use.second.first,use.first)));
        }
        swap(swap1->val,swap2->val);
    }
};